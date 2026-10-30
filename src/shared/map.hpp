// MapClass: the cell map layer of the screen chain (Map.cpp, 0x00547930 to the
// template COMDATs before 0x0056CEF0; RTTI vtable 0x007A593C, 30 slots),
// derived from GScreenClass.
//
// Layout from the constructors 0x00547960 / 0x00547A60, the destructor
// 0x00547B90, One_Time 0x005480D0 and the cell accessors. Member vector types
// are the RTTI names of the vtables the constructors store:
//   +0x4C  DynamicVectorClass<ZoneConnectionClass>      0x007A59F8
//   +0x88  DynamicVectorClass<SubzoneTrackingStruct>[3] 0x007A59D8
//   +0xD0  DynamicVectorClass<Cell>                     0x0079C5A0
//   +0x134 VectorClass<CellClass *>                     0x007A59B8
//   +0x1158 DynamicVectorClass<Cell>                    0x0079C5A0
// RTTI's "Cell" is the 4-byte cell coordinate (shared/coord.hpp Cell:
// VectorClass<Cell>'s constructor allocates 4 bytes per element and runs an
// empty element constructor). Names are hypotheses unless stated; the TS
// MapSize / MapLocalSize naming of +0xE8 / +0xF8 is one too.
// Unrecovered members stay unknown_.
#ifndef RA2_SHARED_MAP_HPP
#define RA2_SHARED_MAP_HPP
#include "shared/zone_table.hpp"
#include "shared/unknown_globals.hpp"
#ifdef RA2_SHARED_MAP_VIEW_HPP
#error "shared/map_view.hpp declares light screen layers: include the full layer headers before it"
#endif

#include "shared/gscreen.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/cd_timer.hpp"

// CellClass: the Map units' stand-in is shared/map_cell.hpp (the real
// shared/cell.hpp brings abstract.hpp's header statics, which Map.cpp has
// not); the layer classes only need the declaration.
class AbstractClass;
class CellClass;
class HouseClass;
class ObjectClass;

// The cell returned for coordinates outside the map (0x00A6F9F8; its
// MapCoords are set to the requested cell). Defined in Map.cpp: dynamic
// initializer 0x00547930, atexit destructor 0x00547950.
extern CellClass unknown_dummy_cell_a6f9f8;

#include "shared/map_elements.hpp"
#include "shared/subzone_tracking.hpp"

// A hash table of HashObject buckets (16 bytes; built by MapClass::One_Time
// with 256 buckets, hash function 0x0054F240 and growth step 20; the
// destructor inlined into MapClass's frees the bucket array).
template <class K, class V>
class HashTableClass {
public:
    HashTableClass(unsigned (__fastcall *hash)(K const &key), int count, int growth)
        : Hash(hash), BucketCount(count), GrowthStep(growth)
    {
        Buckets = new DynamicVectorClass<HashObject<K, V> >[BucketCount];
        for (int index = 0; index < BucketCount; index++) {
            Buckets[index].Set_Growth_Step(growth);
        }
    }
    ~HashTableClass() { delete[] Buckets; }

    DynamicVectorClass<HashObject<K, V> > *Buckets;    // +0x00 BucketCount vectors
    unsigned (__fastcall *Hash)(K const &key);          // +0x04
    int BucketCount;                                    // +0x08
    int GrowthStep;                                     // +0x0C
};

// One of the 256 entries at +0x154 (16 bytes): a frame countdown and a cell.
// The constructors only clear the cell, so the timer is built uninitialized
// (hypothesis: CDTimerClass's NoInitClass form); Init_Clear stops it.
struct UnknownMapEntry154 {
    UnknownMapEntry154() : Timer(NoInitClass()), Cell(0, 0) {}
    // Removes the entry's crate from its cell and forgets the cell
    // (0x00493930; hypothesis: CrateClass::Remove_It).
    bool Unknown_00493930();
    // Places a crate at or near the cell (updated in place); false when none fits (0x004939A0; hypothesis: CrateClass::Create_Crate).
    bool Unknown_004939A0(::Cell &cell);
    CDTimerClass<FrameTimerClass> Timer;    // +0x00 (Started, Timer, DelayTime)
    ::Cell Cell;                        // +0x0C
};

// Hash of a cell key for the map's hash tables (0x0054F240).
unsigned __fastcall Unknown_Hash_0054F240(unsigned const &key);

