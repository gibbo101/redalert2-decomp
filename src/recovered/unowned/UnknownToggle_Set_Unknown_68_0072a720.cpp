// void UnknownToggle_72a6d0::Set_Unknown_68(MSEngine *target, bool value) -- 0x0072A720
// Purpose: when the second flag (+0x68) changes, stores it, gives the
// shape object at +0x64 the frame +0x70 when both flags (+0x74, +0x68) are
// set and +0x6C otherwise (0x005AD820), and has the engine broadcast the
// address of +0x54 (MSEngine::Broadcast) and redraw.
// Assumptions: the owner (a two-state button of the 0x0072Exxx dialog code)
// and the callees' classes are unidentified; names are placeholders.
// @ref ?Unknown_005AD820@UnknownShape_72a6d0@@QAEXH@Z=005ad820
// @ref ?Broadcast@MSEngine@@QAEXH@Z=005b3800
// @ref ?Redraw@MSEngine@@QAEXXZ=005b2f90

class UnknownShape_72a6d0 {
public:
    void Unknown_005AD820(int frame);
};
// As shared/ms_engine.hpp declares the members used here.
class MSEngine {
public:
    void Redraw();                      // 0x005B2F90
    void Broadcast(int unknown1);       // 0x005B3800
};

class UnknownToggle_72a6d0 {
public:
    void Set_Unknown_68(MSEngine *target, bool value);

    char unknown_00[0x54];
    char unknown_54[0x10];              // +0x54 area (passed by address)
    UnknownShape_72a6d0 *Shape;         // +0x64
    bool unknown_68;                    // +0x68
    int unknown_6c;                     // +0x6C frame when off
    int unknown_70;                     // +0x70 frame when on
    bool unknown_74;                    // +0x74
};

void UnknownToggle_72a6d0::Set_Unknown_68(MSEngine *target, bool value)
{
    if (unknown_68 != value) {
        unknown_68 = value;
        Shape->Unknown_005AD820(unknown_74 && unknown_68 ? unknown_70 : unknown_6c);
        target->Broadcast((int)unknown_54);
        target->Redraw();
    }
}
