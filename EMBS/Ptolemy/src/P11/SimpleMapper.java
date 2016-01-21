package P11;

import java.util.StringTokenizer;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.data.IntToken;
import ptolemy.data.RecordToken;
import ptolemy.data.Token;
import ptolemy.data.expr.StringParameter;
import ptolemy.data.type.BaseType;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

public class SimpleMapper extends TypedAtomicActor {

	protected TypedIOPort input; // receives tasks
	protected TypedIOPort output; // dispatches tasks

	protected int[] mapping;


	public SimpleMapper(CompositeEntity container, String name)
	throws NameDuplicationException, IllegalActionException  {

		super(container, name);

		input = new TypedIOPort(this, "input", true, false);
		input.setTypeEquals(BaseType.GENERAL);
		input.setMultiport(true);

		output = new TypedIOPort(this, "output", false, true);
		output.setMultiport(true);
		output.setTypeEquals(BaseType.GENERAL);


		mappingGuide = new StringParameter(this, "mapping");

	}



	public void initialize() throws IllegalActionException{

		StringTokenizer st = new StringTokenizer(mappingGuide.getExpression(), ",");
		mapping = new int[st.countTokens()];
		int i=0;
		while (st.hasMoreTokens()){

			mapping[i] = Integer.parseInt(st.nextToken());
			i++;
		}


	}

	public void fire() throws IllegalActionException{


		for(int i=0;i<input.getWidth();i++){
			//maps new tasks
			if(input.hasToken(i)){

				//reads task
				RecordToken task = (RecordToken)input.get(i);
				RecordToken comm = (RecordToken)task.get("communication");

				if(comm!=null){
					//substitutes the destination task number by the index of the core where the task was mapped
					int destinationTask = ((IntToken)comm.get("destination")).intValue();
					int destinationCore = mapping[destinationTask];

					String[] newlabels = {"destination","messagelength"};
					Token[] newtokens = {new IntToken(destinationCore), comm.get("messagelength")};
					RecordToken newcomm = new RecordToken(newlabels,newtokens);

					String[] newtlabels =	{"communication"};
					Token[] newttokens ={newcomm};
					RecordToken newtask = new RecordToken(newtlabels,newttokens);

					task = RecordToken.merge(newtask, task);
				}
				//sends out the mapped task through the respective output
				output.send(mapping[i], task);

			}
		}
	}


	StringParameter mappingGuide;

}
