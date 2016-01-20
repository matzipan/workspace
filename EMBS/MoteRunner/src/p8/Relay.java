package p8;

import com.ibm.saguaro.system.*;

public class Relay {
	private final static byte INIT_PACKET = 0x1;
	private final static byte ACK_PACKET = 0x2;
	private final static byte SEND_PACKET = 0x3;
	private final static byte FINAL_PACKET = 0x4;
    private static Radio radioDev = new Radio();
    private static byte[] xmit;
    private static int messageSequenceCounter = 0;

	static {
	 	// Open the default radio
        radioDev.open(Radio.DID, null, 0, 0);
        // Set the PAN ID to 0x32 and the short address to 0x31
        radioDev.setPanId(0x32, true);
        radioDev.setShortAddr(0x31);

        // Prepare beacon frame with source addressing
        xmit = new byte[10];
        xmit[0] = Radio.FCF_BEACON;
        xmit[1] = Radio.FCA_SRC_SADDR;
        Util.set16le(xmit, 3, 0x32);
        Util.set16le(xmit, 5, 0x31);

        radioDev.setChannel((byte)10);
        
        radioDev.setRxHandler(new DevCallback(null){
        	public int invoke (int flags, byte[] data, int len, int info, long time) {
				return Relay.onReceive(flags, data, len, info, time);
			}
		});
        
        radioDev.startRx(Device.RX4EVER, 0, 0);
	}
	
	private static int onReceive(int flags, byte[] data, int len, int info, long time) {
		if (data == null) { // marks end of reception period
			// re-enable reception for a very long time
			radioDev.startRx(Device.RX4EVER, 0, 0);
			return 0;
		}
		
		if(data[8] == INIT_PACKET) {
			messageSequenceCounter = data[7] + 1;

	        radioDev.transmit(Device.ASAP|Radio.TXMODE_CCA, data, 0, len, 0);   
		} else if(data[7] == messageSequenceCounter+1) {
			messageSequenceCounter = data[7] + 1;

	        radioDev.transmit(Device.ASAP|Radio.TXMODE_CCA, data, 0, len, 0);   
		} 		
		
	
		return 0;
	}
}