// Called first by the destructor (no arguments; owners unknown).
void Unknown_00710B50();
void Unknown_00711C70();
void Unknown_006E9670();
void __fastcall Unknown_006EA130();  // tail-called by 0x00562EA0 (pop; jmp): __fastcall
// Called by MapClass slot 23 with (0, true) (0x00529710).
void __fastcall Unknown_00529710(int unknown1, bool unknown2);

// Used by MapClass::Init_Clear (owners unknown).
#include "shared/debug_printf.hpp"
void unknown_481fb0();                                  // 0x00481FB0 (shared/ms_engine.hpp)
class Unknown839C6C {
public:
    void Unknown_00776160(int value);                   // 0x00776160 (called with 0xFFFF)
};
extern Unknown839C6C *unknown_839c6c;                   // 0x00839C6C
class Unknown8315B4 {
public:
    void Unknown_00411050(int value);                   // 0x00411050 (called with 0x7F)
};
extern Unknown8315B4 *unknown_8315b4;                   // 0x008315B4
extern Cell unknown_cell_a6f238;                  // 0x00A6F238 copied into every +0x154 entry
// The crates option byte (unknown_flag_a3d2c1, 0x00A3D2C1) is in shared/unknown_globals.hpp.

// A 4-byte element of the array at MapClass +0x64 (unknown_68 elements;
// the load fills it with the constructor's values before reading).
struct UnknownMapElem4 {
    UnknownMapElem4() : unknown_00(7), unknown_01(0) {}
    unsigned char unknown_00;
    unsigned char unknown_01;
    unsigned short unknown_02;      // +0x02 (read by 0x0054FA60)
};

// The zone table 0x007E00C4 and Unknown_0056A900: shared/zone_table.hpp.

// Whether a cell's overlay is in 0x4A..0x65 (0x00562930) or in 0xCD..0xE8
// (0x00562980); the cell of the global Map (two overlay ranges; hypothesis).
int __fastcall Unknown_00562930(Cell const &cell);
int __fastcall Unknown_00562980(Cell const &cell);

// Tile set start indices: shared/tileset_index.hpp (the tile tests
// 0x0055AF60 and 0x0055AF80).
#include "shared/tileset_index.hpp"
// Whether a tile is one of the 42 of the tile set at 0x00A6CB74 (0x0055AF60).
bool __fastcall Unknown_0055AF60(int tile);
// Whether a tile is passable in direction kind: the sets at 0x00A52E68 (40)
// and 0x00A6DD00 (20) always, the four-tile sets at 0x00A52584, 0x00A6CF58,
// 0x00A52EA0 and 0x00A52EF0 except their first and last tile for two of the
// four kinds each (0x0055AF80).
bool __fastcall Unknown_0055AF80(int tile, int kind);
// Flags from the overlays of a cell's X - 1 and X + 1 neighbours (of the
// global Map): 1 or 2 by the right one, 4 or 8 added by the left one
// (0x0055DA70).
int __fastcall Unknown_0055DA70(Cell const &cell);
// The same for the Y - 1 and Y + 1 neighbours and two other overlay sets
// (0x0055DB90, 0x0055ECA0).
int __fastcall Unknown_0055DB90(Cell const &cell);
int __fastcall Unknown_0055EB70(Cell const &cell);      // 0x0055EB70 (as 0x0055DA70, other overlays)
int __fastcall Unknown_0055ECA0(Cell const &cell);
// Whether a tile is a bridge piece of kind 2 (cell +0x11A 4) or kind 4 (+0x11A 2) (0x00556B30).
bool __fastcall Unknown_00556B30(int tile, int kind, CellClass const *cell);

