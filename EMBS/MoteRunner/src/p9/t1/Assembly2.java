package p9.t1;

import com.ibm.saguaro.system.*;
import com.ibm.saguaro.logger.*;

public class Assembly2 {
	private static Radio radioDev = new Radio();
	
	static {
	
		// Open the default radio
        radioDev.open(Radio.DID, null, 0, 0);
        // Set the PAN ID to 0x32 and the short address to 0x31
        radioDev.setPanId(0x32, true);
        radioDev.setShortAddr(0x32);

        // Put radio into receive mode for a long time on channel 1
        radioDev.setChannel((byte)10);
        
        radioDev.setRxHandler(new DevCallback(null){
			public int invoke (int flags, byte[] data, int len, int info, long time) {
				return Assembly2.onReceive(flags, data, len, info, time);
			}
		});
		
		radioDev.startRx(Device.RX4EVER, 0, 0);
	}
	
	private static int onReceive (int flags, byte[] data, int len, int info, long time) {
		if (data == null) { // marks end of reception period
			// re-enable reception for a very long time
			Logger.flush(Mote.INFO);
			radioDev.startRx(Device.RX4EVER, 0, 0);
			return 0;
		}
		
		int value = data[7] << 8;
        value &= data[8];
		
		Logger.appendString(csr.s2b("data: "));
		Logger.appendByte(data[7]);
		Logger.appendString(csr.s2b(" "));
		Logger.appendByte(data[8]);
		Logger.flush(Mote.INFO);
		
		LED.setState((byte)0, (byte)0);
		LED.setState((byte)1, (byte)0);
		LED.setState((byte)2, (byte)0);
		
		if(value > 100) {
			LED.setState((byte)0, (byte)1);
		} else if(value > 50) {
			LED.setState((byte)1, (byte)1);
		} else {
			LED.setState((byte)2, (byte)1);
		}
		
		return 0;
	}
}
