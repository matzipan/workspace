package OA1;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.actor.util.Time;
import ptolemy.data.IntToken;
import ptolemy.data.type.BaseType;
import ptolemy.domains.wireless.kernel.WirelessIOPort;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

import java.util.*;

public class SourceProcessor extends TypedAtomicActor {
    // io
    protected TypedIOPort input;
    protected TypedIOPort output;
    // used to indicate the channel we're working on
    protected TypedIOPort channelSelect;

    // keep track of states for different channels
    protected ArrayList<ChannelState> channelStates = new ArrayList<>();

    // store state transitions of actor to decide what to do at currentTime when fire gets called
    protected HashMap<Time, StateTransition> stateTransitions = new HashMap<>();

    // rx state definitions
    public static final int RX_STATE_DISCOVER = 1;
    public static final int RX_STATE_GET_N = 2;

    // store state of rx phase
    protected int rxState = RX_STATE_DISCOVER;

    // variable used to decide when channel discovery needs to stop
    protected boolean undiscoveredChannels = true;

    // priority levels for channels:
    //  * auxiliary channel: 2 (highest)
    //  * discovery channel: 1 (lowest)
    //
    // higher channels always preempt activity on the lowest.

    // discovery is used for channel discovery
    protected int discoveryChannelIndex = -1;

    // send channel is used for transmitting frames
    protected int auxiliaryChannelIndex = -1;

    // in the ptolemy version we only need two channel priorities because we can keep them from clashing by using slightly
    // different values for fireAt (+0.0001) and the computation time does not count, whereas we don't have the same luxury
    // on mote runner

    public SourceProcessor(CompositeEntity container, String name) throws IllegalActionException, NameDuplicationException {
        super(container, name);

        input = new WirelessIOPort(this, "input", true, false);
        output = new WirelessIOPort(this, "output", false, true);
        channelSelect = new WirelessIOPort(this, "channelSelect", false, true);

        input.setTypeEquals(BaseType.INT);
        output.setTypeEquals(BaseType.INT);
        channelSelect.setTypeEquals(BaseType.INT);
    }


    public void initialize() throws IllegalActionException {
        super.initialize();

        // initialization of channels
        for (int channelId : Arrays.asList(11, 12, 13, 14, 15)) {
            ChannelState channelState = new ChannelState();
            channelState.channelId = channelId;

            channelStates.add(channelState);
        }

        discoveryChannelIndex = 0;
        setChannel();
    }

    public void fire() throws IllegalActionException {
        Time currentTime = getDirector().getModelTime();
        int currentChannelIndex = getCurrentChannelIndex();
        ChannelState currentChannel = getChannel(currentChannelIndex);

        // state machine for handling rx frames
        if(input.hasToken(0)) {
            // woken up by token on channel
            int payload = ((IntToken) input.get(0)).intValue();

            switch (rxState) {
                case RX_STATE_DISCOVER:
                    if (undiscoveredChannels) {
                        printLog("Recieved "+ Integer.toString(payload) + " on " + getCurrentChannel().channelId);

                        if (currentChannel.channelNeedsSamples()) {
                            int sampleTimeId = currentChannel.addChannelSampleTime(currentTime, payload);

                            if(sampleTimeId == 2) {
                                if(currentChannel.firstSamplePayload == 1 && currentChannel.secondSamplePayload == 1 && currentChannel.getRealChannelPeriod() > 1.5) {
                                    // period between samples is more than the maximum period
                                    // it means that n=1 so the period between signals is 12*t
                                    currentChannel.n = 1;
                                } else if(currentChannel.isPeriodInconclusive()) {
                                    currentChannel.discardFirstAndRotate();
                                }
                            }
                        }

                        // recheck if we have both samples after addChannelSampleTime
                        if (!currentChannel.channelNeedsSamples()) {
                            printLog("Channel " + currentChannel.channelId + " with current payload " + Integer.toString(payload) + " has period " + Double.toString(currentChannel.getChannelPeriod()));

                            scheduleMessageSend(getCurrentChannelIndex(), payload * currentChannel.getChannelPeriod());

                            //set the channel and source state to recieve the n value before the message is emitted (-0.001 seconds before)
                            scheduleEventAtOffset(getCurrentChannelIndex(), StateTransition.STATE_PUSH_AND_GET_N, (payload + 11) * currentChannel.getChannelPeriod(),  -0.0001);

                            selectNextUndiscoveredChannel();
                        }
                    }

                    break;
                case RX_STATE_GET_N:
                    if(currentChannel.hasMissedGetNWindow(currentTime)) {
                        // because of interference from message sending or free slot delaying, we might have been looking at another channel
                        // when the n value was emmitted.

                        printLog("Missed get n window for "+ currentChannel.channelId + ". Rescheduling...");

                        scheduleEventAtOffset(getCurrentChannelIndex(), StateTransition.STATE_PUSH_AND_GET_N, (payload + 11) * currentChannel.getChannelPeriod(), -0.0001);
                    } else {
                        printLog("Getting n for "+ currentChannel.channelId);

                        // capture n
                        currentChannel.n = payload;

                        // STATE_PUSH_AND_GET is scheduled at -0.001 but that doesn't matter, because this code runs when
                        // fire is called by token at 0.0, so the loop schedule doesn't have any offset. YAY.
                        // we have n, so we can schedule loop starting now
                        scheduleEventAtOffset(getCurrentChannelIndex(), StateTransition.STATE_LOOP, 0, 0, false);
                    }

                    unsetAuxiliaryChannel();

                    rxState = RX_STATE_DISCOVER;
                    break;
            }
        }


        // state transitions and frame sending
        if (stateTransitions.containsKey(currentTime)) {
            // if there is state information about current timing
            printLog("Handling event");
            StateTransition nextState = stateTransitions.get(currentTime);
            ChannelState nextChannel = getChannel(nextState.channelIndex);

            switch(nextState.stateId) {
                case StateTransition.STATE_LOOP:
                    printLog("Loop on channel "+ nextChannel.channelId);

                    scheduleMessageSend(nextState.channelIndex, nextChannel.n * nextChannel.getChannelPeriod());

                    // loop again
                    scheduleEventAtOffset(nextState.channelIndex, StateTransition.STATE_LOOP, (nextChannel.n+11) * nextChannel.getChannelPeriod(), 0);

                    break;
                case StateTransition.STATE_SEND:
                    printLog("Sending token on channel "+ nextChannel.channelId);

                    output.send(0, new IntToken(10));
                    break;
                case StateTransition.STATE_UNSET:
                    printLog("Unsetting auxiliary channel");

                    unsetAuxiliaryChannel();
                    break;
                case StateTransition.STATE_SET:
                    printLog("Setting auxiliary channel " + Integer.toString(nextChannel.channelId));

                    auxiliaryChannelIndex = nextState.channelIndex;

                    setChannel();
                    break;
                case StateTransition.STATE_PUSH_AND_GET_N:
                    printLog("Waiting for n value on channel "+ Integer.toString(nextChannel.channelId));

                    auxiliaryChannelIndex = nextState.channelIndex;

                    setChannel();

                    rxState =  RX_STATE_GET_N;
                    break;
            }
        }
    }

