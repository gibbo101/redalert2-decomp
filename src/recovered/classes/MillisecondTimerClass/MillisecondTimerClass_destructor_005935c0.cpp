
MillisecondTimerClass::~MillisecondTimerClass()
{
    if (Frequency != 1.0) {
        timeEndPeriod(1);
    }
}
