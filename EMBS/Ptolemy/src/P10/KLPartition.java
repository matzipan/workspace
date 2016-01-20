package P10;

import java.util.Hashtable;
import java.util.List;

/**
 * Created by Andrei on 14/01/2016.
 */
public class KLPartition {
    KLWeights weights;
    List<Character> orderedSet;
    int levels;

    public KLPartition(KLWeights weights,  List<Character> orderedSet, int levels) {
        this.weights = weights;
        this.orderedSet = orderedSet;
        this.levels = levels;
    }

    public void optimize() {
        int setSize = orderedSet.size();
        optimizePartitions(orderedSet.subList(0,setSize/2), orderedSet.subList(setSize/2,setSize), levels-1);
    }

    public void optimizePartitions(List<Character> a, List<Character> b, int levels) {
        if(levels == -1) {
            return;
        } else {
            double sumDeltaTMax;

            // after the first switch, the set items become locked and this hashtable is used to signal that
            Hashtable locked = new Hashtable<Character, Boolean>();

            do {
                // the deltaT values which cause a switch get recorded here
                double[] deltaTs = new double[a.size()];

                // the original indices of the items which got switched are recorded here
                int[] originalIndexForA = new int[a.size()];
                int[] originalIndexForB = new int[a.size()];

                for (int i = 0; i < a.size(); i++) {
                    double deltaT;

                    Hashtable<Character, Integer> difference = new Hashtable<>();

                    difference.putAll(calculateDifference(a, b));
                    difference.putAll(calculateDifference(b, a));

                    // to switch, deltaT = Da + Db - 2 ca,b needs to be maximal
                    deltaT = Double.NEGATIVE_INFINITY;
                    Character deltaTA = new Character('0');
                    Character deltaTB = new Character('0');

                    // these nested loops find the "best" (local optimum) switches to be made
                    for (Character c : a) {
                        for (Character d : b) {
                            if (!locked.containsKey(c) && !locked.containsKey(d)) {
                                double tempDeltaT =
                                        difference.get(c) + difference.get(d) - 2 * (weights.getWeight(c,d) + weights.getWeight(d,c));

                                if (tempDeltaT > deltaT) {
                                    deltaT = tempDeltaT;

                                    deltaTA = c;
                                    deltaTB = d;
                                }
                            }
                        }
                    }

                    // perform switch
                    if(deltaTA!='0' && deltaTB!='0') {
                        // keep track of where the switch has happened
                        deltaTs[i] = deltaT;
                        originalIndexForA[i] = a.indexOf(deltaTA);
                        originalIndexForB[i] = b.indexOf(deltaTB);

                        // switch
                        a.set(a.indexOf(deltaTA), deltaTB);
                        b.set(b.indexOf(deltaTB), deltaTA);

                        // mark the items as locked
                        locked.put(deltaTA, new Boolean(true));
                        locked.put(deltaTB, new Boolean(true));
                    }
                }


                sumDeltaTMax = 0;
                double tempSumDeltaT = 0;
                int maxIndex = -1;

                // find the greatest partial sum starting from the first switch, again, local optimum
                for (int i = 0; i < a.size(); i++) {
                    tempSumDeltaT = tempSumDeltaT + deltaTs[i];

                    if (tempSumDeltaT > sumDeltaTMax) {
                        sumDeltaTMax = tempSumDeltaT;
                        maxIndex = i;
                    }
                }

                // revert the switches which cause the sum to decrease
                for (int i = maxIndex + 1; i < a.size(); i++) {
                    Character x = a.get(originalIndexForA[i]);
                    a.set(originalIndexForA[i], b.get(originalIndexForB[i]));
                    b.set(originalIndexForB[i], x);
                }
            } while(sumDeltaTMax > 0);

            System.out.println(a + " " + b);

            int setSize = a.size();
            optimizePartitions(a.subList(0, setSize / 2), a.subList(setSize / 2, setSize), levels - 1);
            optimizePartitions(b.subList(0, setSize / 2), b.subList(setSize / 2, setSize), levels - 1);
        }
    }

    public Hashtable<Character, Integer> calculateDifference(List<Character> a, List<Character> b) {
        Hashtable<Character, Integer> difference = new Hashtable<>();

        // for each node, calculate internal/external cost  and then store difference E - I for both outward and inward edges
        for(Character c : a) {
            int D = 0;
            for(int i=0; i<orderedSet.size(); i++) {
                char iChar = KLWeights.intToChar(i);
                if(a.contains(iChar)) { // internal
                    D -= weights.getWeight(c, iChar);
                    D -= weights.getWeight(iChar, c);
                } else if(b.contains(KLWeights.intToChar(i))) { // external
                    D += weights.getWeight(c,iChar);
                    D += weights.getWeight(iChar, c);
                }
            }
            difference.put(c, D);
        }

        return difference;
    }

    public List<Character> getOrderedSet() {
        return orderedSet;
    }
}