    private void setChannel() throws  IllegalActionException {
        // it doesn't matter if it lands between a STATE_SET and a STATE_SEND because aux whill have a different priority level
        channelSelect.send(0, new IntToken(getCurrentChannel().channelId));
    }

    private void unsetAuxiliaryChannel() throws IllegalActionException {
        auxiliaryChannelIndex = -1;

        setChannel();
    }

    private void selectNextUndiscoveredChannel() throws IllegalActionException {
        int nextChannel = discoveryChannelIndex + 1;

        if (nextChannel == channelStates.size()) {
            printLog("No more undiscovered channels after this point");
            undiscoveredChannels = false;
        } else {
            printLog("Next discovery channel is "+ nextChannel);
            discoveryChannelIndex = nextChannel;

            setChannel();
        }
    }

    private ChannelState getChannel(int channelIndex) {
        return channelStates.get(channelIndex);
    }

    private ChannelState getCurrentChannel() {
        return getChannel(getCurrentChannelIndex());
    }

    private void scheduleMessageSend(int channel, double eventTime) throws IllegalActionException {
        // schedule sending message in reception period
        double freeTime = findNextFreeTimeAtOffset(eventTime);

        // we have to schedule these as events at different times because the DEDirector needs time to propagate the
        // channel selection so that the rx values go where they need to.
        scheduleEventAtOffset(channel, StateTransition.STATE_SET, freeTime, 0);
        scheduleEventAtOffset(channel, StateTransition.STATE_SEND, freeTime, 0.0001);
        scheduleEventAtOffset(channel, StateTransition.STATE_UNSET, freeTime,  0.0002);
    }

    // this function finds a free time slot to run a series of events without being afraid of concurrency issues
    private double findNextFreeTimeAtOffset(double eventOffset) {
        Time eventTime = getDirector().getModelTime().add(eventOffset);

        while(stateTransitions.containsKey(eventTime)) {
            eventOffset += 0.001;
            eventTime = getDirector().getModelTime().add(eventOffset);
        }

        return eventOffset;
    }

    private void scheduleEventAtOffset(int channelIndex, int stateId, double timeOffset, double correction) throws IllegalActionException {
        scheduleEventAtOffset(channelIndex,stateId,timeOffset, correction, true);
    }

    private void scheduleEventAtOffset(int channelIndex, int stateId, double timeOffset, double correction, boolean fireAt) throws IllegalActionException {
        // the correction must be a value between 0.0001 and 0.0009 or 0 to avoid overlapping with the free slots found by findNextFreeTimeAtOffset
        if(correction != 0 && (Math.abs(correction) < 0.0001 || Math.abs(correction) > 0.0009)) {
            throw new IllegalActionException("The correction parameter must be a value between 0.0001 and 0.0009 or 0, "+ Double.toString(correction) + "given");
        }

        if(stateId == StateTransition.STATE_PUSH_AND_GET_N) {
            getChannel(channelIndex).setGetNTime(getDirector().getModelTime().add(timeOffset));
        }

        StateTransition newState = new StateTransition();
        newState.channelIndex = channelIndex;
        newState.stateId = stateId;

        Time newTime = getDirector().getModelTime().add(timeOffset + correction);

        stateTransitions.put(newTime,newState);

        if(fireAt == true) {
            getDirector().fireAt(this, newTime);
        }

        printLog("Scheduled event type "+ Integer.toString(stateId) +" at "+ newTime.toString());
    }

    // this function is what decides the priority levels of the given channels
    private int getCurrentChannelIndex() {
        return auxiliaryChannelIndex != -1 ? auxiliaryChannelIndex : discoveryChannelIndex;
    }

    private void printLog(String log) {
        System.out.println(getDirector().getModelTime() + ": " + log);
    }

}
