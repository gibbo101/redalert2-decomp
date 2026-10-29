// CellClass: one map cell (Cell.cpp, 0x00470490 unit: members 0x00470680-
// 0x0047D08F; RTTI vtables 0x0079DB04 primary (24 slots, AbstractClass's
// plus overrides), 0x0079DAE8 IRTTITypeInfo at +4, 0x0079DAE0 INoticeSink,
// 0x0079DAD8 INoticeSource). Moved out of shared/map.hpp, where a stand-in
// with placeholder slots stood for it.
//
// Layout (from the constructor 0x00470F10, the NoInitClass constructor
// 0x00470680, the destructor 0x00470E80, Load 0x00478CB0 and Save
// 0x00478ED0; names are hypotheses unless stated):
//   +0x000  AbstractClass (0x24)
//   +0x024  Cell MapCoords      the zero cell when constructed
//   +0x028  DynamicVectorClass<FoggedObjectClass *> *FoggedObjects (owned;
//           saved as a count and pointers, swizzled)
//   +0x02C  CellClass *unknown_2c     (swizzled; bridge owner cell)
//   +0x030  void *unknown_30          (swizzled)
//   +0x034  UnknownCellCounted *unknown_34 (cleared by the NoInit
//           constructor; the destructor drops a count at its +0x194)
//   +0x038  int IsoTileIndex          0xFFFF when constructed
//   +0x03C  TagClass *unknown_3c (swizzled; the cell tag: counted at +0x2C,
//           cells with one are listed in the map at 0x00833638)
//   +0x040  void * (swizzled)
//   +0x044  int OverlayIndex, +0x048 int SmudgeIndex (-1)
//   +0x04C  int unknown_4c            (cleared by the NoInit constructor)
//   +0x050..+0x064  int unknown_50[6] (-1)
//   +0x068  Rect unknown_68           (0)
//   +0x078  unsigned int unknown_78   per-house bit mask
//   +0x07C  short unknown_7c[24]      per-house counters (zero-filled)
//   +0x0AC  int unknown_ac[12]        (zero-filled)
//   +0x0DC  int, +0x0E0 void * (swizzled; Set_unknown_e0)
//   +0x0E4  ObjectClass *OccupierPtr, +0x0E8 ObjectClass *AltOccupierPtr
//           (swizzled; chained through ObjectClass +0x30)
//   +0x0EC  int unknown_ec            the land type (index into Ground,
//           0x00850EA0)
//   +0x0F0  double unknown_f0         (Reduce_f0 0x0047CEC0)
//   +0x0F8  void * (swizzled), +0x0FC owned object (deleted by the destructor)
//   +0x100  int, +0x104 int (0x10000)
//   +0x108  short, +0x10A..+0x114 short (1000), +0x116 short (-1)
//   +0x118..+0x122  chars (+0x118 -1, +0x120/+0x121 -2; +0x11C blocks
//           smudges, +0x11E OverlayData, +0x11F SmudgeData, +0x122 adjacent
//           terrain count)
//   +0x124, +0x128  unsigned char
//   +0x12C  flag bits (bits 0..4 cleared when constructed)
//   +0x130  int (1), +0x134 int, +0x138 bool, +0x13C int
//   +0x140  flag bits (bits 0..22 cleared when constructed)
//   size 0x148
#ifndef RA2_SHARED_CELL_HPP
#define RA2_SHARED_CELL_HPP

#include "shared/abstract_type.hpp"
#include "shared/rect.hpp"

class CellClass;
class ObjectClass;
class TechnoClass;
class TagClass;
class FoggedObjectClass;

extern "C" GUID const CLSID_CellClass;          // 0x007A1E70

// Isometric tile set start indices: shared/tileset_index.hpp.
#include "shared/tileset_index.hpp"

// The offsets of the eight neighbouring cells by facing (0x00851A70).
#include "shared/adjacent_cell.hpp"

// The land types (Ground, 0x00850EA0) that CellClass +0xEC indexes.
#include "shared/ground_type.hpp"