class MapClass : public GScreenClass {
public:
    MapClass();                                                                 // 0x00547960
    MapClass(NoInitClass const &noinit);                                        // 0x00547A60
    // A cell test with a flag (0x0055A660; radar 0x00630340 passes true).
    bool Unknown_0055A660(Cell const &cell, bool flag);
    void Unknown_0055D990(Cell const &cell);      // 0x0055D990
    void Unknown_00562F50(CellClass *cell); // 00562F50: observed thiscall/RET4; unused return hypothesis
    CellClass *Unknown_005629D0(AbstractClass *object);                         // 0x005629D0 (the cell under an object; hypothesis)
    bool Unknown_0054AAB0(Cell const &cell);      // 0x0054AAB0 (a cell test: on the map; hypothesis)
    bool Unknown_0054AB00(CoordStruct const &coord);    // 0x0054AB00 (a coordinate test; InfantryClass 0x005070E0 tests al)
    // The +0x02 value of the cell's +0x64 element (0x0054FA60); the cell's
    // index in that array, clamped to it (0x0054FAB0), and unclamped
    // (0x0054FAF0): Y * (width + height + 1) + X.
    int Unknown_0054FA60(Cell const &cell);
    int Unknown_0054FAB0(Cell const &cell);
    int Unknown_0054FAF0(Cell const &cell);
    // The house's +0x56D0 value for the 4 x 4 block of a cell (0x0054E3A0;
    // the block index is 0x0054E370's).
    int Unknown_0054E3A0(Cell const &cell, HouseClass *house);
    // Redraws a cell whose shroud changed (0x00568520; DisplayClass slot 37 passes the
    // cell, its second argument and whether the cell was already mapped; hypothesis).
    void Unknown_00568520(CellClass *cell, HouseClass *house, bool arg3);
    // Reveals the map around coord for house (0x0054A110; hypothesis:
    // Westwood's Sight_From; the meaning of the last five arguments is
    // unknown).
    void Sight_From(CoordStruct const &coord, int sight, HouseClass *house, bool arg4, bool arg5, int arg6, bool arg7, int arg8);
    void Unknown_00549C50(CoordStruct const &coord, int sight, HouseClass *house, bool arg4, bool arg5, bool arg6, bool arg7, bool arg8);   // 0x00549C50 (reveals around coord; TechnoClass slot 70)
    unsigned int Unknown_0055BD70(CellClass *cell); // physical full-EAX mask/RET4; Map receiver/source intent hypotheses
    unsigned char Unknown_0055C2C0(int first, int second); // physical AL-only/RET8; signedness/source intent hypotheses
    void Unknown_00559F10();                                              // 0x00559F10
    void Unknown_0054AB70(Cell const &cell, ObjectClass *object);   // 0x0054AB70 (FootClass slot 71, cases 1 and 3; hypothesis: occupation)
    void Unknown_0054AF70(Cell const &cell, ObjectClass *object);   // 0x0054AF70 (FootClass slot 71, case 0)
    bool Unknown_0054F7C0(Cell const &from, Cell const &to, int zone, bool arg4, bool bridge, bool arg6);  // 0x0054F7C0 (a path test; FootClass slot 171)
    int Zone(Cell const &cell, int zone_type, bool alt); // 0x0054F8F0 (the cell's movement zone; hypothesis)
    void Unknown_0054FB20(Cell const &cell);      // 0x0054FB20 (after a tiberium cell is cleared; AnimClass)
    int Unknown_0055A280(CoordStruct const &coord);     // 0x0055A280 (ground height; hypothesis)
    int Cell_To_Local_Sector_Index(Cell const &cell);   // 0x0055AD70 (the local view sector 1-9 of a cell)
    Cell Clip_To_Map(Cell const &cell);                 // 0x00568D60 (a cell moved into the local view)
    Cell Local_Sector_Index_To_Cell(int index);         // 0x0055AE50 (a sector's cell)
    bool Unknown_0055A740(CellClass *cell, bool flag);  // 0x0055A740 (AircraftClass slot 101; 0x0055A660 for a cell object, flag read as a byte)
    // The cell test 0x0055A660 (with true) for the cell of a lepton position
    // (0x0055A7F0; FootClass slot 282 and others).
    bool Unknown_0055A7F0(CoordStruct const &coord);
    void Unknown_0055ACC0();                            // 0x0055ACC0 increments unknown_1154 (GScreenClass::Flag_To_Redraw)
    void Unknown_0054FC60(Cell const &cell);      // 0x0054FC60
    void Unknown_00566340(Cell const &cell);      // 0x00566340
    bool Unknown_005683C0(CoordStruct const &coord);                            // 0x005683C0 (Tunnel.cpp)
    bool Unknown_00568140(CoordStruct const &coord);    // 0x00568140 (AircraftClass slot 101)
    bool Unknown_00568280(CoordStruct const &coord);    // 0x00568280 (as 0x00568140 for the cells' +0x13C; RadarClass)
    void Unknown_0054A550(CoordStruct const &coord, int arg2, int arg3, int arg4);   // 0x0054A550 (InfantryClass slot 93)
    // The index of a cell's 4 x 4 block in a 130 x 130 grid with a one-block
    // border, the layout of HouseClass +0x56D0 (0x0054E370; FootClass slot 93).
    int Unknown_0054E370(Cell const &cell);
    // A reachable cell near `cell` for a speed type and zone (0x005502E0;
    // hypothesis: Westwood's Nearby_Location; FootClass 0x004CCA40). `size` is
    // a Point2D by value (width, height): callers build it in a register pair,
    // the second a copy of the first (UnitClass slot 87 0x007072D0).
    Cell Unknown_005502E0(Cell const &cell, int speed, int zone_index, int zone, bool bridge, Point2D size, int arg8, int arg9, int arg10, int arg11, Cell const &arg12, int arg13);
    void Unknown_00552570(Cell const &cell);      // 0x00552570 (repairs the bridge at a cell; InfantryClass slot 93)
    void Unknown_00555A60(Cell const &cell);      // 0x00555A60 (the other bridge kind)
    Cell Unknown_00568ED0(Cell const &cell, Cell const &from);   // 0x00568ED0 (FootClass 0x004C4C30)
    bool Unknown_00569320(Cell const &cell);      // 0x00569320 (a bridge hut's bridge is intact; InfantryClass slot 28; hypothesis)
    // A walk over the map's cells: restart (0x0055A550) and next cell, or
    // null at the end (0x0055A490).
    void Unknown_0055A550();
    CellClass *Unknown_0055A490();
    bool Unknown_00569090(Cell *cell);              // 0x00569090 (whether a cell can be scrolled to; hypothesis)
    bool Unknown_0054E580(Cell cell, int arg2);     // 0x0054E580
    void Unknown_00559FD0();                        // 0x00559FD0
    // Lets every cell refresh (0x0047C8A0) and clears the visibility bits of
    // those with +0x130 not negative, then the 0x00559FD0 tail (0x0055A070).
    void Unknown_0055A070();
    // Once per game (player +0x188 clear): covers every cell of the global
    // Map (visibility bits set, +0x130/+0x134 cleared) between DisplayClass
    // 0x0049E000 and 0x0049DE00, and redraws (0x0055A120).
    void Unknown_0055A120();
    // Once per game (player +0x188 clear): passes every cell of the global Map
    // with the player to DisplayClass slot 39, then redraws (0x0055A1F0).
    void Unknown_0055A1F0();
    // Whether all four corner cells of a cell rectangle pass 0x0055A660
    // (0x0055A590).
    bool Unknown_0055A590(Rect const &rect, bool flag);
    // The test of 0x0055A660 against a given rectangle instead of the local
    // map rectangle (0x0055A840).
    bool Unknown_0055A840(Rect const &rect, Cell const &cell, bool flag);
    // Rebuilds the three subzone tracking vectors (each cleared, then
    // 0x00563D80 with its index, from 2 down) and resets the path estimator
    // (0x00563D40).
    void Unknown_00563D40();
    void Unknown_00567380();                            // 0x00567380 (TibSun Initialize_Wall_Ownership)
    void Unknown_00563D80(int index);                   // 0x00563D80
    // Runs 0x00564B60 with arg on every zone connection whose +0x08 is set
    // (0x00564B20).
    void Unknown_00564B20(int arg);
    void Unknown_00564B60(ZoneConnectionClass *connection, int arg);   // 0x00564B60
    // Lowers +0x144 to value, not below 0 (0x0056A870).
    void Unknown_0056A870(int value);
    // From +0x144 13 or more: lowers +0x144 (0x0056A870) to every cell's
    // +0x11B; returns +0x144 (0x0056A8A0).
    int Unknown_0056A8A0();
    // Runs CellClass 0x0047BC80 on every cell without +0x140 bit 1
    // (0x005685F0) and CellClass 0x0047BE00 on every cell (0x00568650).
    void Unknown_005685F0();
    void Unknown_00568650();
    // Whether any cell within radius of a cell (a square) has an occupier
    // (0x005680A0).
    bool Unknown_005680A0(Cell const &cell, int radius);
    // Whether every cell of a cell rectangle has +0x4C 3 or 4 (0x00565E20).
    bool Unknown_00565E20(Rect const &rect);
    // Collects the cells of a cell rectangle (column by column) and passes
    // them to 0x005688A0 (0x005687B0).
    void Unknown_005687B0(Rect const &rect);
    // Whether a cell rectangle is free for the house: no terrain, no house
    // bit in +0xDC, no overlay, +0x4C and +0x11C clear, no building, and all
    // four corners inside the local map (0x0055A590) (0x005686B0).
    bool Unknown_005686B0(Rect const &rect, int house);
    // The first zone connection from start on whose unset (+0x0C 0)
    // straight segment passes within distance of a cell, or -1 (0x005500D0).
    int Unknown_005500D0(Cell const &cell, int distance, int start);
    void Unknown_0054FDA0();                                    // 0x0054FDA0
    void Unknown_00566C30(ZoneConnectionClass *connection);     // 0x00566C30
    // Runs 0x00566C30 on (and clears +0x08 of) every flagged connection
    // within 3 of a cell, rebuilding (0x0054FDA0) once when none is found;
    // whether any was flagged (0x005501A0).
    bool Unknown_005501A0(Cell const &cell);
    // Flags every unflagged connection within 3 of a cell (+0x08 set,
    // 0x00566F90) and tests its path (0x0054F7C0); whether any path failed
    // (0x00550230).
    bool Unknown_00550230(Cell const &cell);
    // Whether every cell of a width x height block from a cell can be
    // entered (CellClass 0x00478760 with the movement arguments) and, with
    // the last flag, has no overlay (0x00550CF0).
    bool Unknown_00550CF0(Cell const &cell, int width, int height, int speed, int arg5, int arg6, int arg7, bool arg8, bool no_overlay);
    void Unknown_00566F90(ZoneConnectionClass *connection);     // 0x00566F90
    void Unknown_005688A0(DynamicVectorClass<Cell> &cells);    // 0x005688A0
    // Rebuilds the zone data for the map size: the +0x64 and +0x6C arrays
    // ((width + height + 1) squared elements), the path estimator's size,
    // the subzone vectors' growth steps, 0x0054B2E0, 0x0054FDA0, 0x0054EBD0
    // and the subzone tracking (0x00563D40, expanded inline) (0x005499C0).
    void Unknown_005499C0();
    // The next cell of the walk over the local map rectangle kept in
    // +0x118/+0x11C that passes 0x0055A660, or null at its end (0x0055A910).
    CellClass *Unknown_0055A910();
    void Unknown_0054B2E0();                                    // 0x0054B2E0
    void Unknown_0054EBD0();                                    // 0x0054EBD0
    virtual ~MapClass();                                                        // 0x00547B90 (??_G 0x0056A9D0)

