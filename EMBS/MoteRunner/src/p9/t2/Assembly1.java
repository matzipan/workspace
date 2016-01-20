
package p9.t2;

import com.ibm.saguaro.system.*;
import com.ibm.iris.IRIS;
import com.ibm.saguaro.logger.*;

public class Assembly1 {	
	private static GPIO gpioDev = new GPIO();
	private static ADC adcDev = new ADC();
    private static Radio radioDev = new Radio();
    private static byte[] xmit;
    
	static {
		// Open the processor's GPIO handler
		gpioDev.open();
	
		// enable the GPIO pin that powers the light sensor (pin INT 5)
		// (i.e. sets the output value to be 1)
		gpioDev.configureOutput(IRIS.PIN_PW0,GPIO.OUT_SET);
	
		// Open the required channels for the ADC
		adcDev.open(0x02 /*MDA100 channel mask, from the data sheet */,
					GPIO.NO_PIN/*use manual power */,
					0/*no warmup*/,
					0/*no interval, sample as fast as possible*/
				);
	 				//sets up a callback for the ADC
	 	adcDev.setReadHandler(new DevCallback(null){
				public int invoke (int flags, byte[] data, int len, int info, long time) {
		 			return adcReadCallback(flags, data, len, info, time);
		 		}
	 		}
	 	);
	 	
	 	// trigger a read over the ADC
	 	adcDev.read(Device.TIMED, 
	 				1 /*read open channels once*/,
	 				Time.currentTicks()+Time.toTickSpan(Time.SECONDS,1)
	 			);
	 	 	
	 	// Open the default radio
        radioDev.open(Radio.DID, null, 0, 0);
        // Set the PAN ID to 0x32 and the short address to 0x31
        radioDev.setPanId(0x32, true);
        radioDev.setShortAddr(0x31);

        // Prepare beacon frame with source addressing
        xmit = new byte[7];
        xmit[0] = Radio.FCF_BEACON;
        xmit[1] = Radio.FCA_SRC_SADDR;
        Util.set16le(xmit, 3, 0x32);
        Util.set16le(xmit, 5, 0x31);

        // Put radio into receive mode for a long time on channel 1
        radioDev.setChannel((byte)10);
	}
	
	private static int adcReadCallback (int flags, byte[] data, int len, int info, long time) {
		// data[0] and data[1] store the raw 10 bit sensor value sampled by the ADC
		Logger.appendString(csr.s2b("data: "));
		Logger.appendByte(data[0]);
		Logger.appendString(csr.s2b(" "));
		Logger.appendByte(data[1]);
		Logger.flush(Mote.INFO);
		
		// schedule a new ADC sampling in 1s
		adcDev.read(Device.TIMED,
					1 /*read open channels once*/,
					Time.currentTicks()+Time.toTickSpan(Time.SECONDS,1)
				);
		
		
		if (LED.getState((byte)0) == 1) {
    		LED.setState((byte)0, (byte)0);
        } else {
            LED.setState((byte)0, (byte)1);
        }
        
        int value = data[0] << 8;
        value &= data[1];
        
        Util.set16le(xmit, 7, value);
           
        // send the message
        radioDev.transmit(Device.ASAP|Radio.TXMODE_CCA, xmit, 0, 7, 0);
        		
		return 0;
	}
	
}