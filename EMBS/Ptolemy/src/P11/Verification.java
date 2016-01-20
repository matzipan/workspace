package lsi.edi;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.data.DoubleToken;
import ptolemy.data.IntToken;
import ptolemy.data.RecordToken;
import ptolemy.data.StringToken;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

public class Verification extends TypedAtomicActor {

	protected TypedIOPort input;
	protected TypedIOPort output;
	
	public Verification(CompositeEntity container, String name) throws NameDuplicationException, IllegalActionException  {

		super(container, name);
		
		input = new TypedIOPort(this, "input", true, false);
		input.setMultiport(true);
		output = new TypedIOPort(this, "output", false, true);
	}
	
	public void fire() throws IllegalActionException{
		
		for(int i=0;i<input.getWidth();i++){
			if(input.hasToken(i)){
				
				RecordToken packet = (RecordToken)input.get(i);
				double release = ((DoubleToken)packet.get("releasetime")).doubleValue();
				double commfinish = getDirector().getCurrentTime();
				double period = ((DoubleToken)packet.get("period")).doubleValue();
				
				double totalresponsetime = commfinish - release;
				String s="";
				
				if(totalresponsetime<=period){s=s+"SCHEDULABLE ";} else {s=s+"NOT SCHEDULABLE ";}
				s = s+ "resp time: "+totalresponsetime+" - period: "+period;
				StringToken st = new StringToken(s);
				output.send(0,st);
				
			}
			
		}
		
	}

}