package P11;

import ptolemy.actor.TypedIOPort;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

public class MultiTypeProcessorComms extends MultiTypeProcessor {

	protected TypedIOPort comms;
	
	public MultiTypeProcessorComms(CompositeEntity container, String name)
			throws NameDuplicationException, IllegalActionException {
		super(container, name);
		comms = new TypedIOPort(this, "comms", false, true);
		
	}

	protected void sendOut(double finishtime) throws IllegalActionException{
		
		super.sendOut(finishtime);
		//sends out communication
		if(current.get("communication")!=null){
			comms.send(0,current);
		}
		
		
	}
	
	
}
