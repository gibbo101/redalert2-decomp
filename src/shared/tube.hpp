// TubeClass: a tunnel (Tube.cpp; RTTI vtable 0x007ADB38, TClassFactory<TubeClass>).
// Layout from the constructor 0x006EF1D0, the [Tubes] reader 0x006EF5C0 and the writer 0x006EF480
// (names after the "%d,%d,%d,%d,%d" entry; hypotheses):
//   +0x24 Cell EnterCell, +0x28 Cell ExitCell (FootClass slot 19 0x004CA6F0 reads it for the tube
//   FootClass +0x574 indexes), +0x2C int Facing, +0x30 int Directions[100] (-1 ends the list),
//   +0x1C0 int unknown_1c0 (the directions read); size 0x1C4.
#ifndef RA2_SHARED_TUBE_HPP
#define RA2_SHARED_TUBE_HPP

#include "shared/abstract_class.hpp"
#include "shared/vector_class_decl.hpp"

extern "C" GUID const CLSID_TubeClass;                // 0x007A1CC0
class CCINIClass;
class NoInitClass;
class TubeClass : public AbstractClass {
public:
    TubeClass(Cell const &enter, int facing);                           // 0x006EF1D0
    // The Load restore: the AbstractClass constructor (0x0040FF10), not its NoInit one.
    TubeClass(NoInitClass const &noinit) {}
    virtual ~TubeClass();                                               // 0x006EF2D0 (scalar deleting 0x006EF910)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x006EF8D0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006EF3A0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006EF3E0 slot 6
    virtual int Kind_Of() const;                                        // 0x006EF8C0 slot 11 (0x35)
    virtual int Size_Of() const;                                        // 0x006EF8B0 slot 12 (0x1C4)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006EF830 slot 13

    // Numbers the tubes whose entry cell can be entered and deletes the rest (0x006EF400).
    static void Update_All_Indexes();
    bool unknown_6ef740(Cell const &cell) const;      // 0x006EF740
    // Writes the tunnels (0x006EF480; "%d,%d,%d,%d,%d" entries; Write_Scenario_INI).
    static void __fastcall Write_INI(CCINIClass &ini);
    // Reads the [Tubes] entries (0x006EF5C0; "enter x,y,facing,exit x,y,directions").
    static void __fastcall Read_INI(CCINIClass &ini);

    Cell EnterCell;                 // +0x24
    Cell ExitCell;                  // +0x28
    int Facing;                     // +0x2C
    int Directions[100];            // +0x30
    int unknown_1c0;                // +0x1C0
};

void __fastcall Detach_This_From_All(AbstractClass *object, bool all);     // 0x006ECB90

// Every tube (0x008661C8; defined in the globals unit).
extern DynamicVectorClass<TubeClass *> unknown_TubeClass_list_008661c8;

#endif
