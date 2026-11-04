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
//   +0x034  LightConvertClass *unknown_34  the tile drawer (Westwood's Drawer;
//           counted at its +0x194, Init_Drawer 0x004790F0)
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
#ifndef RA2_SHARED_CELL_CLASS_HPP
#define RA2_SHARED_CELL_CLASS_HPP

#ifndef RA2_SHARED_CELL_HPP
#define RA2_SHARED_CELL_HPP
#endif

#include "shared/abstract_class.hpp"
template<class T> class DynamicVectorClass;
#include "shared/rect.hpp"

// The occupation bits of a cell (Westwood's OccupyFlagsType): the five sub-cell spots (centre,
// north-west, north-east, south-west, south-east), a vehicle, a building ("monolith") and a
// building owner bit.
struct CellOccupyFlags {
    unsigned Center:1;
    unsigned NW:1;
    unsigned NE:1;
    unsigned SW:1;
    unsigned SE:1;
    unsigned Vehicle:1;
    unsigned Monolith:1;
    unsigned Building:1;
};
class CellClass;
class ObjectClass;
class TechnoClass;
class TagClass;
class FoggedObjectClass;
class LightConvertClass;
class TiberiumClass;

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


// The ore stage by the count of neighbours with the same tiberium (0x007D2C10;
// Westwood's _adj in Tiberium_Adjust: 0, 1, 3, 4, 6, 7, 8, 10, 11).
extern int unknown_tiberium_stage_7d2c10[9];

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

class CellClass : public AbstractClass {
public:
#ifdef RA2_SHIP_CELL_ACCESSORS
    // Native ShipProcess retains the address of MapCoords through the comparison.
    Cell const &Fetch_CellID() const { return MapCoords; }
    int Land_Type() const { return unknown_ec; }
#else
    Cell Fetch_CellID() const { return MapCoords; }
#endif

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
    bool unknown_47b5e0() const;                // 0x0047B5E0 (Westwood's Is_Tile_Cliff: a cliff, waterfall, ramp, cave or bridge tile)
    int unknown_47bfa0(int house);              // 0x0047BFA0 (-1 unless unknown_dc has the house bit, else the facings whose neighbour has it; BuildingClass 0x004512C6/0x004515A9)
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
    bool unknown_47c2e0(int house) const;       // 0x0047C2E0 (overlay)
    void unknown_476920(void const *arg1, bool arg2, bool arg3, bool alt);  // 0x00476920 (scatters the occupants; alt picks AltOccupierPtr; UnitClass slot 302)
    bool unknown_479cc0() const;                // 0x00479CC0 (Westwood's Has_Tunnel: a valid tube index and LAND_TUNNEL; UnitClass slot 27)
    // TibSun names. Not const in RA2: they reach Adjacent_Cell 0x00476AC0 directly, not
    // through the const wrapper (Is_Near_Tunnel_ES's inline expansions show the depth).
    bool Is_Near_Tunnel_NW();                   // 0x00479CF0
    bool Is_Near_Tunnel_ES();                   // 0x00479F70
    bool unknown_47a120(TechnoClass *techno) const;   // 0x0047A120 (UnitClass slot 27)
    void Set_House_Bit(int house);              // 0x0047C320
    void Clear_House_Bit(int house);            // 0x0047C340