    virtual long __stdcall Is_Visible(Cell cell);                         // slot 3 0x00547FA0
    virtual void One_Time();                                                    // slot 5 0x005480D0
    virtual void Init_Clear();                                                  // slot 7 0x005482C0
    virtual void unknown_slot22();                                              // slot 22 0x00548370
    virtual void unknown_slot23();                                              // slot 23 0x005483D0
    virtual void unknown_slot24();                                              // slot 24 0x00548490
    // Forgets a target (0x00559D80, slot 25, RET 8): for a tag (kind 0x2C)
    // the cells of +0x1158 carrying it lose it and leave the list, the dummy
    // cell forgets it (0x0047A340) and it leaves the tag list 0x00866238.
    virtual void Detach(AbstractClass *target, bool all);
    virtual bool unknown_slot26() { return false; }                             // slot 26 0x0049ED10 (kept in Display.CPP)
    // Every frame: each +0x154 entry with a cell whose countdown ran out is
    // removed and a new one placed (0x0054E410), outside the campaign when
    // the 0x00A3D2C1 option is on (0x0054E300; hypothesis: Logic for crates).
    virtual void unknown_slot27();                                              // slot 27 0x0054E300
    // Places a new +0x154 entry on a random cell (0x0054E410; hypothesis:
    // Place_Random_Crate).
    bool Unknown_0054E410();
    virtual void unknown_slot28(Rect const *rect, bool arg2, bool arg3, bool arg4);   // slot 28 0x005484E0 (callee pops 4 arguments, ret 0x10)
    virtual void unknown_slot29(Rect const &rect);                                      // slot 29 0x00549AE0 (sets the map size; hypothesis)

