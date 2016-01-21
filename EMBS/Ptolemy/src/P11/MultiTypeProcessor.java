package P11;

import java.util.ArrayList;
import java.util.Iterator;

import ptolemy.actor.TypedIOPort;
import ptolemy.actor.util.Time;
import ptolemy.data.DoubleToken;
import ptolemy.data.IntToken;
import ptolemy.data.RecordToken;
import ptolemy.data.Token;
import ptolemy.data.expr.Parameter;
import ptolemy.data.type.BaseType;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

public class MultiTypeProcessor extends FIFOProcessor {

	protected TypedIOPort done;
	protected Parameter type;
	protected RecordToken current;
	protected boolean isDone = false;
	
	public MultiTypeProcessor(CompositeEntity container, String name)
			throws NameDuplicationException, IllegalActionException {
		super(container, name);
		
		done = new TypedIOPort(this, "done", false, true);
		type = new Parameter(this, "processor type (0 - CPU, 1 - DSP, 2 - HW)");
		type.setExpression("0");
	}
	
	
	
	public void fire() throws IllegalActionException{

		Time currentTime = getDirector().getModelTime();

		if(currentTime.compareTo(readyTime)>=0 & util!=0){
			util=0;
			sendOut(currentTime.getDoubleValue());

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

	
	
	
	protected void processTask(RecordToken rt, Time time) throws IllegalActionException{
		
		double comptime=-1;
		
		if(type.getExpression().equals("0")){ comptime= ((DoubleToken)rt.get("comptimeCPU")).doubleValue();}
		else if(type.getExpression().equals("1")){ comptime= ((DoubleToken)rt.get("comptimeDSP")).doubleValue();}
		else if(type.getExpression().equals("2")){ comptime= ((DoubleToken)rt.get("comptimeHW")).doubleValue();}

		if(comptime<0) throw new IllegalActionException("Task can not run on this processor.");
		
		readyTime = time.add(comptime);
		current=rt;
		getDirector().fireAt(this, readyTime);
		util=100;

		
	}

	protected void sendOut(double finishtime) throws IllegalActionException{
		
		String[] labels = {"finishtime", "responsetime"};
		
		double responsetime = finishtime -((DoubleToken)current.get("releasetime")).doubleValue();
		Token[] tokens = {new DoubleToken(finishtime), new DoubleToken(responsetime)};
		
		RecordToken addon = new RecordToken(labels,tokens); 
		
		done.send(0,RecordToken.merge(current, addon));
		
	}
	
	
	public void pruneDependencies() {
		super.pruneDependencies();
		removeDependency(input, done);
	}
	

}
