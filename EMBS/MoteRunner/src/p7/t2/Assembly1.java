package p7.t2;

import com.ibm.saguaro.system.*;
import com.ibm.saguaro.logger.*;

public class Assembly1 {
	private static Timer recieveTimer;
	private static long recieveTurnOffDelay;
	private static long recieveTurnOnDelay;
	private static Radio radio = new Radio();
	private static int recievePhase = 0;
	

	static {
		// Open the default radio
		radio.open(Radio.DID, null, 0, 0);

		// Set the PAN ID to 0x22 and the short address to 0x31
		radio.setPanId(0x22, true);
		radio.setShortAddr(0x31);
		
		// Put radio into receive mode for a long time on channel 1
		radio.setChannel((byte)1);
		radio.setRxHandler(new DevCallback(null){
			public int invoke (int flags, byte[] data, int len, int info, long time) {
				return Assembly1.onReceive(flags, data, len, info, time);
			}
		});
		
		// Setup a periodic timer callback for transmissions
		recieveTimer = new Timer();
		recieveTimer.setCallback(new TimerEvent(null){
			public void invoke(byte param, long time){
				Assembly1.recieveToggler();
			}
		});
		
		// Convert the periodic delay from ms to platform ticks
		recieveTurnOffDelay = Time.toTickSpan(Time.MILLISECS, 5000);
		recieveTurnOnDelay = Time.toTickSpan(Time.MILLISECS, 10000);
		
		Assembly1.recieveToggler();
	}
	
	// On a received frame toggle LED
	private static int onReceive (int flags, byte[] data, int len, int info, long time) {
		if (data == null) { // marks end of reception period
			// re-enable reception for a very long time
			Logger.flush(Mote.INFO);
			radio.startRx(Device.RX4EVER, 0, 0);
			return 0;
		}
		
		Logger.appendByte(data[8]);
 
 		if (LED.getState((byte)0) == 1)
 			LED.setState((byte)0, (byte)0);
 		else
 			LED.setState((byte)0, (byte)1);
		
		return 0;
	}
		
	private static void recieveToggler() {
		if(recievePhase == 0) {
			recievePhase = 1; 
			
			recieveTimer.setAlarmBySpan(recieveTurnOffDelay);
		
	 		LED.setState((byte)1, (byte)1);
	
			radio.startRx(Device.RX4EVER, 0, 0);
		} else {
			recievePhase = 0;
			
			radio.stopRx();
		
			LED.setState((byte)1, (byte)0);
			
			recieveTimer.setAlarmBySpan(recieveTurnOnDelay);
		}
	}
}