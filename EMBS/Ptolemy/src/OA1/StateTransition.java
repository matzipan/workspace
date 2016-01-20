package OA1;


// utility data structure which keeps together all the information we need for tx state transitions
public class StateTransition {
    public int stateId = 0;

    public int channelIndex = 0;

    public static final int STATE_SEND = 1;
    public static final int STATE_SET = 2;
    public static final int STATE_PUSH_AND_GET_N = 3;
    public static final int STATE_UNSET = 4;
    public static final int STATE_LOOP = 5;
}
