package lsi.edi;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.data.IntToken;
import ptolemy.data.Token;
import ptolemy.data.type.BaseType;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

@SuppressWarnings("serial")
public class Dispatcher extends TypedAtomicActor {
	
	
	protected TypedIOPort input; // receives tasks
	protected TypedIOPort queueUpdate; // receives updates on number of queued tasks
	protected TypedIOPort output; // dispatches tasks

	private int[] queues; // number of queued tasks
	int nqueues; // number of queues managed by this dispatcher
	
	
	
	public Dispatcher(CompositeEntity container, String name)
	throws NameDuplicationException, IllegalActionException  {

		super(container, name);

		input = new TypedIOPort(this, "input", true, false);
		input.setTypeEquals(BaseType.GENERAL);

		queueUpdate = new TypedIOPort(this, "update", true, false);
		queueUpdate.setMultiport(true);
		
		output = new TypedIOPort(this, "output", false, true);
		output.setMultiport(true);
		output.setTypeEquals(BaseType.GENERAL);
		
		
	}
	

	public void initialize() throws IllegalActionException{
		
		nqueues= queueUpdate.getWidth(); // initialises number of queues by checking how many channels link to queueUpdate port
		queues = new int[nqueues];
		for(int i=0;i<nqueues;i++){queues[i]=0;} 
		
		output.setTypeEquals(input.getType());
		
	}
	
	
	public void fire() throws IllegalActionException{

		//reads all queue updates
		for(int i=0;i<nqueues;i++){
			
			if(queueUpdate.hasToken(i)){
				
				IntToken queuedTasks = (IntToken) queueUpdate.get(i);
				queues[i]=queuedTasks.intValue();
			}
		}

		
		//sends new task, if any, to the queue with the shortest queue
		if(input.hasToken(0)){
			
			output.send(this.getShortestQueue(), input.get(0));
			
			
		}
		
	}

	/** Finds the shortest queue.
	 * 
	 * @return the index of the shortest queue
	 */
	private int getShortestQueue(){

		int shortest=0;
		
		for(int i=1;i<nqueues;i++){
			if(queues[i]<queues[shortest]){shortest=i;}
		}
		return shortest;
		
	}
	
	
	/** Override the base class to declare that the <i>output</i>
	 *  does not depend on the  <i>queueUpdate</i> port in a firing.
	 *  
	 *  If this is not present, DE director may throw an Exception because of a zero delay loop.
	 *  
	 */
	public void pruneDependencies() {
		super.pruneDependencies();
		removeDependency(queueUpdate, output);
	}
	
	

}
