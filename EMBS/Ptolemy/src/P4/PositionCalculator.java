package P4;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.data.DoubleToken;
import ptolemy.data.IntToken;
import ptolemy.data.RecordToken;
import ptolemy.data.type.BaseType;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

/**
 * Created by Andrei on 23/10/2015.
 */
public class PositionCalculator extends TypedAtomicActor {
    protected TypedIOPort signalStrength;
    protected TypedIOPort outputX;
    protected TypedIOPort outputY;
    protected TypedIOPort outputSquareX;
    protected TypedIOPort outputSquareY;
    protected double a = -1.0;
    protected double b = -0.0;
    protected double c = -0.0;

    public PositionCalculator(CompositeEntity container, String name) throws NameDuplicationException, IllegalActionException {
        super(container, name);

        signalStrength = new TypedIOPort(this, "signalStrength", true, false);

        outputX = new TypedIOPort(this, "x", false, true);
        outputX.setTypeEquals(BaseType.DOUBLE);
        outputY = new TypedIOPort(this, "y", false, true);
        outputY.setTypeEquals(BaseType.DOUBLE);

        outputSquareX = new TypedIOPort(this, "squareX", false, true);
        outputSquareX.setTypeEquals(BaseType.INT);
        outputSquareY = new TypedIOPort(this, "squareY", false, true);
        outputSquareY.setTypeEquals(BaseType.INT);

    }

    public void fire() throws IllegalActionException{
        RecordToken signalToken = (RecordToken) signalStrength.get(0);

        double distance = 0;
        int id = ((IntToken) signalToken.get("id")).intValue();
        double power = ((DoubleToken) signalToken.get("power")).doubleValue();

        distance = 1/(2*1.7724*Math.sqrt(power));

        if(id == 1) {
            a = distance;
        }

        if(id == 2) {
            b = distance;
        }

        if(id == 4) {
            c = distance;
        }

        double x = 0;
        double y = 0;

        if(a > 0 && b > 0 && c > 0) {
            double semiPerim = (a+b+800)/2;
            double area = Math.sqrt(semiPerim*(semiPerim-a)*(semiPerim-b)*(semiPerim-800));
            x = 2*area/800;

            semiPerim = (b+c+800)/2;
            area = Math.sqrt(semiPerim*(semiPerim-b)*(semiPerim-c)*(semiPerim-800));
            y = 2*area/800;
        }

        outputX.send(0, new DoubleToken(x));
        outputY.send(0, new DoubleToken(y));

        outputSquareX.send(0, new IntToken(((int)x/200)+1));
        outputSquareY.send(0, new IntToken(((int)y/200)+1));
    }
}
