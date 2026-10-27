// Observed counter prefix only: +0 remaining ticks, +4 alternating phase.
// Original non-polymorphic class name and total storage extent are unknown;
// this view is never instantiated or used for pointer arithmetic.
struct UnknownAlternatingCounterPrefix {
    unsigned int Remaining;
    bool Phase;
};
bool __fastcall Advance_Alternating_Counter_004bbf00(UnknownAlternatingCounterPrefix &counter)
{
    if (counter.Remaining!=0) {
        unsigned int remaining=counter.Remaining-1;
        counter.Phase=false;
        counter.Remaining=remaining;
        if (remaining & 1) counter.Phase=true;
        return true;
    }
    return false;
}
