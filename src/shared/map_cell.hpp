// CellClass as the Map units see it (moved out of shared/map.hpp so the
// layer headers only declare CellClass; units that include the real
// shared/cell.hpp must not include this stand-in).
#ifndef RA2_SHARED_MAP_CELL_HPP
#define RA2_SHARED_MAP_CELL_HPP

#include "shared/coord.hpp"
#include "shared/rect.hpp"

// Stand-in for CellClass (an AbstractClass: slot 8 of its primary vtable is
// the virtual destructor, as in AbstractClass): only the members the map
// code touches; the first eight slots are placeholders.
class CellClass {
public:
    CellClass();                    // 0x00470F10
    virtual void unknown_slot0();
    virtual void unknown_slot1();
    virtual void unknown_slot2();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual ~CellClass();           // slot 8 (0x00470E80 is the destructor proper)

    char unknown_04[0x24 - 0x04];
    Cell MapCoords;           // +0x24 the cell's own coordinates
    int unknown_28;                 // +0x28
    int unknown_2c;                 // +0x2C cleared by MapClass slot 23
    int unknown_30;                 // +0x30 cleared by MapClass slot 23
    char unknown_34[0x38 - 0x34];
    int IsoTileIndex;               // +0x38
    class TagClass *unknown_3c;     // +0x3C
    char unknown_40[0x44 - 0x40];
    int OverlayIndex;               // +0x44
    char unknown_48[0x4C - 0x48];
    int unknown_4c;                 // +0x4C (MapClass 0x00565E20 accepts 3 and 4; as shared/cell.hpp)
    char unknown_50[0xDC - 0x50];
    int unknown_dc;                 // +0xDC per-house bits (as shared/cell.hpp)
    char unknown_e0[0xE4 - 0xE0];
    class ObjectClass *OccupierPtr; // +0xE4 (as shared/cell.hpp)
    char unknown_e8[0x119 - 0xE8];
    char unknown_119;               // +0x119
    char unknown_11a;               // +0x11A
    char unknown_11b;               // +0x11B signed; the bridge height in levels (view of cell.hpp's unknown_11b)
    unsigned char unknown_11c;      // +0x11C
    char unknown_11d;               // +0x11D
    unsigned char OverlayData;      // +0x11E
    char unknown_11f;               // +0x11F
    unsigned char unknown_120;      // +0x120 the shroud frame of layer 0 (0xFF: fully shrouded; hypothesis)
    unsigned char unknown_121;      // +0x121 the same for layer 1
    char unknown_122[0x12C - 0x122];
    unsigned int unknown_12c;       // +0x12C flags; bit 3 answers IGameMap::Is_Visible
    int unknown_130;                // +0x130 (1 after MapClass 0x00559F10)
    int unknown_134;                // +0x134 (0 after MapClass 0x00559F10)
    char unknown_138[0x140 - 0x138];
    unsigned int unknown_140;       // +0x140 flags (bit 1: mapped, bit 0 set when layer 1 is fully shrouded)
    void unknown_47bc80();          // 0x0047BC80 (DisplayClass 0x0049CDB0, for a cell that was mapped)
    void unknown_47be00();          // 0x0047BE00 (as shared/cell.hpp)
    void unknown_47c840();          // 0x0047C840 (as shared/cell.hpp)
    void unknown_47c8a0();          // 0x0047C8A0 (as shared/cell.hpp)
    void Unknown_004798F0();        // 0x004798F0 (run over every cell by DisplayClass 0x0049E5E0)
    class ObjectClass *unknown_4717b0() const;  // 0x004717B0 the building in the cell (as shared/cell.hpp)
    class ObjectClass *Cell_Terrain(bool alt = false) const;   // 0x004717E0 (as shared/cell.hpp)
    // Whether the cell can be entered (0x00478760; hypothesis: Is_Clear_To_Move).
    bool Unknown_00478760(int speed, bool arg2, bool arg3, int arg4, int arg5, int arg6, bool arg7);
    // An object in the cell near a point, or 0 (0x00471660; hypothesis).
    class ObjectClass *Unknown_00471660(Point2D const &point, int arg2, int arg3);
    CoordStruct Closest_Free_Spot(CoordStruct const &coord, bool any = false, int alt = 0) const;   // 0x004764B0
    bool unknown_476460(int facing, bool alt) const;   // 0x00476460
    void Unknown_004712c0(class RGBClass *first, class RGBClass *second);   // 0x004712C0 the two radar colours of the cell
    void Unknown_004790F0(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);   // 0x004790F0 (DisplayClass 0x0049E570)
};

#endif