    bool unknown_47ba10(int house) const;      // 0x0047BA10 (visible to the player's house; hypothesis)
    bool unknown_47cdd0() const;                // 0x0047CDD0 (land allows ...; no building, not blocked)
    Point2D unknown_475440() const;             // 0x00475440 (the overlay image offset in the cell; hypothesis)
    void unknown_4754b0(Point2D const &point, Rect const &rect);   // 0x004754B0 (draws IsoTileTypes[0] at point; Tactical 0x006A3641)
    void unknown_474830(Point2D const &point, Rect const &clip);   // 0x00474830 (Westwood's Draw_Overlay_Shadow: the overlay's shadow frame, or a rubble building's)
    void unknown_4749c0(Point2D const &point, Rect const &clip);   // 0x004749C0 (Westwood's Draw_Overlay: the overlay image at point within clip; not recovered; Tactical Draw_Overlays 0x006A7350)
    void Draw_Shroud_Or_Fog_Shape(Point2D const &point, Rect const &clip, int frame);  // 0x00474260 (TibSun name: SHROUD.SHP, or FOG.SHP with fog of war, into the depth buffer; its ebp frame and fast loop (cmp eax, [0x0079DAD0]) look like an __asm block, hypothesis)
    void Draw_Fog_Shape(Point2D const &point, Rect const &clip, int frame);  // 0x00474510 (TibSun name: FOG.SHP blended into the depth buffer)
    void Draw_Shroud_And_Fog(Point2D const &point, Rect const &clip);  // 0x00475520 (TibSun name; updates and draws the cell's shroud and fog frames; Tactical 0x006A3FA6)
    void unknown_4724a0();                      // 0x004724A0 (a wall overlay: +0x50 = owner of the nearest building of a WallOwner house)
    bool Is_Tile_Water() const;                 // 0x0047A270 (TibSun name hypothesis)
    int unknown_47a290() const;                 // 0x0047A290 (the height of the top of the cell: ground plus a building's height or 0x55 for an object at the spot)
    void unknown_47a160();                      // 0x0047A160 (slot 109 on up to ten occupants; units and aircraft get Force_New_Slope(+0x11C))
    void unknown_476b20(int house, int value);  // 0x00476B20 (every other house that is not an ally (or fails 0x004F52F0) gets unknown_func_4e5dc0(the cell's map block, value); TechnoClass 0x006D95A0/0x006D95D0)
    void unknown_47a4e0();                      // 0x0047A4E0 (redraws the cell's 60x30 screen area; BuildingClass 0x0043C1F0)
    int unknown_47a5a0();                       // 0x0047A5A0 (bit per cardinal neighbour holding veins: an IsVeins overlay, or overlay 0x7E with data from 48)
    bool unknown_475840(int overlay, int facing) const;   // 0x00475840 (whether a wall of overlay type joins this cell toward facing: the same wall, or a gate or wall tower; hypothesis)
    bool Can_Tiberium_Germinate(TiberiumClass *tiberium);   // 0x00478BA0 (TibSun name; tiberium unused: Spread_Tiberium 0x00478A40 passes its type, other callers 0; constness unknown)
    void unknown_473d20(ObjectClass *object, bool alt);   // 0x00473D20 (unlinks object from the occupier list; MapClass 0x0054B04D)
    Rect unknown_4752b0() const;                // 0x004752B0 (a screen rectangle of the cell's contents; hypothesis)
    Rect unknown_474eb0() const;                // 0x00474EB0 (another; hypothesis)
    Rect unknown_475100() const;                // 0x00475100 (another; hypothesis)
    unsigned int unknown_4788d0() const;        // 0x004788D0 (the under-bridge flag, bit 8 of +0x140; TeleportLocomotionClass 0x006DFF00 reads its address, not its value)
    bool unknown_4788e0() const;                // 0x004788E0 (the ore may grow here: scenario +0x222A, ore below its last stage; hypothesis)
    bool unknown_478950() const;                // 0x00478950 (the ore may spread from here; hypothesis)
    bool unknown_4789d0();                      // 0x004789D0 (grows the ore through unknown_47c3a0; hypothesis)
    bool unknown_47c3a0(int tiberium, int data);    // 0x0047C3A0 (not recovered; TibSun Place_Tiberium(tib, data): Spread_Tiberium 0x00478A40 passes 3)
    int unknown_47ce70() const;                 // 0x0047CE70 (+0xF0 limited to Rules RadLevelMax, as an int)
    bool unknown_47c200();                      // 0x0047C200 (the map allows the cell, its tile type does not refuse it, it is not blocked and holds no building or terrain object)
    void unknown_47bc80();                      // 0x0047BC80 (Westwood's Fog_Cell: fogs the diagonal cells, keeping fogged copies of their buildings)
    void unknown_47be00();                      // 0x0047BE00 (diagonal pass over the cells ahead)
    void unknown_47be60();                      // 0x0047BE60

    void unknown_47a340(AbstractClass *target);   // 0x0047A340 (forgets a target)
    void Set_unknown_3c(TagClass *tag);         // 0x0047A460

    // Tiberium (OverlayClass::To_Tiberium of the overlay).
    wchar_t const *unknown_47a200() const;      // 0x0047A200 (the tiberium's UI name)
    int Get_Tiberium_Type() const;              // 0x0047A220
    int Get_Tiberium_Value() const;             // 0x0047A230

