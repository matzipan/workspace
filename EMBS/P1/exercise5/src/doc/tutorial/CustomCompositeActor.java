package doc.tutorial;

import ptolemy.actor.TypedCompositeActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.actor.lib.*;
import ptolemy.actor.lib.gui.TimedPlotter;
import ptolemy.actor.lib.logic.Comparator;
import ptolemy.actor.parameters.PortParameter;
import ptolemy.data.BooleanToken;
import ptolemy.data.DoubleToken;
import ptolemy.data.expr.Parameter;
import ptolemy.data.expr.SingletonParameter;
import ptolemy.data.type.BaseType;
import ptolemy.domains.de.kernel.DEDirector;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.Relation;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;
import ptolemy.kernel.util.Workspace;

public class CustomCompositeActor extends TypedCompositeActor {
    public PortParameter dropFrequency;



    public CustomCompositeActor(CompositeEntity container, String name) throws IllegalActionException,
            NameDuplicationException {
        super(container, name);

        this.dropFrequency = new PortParameter(this, "drop freq", new DoubleToken(5.0D));
        this.dropFrequency.setTypeEquals(BaseType.DOUBLE);
        (new SingletonParameter(this.dropFrequency.getPort(), "_showName")).setToken(BooleanToken.TRUE);

        TypedIOPort output = new TypedIOPort(this, "output");
        TypedIOPort input = new TypedIOPort(this, "input");

        this.inputPortList().add(output);
        this.inputPortList().add(input);

        Discard discard = new Discard(this, "discard");
        BooleanSwitch booleanSwitch = new BooleanSwitch(this, "switch");
        Comparator comparator = new Comparator(this, "comparator");
        Const constant = new Const(this, "constant");
        constant.value.setExpression("1.0");
        Uniform uniform = new Uniform(this, "uniform");
        uniform.upperBound.setExpression("5.0");

        Relation relation9 = new Relation("relation9");

        input.link(relation9);
        uniform.trigger.link(relation9);
        constant.trigger.link(relation9);
        booleanSwitch.input.link(relation9);

        connect(booleanSwitch.trueOutput, output);
        connect(discard.input, booleanSwitch.falseOutput);
        connect(booleanSwitch.control, comparator.output);
        connect(booleanSwitch.falseOutput, discard.input);
        connect(comparator.left, uniform.output);
        connect(comparator.right, constant.output);
    }
}