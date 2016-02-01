package OA2;

import com.ibm.saguaro.system.DevCallback;
import com.ibm.saguaro.system.Device;
import com.ibm.saguaro.system.LED;
import com.ibm.saguaro.system.Radio;
import com.ibm.saguaro.system.Time;

/*import com.ibm.saguaro.logger.Logger;
import com.ibm.saguaro.system.Mote;
import com.ibm.saguaro.system.csr;*/

public class Source {
	public static ChannelState[] channels;

	// priority levels for channels:
	//  * send channel: 3 (highest)
	//  * auxiliary channel: 2 (mid)
	//  * discovery channel: 1 (lowest)
	//
	// higher channels always preempt activity on the lowest.

	// discovery is used for channel discovery
	private static int discoveryChannelIndex = -1;
	// auxiliary is used for other things, like getting the value of n
	private static int auxiliaryChannelIndex = -1;
	// send channel is used for transmitting frames
	public static int sendChannelIndex = -1;

	// number of channels for which n has been fetched
	public static int gotNChannels = 0;

	private static boolean undiscoveredChannels = true;
	private static boolean rxOn = false;

	private static Radio radioDev = new Radio();

	// rx state definitions
	public static final int STATE_DISCOVER = 1;
	public static final int STATE_GETN = 2;

	public static int rxState = STATE_DISCOVER;

	static {
		channels = new ChannelState[3];

		channels[0] = new ChannelState(0, 0, 0x11, radioDev);
		channels[1] = new ChannelState(1, 1, 0x12, radioDev);
		channels[2] = new ChannelState(2, 2, 0x13, radioDev);

		radioDev.open(Radio.DID, null, 0, 0);
		radioDev.setShortAddr(Radio.SADDR_BROADCAST);

		discoveryChannelIndex = 0;
		setChannel(true);

		radioDev.setRxHandler(new DevCallback(null){
			public int invoke (int flags, byte[] data, int len, int info, long time) {
				return Source.onReceive(flags, data, len, info, time);
			}
		});

	}

	private static int onReceive (int flags, byte[] data, int len, int info, long time) {
		if (data == null) {
			radioDev.startRx(Device.ASAP|Device.RX4EVER, 0, 0);
			return 0;
		}

		if (LED.getState((byte)0) == 1) {
			LED.setState((byte)0, (byte)0);
		} else {
			LED.setState((byte)0, (byte)1);
		}

		int payload = data[11];

		long currentTime = Time.currentTime(Time.MILLISECS);

		ChannelState currentChannel = getCurrentChannel();

		/*Logger.appendString(csr.s2b("Recieving on channel "));
        Logger.appendInt(currentChannel.id);
        Logger.flush(Mote.WARN);*/


		switch(rxState) {
			case STATE_DISCOVER:
				if(undiscoveredChannels) {
					if (currentChannel.channelNeedsSamples()) {
			        	/*Logger.appendString(csr.s2b("Payload  "));
			            Logger.appendInt(payload);
			            Logger.flush(Mote.WARN);*/

						int sampleTimeId = currentChannel.addChannelSampleTime(currentTime, payload);

						if(sampleTimeId == 2) {
							if(currentChannel.isPeriodInconclusive()) {
                                	/*Logger.appendString(csr.s2b("Period is inconclusive  "));
        				            Logger.flush(Mote.WARN);*/

								currentChannel.discardFirstAndRotate();
							}
						}
					}

					// recheck if we have both samples after addChannelSampleTime (because we can discard some if the results are inconclusive)
					if (!currentChannel.channelNeedsSamples()) {
			        	/*Logger.appendString(csr.s2b("Discovered channel "));
			            Logger.appendInt(currentChannel.id);
			        	Logger.appendString(csr.s2b(" with payload "));
			            Logger.appendInt(payload);
			        	Logger.appendString(csr.s2b(" and period "));
			            Logger.appendLong(currentChannel.getChannelPeriod());
			            Logger.appendString(csr.s2b(". Scheduling send and get n"));
			            Logger.flush(Mote.WARN);*/

						currentChannel.scheduleSend(payload);
						currentChannel.scheduleGetN(payload);

						selectNextUndiscoveredChannel();
					}
				}
				break;
			case STATE_GETN:
				if(currentChannel.hasMissedGetNWindow(time)) {
					// because the auxiliary channel might get preempted by the send channel,
					// we might have missed the window to get the value of n. thus, we reschedule
					// using the current payload.

					/*Logger.appendString(csr.s2b("Missed get n window on channel "));
		            Logger.appendInt(currentChannel.id);
					Logger.appendString(csr.s2b(". Handled at "));
		            Logger.appendLong(time);
					Logger.appendString(csr.s2b(" with payload "));
					Logger.appendInt(payload);
		            Logger.flush(Mote.WARN);*/

					currentChannel.scheduleGetN(payload);
				} else {
					/*Logger.appendString(csr.s2b("Got n on channel "));
		            Logger.appendInt(currentChannel.id);
		            Logger.appendString(csr.s2b(" with payload "));
					Logger.appendInt(payload);
		            Logger.flush(Mote.WARN);*/

					currentChannel.n = payload;

					// start the message sending loop
					currentChannel.startLoop();

					gotNChannels++;
				}

				auxiliaryChannelIndex = -1;
				setChannel();

				rxState = STATE_DISCOVER;

				break;
		}



		return 0;
	}

	// this function is what decides the priority levels of the given channels
	private static int getCurrentChannelIndex() {
		return sendChannelIndex != -1 ? sendChannelIndex : auxiliaryChannelIndex != -1 ? auxiliaryChannelIndex : discoveryChannelIndex;
	}

	private static ChannelState getChannel(int channelIndex) {
		return channels[channelIndex];
	}


	private static ChannelState getCurrentChannel() {
		return getChannel(getCurrentChannelIndex());
	}

	// this function is referenced from the ChannelState class as a callback for preparing to get the value of n
	public static void setGetNOnChannelIndex(int auxiliaryChannelIndex) {
		/*Logger.appendString(csr.s2b("Entering state getN on "));
		Logger.appendInt(auxiliaryChannelIndex);
        Logger.flush(Mote.WARN);*/

		Source.auxiliaryChannelIndex = auxiliaryChannelIndex;
		rxState = Source.STATE_GETN;
		setChannel();
	}

	public static void setChannel() {
		setChannel(false);
	}

	private static void setChannel(boolean initial) {
		if(!initial || rxOn) {
			radioDev.stopRx();
			rxOn = false;
		}

		// no need for concurrency controls because mote runner isn't preemptive
		radioDev.setChannel(getCurrentChannel().id);
		radioDev.setPanId(getCurrentChannel().pan, false);

		if(sendChannelIndex == -1 && gotNChannels < channels.length) {
			radioDev.startRx(Device.ASAP|Device.RX4EVER, 0, 0);
			rxOn = true;
		}
	}

	private static void selectNextUndiscoveredChannel() {
		int nextChannel = discoveryChannelIndex + 1;

		if (nextChannel == channels.length) {
			undiscoveredChannels = false;
		} else {
            /*Logger.appendString(csr.s2b("Selected next undiscovered channel, index"));
            Logger.appendInt(nextChannel);
            Logger.flush(Mote.WARN);*/

			discoveryChannelIndex = nextChannel;

			setChannel();
		}
	}
}