    bool unknown_47cb50();                      // 0x0047CB50 (map call at the cell centre)
    void unknown_47cbb0();                      // 0x0047CBB0
    int unknown_475db0(int amount);             // 0x00475DB0 (takes up to amount of tiberium; answers what it took; hypothesis)
    int unknown_47c040();                       // 0x0047C040
    void unknown_47a7a0();                      // 0x0047A7A0

    // Counters and scalars.
    void unknown_47c840();                      // 0x0047C840 (decrements +0x130)
    void unknown_47c8a0();                      // 0x0047C8A0 (increments +0x130 up to +0x134)
    // Westwood's Init_Drawer: takes the drawer given, or finds or makes one for the cell's light (+0x34), and keeps the light values.
    // arg1 is the drawer (a LightConvertClass *; retyping it is a rename of the accepted callers' binding).
    void Init_Drawer(LightConvertClass *drawer, int intensity, int ambient, int brightness, int tile_brightness, int alt_brightness);   // 0x004790F0 (TerrainClass slots 67/68, DisplayClass 0x0049E570 pass no drawer)
#ifdef CELL_DECLARE_PREVIEW_CELL_COLOR
    // The cell's two preview pixel colours packed low << 16 | high (0x004710D0; TibSun
    // Preview_Cell_Color; declared only for the map preview unit 0x0061D240).
    unsigned int Preview_Cell_Color(unsigned char &unknown, bool flag);
#endif
#ifdef CELL_DECLARE_CLEAR_ICON
    // A variation index for a tile set of `count` variations, picked from the cell's position
    // (0x004767A0; TibSun Clear_Icon; declared only for IsometricTileTypeClass::Load_Tiles,
    // as this header is in Refresh_Wonline_Players 0x0073FEE0's closure).
    int Clear_Icon(int type, int count) const;
#endif
#ifdef CELL_DECLARE_DRAW_IT
    void unknown_47c930();                      // 0x0047C930 (TibSun On_Bridge_Collapse)
    void unknown_47cc10();                      // 0x0047CC10 (TibSun Kill_Illegal_Occupiers)
    // The cell's tile and smudge at the screen point, unless `objects` (0x00475680; TibSun Draw_It).
    void unknown_473b30(ObjectClass *object, bool alt);   // 0x00473B30 (TibSun Occupy_Down: links object into the occupier list)
    void Draw_It(Point2D const &point, Rect const &clip, bool objects);
    // The cell tile's cast shadow (0x004755D0; TibSun Draw_Shadow_Cast).
    void Draw_Shadow_Cast(Point2D const &point, Rect const &clip);
    inline void Fetch_Icon(class IsometricTileTypeClass *&ittype, int &subtile, int *icon, bool doicon) const;
#endif
#ifdef CELL_DECLARE_CELL_COLOR
    // The cell's low and high radar colours (0x004712C0; TibSun Cell_Color; guarded: this header is
    // in Refresh_Wonline_Players 0x0073FEE0's closure).
    void Cell_Color(class RGBClass &lowcolor, class RGBClass &highcolor) const;
#endif
    class BuildingClass *Get_Gate() const;   // Westwood's Get_Gate: the gate building in the cell, or 0 (inline in the Cell unit)
    CoordStruct Closest_Free_Spot(CoordStruct const &coord, bool any = false, bool alt = false) const;   // 0x004764B0 (the free sub-cell spot nearest coord, alt on the bridge; any: the nearest spot even if taken)
    void unknown_478f40();                      // 0x00478F40 (Westwood's Recalc_Passability: sets unknown_4c from the overlay, land and occupiers)
    void unknown_47bb30();                      // 0x0047BB30 (veins attack the occupants; hypothesis)
    int unknown_479ac0(CoordStruct const &origin) const;   // 0x00479AC0 (Westwood's Bounce_Direction: the facing to bounce toward from origin's cell)
    void Inc_Drawer_Ref_Count(LightConvertClass *drawer) const;   // 0x00479C90
    void Dec_Drawer_Ref_Count(LightConvertClass *drawer) const;   // 0x00479CA0
    // Westwood's Pick_Drawer and Init_Light (TibSun CELL.CPP order).
    void Pick_Drawer(LightConvertClass *&drawer, int &intensity, int &ambient, int &brightness, int &tile_brightness, int &alt_brightness) const;   // 0x00479310
    void unknown_4798f0();                      // 0x004798F0 (Westwood's Recalc_Light: the brightness values from the scenario light; DisplayClass 0x0049E5E0)
    void Init_Light(int &intensity, int &ambient, int &brightness, int &tile_brightness, int &alt_brightness, int &red, int &green, int &blue) const;   // 0x00479440
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
    bool Spread_Tiberium(bool forced);          // 0x00478A40 (TibSun name; TerrainClass::AI forces it, TiberiumClass::Process_Spread does not)
    void Set_Under_Bridge(unsigned facing, bool state);                  // 0x004732D0 (TibSun name: marks the cells one high-bridge deck piece covers; OverlayClass slot 71)
    void Set_Under_Rail_Bridge(unsigned facing, bool state);             // 0x00473700 (TibSun name: the train bridge counterpart; OverlayClass slot 71)
    void Destroy_Bridge();                                               // 0x00473000 (TibSun name hypothesis: called when a bridge flag is cleared)
    bool unknown_4718b0(int arg1, int arg2, int arg3);                   // 0x004718B0 (whether a wall may be placed; hypothesis)
#ifdef RA2_TACTICAL_PLACEMENT
    bool Draw_Placement_Cursor(Point2D const &pixel, Rect const &rect, bool drawtrans);   // 0x00473F20 (TibSun name)
#endif
    void unknown_475960(bool arg1);                                      // 0x00475960
    int unknown_476ba0(bool pregame);                                    // 0x00476BA0 (Westwood's Tiberium_Adjust: the ore stage from its neighbours; answers the value)
    void unknown_471d10();                      // 0x00471D10 (IsometricTileClass slot 71: after the tile changes; hypothesis)
    void Unknown_00472540(int value);           // 0x00472540 (clears an overlay with -1: AnimClass 0x004226D0, TerrainClass slot 52)
    int unknown_4706c0(Point2D const &point) const;       // 0x004706C0 (height at a lepton position in the cell; hypothesis)

