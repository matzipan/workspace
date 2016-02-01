package P1;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.data.expr.Parameter;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

import java.util.Random;

/**
 * Created by Andrei on 21/10/2015.
 */
public class RandomizedDiscarder extends TypedAtomicActor {
    protected TypedIOPort input;
    protected TypedIOPort output;
    protected TypedIOPort discarder;
    protected Parameter param;
    public RandomizedDiscarder(CompositeEntity container, String name) throws NameDuplicationException, IllegalActionException {
        super(container, name);
        input = new TypedIOPort(this, "input", true, false);
        output = new TypedIOPort(this, "ouput", false, true);
        discarder = new TypedIOPort(this, "discarder", false, true);
        param = new Parameter(this, "Ratio");
        param.setExpression("20.0");
    }

    public void fire() throws IllegalActionException{
        Random random = new Random();

        if(100.0 * random.nextDouble() > Double.parseDouble(param.getValueAsString())) {
            output.send(0, input.get(0));
        } else {
            discarder.send(0, input.get(0));
        }
    }
}