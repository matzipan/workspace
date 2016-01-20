package P10;

/**
 * Created by Andrei on 20/01/2016.
 */
public class KLWeights {
    double[][] weights;
    public KLWeights(int size) {
        weights = new double[size][size];
    }

    // We are representing weights of a directed graph, so a is the origin and b the destination
    public void setWeight(Character a, Character b, double weight) {
        weights[charToInt(a)][charToInt(b)] = weight;
    }

    public double getWeight(Character a, Character b) {
        return weights[charToInt(a)][charToInt(b)];
    }

    public static int charToInt(Character x) { // used th access the weights matrix
        return (int) x - (int) 'A';
    }

    public static Character intToChar(int x) { // used to walk through the weights matrix
        return new Character((char) ((int) 'A' + x));
    }
}
