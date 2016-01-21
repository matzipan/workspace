package P11;

import java.util.LinkedList;
import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.actor.util.Time;
import ptolemy.data.DoubleToken;
import ptolemy.data.IntToken;
import ptolemy.data.RecordToken;
import ptolemy.data.Token;
import ptolemy.data.type.BaseType;
import ptolemy.data.type.RecordType;
import ptolemy.data.type.Type;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;
@SuppressWarnings("serial")


public class FIFOProcessor extends Processor{


	protected LinkedList<RecordToken> fifo;
	protected TypedIOPort queue;


	public FIFOProcessor(CompositeEntity container, String name)
	throws NameDuplicationException, IllegalActionException  {

		super(container, name);
		
		queue = new TypedIOPort(this, "queue", false, true);
		queue.setTypeEquals(BaseType.INT);

	}

	public void initialize() throws IllegalActionException{	
		super.initialize();
		fifo=new LinkedList<RecordToken>();
	}

	public void fire() throws IllegalActionException{

		Time currentTime = getDirector().getModelTime();

		if(currentTime.compareTo(readyTime)>=0){
			util=0;

		}

		if(fifo.size()>0){
			if(util<100){
				processTask(fifo.removeFirst(),currentTime);				
			}
			
		}
		
		if(input.hasToken(0)){

			Token t = input.get(0);
			if(t instanceof RecordToken){ 
				if(util<100){
					processTask((RecordToken)t,currentTime);				
				}

				else{fifo.add((RecordToken)t);}
			}	
		}

		utilisation.send(0, new DoubleToken(util));
		queue.send(0,new IntToken(fifo.size()));
	}




	public void pruneDependencies() {
		super.pruneDependencies();
		removeDependency(input, utilisation);
	}

}