// The map's list of tagged cells (MapClass +0x1158,
// DynamicVectorClass<Cell> at 0x00833638).
extern DynamicVectorClass<Cell> unknown_map_tagged_cells_833638;

// Looked up by cell (0x007101B0, __fastcall; hypothesis: a tube or bridge
// object) and told about the cell (0x00712300).
class UnknownCellLookup {
public:
    void Unknown_00712300(CellClass *cell);
};
UnknownCellLookup *__fastcall Unknown_007101B0(Cell const &cell);


// The map's cell table (MapClass +0x134 VectorClass<CellClass *>; this is
// its element storage pointer at 0x00832618, x + y * 512).
extern CellClass **unknown_map_cells_832618;

// Member-wise cell sum: shared/coord.hpp's operator+ (the multi-cell loops
// of SmudgeTypeClass copy its result into a local).

// Cell equality and comparison: shared/house.hpp defines operator== and
// operator!= for Cell (merge debt: Cell.cpp's copies differ in !=).

// The object owned at +0xFC (deleted through its first virtual slot; type
// unknown).
class UnknownCellOwned {
public:
    virtual ~UnknownCellOwned();
};

// Four words at +0x68 cleared together (type unknown).
struct UnknownCell68 {
    UnknownCell68(int a = 0, int b = 0, int c = 0, int d = 0) : unknown_00(a), unknown_04(b), unknown_08(c), unknown_0c(d) {}
    UnknownCell68(NoInitClass const &noinit) {}
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
};

// The object at +0x34: while unknown_flag_a40958 is set the destructor drops
// a count at its +0x194 (type unknown; not a TagClass, which is 0x38 bytes).
struct UnknownCellCounted {
    char unknown_000[0x194];
    int unknown_194;                // +0x194
};

class CellClass : public AbstractClass {
public:
    int unknown_475fe0(int damage); // 00475FE0: wall mutation, full EAX/RET4; hypothesis
    CellClass();                                                        // 0x00470F10
    CellClass(NoInitClass const &noinit);                               // 0x00470680
    virtual ~CellClass();                                               // 0x00470E80

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x0047A410 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00478CB0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00478ED0 slot 6
    virtual int __stdcall What_Am_I() { return 0x0B; }                  // 0x0047CF70 (IRTTITypeInfo slot 3; inline)
    virtual int Kind_Of() const { return 0x0B; }                        // 0x0047CF80 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(CellClass); }           // 0x0047CF90 slot 12 (inline)
    virtual CoordStruct Center_Coord() const;                           // 0x0047BA50 slot 18
    virtual bool unknown_slot20() const;                                // 0x0047B9F0
    virtual CoordStruct unknown_slot22() const;                         // 0x0047BAA0

    // Occupants.
    ObjectClass *unknown_471660(Point2D const &spot, bool alt, ObjectClass *except) const;   // 0x00471660 (nearest flagged occupant to a sub-cell spot)
    ObjectClass *Find_Object(int kind, bool alt = false) const;         // 0x00471760
    ObjectClass *unknown_471830(Point2D const &spot, bool alt);         // 0x00471830 (an aircraft over the cell when the flag at 0x00A40958 is set, else the occupant nearest the spot; TeamClass 0x006BB260)
    ObjectClass *unknown_4717b0() const;                                // 0x004717B0 (the building; kind 6)
    ObjectClass *Cell_Terrain(bool alt = false) const;                  // 0x004717E0 (kind 0x24)
    ObjectClass *Cell_Unit(bool alt = false) const;                     // 0x00473E30 (kind 1)
    ObjectClass *Cell_Aircraft(bool alt = false) const;                 // 0x00473E80 (kind 2)
    ObjectClass *Cell_Infantry(bool alt = false) const;                 // 0x00473ED0 (kind 0x0F)

