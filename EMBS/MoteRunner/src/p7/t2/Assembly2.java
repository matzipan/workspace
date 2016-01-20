package p7.t2;

import com.ibm.saguaro.system.*;

public class Assembly2 {	
	private static Timer  sendTimer;
    private static byte[] xmit;
    private static long   transmitDelay;
    private static int counter = 0;
    static Radio radio = new Radio();

    static {
        // Open the default radio
        radio.open(Radio.DID, null, 0, 0);
        // Set the PAN ID to 0x22 and the short address to 0x31
        radio.setPanId(0x22, true);
        radio.setShortAddr(0x31);

        // Prepare beacon frame with source addressing
        xmit = new byte[7];
        xmit[0] = Radio.FCF_BEACON;
        xmit[1] = Radio.FCA_SRC_SADDR;
        Util.set16le(xmit, 3, 0x22);
        Util.set16le(xmit, 5, 0x31);

        // Put radio into receive mode for a long time on channel 1
        radio.setChannel((byte)1);
        
        // Setup a periodic timer callback for transmissions
        sendTimer = new Timer();
        sendTimer.setCallback(new TimerEvent(null){
                public void invoke(byte param, long time){
                    Assembly2.periodicSend(param, time);
                }
            });
        // Convert the periodic delay from ms to platform ticks
        transmitDelay = Time.toTickSpan(Time.MILLISECS, 2000);
        // Start the timer
        sendTimer.setAlarmBySpan(transmitDelay);
    }

    // Called on a timer alarm
    public static void periodicSend(byte param, long time) {
    	if (LED.getState((byte)0) == 1) {
    		LED.setState((byte)0, (byte)0);
        } else {
            LED.setState((byte)0, (byte)1);
        }
        
        Util.set16le(xmit, 7, counter);
           
        // send the message
        radio.transmit(Device.ASAP|Radio.TXMODE_CCA, xmit, 0, 7, 0);
        // Setup a new alarm
        sendTimer.setAlarmBySpan(transmitDelay);
        
        counter++;
    }
}
