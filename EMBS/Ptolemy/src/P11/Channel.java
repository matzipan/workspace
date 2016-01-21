package P11;

import java.util.Random;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.data.Token;
import ptolemy.data.expr.Parameter;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

@SuppressWarnings("serial")
public class Channel extends TypedAtomicActor {
	
	protected TypedIOPort input;
	protected TypedIOPort output;
	protected Parameter discard;
	
	public Channel(CompositeEntity container, String name) throws NameDuplicationException, IllegalActionException  {

		super(container, name);
		
		input = new TypedIOPort(this, "input", true, false);
		output = new TypedIOPort(this, "output", false, true);

		
		discard = new Parameter(this,"discard percentage");
		discard.setExpression("20.0");
		
	}	

	public void fire() throws IllegalActionException{
		
		Token t = input.get(0);
		
		Random rnd = new Random();
		int r = rnd.nextInt(100);
		double d = Double.parseDouble(discard.getExpression());
		
		if(r>d){output.send(0, t);}
		
	}

}