    // Tile kinds (IsoTileIndex ranges).
    bool unknown_476cc0(ObjectClass *object);   // 0x00476CC0 (the object may stand here; MechLocomotionClass 0x00592F70)
    bool unknown_47b590() const;                // 0x0047B590 (no tile: 0 or 0xFFFF)
    bool unknown_47b5b0() const;                // 0x0047B5B0
    bool unknown_47b7c0() const;                // 0x0047B7C0
    bool unknown_47b7e0() const;                // 0x0047B7E0
    bool unknown_47b860() const;                // 0x0047B860
    bool unknown_47b880() const;                // 0x0047B880
    bool unknown_47b8a0() const;                // 0x0047B8A0
    bool unknown_47b8e0() const;                // 0x0047B8E0
    bool unknown_47b900() const;                // 0x0047B900
    bool unknown_47b920() const;                // 0x0047B920
    bool unknown_47b940() const;                // 0x0047B940
    bool unknown_47b960() const;                // 0x0047B960
    bool unknown_47b980() const;                // 0x0047B980
    bool unknown_47b9a0() const;                // 0x0047B9A0
    bool unknown_47b9c0() const;                // 0x0047B9C0
    bool unknown_47bb10() const;                // 0x0047BB10

    // Per-house bits.
    bool Is_House_Bit(int house) const;         // 0x0047C2C0
    bool unknown_47c300(int house) const;       // 0x0047C300 (a second per-house bit test; UnitClass slot 49)
    void unknown_476920(void const *arg1, bool arg2, bool arg3, bool alt);  // 0x00476920 (scatters the occupants; alt picks AltOccupierPtr; UnitClass slot 302)
    bool unknown_479cc0() const;                // 0x00479CC0 (UnitClass slot 27)
    bool unknown_479cf0() const;                // 0x00479CF0, no stack arguments; AL result
    bool unknown_479f70() const;                // 0x00479F70, no stack arguments; AL result
    bool unknown_47a120(TechnoClass *techno) const;   // 0x0047A120 (UnitClass slot 27)
    void Set_House_Bit(int house);              // 0x0047C320
    void Clear_House_Bit(int house);            // 0x0047C340

    bool unknown_47ba10(int house) const;      // 0x0047BA10 (visible to the player's house; hypothesis)
    bool unknown_47cdd0() const;                // 0x0047CDD0 (land allows ...; no building, not blocked)
    Point2D unknown_475440() const;             // 0x00475440 (the overlay image offset in the cell; hypothesis)
    void unknown_474260(int arg1, int arg2, int frame);  // 0x00474260 (draws the shroud frame; hypothesis)
    void unknown_474510(int arg1, int arg2, int frame);  // 0x00474510 (draws the fog frame; hypothesis)
    void unknown_475520(int arg1, int arg2);    // 0x00475520 (updates and draws the cell's shroud and fog frames; Tactical 0x006A3FA6)
    void unknown_4724a0();                      // 0x004724A0 (a wall overlay: +0x50 = owner of the nearest building of a WallOwner house)
    int unknown_47a290() const;                 // 0x0047A290 (the height of the top of the cell: ground plus a building's height or 0x55 for an object at the spot)
    void unknown_47a160();                      // 0x0047A160 (slot 109 on up to ten occupants; units and aircraft get Force_New_Slope(+0x11C))
    void unknown_476b20(int house, int value);  // 0x00476B20 (every other house that is not an ally (or fails 0x004F52F0) gets unknown_func_4e5dc0(the cell's map block, value); TechnoClass 0x006D95A0/0x006D95D0)
    void unknown_47a4e0();                      // 0x0047A4E0 (redraws the cell's 60x30 screen area; BuildingClass 0x0043C1F0)
    int unknown_47a5a0();                       // 0x0047A5A0 (bit per cardinal neighbour holding veins: an IsVeins overlay, or overlay 0x7E with data from 48)
    bool unknown_475840(int overlay, int facing) const;   // 0x00475840 (whether a wall of overlay type joins this cell toward facing: the same wall, or a gate or wall tower; hypothesis)
    bool unknown_478ba0(bool arg1);             // 0x00478BA0 (whether tiberium may grow here; hypothesis)
    void unknown_473d20(ObjectClass *object, bool alt);   // 0x00473D20 (unlinks object from the occupier list; MapClass 0x0054B04D)
    Rect unknown_4752b0() const;                // 0x004752B0 (a screen rectangle of the cell's contents; hypothesis)
    Rect unknown_474eb0() const;                // 0x00474EB0 (another; hypothesis)
    Rect unknown_475100() const;                // 0x00475100 (another; hypothesis)
    bool unknown_4788e0() const;                // 0x004788E0 (the ore may grow here: scenario +0x222A, ore below its last stage; hypothesis)
    bool unknown_478950() const;                // 0x00478950 (the ore may spread from here; hypothesis)
    bool unknown_4789d0();                      // 0x004789D0 (grows the ore through unknown_47c3a0; hypothesis)
    bool unknown_47c3a0(int tiberium, bool arg2);   // 0x0047C3A0 (not recovered)
    int unknown_47ce70() const;                 // 0x0047CE70 (+0xF0 limited to Rules RadLevelMax, as an int)
    bool unknown_47c200();                      // 0x0047C200 (the map allows the cell, its tile type does not refuse it, it is not blocked and holds no building or terrain object)
    void unknown_47be00();                      // 0x0047BE00 (diagonal pass over the cells ahead)
    void unknown_47be60();                      // 0x0047BE60