    // Cell at coord (leptons, 256 per cell), or the dummy cell when off map.
    CoordStruct Unknown_00569FB0(CoordStruct const &from, CoordStruct const &to, HouseClass *house); // owner0200Z, observed hidden-result thiscall
    CellClass &operator[](CoordStruct const &coord);                            // 0x00548000
    // Cell at cell, or the dummy cell when outside the 512 x 512 index range.
    CellClass &operator[](Cell const &cell);                              // 0x00548070
    // Whether the cell slot is filled (no range check).
    bool Has_Cell(Cell const &cell);                                      // 0x005480B0

    // Isometric coordinate transforms between map and rectangle space
    // (names unknown; the out-of-line copies 0x00547D40, 0x00547DB0,
    // 0x00547E50, 0x00547E90 and 0x00547EE0 have no direct callers).
    Point2D Unknown_00547D40(Point2D const &point);
    Point2D Unknown_00547D70(Point2D const &point);    // 0x00547D40 after adding +0xF8/+0xFC
    Point2D Unknown_00547DB0(Point2D const &point);    // inverse of 0x00547D40
    Point2D Unknown_00547DF0(Point2D const &point);    // 0x00547DB0, then less +0xF8/+0xFC
    Cell Unknown_00547E50(Cell const &cell);
    void Unknown_00562EA0();                // 0x00562EA0 (frees the twelve unknown_18 blocks; Prog_End)
    Cell Unknown_00547E90(Cell const &cell);
    Cell Unknown_00547EE0(Cell const &cell);
    Cell Unknown_00547F30(Cell const &cell);

