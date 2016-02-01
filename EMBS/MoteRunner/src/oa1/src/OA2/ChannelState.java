package OA2;

import com.ibm.saguaro.system.Radio;
import com.ibm.saguaro.system.Time;
import com.ibm.saguaro.system.Timer;
import com.ibm.saguaro.system.TimerEvent;
import com.ibm.saguaro.system.Util;
import com.ibm.saguaro.system.Device;
import com.ibm.saguaro.system.LED;
/*import com.ibm.saguaro.system.csr;
import com.ibm.saguaro.logger.Logger;
import com.ibm.saguaro.system.Mote;*/

public class ChannelState {
    // the time value in miliseconds at second first time
    private long firstSample = 0;
    // the payload captured with the first sample
    private int firstSamplePayload = 0;
    // the time value in miliseconds at second sample time
    private long secondSample = 0;
    // the payload captured with the second sample
    private int secondSamplePayload = 0;

    // channel number
    public byte id = 0;
    // pan id
    public int pan = 0;
    // for ease of use, this is the index at which this instance exists in Source.channels
    public int index = 0;

    // determined value for n
    public int n = 0;

    // counter value for the number of iterations the message sending loop has gone through
    private int loopIncrement = 0;
    // the ticks vlaue at the time the loop has been started, useful in preventing timer drift
    private long loopBaseTicks = 0;

    // the tick value at which the n value transmission window starts. the channel needs to be setup before this value.
    public long getNTimeTicks = 0;

    // frame container
    private byte[] xmit;

    // reference to Radio device passed on from Source
    private Radio radioDev;

    // timers
    private Timer sendTimer = new Timer();
    private Timer getNTimer = new Timer();
    private Timer loopTimer = new Timer();

    // we use this value to offset timer alarm values so we can setup before the event needs to take place
    private static final long offsetCorrectionTicks = Time.toTickSpan(Time.MILLISECS, 50);

    public ChannelState(int index, int id, int pan, Radio radioDev) {
        this.index = index;
        this.id = (byte) id;
        this.pan = pan;
        this.radioDev = radioDev;

        xmit = new byte[12];
        xmit[0] = Radio.FCF_BEACON;
        xmit[1] = Radio.FCA_SRC_SADDR | Radio.FCA_DST_SADDR;
        Util.set16le(xmit, 3, pan); // dest panid
        Util.set16le(xmit, 5, pan); // broadcast address
        Util.set16le(xmit, 7, pan); // own PAN address
        Util.set16le(xmit, 9, 0x1); // own short address
        xmit[11] = (byte)(11+id);

        sendTimer.setCallback(new TimerEvent(this) {
            public void invoke(byte arg0, long time) {
                ((ChannelState)obj).send(arg0, time);
            }
        });

        loopTimer.setCallback(new TimerEvent(this) {
            public void invoke(byte arg0, long time) {
                ((ChannelState)obj).loop(arg0, time);
            }
        });

        getNTimer.setCallback(new TimerEvent(this) {
            public void invoke(byte arg0, long time) {
                ((ChannelState)obj).setGetN(arg0, time);
            }
        });
    }

    public long getChannelPeriod() {
        int sampleDifference = (int)(secondSample - firstSample);
        int payloadDifference = (int)(firstSamplePayload - secondSamplePayload);

        if(firstSamplePayload <= secondSamplePayload || (firstSamplePayload > secondSamplePayload &&  (sampleDifference/payloadDifference >= 1500))) {
            // assumption: we're sticking our head in the sand and hoping that we can't be delayed by more than one reception/sleep phase.
            return sampleDifference/(payloadDifference + 13);
        } else {
            return sampleDifference/payloadDifference;
        }
    }

    public boolean isPeriodInconclusive() {
        int sampleDifference = (int)(secondSample - firstSample);
        int payloadDifference = (int)(firstSamplePayload - secondSamplePayload);

        // if the both linear equations below are true, then we cannot be sure which one reflects reality (as per Nyquist theorem), so we need new samples
        return firstSamplePayload > secondSamplePayload &&
                sampleDifference/payloadDifference <= 1500 &&
                sampleDifference/(payloadDifference+13) >= 250
                // also, if the period is higher than the maximum admissible t (because we met more than one reception/sleep phase), then it's clearly wrong, need new samples
                || sampleDifference/(payloadDifference+13) >= 1500;
    }

