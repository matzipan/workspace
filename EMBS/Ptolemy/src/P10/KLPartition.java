package P10;

import com.sun.deploy.util.ArrayUtil;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Andrei on 14/01/2016.
 */
public class KLPartition {


    int[][] weights;
    List<Character> orderedSet;
    int levels;

    public KLPartition(int[][] weights,  List<Character> orderedSet, int levels) {
        this.weights = weights;
        this.orderedSet = orderedSet;
        this.levels = levels;
    }

    public void optimize() {
        int setSize = orderedSet.size();
        optimizePartitions(orderedSet.subList(0,setSize/2), orderedSet.subList(setSize/2,setSize), levels-1);
    }

    public void optimizePartitions(List<Character> a, List<Character> b, int levels) {
        if(levels == 0) {
            return;
        } else {
            int deltaT;

            do {
                ArrayList<Integer> difference = new ArrayList<>();

                difference.addAll(calculateDifference(a, b));
                difference.addAll(calculateDifference(b, a));

                // to switch, deltaT = Da + Db - 2 ca,b needs to be maximal
                deltaT = Integer.MIN_VALUE;
                Character deltaTA = new Character('0');
                Character deltaTB = new Character('0');

                for (Character c : a) {
                    for (Character d : b) {
                        int tempDeltaT =
                                difference.get(charToInt(c)) +
                                        difference.get(charToInt(d)) -
                                        weights[charToInt(c)][charToInt(d)] -
                                        weights[charToInt(d)][charToInt(c)];

                        if (tempDeltaT > deltaT) {
                            deltaT = tempDeltaT;

                            deltaTA = c;
                            deltaTB = d;
                        }
                    }
                }

                orderedSet.set(orderedSet.indexOf(deltaTA), deltaTB);
                orderedSet.set(orderedSet.indexOf(deltaTB), deltaTA);
            } while(deltaT >= 0); // repeat until deltaT is negative

            int setSize = orderedSet.size();
            optimizePartitions(a.subList(0,setSize/2), a.subList(setSize/2,setSize), levels-1);
            optimizePartitions(b.subList(0,setSize/2), b.subList(setSize/2,setSize), levels-1);
        }
    }

    public ArrayList<Integer> calculateDifference(List<Character> a, List<Character> b) {
        ArrayList<Integer> difference = new ArrayList<>();

        // for each node, calculate internal/external cost  and then store difference E - I for both outward and inward edges
        for(Character c : a) {
            int D = 0;
            for(int i=0; i<weights[charToInt(c)].length; i++) {
                if(a.contains(intToChar(i))) {
                    D -= weights[charToInt(c)][i];
                    D -= weights[i][charToInt(c)];
                } else if(b.contains(intToChar(i))) {
                    D += weights[charToInt(c)][i];
                    D += weights[i][charToInt(c)];
                }
            }
            difference.add(D);
        }

        return difference;
    }

    public List<Character> getOrderedSet() {
        return orderedSet;
    }

    public static int charToInt(Character x) {
        return (int) x - (int) 'A';
    }

    public static Character intToChar(int x) {
        return new Character((char) ((int) 'A' + x));
    }
}