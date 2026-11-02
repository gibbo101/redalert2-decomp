// The rank: 0 elite, 1 veteran, 2 rookie (0x00713440).
int UnknownTechnoPair::unknown_713440() const
{
    if (Experience >= 2) {
        return 0;
    }
    return Experience >= 1 ? 1 : 2;
}