    void unknown_47a340(AbstractClass *target);   // 0x0047A340 (forgets a target)
    void Set_unknown_3c(TagClass *tag);         // 0x0047A460

    // Tiberium (OverlayClass::To_Tiberium of the overlay).
    wchar_t const *unknown_47a200() const;      // 0x0047A200 (the tiberium's UI name)
    int Get_Tiberium_Type() const;              // 0x0047A220
    int Get_Tiberium_Value() const;             // 0x0047A230

    void unknown_47cb50();                      // 0x0047CB50 (map call at the cell centre)
    void unknown_47cbb0();                      // 0x0047CBB0
    int unknown_475db0(int amount);             // 0x00475DB0 (takes up to amount of tiberium; answers what it took; hypothesis)
    int unknown_47c040();                       // 0x0047C040
    void unknown_47a7a0();                      // 0x0047A7A0

    // Counters and scalars.
    void unknown_47c840();                      // 0x0047C840 (decrements +0x130)
    void unknown_47c8a0();                      // 0x0047C8A0 (increments +0x130 up to +0x134)
    void Unknown_004790F0(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);   // 0x004790F0 (sets up the cell's light drawer at +0x34; TerrainClass slots 67/68, DisplayClass 0x0049E570)
    int unknown_47ce50() const;                 // 0x0047CE50 (+0xF0 above 1.0)
    void Reduce_f0(double amount);              // 0x0047CEC0
    bool Set_unknown_e0(void *value);           // 0x0047CF30

    static Cell __fastcall Adjacent_Cell(Cell const &cell, int facing);   // 0x0047CFC0
    CellClass &Adjacent_Cell(unsigned facing);  // 0x00476AC0 (this cell for facings past 7)
    // The const form (as in Westwood's CELL.H: casts away const and calls the above).
    CellClass const &Adjacent_Cell(unsigned facing) const { return ((CellClass *)this)->Adjacent_Cell(facing); }
    CoordStruct unknown_475d60() const;         // 0x00475D60 (centre at the middle's height)
    bool unknown_476460(int facing, bool alt) const;   // 0x00476460 (+0x124/+0x128 bit clear)
    ObjectClass *unknown_476750() const;        // 0x00476750 (the building, if its type's +0x1351 flag is set)
    bool unknown_4786d0(int value);             // 0x004786D0
    bool unknown_478720();                      // 0x00478720
    void unknown_478740();                      // 0x00478740 (occupants' ObjectClass slot 61)
    // Whether an object of speed type speed may enter (zone and level -1: any;
    // arg2/arg3 ignore some blocked directions; hypothesis).
    bool unknown_478760(int speed, bool arg2, bool arg3, int zone, int zone_type, int level, bool alt);   // 0x00478760

