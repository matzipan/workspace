package lsi.edi;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.actor.util.Time;
import ptolemy.data.DoubleToken;
import ptolemy.data.RecordToken;
import ptolemy.data.Token;
import ptolemy.data.type.BaseType;
import ptolemy.data.type.RecordType;
import ptolemy.data.type.Type;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;
@SuppressWarnings("serial")


public class Processor extends TypedAtomicActor{

	
	protected TypedIOPort input;
	protected TypedIOPort utilisation;
	protected TypedIOPort discard;

	protected Time readyTime;

	double util;
	
	public Processor(CompositeEntity container, String name)
	throws NameDuplicationException, IllegalActionException  {

		super(container, name);

		input = new TypedIOPort(this, "input", true, false);
		
		utilisation = new TypedIOPort(this, "utilisation", false, true);
		utilisation.setTypeEquals(BaseType.DOUBLE);
		
		discard = new TypedIOPort(this, "discard", false, true);
		
	}
	

	public void initialize() throws IllegalActionException{
		
		util=0;
		
		readyTime = getDirector().getModelTime();
		utilisation.send(0, new DoubleToken(util));
		
		
	}
	
	
	public void fire() throws IllegalActionException{

        Time currentTime = getDirector().getModelTime();

		if(currentTime.compareTo(readyTime)>=0){
			util=0;

		}
		
		if(input.hasToken(0)){
			
			Token t = input.get(0);

			if(util<100 && t instanceof RecordToken){
				this.processTask((RecordToken)t, currentTime);
				
			}
			
			else{discard.send(0, t);}
			
		}
		
		utilisation.send(0, new DoubleToken(util));
	}
	

	protected void processTask(RecordToken rt, Time time) throws IllegalActionException{
		
		double comptime = ((DoubleToken)rt.get("comptime")).doubleValue();
		
        readyTime = time.add(comptime);
		getDirector().fireAt(this, readyTime);
		util=100;
		
	}
	
	public void pruneDependencies() {
		super.pruneDependencies();
		removeDependency(input, utilisation);
	}
	
}
