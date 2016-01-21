package embs;

import ptolemy.actor.TypedAtomicActor;
import ptolemy.actor.TypedIOPort;
import ptolemy.actor.util.Time;
import ptolemy.data.DoubleToken;
import ptolemy.data.IntToken;
import ptolemy.data.RecordToken;
import ptolemy.data.type.BaseType;
import ptolemy.kernel.CompositeEntity;
import ptolemy.kernel.util.IllegalActionException;
import ptolemy.kernel.util.NameDuplicationException;

import java.util.LinkedList;

/**
 * Created by az579 on 16/10/2015.
 */
public class CPU extends TypedAtomicActor {

	protected LinkedList<RecordToken> queue;
	protected TypedIOPort taskInput;
	protected TypedIOPort taskOutput;
	protected TypedIOPort utilisationOutput;
	protected TypedIOPort queueOutput;

	protected double utilisation = 0.0;
	protected Time busyEndTime;

	public CPU(CompositeEntity entity, String name) throws IllegalActionException, NameDuplicationException {
		super(entity, name);

		taskInput = new TypedIOPort(this, "task", true, false);
		taskInput.setTypeEquals(BaseType.GENERAL);
		taskOutput = new TypedIOPort(this, "runningTask", false, true);
		taskOutput.setTypeEquals(BaseType.DOUBLE);
		utilisationOutput = new TypedIOPort(this, "utilisation", false, true);
		utilisationOutput.setTypeEquals(BaseType.DOUBLE);
		queueOutput = new TypedIOPort(this, "queue", false, true);
		queueOutput.setTypeEquals(BaseType.INT);
	}

	public void initialize() throws IllegalActionException{
		super.initialize();
		queue = new LinkedList<>();
		busyEndTime = getDirector().getModelTime();
	}

	public void fire() throws IllegalActionException{
		super.fire();

		if(taskInput.hasToken(0)) {
			queue.add((RecordToken) taskInput.get(0));
		}

		sendUtilisation();

		if(!queue.isEmpty() && busyEndTime.compareTo(getDirector().getModelTime()) <= 0) {
			processTask(queue.removeFirst());
		}

		queueOutput.send(0, new IntToken(queue.size()));
	}

	protected void processTask(RecordToken taskToken) throws IllegalActionException {
		DoubleToken comptimeToken = (DoubleToken) taskToken.get("comptime");
		taskOutput.send(0, comptimeToken);
		busyEndTime = getDirector().getModelTime().add(comptimeToken.doubleValue());
		getDirector().fireAt(this, busyEndTime);
	}

	protected void sendUtilisation() throws IllegalActionException {
		double utilisation = queue.size() > 0 ? 100.0 : 0.0;

		if(this.utilisation != utilisation) {
			utilisationOutput.send(0, new DoubleToken(this.utilisation));
			utilisationOutput.send(0, new DoubleToken(utilisation));
			this.utilisation = utilisation;
		} else {
			utilisationOutput.send(0, new DoubleToken(this.utilisation));
		}
	}

}