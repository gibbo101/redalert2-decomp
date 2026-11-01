// TerrainClass: a terrain object on the map (trees, rocks, veinholes;
// Terrain.cpp, members 0x006E3000-0x006E4B6D; RTTI vtables 0x007AD3CC
// primary (119 slots), 0x007AD3A0 IRTTITypeInfo at +4, 0x007AD3C4
// INoticeSink, 0x007AD3BC INoticeSource).
//
// Layout (from the constructors 0x006E33D0 and 0x006E3620 and the
// destructor 0x006E3000):
//   +0x000  ObjectClass (0x98)
//   +0x098  UnknownStage Animation   (shared/stage.hpp; hypothesis: the
//           animation stage of animated terrain)
//   +0x0B0  TerrainTypeClass *Class  (slot 33 returns it)
//   +0x0B4  bool unknown_b4, +0x0B5 bool unknown_b5
//   +0x0B8  Rect unknown_b8          (+0xC0/+0xC4 serve slot 73 as a draw
//           offset; hypothesis)
//   size 0xC8
// Every terrain object is in the list at 0x00A40940 and in the ID index at
// 0x00ABFF58 (shared/object_index.hpp).
#ifndef RA2_SHARED_TERRAIN_HPP
#define RA2_SHARED_TERRAIN_HPP

#include "shared/unknown_globals.hpp"
#include "shared/terrain_type.hpp"
#include "shared/stage.hpp"
#include "shared/rect.hpp"
#include "shared/map_cell_view.hpp"

extern "C" GUID const CLSID_TerrainClass;       // 0x007A1CB0

// The cell offsets of the eight facings (0x00851A70; Westwood's AdjacentCell)
// and the cell next to one toward a facing (the guard is shared with
// shared/display.hpp, shared/infantry.hpp and shared/aircraft.hpp; the cell
// sum is TPoint2D<short>::operator+, shared/point.hpp).
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    return cell + AdjacentCell[facing & 7];
}
#endif

// A cell's occupation flags as TechnoClass sees them (shared/techno.hpp's
// UnknownCellOccupy; this unit does not include it).
union TerrainCellOccupy {
    struct {
        unsigned Center : 1;
        unsigned NW : 1;
        unsigned NE : 1;
        unsigned SW : 1;
        unsigned SE : 1;
        unsigned Vehicle : 1;
        unsigned Monolith : 1;
        unsigned Building : 1;
    } Occupy;
    unsigned char Composite;
};
// The cell's occupation word at +0x124 (a view of CellClass).
struct TerrainCellView {
    char unknown_000[0x124];
    TerrainCellOccupy unknown_124;
};

class TerrainClass : public ObjectClass {
public:
    TerrainClass(TerrainTypeClass *type, Cell const &cell);       // 0x006E33D0
    TerrainClass();                                                     // 0x006E3620
    TerrainClass(NoInitClass const &noinit) : ObjectClass(noinit), Animation(noinit) {}   // inline (Load)
    virtual ~TerrainClass();                                            // 0x006E3000

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                   // 0x006E4B10 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_TerrainClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006E4570 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006E4700 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x006E47A0 slot 10
    virtual int Kind_Of() const { return 0x24; }                        // 0x006E4B00 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(TerrainClass); }        // 0x006E4AF0 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006E4720 slot 13
    virtual void AI();                                                  // 0x006E3F10 slot 23
    virtual ObjectTypeClass *Class_Of() const;                          // 0x006E4900 slot 33
    virtual bool unknown_slot52();                                       // 0x006E4120
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);     // 0x006E47D0
    virtual void unknown_slot58(CoordStruct const &coord);              // 0x006E38F0 (marks the occupation bits)
    virtual void unknown_slot59(CoordStruct const &coord);              // 0x006E3850 (clears them)
    virtual bool unknown_slot63(Rect *bounds, bool arg2, bool arg3);           // 0x006E4430
    virtual void unknown_slot67(int arg1, int arg2);                    // 0x006E3990
    virtual void unknown_slot68(int arg1, int arg2);                    // 0x006E3B40
    virtual bool unknown_slot71(int arg1);                              // 0x006E37E0
    virtual Rect unknown_slot73();                               // 0x006E4910
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6);   // 0x006E3170
    virtual bool unknown_slot88();                                      // 0x006E3D90
    virtual void unknown_slot89();                                      // 0x006E3E90
    virtual int unknown_slot101(CellClass *arg1, int arg2, int arg3, int arg4, bool arg5);   // 0x006E3CB0

    static void __fastcall Read_INI(CCINIClass &ini);                   // 0x006E4260 ([Terrain] entries)
    static void __fastcall Write_INI(CCINIClass &ini);                  // 0x006E4380
    void Start_Crumbling();                                             // 0x006E40D0 (name hypothesis)

    UnknownStage Animation;                 // +0x098
    TerrainTypeClass *Class;                // +0x0B0
    bool unknown_b4;                        // +0x0B4
    bool unknown_b5;                        // +0x0B5
    Rect unknown_b8;                        // +0x0B8 (its Width and Height, +0xC0 and +0xC4, hold the object's screen position: slot 53)
};

// Set while the map is loaded or edited (0x00A40774; hypothesis; also shared/smudge.hpp):
// cell refreshes are skipped while it is positive.
// The tactical area X, Y, width, height (0x00839630; shared/display.hpp), a
// counter the draw tests (0x00B263D8; shared/techno.hpp) and the flag that
// forces image reloads (0x00A40D13; shared/anim_type.hpp).
extern Rect unknown_rect_839630;
// The [Terrain] section name (a pointer variable at 0x007AD390).
extern char const *unknown_terrain_section_7ad390;
// The scenario INI format (0x00A40D24; below 4 cells are numbered x + y *
// 128, else x + y * 1000; hypothesis).

// The object index keyed by Fetch_ID (0x00ABFF58): shared/object_index.hpp
// (the Terrain unit's helper over it: shared/terrain_object_index.hpp).

// The list of terrain objects (0x00A40940; defined by the unit at 0x004D2BA0).
extern DynamicVectorClass<TerrainClass *> Terrains;

#endif
