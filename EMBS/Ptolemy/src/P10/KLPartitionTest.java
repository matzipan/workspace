package P10;

import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;
import java.util.List;

/**
 * Created by Andrei on 14/01/2016.
 */
public class KLPartitionTest {
    @Test
    public void PartitionTest() {
        List<Character> orderedSet = Arrays.asList('A', 'B', 'G', 'J', 'K', 'L', 'C', 'D', 'E', 'F', 'H', 'I');

        KLWeights weights = new KLWeights(orderedSet.size());

        weights.setWeight('A', 'C', 64);
        weights.setWeight('B', 'C', 64);
        weights.setWeight('A', 'F', 8);
        weights.setWeight('C', 'D', 128);
        weights.setWeight('D', 'B', 16);
        weights.setWeight('F', 'A', 16);
        weights.setWeight('F', 'G', 16);
        weights.setWeight('D', 'E', 48);
        weights.setWeight('D', 'H', 48);
        weights.setWeight('H', 'I', 48);
        weights.setWeight('I', 'K', 12);
        weights.setWeight('J', 'K', 48);
        weights.setWeight('K', 'L', 24);
        weights.setWeight('E', 'G', 16);
        weights.setWeight('G', 'L', 8);

        KLPartition partition = new KLPartition(weights, orderedSet, 2);

        partition.optimize();

        Assert.assertEquals("[E, F, G, J, K, L, A, D, B, C, H, I]", partition.getOrderedSet().toString());
    }

    @Test
    public void SmallPartitionTest() {
        List<Character> orderedSet = Arrays.asList('A', 'B', 'C', 'D');

        KLWeights weights = new KLWeights(orderedSet.size());

        weights.setWeight('A', 'B', 10);
        weights.setWeight('A', 'C', 64);
        weights.setWeight('B', 'C', 200);


        KLPartition partition = new KLPartition(weights, orderedSet, 1);

        partition.optimize();

        Assert.assertEquals("[C, B, A, D]", partition.getOrderedSet().toString());
    }

    @Test
    public void CharConversionTest() {
        Assert.assertTrue(KLWeights.charToInt(new Character('A'))==0);
        Assert.assertTrue(KLWeights.intToChar(0).charValue() == 'A');
    }
}