    // store captured samples
    public int addChannelSampleTime(long currentTime, int payload) {
        if (firstSample == 0) {
            firstSample = currentTime;
            firstSamplePayload = payload;

            return 1;
        } else if (secondSample == 0) {
            secondSample = currentTime;
            secondSamplePayload = payload;

            return 2;
        }

        return -1;
    }

    public boolean  channelNeedsSamples() {
        return firstSample == 0 || secondSample == 0;
    }

    public void discardFirstAndRotate() {
        firstSample = secondSample;
        firstSamplePayload = secondSamplePayload;
        secondSample = 0;
        secondSamplePayload = 0;
    }

    public void scheduleSend(int payload) {
        /*Logger.appendString(csr.s2b("Scheduling send at "));
    	Logger.appendLong(Time.toTickSpan(Time.MILLISECS, payload*getChannelPeriod()));
        Logger.flush(Mote.WARN);*/

        // set timer for sending a message on this channel, plus an  offset so that we can be sure it lands inside the reception phase
        sendTimer.setAlarmBySpan(Time.toTickSpan(Time.MILLISECS, payload*getChannelPeriod())+offsetCorrectionTicks);
    }
    public void scheduleGetN(int payload) {
        getNTimeTicks = Time.currentTicks() + Time.toTickSpan(Time.MILLISECS, (payload+11)*getChannelPeriod());
    	
    	/*Logger.appendString(csr.s2b("Scheduling getN at "));
    	Logger.appendLong(getNTimeTicks);
        Logger.flush(Mote.WARN);*/

        // set timer for getting the value of n, minus an offset so that we can be sure we're listening to the channel when n will be sent by the sink
        getNTimer.setAlarmTime(getNTimeTicks-offsetCorrectionTicks);
    }

    public void loop(byte arg0, long time) {
        scheduleSend(n);
        setLoopTimer();
    }

    public void send(byte arg0, long time) {
    	/*Logger.appendString(csr.s2b("Sending message on channel "));
        Logger.appendInt(id);
        Logger.flush(Mote.WARN);*/

        LED.setState((byte)2, (byte)1);

        Source.sendChannelIndex = index;
        Source.setChannel();

        radioDev.transmit(Device.ASAP|Radio.TXMODE_CCA, xmit, 0, xmit.length, 0);

        LED.setState((byte)2, (byte)0);

        Source.sendChannelIndex = -1;
        Source.setChannel();
    }

    public void setGetN(byte arg0, long time) {
        Source.setGetNOnChannelIndex(index);
    }

    public void startLoop() {
    	/*Logger.appendString(csr.s2b("Starting loop for channel "));
        Logger.appendInt(id);
        Logger.flush(Mote.WARN);*/

        // this function is invoked onRecieve of the n value.
        // thus, we can use the time of the initial call of this function
        // as an un-skewed base (synced with the Sink) for further invocations of loop.
        // if we set subsequent loop alarms relative to the previous invocation we might end
        // up with having an ever-increasing drift/skew/offset in our invocations
        loopBaseTicks = Time.currentTicks();

        // initialize the counter
        loopIncrement = 1;

        //  messages 2,3,4.... will have a period of n+11 starting at n
        loopTimer.setAlarmTime(loopBaseTicks+Time.toTickSpan(Time.MILLISECS, n*getChannelPeriod()));

        // schedule sending the first message outside of the loop. we are sending this separately,
        // because it doesn't have the same period as the rest.
        scheduleSend(n);

        setLoopTimer();
    }

    private void setLoopTimer() {
        // periodic sender
        loopTimer.setAlarmTime(loopBaseTicks+Time.toTickSpan(Time.MILLISECS, loopIncrement*(n+11)*getChannelPeriod()));
        loopIncrement++;
    }

    public boolean hasMissedGetNWindow(long time) {
        // ideally, we're looking to compare if time == getNTime + getChannelPeriod()
        // but the documentation is not very clear about what values time might take
        // (and what offsets to expect), so we're taking the safe side and comparing
        // if it's more than half of a period away from getNTime. so the assumption
        // is that those offsets are smaller than half of a period.

        return getNTimeTicks + Time.toTickSpan(Time.MILLISECS, getChannelPeriod()/2) < time;
    }
}