    Cell MapCoords;                       // +0x024
    DynamicVectorClass<FoggedObjectClass *> *FoggedObjects;   // +0x028
    CellClass *unknown_2c;                      // +0x02C
    void *unknown_30;                           // +0x030
    LightConvertClass *unknown_34;              // +0x034 the tile drawer (Westwood's Drawer)
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
    Rect unknown_68;                            // +0x068 (Westwood's LastBridgeDrawRect)
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
    unsigned char unknown_118;                  // +0x118
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
    // +0x124 occupation flags (Westwood's Flag: the five sub-cell spots, then Vehicle, Monolith,
    // Building); +0x128 the same for the bridge (BridgeFlag). unknown_124/unknown_128 read them as a
    // byte (Westwood's Composite), Occupy_124/Occupy_128 bit by bit (Closest_Free_Spot 0x004764B0).
    union {
        unsigned char unknown_124;
        CellOccupyFlags Occupy_124;
    };
    union {
        unsigned char unknown_128;
        CellOccupyFlags Occupy_128;
    };
    union {                                     // +0x12C flags; bit 3 answers IGameMap::Is_Visible
        unsigned int unknown_12c;
        struct {
            unsigned Flags_12c:5;
        };
    };
    int unknown_130;                            // +0x130
    int unknown_134;                            // +0x134
    bool unknown_138;                           // +0x138
    int unknown_13c;                            // +0x13C
    union {                                     // +0x140 flags
        unsigned int unknown_140;
        struct {
            unsigned Flags_140:23;
        };
        struct {                                // TibSun names, from Set_Under_Bridge 0x004732D0
            unsigned :7;
            unsigned IsBridgeDeck:1;            // bit 7
            unsigned IsUnderBridge:1;           // bit 8
            unsigned IsBridgeTraversable:1;     // bit 9
            unsigned WasUnderBridge:1;          // bit 10
            unsigned IsBridgeEastWest:1;        // bit 11
            unsigned IsBridgeSurface:1;         // bit 12
            unsigned :3;
            unsigned IsOvershadowed:1;          // bit 16
        };
    };
    int unknown_144;                            // +0x144
};

#endif
