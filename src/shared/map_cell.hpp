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
    void unknown_471d10(); //actual declaration from shared/cell.hpp, original RET0
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
    virtual void unknown_slot9(); virtual void unknown_slot10(); virtual void unknown_slot11(); virtual void unknown_slot12(); virtual void unknown_slot13();
    virtual void unknown_slot14(); virtual void unknown_slot15(); virtual void unknown_slot16(); virtual void unknown_slot17();
    virtual CoordStruct Center_Coord() const;   // slot 18 0x0047BA50 (as shared/cell.hpp)

    char unknown_04[0x24 - 0x04];
    Cell MapCoords;           // +0x24 the cell's own coordinates
    int unknown_28;                 // +0x28
    CellClass *unknown_2c;          // +0x2C cleared by MapClass slot 23 (TibSun BridgeDeckCell)
    int unknown_30;                 // +0x30 cleared by MapClass slot 23
    char unknown_34[0x38 - 0x34];
    int IsoTileIndex;               // +0x38
    class TagClass *unknown_3c;     // +0x3C
    char unknown_40[0x44 - 0x40];
    int OverlayIndex;               // +0x44
    char unknown_48[0x4C - 0x48];
    int unknown_4c;                 // +0x4C (MapClass 0x00565E20 accepts 3 and 4; as shared/cell.hpp)
    int unknown_50;                 // +0x50 the wall owner's house index (MapClass 0x00567380)
    char unknown_54[0xDC - 0x54];
    int unknown_dc;                 // +0xDC per-house bits (as shared/cell.hpp)
    char unknown_e0[0xE4 - 0xE0];
    class ObjectClass *OccupierPtr; // +0xE4 (as shared/cell.hpp)
    char unknown_e8[0xEC - 0xE8];
    int unknown_ec;                 // +0xEC the land type (as shared/cell.hpp)
    char unknown_f0[0x100 - 0xF0];
    int unknown_100;                // +0x100 counted up by the buildings that hide the cell (as shared/cell_class.hpp)
    char unknown_104[0x116 - 0x104];
    short unknown_116;              // +0x116 the index of the tube that enters here, -1 for none (as shared/cell.hpp)
    char unknown_118;               // +0x118
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
    bool unknown_138;               // +0x138 (as shared/cell.hpp)
    int unknown_13c;                // +0x13C (as shared/cell.hpp; positive: MapClass 0x00568280)
    union {                         // +0x140 flags (bit 1: mapped, bit 0 set when layer 1 is fully shrouded)
        unsigned int unknown_140;
        struct {                    // TibSun names (as shared/cell_class.hpp)
            unsigned :7;
            unsigned IsBridgeDeck:1;            // bit 7
            unsigned IsUnderBridge:1;           // bit 8
            unsigned IsBridgeTraversable:1;     // bit 9
            unsigned WasUnderBridge:1;          // bit 10
            unsigned IsBridgeEastWest:1;        // bit 11
        };
    };
    Cell Fetch_CellID() const { return MapCoords; }    // the cell's own coordinates as a value (inline; TibSun name)
    // The cell of the bridge deck piece over this cell (TibSun Get_Bridge_Deck_Cell).
    Cell Get_Bridge_Deck_Cell() const
    {
        if (IsBridgeDeck) {
            return Fetch_CellID();
        } else {
            return unknown_2c->Fetch_CellID();
        }
    }
    void unknown_47a340(class AbstractClass *target);  // 0x0047A340 forgets a target (as shared/cell.hpp)
    unsigned short const *unknown_47a200() const;   // 0x0047A200 the tiberium's UI name (as shared/cell.hpp; wchar_t is not declared here)
    bool unknown_47c2e0(int house) const;       // 0x0047C2E0 (unknown_7c[house] > 0; TibSun Is_Sensed; DisplayClass slot 33)
    int unknown_4706c0(Point2D const &point) const;       // 0x004706C0 (height at a lepton position in the cell; as shared/cell.hpp)
    CellClass &Adjacent_Cell(unsigned facing);  // 0x00476AC0 (as shared/cell.hpp)
    void Set_unknown_3c(class TagClass *tag);         // 0x0047A460 (as shared/cell.hpp)
    Rect unknown_474eb0() const;    // 0x00474EB0 (as shared/cell.hpp)
    Rect unknown_475100() const;    // 0x00475100 (as shared/cell.hpp)
    bool unknown_479cc0() const;    // 0x00479CC0 (as shared/cell.hpp)
    bool unknown_47a270();          // 0x0047A270 (a water tile; hypothesis: TibSun Is_Tile_Water)
    bool unknown_47b590() const;    // 0x0047B590 (no tile: 0 or 0xFFFF; as shared/cell.hpp)
    void unknown_4724a0();          // 0x004724A0 (a wall overlay: its owner; TibSun Set_Wall_Owner; as shared/cell.hpp)
    int unknown_476ba0(bool pregame);   // 0x00476BA0 (TibSun Tiberium_Adjust; as shared/cell.hpp)
    void unknown_473000();          // 0x00473000 (drops the cell's bridge; TibSun Destroy_Bridge)
    // Whether a building of the type may be placed in the cell for the house (0x004718B0;
    // TibSun Is_Clear_To_Build; elsewhere declared with a TechnoTypeClass const *).
    bool unknown_4718b0(int speed, class BuildingTypeClass const *type, class HouseClass *house);
    void Set_Under_Bridge(unsigned facing, bool state);   // 0x004732D0 (a high bridge piece; as shared/cell.hpp)
    void Set_Under_Rail_Bridge(unsigned facing, bool state);   // 0x00473700 (the other bridge piece; as shared/cell.hpp)
    bool unknown_47b960() const;    // 0x0047B960 (a bridge tile; as shared/cell.hpp)
    void unknown_47c930();          // 0x0047C930 (a cell of a collapsed bridge; TibSun On_Bridge_Collapse)
    void unknown_47c900();          // 0x0047C900 (maps the cell for the player; MapClass 0x00549C50)
    bool unknown_47b980() const;    // 0x0047B980 (a train bridge tile; as shared/cell.hpp)
#ifdef RA2_MAP_BRIDGE_PIECES
    void Unknown_0047CC10();
    bool unknown_47b5e0() const;    // 0x0047B5E0 (as shared/cell_class.hpp; Westwood's Is_Tile_Cliff)
#endif
    void Unknown_00472540(int value);   // 0x00472540 (as shared/cell.hpp)
    void unknown_473b30(class ObjectClass *object, bool alt);   // 0x00473B30 (links object into the occupier list; TibSun Occupy_Down)
    void unknown_473d20(class ObjectClass *object, bool alt);   // 0x00473D20 (as shared/cell_class.hpp; TibSun Occupy_Up)
    int unknown_475db0(int amount);     // 0x00475DB0 (takes up to amount of tiberium; as shared/cell.hpp)
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
    void Init_Drawer(class LightConvertClass *drawer, int intensity, int ambient, int brightness, int tile_brightness, int alt_brightness);   // 0x004790F0 (DisplayClass 0x0049E570)
};

#endif