    bool unknown_10;                                            // +0x10
    HashTableClass<unsigned int, unsigned int> *unknown_14;     // +0x14 (One_Time)
    void *unknown_18[12];                                       // +0x18 cleared by One_Time; freed and refilled by the load
    int unknown_48;                                             // +0x48
    DynamicVectorClass<ZoneConnectionClass> ZoneConnections;    // +0x4C
    UnknownMapElem4 *unknown_64;                                // +0x64 freed by the destructor
    int unknown_68;                                             // +0x68
    char *unknown_6c;                                           // +0x6C freed by the destructor
    int unknown_70[3];                                          // +0x70 entry counts of the path estimator's three layer arrays (0x00427E90, 0x00429A90)
    HashTableClass<unsigned int, SubzoneConnectionStruct> *unknown_7c[3];      // +0x7C (One_Time)
    DynamicVectorClass<SubzoneTrackingStruct> SubzoneTracking[3];              // +0x88
    DynamicVectorClass<Cell> unknown_d0;                  // +0xD0
    Rect MapSize;                                               // +0xE8 (Width +0xF0)
    Rect MapLocalSize;                                          // +0xF8 (X +0xF8, Y +0xFC)
    // The state of the cell walk 0x0055A550 / 0x0055A490: the current cell's
    // X and Y, the cells left in its diagonal row and its slot in Cells.
    int unknown_108;                                            // +0x108
    int unknown_10c;                                            // +0x10C
    int unknown_110;                                            // +0x110
    CellClass **unknown_114;                                    // +0x114
    int unknown_118;                                            // +0x118 X of the second cell walk (0x0055A910)
    int unknown_11c;                                            // +0x11C Y
    int unknown_120;                                            // +0x120 (0x00832600) the map's first cell X (hypothesis: MapCellX)
    int unknown_124;                                            // +0x124 the first cell Y
    int unknown_128;                                            // +0x128 the width in cells
    int unknown_12c;                                            // +0x12C the height in cells
    int unknown_130;                                            // +0x130
    VectorClass<CellClass *> Cells;                             // +0x134 indexed Y * 512 + X
    int unknown_144;                                            // +0x144 13 after construction
    int MapCellWidth;                                           // +0x148 512 (One_Time)
    int MapCellHeight;                                          // +0x14C 512
    int MapCellTotal;                                           // +0x150 0x40000
    UnknownMapEntry154 unknown_154[256];                        // +0x154
    bool unknown_1154;                                          // +0x1154 counted up by 0x0055ACC0
    DynamicVectorClass<Cell> unknown_1158;                // +0x1158
};

#endif
