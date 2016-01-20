package lsi.edi;

import java.util.LinkedList;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.data.IntToken;
import ptolemy.data.RecordToken;
import ptolemy.data.expr.Parameter;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

public class Bus extends TypedAtomicActor{
	
	protected TypedIOPort input;
	protected TypedIOPort output;
	protected Parameter bandwidth;
	protected LinkedList<RecordToken> commrequests;
	protected LinkedList<IntToken> sources;
	protected boolean busy = false;
	protected double doneTime;
	
	public Bus(CompositeEntity container, String name)
	throws NameDuplicationException, IllegalActionException {
		super(container,name);
		input = new TypedIOPort(this, "input", true, false);
		input.setMultiport(true);
		
		output = new TypedIOPort(this, "output", false, true);
		output.setMultiport(true);
	
		bandwidth = new Parameter(this,"bandwidth");
		bandwidth.setExpression("1");
		
	}
	
	public void initialize(){
		
		commrequests = new LinkedList<RecordToken>();
		sources = new LinkedList<IntToken>();
		doneTime=0;
		busy=false;
	}
	
	public void fire() throws IllegalActionException{
		
		//checks whether ongoing communication is finished
		if(busy & getDirector().getCurrentTime()>=doneTime){
			
			output.send((sources.remove(0)).intValue(), commrequests.remove(0));
			busy=false;
			
		}
		
		//checks for new incoming communication requests

		for(int i=0;i<input.getWidth();i++){
			if(input.hasToken(i)){
				
				
				RecordToken packet = (RecordToken)input.get(i);
				RecordToken comm = (RecordToken)packet.get("communication");
				IntToken dest = (IntToken)comm.get("destination");

				//if source and destination is the same, send right away
				if(dest.intValue()==i){	output.send(i, packet); }
				//otherwise, add to queue
				else{

					queueRequest(i, packet);
				}
				
			}
		}
		
		//if bus is free, serve outstanding comm requests
		if(!busy & commrequests.size()>0){
			
			RecordToken packet = commrequests.get(0);
			RecordToken comm = (RecordToken)packet.get("communication");
			int msglength = ((IntToken)comm.get("messagelength")).intValue();
			double startTime=getDirector().getCurrentTime();
			double bw = Double.parseDouble(bandwidth.getExpression());
			double commTime = msglength/bw;
			doneTime = startTime+commTime;
			
			getDirector().fireAt(this, doneTime);
			busy=true;
			
		}
		

		

		
	}
	
	
	public void queueRequest(int source, RecordToken packet){
		
		commrequests.add(packet);
		sources.add(new IntToken(source));
		
		
		
	}

}
