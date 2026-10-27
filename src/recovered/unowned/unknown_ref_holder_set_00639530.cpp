// void UnknownRefHolder_00639530::Set(UnknownRefCounted_00639530 *object) -- 0x00639530
// Purpose: a reference-counting pointer holder (pointer at +0x04): holds a
// new object (its count at +0x04 goes up) and lets go of the old one
// (cleared first, then its virtual slot 2 runs).
// Assumptions: the classes are unidentified; slot 2 is taken to release a
// reference.

struct UnknownRefCounted_00639530 {
    virtual void unknown_slot0();
    virtual void unknown_slot1();
    virtual void Release();                 // slot 2
    int RefCount;                           // +0x04
};

struct UnknownRefHolder_00639530 {
    int unknown_00;
    UnknownRefCounted_00639530 *Object;     // +0x04
    void Set(UnknownRefCounted_00639530 *object);
};

void UnknownRefHolder_00639530::Set(UnknownRefCounted_00639530 *object)
{
    if (object != Object) {
        if (object != 0) {
            object->RefCount++;
        }
        if (Object != 0) {
            UnknownRefCounted_00639530 *old = Object;
            Object = 0;
            old->Release();
        }
        Object = object;
    }
}
