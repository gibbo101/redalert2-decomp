// WinModemClass::WinModemClass() -- 0x00734120
// Purpose: an idle serial modem: allocates the 8 KB receive buffer, clears
// the counters and flags, and marks the port handle as not open (-1).
// Assumptions: only the constructor's stores are known; the field roles
// (buffer, port handle at +0x5C, closed by 0x00734170) come from the
// destructor; the other fields keep offset names. Slot 0 is the scalar
// deleting destructor (0x00735610), declared as a plain virtual so this
// unit does not emit its own copy.
// @ref ??_7WinModemClass@@6B@=007af4e0
// @ref ??2@YAPAXI@Z=00782017

class WinModemClass {
public:
    WinModemClass();
    virtual void *unknown_deleting_destructor_735610(unsigned int flags);
    virtual void unknown_slot1();
    virtual void unknown_slot2();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual void unknown_slot8();
    virtual void unknown_slot9();

    int unknown_04;
    int unknown_08;
    int unknown_0c;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    int unknown_1c;
    int unknown_20;
    unsigned char *Buffer;                  // +0x24
    int unknown_28[10];
    bool unknown_50;
    bool unknown_51;
    int unknown_54;
    int unknown_58;
    void *PortHandle;                       // +0x5C
    int unknown_60;
    int unknown_64;
    int unknown_68;
};

WinModemClass::WinModemClass()
{
    Buffer = new unsigned char[0x2000];
    unknown_54 = 0;
    unknown_58 = 0;
    unknown_50 = false;
    unknown_51 = false;
    unknown_68 = 0;
    unknown_64 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0c = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    PortHandle = (void *)-1;
}
