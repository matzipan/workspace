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
        int[][] weights = {
                {0, 0, 64, 0, 0, 8, 0, 0, 0, 0, 0, 0},
                {0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 16, 0, 0, 48, 0, 0, 48, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0},
                {16, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8},
                {0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };

        List<Character> orderedSet = Arrays.asList('A', 'J', 'K', 'B', 'G', 'L', 'C', 'H', 'I', 'D', 'E', 'F');

        KLPartition partition = new KLPartition(weights, orderedSet, 2);

        partition.optimize();

        System.out.println(partition.getOrderedSet());
    }

    @Test
    public void CharConversionTest() {
        Assert.assertTrue(KLPartition.charToInt(new Character('A'))==0);
        Assert.assertTrue(KLPartition.intToChar(0).charValue() == 'A');
    }
}