    // Members other units call (not recovered yet).
    void unknown_47c080();                      // 0x0047C080 (after the smudge changes; redraw hypothesis)
    bool unknown_47a670() const;                // 0x0047A670 (Overlay.cpp wall pass; hypothesis)
    void unknown_47ad00();                      // 0x0047AD00
    void unknown_478a40(int arg1);              // 0x00478A40 (TerrainClass::AI: spreads tiberium; hypothesis)
    void unknown_4732d0(unsigned arg1, unsigned arg2);                   // 0x004732D0 (OverlayClass slot 71: bridge piece; hypothesis)
    void unknown_473700(unsigned arg1, unsigned arg2);                   // 0x00473700 (OverlayClass slot 71: the other bridge piece; hypothesis)
    bool unknown_4718b0(int arg1, int arg2, int arg3);                   // 0x004718B0 (whether a wall may be placed; hypothesis)
    void unknown_475960(bool arg1);                                      // 0x00475960
    void unknown_476ba0(bool arg1);                                      // 0x00476BA0
    void unknown_471d10();                      // 0x00471D10 (IsometricTileClass slot 71: after the tile changes; hypothesis)
    void Unknown_00472540(int value);           // 0x00472540 (clears an overlay with -1: AnimClass 0x004226D0, TerrainClass slot 52)
    int unknown_4706c0(Point2D const &point) const;       // 0x004706C0 (height at a lepton position in the cell; hypothesis)

    Cell MapCoords;                       // +0x024
    DynamicVectorClass<FoggedObjectClass *> *FoggedObjects;   // +0x028
    CellClass *unknown_2c;                      // +0x02C
    void *unknown_30;                           // +0x030
    UnknownCellCounted *unknown_34;             // +0x034
    int IsoTileIndex;                           // +0x038
    TagClass *unknown_3c;                       // +0x03C
    void *unknown_40;                           // +0x040
    int OverlayIndex;                           // +0x044
    int SmudgeIndex;                            // +0x048
    int unknown_4c;                             // +0x04C
    int unknown_50;                             // +0x050
    int unknown_54;                             // +0x054
    int unknown_58;                             // +0x058
    int unknown_5c;                             // +0x05C
    int unknown_60;                             // +0x060
    int unknown_64;                             // +0x064
    UnknownCell68 unknown_68;                   // +0x068
    unsigned int unknown_78;                    // +0x078
    short unknown_7c[24];                       // +0x07C
    int unknown_ac[12];                         // +0x0AC
    int unknown_dc;                             // +0x0DC
    void *unknown_e0;                           // +0x0E0
    ObjectClass *OccupierPtr;                   // +0x0E4
    ObjectClass *AltOccupierPtr;                // +0x0E8
    int unknown_ec;                             // +0x0EC
    double unknown_f0;                          // +0x0F0
    void *unknown_f8;                           // +0x0F8
    UnknownCellOwned *unknown_fc;               // +0x0FC
    int unknown_100;                            // +0x100
    int unknown_104;                            // +0x104
    short unknown_108;                          // +0x108
    short unknown_10a;                          // +0x10A
    short unknown_10c;                          // +0x10C
    short unknown_10e;                          // +0x10E
    short unknown_110;                          // +0x110
    short unknown_112;                          // +0x112
    short unknown_114;                          // +0x114
    short unknown_116;                          // +0x116
    char unknown_118;                           // +0x118
    char unknown_119;                           // +0x119
    char unknown_11a;                           // +0x11A
    char unknown_11b;                           // +0x11B
    unsigned char unknown_11c;                  // +0x11C
    char unknown_11d;                           // +0x11D
    unsigned char OverlayData;                  // +0x11E
    unsigned char SmudgeData;                   // +0x11F
    char unknown_120;                           // +0x120
    char unknown_121;                           // +0x121
    char unknown_122;                           // +0x122
    char unknown_123;
    unsigned char unknown_124;                  // +0x124
    char unknown_125[3];
    unsigned char unknown_128;                  // +0x128
    char unknown_129[3];
    unsigned int unknown_12c;                   // +0x12C flags; bit 3 answers IGameMap::Is_Visible
    int unknown_130;                            // +0x130
    int unknown_134;                            // +0x134
    bool unknown_138;                           // +0x138
    int unknown_13c;                            // +0x13C
    unsigned int unknown_140;                   // +0x140 flags
    int unknown_144;                            // +0x144
};

#endif
