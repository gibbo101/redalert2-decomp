int FactoryClass::Cost_Per_Tick_004B9950() const
{
    if (Object) {
        int remaining = 54 - Stage;
        if (remaining) return UnspentCost / remaining;
        return UnspentCost;
    }
    return 0;
}
