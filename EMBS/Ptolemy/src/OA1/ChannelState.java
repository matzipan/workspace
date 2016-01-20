package OA1;

import ptolemy.actor.util.Time;

public class ChannelState {
    // the time value at second sample time
    public Time firstSample = null;
    // the payload captured with the first sample
    public int firstSamplePayload = 0;
    // the time value at second sample time
    public Time secondSample = null;
    // the payload captured with the second sample
    public int secondSamplePayload = 0;

    // channel number
    public int channelId = 0;

    // determined value for n
    public int n = 0;

    // the time at which the n value transmission window starts. the channel needs to be setup before this value.
    public Time getNTime = null;

    public double getChannelPeriod() {
        Time period = secondSample.subtract(firstSample);
        int payloadDifference = firstSamplePayload - secondSamplePayload;

        if(n==1) {
            return period.getDoubleValue()/12;
        } else if(firstSamplePayload <= secondSamplePayload || (firstSamplePayload > secondSamplePayload &&  (period.getDoubleValue()/payloadDifference >= 1.5))) {
            // assumption: we're sticking our head in the sand and hoping that we can't be delayed by more than one reception/sleep phase.
            return period.getDoubleValue()/(payloadDifference + 13);
        } else {
            return period.getDoubleValue()/payloadDifference;
        }
    }

    public boolean isPeriodInconclusive() {
        Time period = secondSample.subtract(firstSample);
        int payloadDifference = firstSamplePayload - secondSamplePayload;

        // if the both linear equations below are true, then we cannot be sure which one reflects reality (as per Nyquist theorem), so we need new samples
        return firstSamplePayload > secondSamplePayload &&
                period.getDoubleValue()/payloadDifference <= 1.5 &&
                period.getDoubleValue()/(payloadDifference+13) >= 0.5
                // also, if the period is higher than the maximum admissible t (because we met more than one reception/sleep phase), then it's clearly wrong, need new samples
                || period.getDoubleValue()/(payloadDifference+13) >= 1.5;

    }

    public double getRealChannelPeriod() {
        return secondSample.subtract(firstSample).getDoubleValue();
    }

    public int addChannelSampleTime(Time currentTime, int payload) {
        if (firstSample == null) {
            firstSample = currentTime;
            firstSamplePayload = payload;

            return 1;
        } else if (secondSample == null) {
            secondSample = currentTime;
            secondSamplePayload = payload;

            return 2;
        }

        return -1;
    }

    public boolean  channelNeedsSamples() {
        return firstSample == null || secondSample == null;
    }

    public void setGetNTime(Time time) {
        getNTime = time;
    }

    public boolean hasMissedGetNWindow(Time currentTime) {
        // ideally, we're looking to compare if time == getNTime + getChannelPeriod()
        // but the documentation is not very clear about what values time might take
        // (and what offsets to expect), so we're taking the safe side and comparing
        // if it's more than half of a period away from getNTime. so the assumption
        // is that those offsets are smaller than half of a period.

        return getNTime.getDoubleValue() + getChannelPeriod()/2 < currentTime.getDoubleValue();
    }

    public void discardFirstAndRotate() {
        firstSample = secondSample;
        firstSamplePayload = secondSamplePayload;
        secondSample = null;
        secondSamplePayload = 0;
    }
}
