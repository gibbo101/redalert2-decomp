// void UnknownLink_0068E270::unknown_forward() -- 0x0068E270
// Purpose: passes the object reached through the pointer at +0x00 (its
// first word) and this link to 0x004B87F0.
// Assumptions: the classes are unidentified.
// @ref ?unknown_call_4b87f0@@YIXPAXPAUUnknownLink_0068e270@@@Z=004b87f0

struct UnknownLink_0068e270;
void __fastcall unknown_call_4b87f0(void *object, UnknownLink_0068e270 *link);  // 0x004B87F0

struct UnknownLink_0068e270 {
    void **Owner;                           // +0x00
    void unknown_forward();
};

void UnknownLink_0068e270::unknown_forward()
{
    unknown_call_4b87f0(*Owner, this);
}
