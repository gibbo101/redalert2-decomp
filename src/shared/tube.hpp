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

class CCINIClass;
class TubeClass : public AbstractClass {
public:
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

// Every tube (0x008661C8; defined in the globals unit).
extern DynamicVectorClass<TubeClass *> unknown_TubeClass_list_008661c8;

#endif
