// FootClass: TechnoClass with movement (Foot.cpp, 0x004C26C0-0x004CEC1F;
// RTTI vtables 0x007A12A0 primary (310 slots), 0x007A1284 IRTTITypeInfo
// at +4, 0x007A127C INoticeSink, 0x007A1274 INoticeSource). Abstract.
//
// Layout (constructor 0x004C2930, NoInitClass constructor 0x004C2C60,
// destructor 0x004C2CB0; names are hypotheses):
//   +0x000  TechnoClass (0x418)
//   +0x418  int (-1), +0x41C..+0x422 shorts, +0x428..+0x438 ints/bool
//   +0x43C  UnknownAudioController (initialized by the constructor body)
//   +0x450..+0x45A shorts, +0x45C..+0x464 ints
//   +0x468  double unknown_468 (0; slot 306 clamps it to 0..1)
//   +0x470  double unknown_470 (1)
//   +0x478, +0x49C  DynamicVectorClass<AbstractClass *> (VectorClass
//           constructor out of line, 0x004CEB90)
//   +0x4B4  int (-1), ... +0x4C4 TeamClass *Team (the destructor removes
//           the unit from it), +0x4D0 int (-1)
//   +0x4D4..+0x52F  not touched by the constructors
//   +0x530, +0x540, +0x54C, +0x558  frame timers (+0x53C int 10)
//   +0x564  the locomotor (a COM interface released by the destructor)
//   +0x568  CoordStruct (the unit's zero coordinate)
//   +0x574  byte 0xFF, +0x575 signed byte, +0x576..+0x57E bools, +0x580..+0x588 ints
//           (+0x588 an owned object deleted by the destructor)
//   +0x58C  frame timer, +0x598..+0x5A2 bools (+0x5A0 true)
//   size 0x5A4 (hypothesis)
// Every foot is added to the unit's FootClass list (0x00865F38) and to the
// list at 0x00AC0C18, and removed from both when destroyed.
#ifndef RA2_SHARED_FOOT_HPP
#define RA2_SHARED_FOOT_HPP

#include "shared/unknown_globals.hpp"
#include "shared/vox_class.hpp"
#include "shared/techno.hpp"
#include "shared/com_ptr.hpp"
#include "shared/ilocomotion.hpp"

class FootClass;
class ParasiteClass;
class TeamTypeClass;

// An object at 0x00839EA0 told when a unit leaves a cell (FootClass slot 52;
// hypothesis).
struct Point2D;
struct UnknownTracker839EA0 {
    void Unknown_004128A0(CellClass *cell, int radius); // original4128A0, thiscall/RET8

    ~UnknownTracker839EA0();
    // Known spatial-vector prefix:400 bins at stride18h, then a query working list.
    // Original base-vector RTTI79A7FC is VectorClass<TechnoClass *>; the 0x2598-byte global ends at83C438. Owner name remains a hypothesis.
    DynamicVectorClass<TechnoClass *> Bins[400];
    DynamicVectorClass<TechnoClass *> Working; // +2580; ActiveCount+2590
    void Append_Bin_00412720(int index);
    int Shift_Bin_004127a0(int index, Point2D offset);
    int Region_Index_00412820(Cell cell); // native128-byte unreferenced out-of-line copy
    long Load_00413400(IStream *stream);
    TechnoClass *Fetch_Next_004134e0();
    void Clear_00413540();
    long Save_00413590(IStream *stream);


    void Unknown_00413310(TechnoClass *foot);    // 0x00413310
    // Drops a detached infantry, unit or aircraft (0x004131D0; Detach_This_From_All).
    void Unknown_004131D0(AbstractClass *target);
    void Unknown_004131E0(FootClass *foot);    // 0x004131E0 (a unit arrives; FootClass slot 53)
    bool Unknown_004132E0(FootClass *foot);    // 0x004132E0
    void Unknown_00413600(TechnoClass *foot, Cell from, Cell to);    // 0x00413600 (a unit moves from one cell to another)
};
extern UnknownTracker839EA0 unknown_tracker_839ea0;
// An object found by cell (0x00710160 searches the list at 0x00AD074C for
// one whose cell, +0xE0, matches; FootClass slot 77; hypothesis).
struct UnknownCellObject710160 {
    char unknown_00[0x6C];
    int unknown_6c;                     // +0x6C
    char unknown_70[0xE8 - 0x70];
    bool unknown_e8;                    // +0xE8
};
UnknownCellObject710160 *__fastcall Unknown_00710160(Cell const &cell);  // 0x00710160

// The tunnels FootClass +0x574 indexes (TubeClass, 0x008661C8).
#include "shared/tube.hpp"

// Announcements by name ("EVA_UnitSold", "EVA_UnitLost") go through
// Speech_Play_Name (shared/vox_class.hpp).
// Raises an event of a kind at a cell: shared/radar_event.hpp.
#include "shared/radar_event.hpp"

// The team a unit belongs to: shared/team.hpp.
#include "shared/team.hpp"

// A COM interface pointer released when destroyed (hypothesis: the
// locomotor, ILocomotionPtr); the loading constructor clears it as well.
class UnknownInterfacePtr {
public:
    UnknownInterfacePtr() : Pointer(0) {}
    // _com_ptr_t-style raw access and assignment (UnitClass::Load restores
    // the pointer around the loading constructor).
    operator IUnknown *() const { return Pointer; }
    UnknownInterfacePtr &operator=(IUnknown *pointer)
    {
        if (Pointer != pointer) {
            IUnknown *old = Pointer;
            Pointer = pointer;
            if (Pointer != 0) {
                Pointer->AddRef();
            }
            if (old != 0) {
                old->Release();
            }
        }
        return *this;
    }
    ~UnknownInterfacePtr()
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
    }
    IUnknown *Pointer;
};

class FootClass : public TechnoClass {
public:
    FootClass(HouseClass *house);                               // 0x004C2930
    FootClass(NoInitClass const &noinit);                       // 0x004C2C60
    virtual ~FootClass();                                       // 0x004C2CB0

    virtual HRESULT __stdcall Load(IStream *stream);            // slot 5 0x004C9D10
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // slot 6 0x004C9FE0
    virtual void Detach(AbstractClass *target, bool all = true);    // slot 10 0x004C8460
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // slot 13 0x004CA3D0
    virtual bool unknown_slot21() const;                        // slot 21 0x004CCE70 (ObjectClass's)
    virtual bool unknown_slot47() { return unknown_5a0; }       // slot 47 (kept copy 0x0041B470)
    virtual Cell unknown_slot178() { return unknown_458; }    // slot 178 (kept copy 0x0041B550)
    virtual void unknown_slot179(Cell cell) { unknown_458 = cell; }   // slot 179 (kept copy 0x0041B560)
    virtual int unknown_slot29() const;                         // slot 29 0x004CA130 (ILocomotion::Layer)
    virtual void unknown_slot103(CoordStruct const &coord);     // slot 103 0x004CA160
    virtual bool unknown_slot154();                             // slot 154 0x004CA6A0
    virtual int unknown_slot177();                              // slot 177 0x004C9A10 (ILocomotion::Z_Gradient)
    virtual bool unknown_slot77(int arg1, int arg2, int arg3, bool arg4);    // slot 77 0x004C69F0
    virtual int unknown_slot126();                              // slot 126 0x004C44C0
    virtual int unknown_slot130();                              // slot 130 0x004C5900
    virtual int unknown_slot137();                              // slot 137 0x004C8D70 (MissionClass's)
    virtual bool unknown_slot202();                             // slot 202 0x004CD080 (timer +0x58C running)
    virtual void unknown_slot216(int arg1);                              // slot 216 (TechnoClass pure; FootClass defines it)
    virtual AbstractClass *unknown_slot219(int arg1, CoordStruct const *coord, bool arg3);  // slot 219 0x004C8420
    virtual void unknown_slot259(int arg1);                     // slot 259 0x004C8020
    virtual void unknown_slot119(int mission, int unknown2, int unknown3);  // slot 119 0x004C7AC0
    virtual bool unknown_slot120();                             // slot 120 0x004C7B00
    virtual bool unknown_slot189();                             // slot 189 0x004C8CA0
    virtual void unknown_slot210();                             // slot 210 0x004C4C00
    virtual bool unknown_slot279();                             // slot 279 0x004CDD70

    // Further overrides (entries of the FootClass vtable inside Foot.cpp;
    // base-class signatures, bodies not yet recovered).
    virtual CoordStruct unknown_slot19(TechnoClass *techno) const;  // slot 19 0x004CA6F0
    virtual void AI();  // slot 23 0x004C8FF0
    virtual int unknown_slot25(bool arg1, int arg2);  // slot 25 0x004C8FA0
    virtual void *unknown_slot26();  // slot 26 0x004CD650
    virtual int unknown_slot27(Cell const *cell, bool arg2, bool arg3);  // slot 27 0x004CC650
    virtual int unknown_slot28(ObjectClass *object, bool arg2);  // slot 28 0x004CC740
    virtual bool unknown_slot37();  // slot 37 0x004C8940
    virtual bool unknown_slot46(int arg1);  // slot 46 0x004CC4B0
    virtual bool unknown_slot52();  // slot 52 0x004C9BD0
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);  // slot 53 0x004C5E40
    virtual void unknown_slot54(bool arg1);  // slot 54 0x004C8220
    virtual void unknown_slot60();  // slot 60 0x004CCE40
    virtual void unknown_slot67(int arg1, int arg2);  // slot 67 0x004C9BC0
    virtual bool unknown_slot71(int arg1);  // slot 71 0x004C2E60
    virtual bool unknown_slot78(int arg1, int arg2, bool arg3);  // slot 78 0x004C61A0
    virtual void unknown_slot82(int arg1);  // slot 82 0x004CD3F0
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6);  // slot 86 0x004C6000
    virtual void unknown_slot93(int arg1);  // slot 93 0x004C7220
    virtual int unknown_slot95(RadioClass *radio, int message, long &param);  // slot 95 0x004C7B30
    virtual void unknown_slot98(int arg1);  // slot 98 0x004C8A40
    virtual void unknown_slot99(int path, char waypoint);  // slot 99 0x004CB060
    virtual int unknown_slot101(CellClass *arg1, int arg2, int arg3, int arg4, bool arg5);  // slot 101 0x004C86E0
    virtual int unknown_slot102(UnknownCellClass *from, int facing, int *level, bool *ramp, UnknownCellClass *to);  // slot 102 0x004C8730
    virtual int unknown_slot127();  // slot 127 0x004C41E0
    virtual int unknown_slot128();  // slot 128 0x004C4370
    virtual int unknown_slot129();  // slot 129 0x004C4660
    virtual int unknown_slot132();  // slot 132 0x004C48E0
    virtual int unknown_slot133();  // slot 133 0x004C38D0
    virtual int unknown_slot134();  // slot 134 0x004C8D80
    virtual int unknown_slot138();  // slot 138 0x004C7E10
    virtual int unknown_slot144();  // slot 144 0x004CC800
    virtual int unknown_slot145();  // slot 145 0x004C3950
    virtual bool unknown_slot169(AbstractClass *target);  // slot 169 0x004CA350
    virtual bool unknown_slot171(CoordStruct const &coord);  // slot 171 0x004C2EF0
    virtual int unknown_slot176();  // slot 176 0x004C9930
    virtual void unknown_slot194();  // slot 194 0x004CCDF0
    virtual bool unknown_slot222(HouseClass *house, int arg2);  // slot 222 0x004CA7D0
    virtual bool unknown_slot224(int arg1);  // slot 224 0x004CD4B0
    virtual CoordStruct unknown_slot241();  // slot 241 0x004C71B0
    virtual void unknown_slot243(bool arg1, int arg2);  // slot 243 0x004CA8B0
    virtual void unknown_slot246(UnknownObjectPair const &voxel, int frame, int key, UnknownBuffer *cache, Rect const &cliprect, Point2D const &draw_point, Matrix3D const &transform, int brightness, unsigned flags);  // slot 246 0x004C9880
    virtual void unknown_slot260(AbstractClass *target, int arg2);  // slot 260 0x004C8030
    virtual bool unknown_slot261(bool arg1, bool arg2);  // slot 261 0x004C6F10
    virtual int unknown_slot268(UnknownSlot268Arg const *arg);  // slot 268 0x004CD9C0
    virtual void unknown_slot269();  // slot 269 0x004CDA80
    virtual bool unknown_slot270();  // slot 270 0x004CDAA0
    virtual bool unknown_slot271();  // slot 271 0x004CDAB0
    virtual int unknown_slot272();  // slot 272 0x004CDAC0
    virtual CoordStruct unknown_slot273();  // slot 273 0x004CDAD0
    virtual bool unknown_slot276();  // slot 276 0x004CDBD0
    virtual bool unknown_slot277();  // slot 277 0x004CDBE0
    virtual void unknown_slot278();  // slot 278 0x004CDC60

    // New virtuals (slots 280-309); placeholder signatures except where a
    // body is recovered.
    virtual void unknown_slot280(int arg1);                     // slot 280 0x004CD060 (ret 4)
    virtual void unknown_slot281(int arg1);                     // slot 281 0x004CD070 (ret 4)
    virtual bool unknown_slot282();                             // slot 282 0x004CAFE0
    virtual bool unknown_slot283();                             // slot 283 0x004CA820
    virtual bool unknown_slot284() { return false; }            // slot 284 (kept copy 0x0041B460)
    virtual void unknown_slot285(Cell cell);              // slot 285 0x004CD0C0 (sensor cells entered)
    virtual void unknown_slot286(Cell cell);              // slot 286 0x004CD250 (ret 4)
    virtual CoordStruct unknown_slot287();                      // slot 287 0x004C8AC0 (slot 40's coordinate)
    virtual void unknown_slot288();                             // slot 288 0x004CA880
    virtual bool unknown_slot289() { return false; }            // slot 289 (kept copy 0x0041B480)
    virtual bool unknown_slot290(CoordStruct &coord);    // slot 290 0x004C4B90 (ILocomotion::Move_To, then Is_Moving)
    virtual bool unknown_slot291();                             // slot 291 0x004C4B60 (ILocomotion::Stop_Moving; false)
    virtual bool unknown_slot292();                             // slot 292 0x004CA2B0
    // slot 293 (kept copy 0x0041B490): passes its arguments on to the
    // TechnoClass shape drawer 0x006D1510 (ret 0x3C).
    virtual void unknown_slot293(void const *shape, int drawer, Point2D const *point, Rect const *bounds, int arg5,
                                 int arg6, int z, int arg8, int arg9, int height, int arg11, int arg12, Point2D offset,
                                 int arg15)
    {
        unknown_6d1510(shape, drawer, point, bounds, arg5, arg6, z, arg8, arg9, height, arg11, arg12, offset, arg15);
    }
    virtual void unknown_slot294() {}                           // slot 294 (kept copy 0x0041B4F0)
    virtual void unknown_slot295() {}                           // slot 295 (kept copy 0x0041B500)
    virtual void unknown_slot296() {}                           // slot 296 (kept copy 0x0041B510)
    virtual void unknown_slot297(int arg1) {}                   // slot 297 (kept copy 0x0041B520)
    Cell unknown_4c8af0(Cell const &cell);          // 0x004C8AF0 (returns its argument; TeamClass callers)
    void unknown_4ca1a0();                                      // 0x004CA1A0 (never called: a drop pod locomotor carries the old one)
    void unknown_4c8c90();                                      // 0x004C8C90 (clears the vector at +0x49C)
    void unknown_4cab90();                                     // 0x004CAB90 (draws the action line; no stack arguments)
    double unknown_4cafb0() const;                              // 0x004CAFB0
    Cell unknown_4cca40(Cell const &cell, bool arg2); // 0x004CCA40 (the cell to head for; arg2 passed on to slot 27)
    Cell unknown_4cc100(int radius);                      // 0x004CC100 (nearest cell passing 0x004CC260, by rings)
    bool unknown_4cc260(Cell &cell, int dx, int dy);      // 0x004CC260
    bool unknown_4cc400(int arg1);                              // 0x004CC400
    void unknown_4cd9b0();                                     // 0x004CD9B0 (clears +0x490 and +0x494)
    void unknown_4c8bb0(AbstractClass *target);                // 0x004C8BB0 (queues a destination; itself turns on looping)
    Cell unknown_4cb8f0(int arg1, int arg2);              // 0x004CB8F0
    bool unknown_4cb830(int arg1, int arg2);                    // 0x004CB830
    bool unknown_4cb6d0(Cell const &cell);               // 0x004CB6D0
    Cell unknown_4cbb40(int radius);                      // 0x004CBB40 (a weighted random cell of the rings that passes 0x004CB6D0; TibSun Search_For_Tiberium_Weighted)
    int unknown_4c82a0(AbstractClass *target);                 // 0x004C82A0 (an attack rate against a target)
    void unknown_4c8b00();                                      // 0x004C8B00 (next queued destination; UnitClass slot 261)
    bool unknown_4c8d60();                                      // 0x004C8D60 (slot 91 == 7)
    void unknown_4cdb60();                                      // 0x004CDB60 (+0x4B8 from +0x4BC's cell)
    void Unknown_004CD9B0();                                    // 0x004CD9B0 (clears +0x490 and +0x494)
    bool unknown_4cb110(WaypointClass *waypoint);               // 0x004CB110 (heads for a waypoint of the path; returns whether the click succeeded; FootClass slots 93, 194)
    BuildingClass *unknown_4c45b0();                            // 0x004C45B0 (an adjacent Overpowerable building of the same owner)
    bool unknown_4c8d00(HouseClass *house);                     // 0x004C8D00 (free to recruit: no team, an idle mission, +0x379)
    FootClass *unknown_4ccfc0();                                // 0x004CCFC0 (a passenger leaves this transport)
    void unknown_4ccf20(FootClass *passenger);                  // 0x004CCF20 (a given passenger leaves; never called)
    void unknown_4c4c30();                                      // 0x004C4C30 (approach the target; hypothesis: Approach_Target)
    bool unknown_4c3000(Cell dest, int arg2, int arg3);   // 0x004C3000 (plans a path to dest; hypothesis: Basic_Path)
    struct UnknownPathType *Unknown_004BB350(Cell *dest, int *buffer, int length, int arg4, int arg5, int arg6);  // 0x004BB350 (hypothesis: Find_Path)
    Cell Unknown_004BB3F0(Cell const &from, Cell const &to, int arg3, int arg4);   // 0x004BB3F0 (hypothesis: TS Safety_Point; TeamClass 0x006B88B0 Regroup)
    void unknown_4c9a40(UnknownObjectPair const &voxel, int layer, int key, UnknownBuffer *cache, Rect const &cliprect, Point2D const &draw_point, Matrix3D const &transform, bool force_cache, unsigned unknown_1, unsigned unknown_2, unsigned unknown_3);  // 0x004C9A40 (the shadow draw; AircraftClass, UnitClass)
    void Unknown_004CCE80(FootClass *passenger);                // 0x004CCE80 (a passenger enters this transport)
    virtual int unknown_slot298();                              // slot 298 0x004C86D0 (0)
    virtual TechnoClass *unknown_slot299(DynamicVectorClass<TechnoTypeClass *> const *types, int arg2, int arg3);  // (hypothesis: the nearest dock of any of the types)   // slot 299 (AircraftClass 0x0041B1E0: ret 0xC, returns +0x5B4)
    virtual TechnoClass *unknown_slot300(TechnoTypeClass *type, int arg2, int arg3, int *score);   // slot 300 0x004CD760
    virtual TechnoClass *unknown_slot301(TechnoTypeClass *type, int arg2, int arg3);  // slot 301 0x004CD730
    virtual void Overrun_Square(Cell const &cell, bool threaten) {}  // slot 302 (kept copy 0x0041B530)
    virtual int unknown_slot303();                              // slot 303 0x004C9B10 (a speed; LocomotionClass::Apparent_Speed)
    virtual void unknown_slot304();
    virtual void unknown_slot305(int arg1) {}                   // slot 305 (kept copy 0x0041B540)
    virtual void unknown_slot306(double value);                 // slot 306 0x004C2DF0 (clamped to 0..1)
    virtual void unknown_slot307();                             // slot 307 0x004CA330 (nothing)
    virtual void unknown_slot308();                             // slot 308 0x004CA340 (nothing)
    virtual bool unknown_slot309(AbstractClass *target);         // slot 309 0x004CC4D0 (whether the target's cell is free to dock at; hypothesis)

    int unknown_418;                            // +0x418
    Cell unknown_41c;                     // +0x41C
    Cell unknown_420;                     // +0x420
    int unknown_424;                            // +0x424
    double unknown_428;                         // +0x428 (Compute_CRC hashes it as a double)
    int unknown_430;                            // +0x430
    bool unknown_434;                           // +0x434
    int unknown_438;                            // +0x438
    UnknownAudioController unknown_43c;         // +0x43C
    Cell unknown_450;                     // +0x450 (Compute_CRC hashes its length)
    Cell unknown_454;                     // +0x454
    Cell unknown_458;                     // +0x458
    CoordStruct unknown_45c;                    // +0x45C (Compute_CRC hashes its length)
    double unknown_468;                         // +0x468
    double unknown_470;                         // +0x470
    DynamicVectorClass<AbstractClass *> unknown_478;    // +0x478
    AbstractClass *unknown_490;                 // +0x490 (slot 259 sets it; slot 241 takes its coordinate; not saved)
    AbstractClass *unknown_494;   // +0x494 (swizzled)
    AbstractClass *unknown_498;   // +0x498 (swizzled)
    DynamicVectorClass<AbstractClass *> unknown_49c;    // +0x49C
    int unknown_4b4;                            // +0x4B4
    AbstractClass *unknown_4b8;   // +0x4B8 (swizzled)
    AbstractClass *unknown_4bc;   // +0x4BC (swizzled)
    bool unknown_4c0;                           // +0x4C0
    bool unknown_4c1;                           // +0x4C1
    TeamClass *Team;                            // +0x4C4
    AbstractClass *unknown_4c8;   // +0x4C8 (swizzled)
    AbstractClass *unknown_4cc;   // +0x4CC (swizzled)
    union {
        int unknown_4d0;                        // +0x4D0 (the first path facing, -1 none)
        int Path[24];                           // +0x4D0 path facings (FootClass 0x004C3000)
    };

    CDTimerClass<FrameTimerClass> unknown_530; // +0x530
    int unknown_53c;                            // +0x53C
    CDTimerClass<FrameTimerClass> unknown_540; // +0x540
    CDTimerClass<FrameTimerClass> unknown_54c; // +0x54C
    CDTimerClass<FrameTimerClass> unknown_558; // +0x558
    UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> Locomotor;  // +0x564 (ILocomotionPtr)
    CoordStruct unknown_568;                    // +0x568
    signed char unknown_574;                    // +0x574 (-1; slot 46 tests its sign)
    signed char unknown_575;                           // +0x575
    char unknown_576;                           // +0x576 (the waypoint index in the path, slot 99)
    bool unknown_577;                           // +0x577
    bool unknown_578;                           // +0x578
    bool unknown_579;                           // +0x579
    bool unknown_57a;                           // +0x57A
    bool unknown_57b;                           // +0x57B
    bool unknown_57c;                           // +0x57C
    bool unknown_57d;                           // +0x57D
    bool unknown_57e;                           // +0x57E
    FootClass *unknown_580;                     // +0x580 (swizzled)
    int unknown_584;                            // +0x584
    ParasiteClass *unknown_588;                 // +0x588 (owned; the parasite attached to this unit, hypothesis)
    CDTimerClass<FrameTimerClass> unknown_58c; // +0x58C
    bool unknown_598;                           // +0x598
    bool unknown_599;                           // +0x599
    bool unknown_59a;                           // +0x59A
    bool unknown_59b;                           // +0x59B
    bool unknown_59c;                           // +0x59C
    bool unknown_59d;                           // +0x59D
    bool unknown_59e;                           // +0x59E
    bool unknown_59f;                           // +0x59F
    bool unknown_5a0;                           // +0x5A0
    bool unknown_5a1;                           // +0x5A1
    bool unknown_5a2;                           // +0x5A2
    int unknown_5a4;                            // +0x5A4 (not constructed; UnitClass members start at +0x5A8)
};

// The unit's list of FootClass objects (0x00865F38; defined by the
// header-static draft of this unit). The list at 0x00AC0C18 is in
// shared/object_lists.hpp.
extern DynamicVectorClass<FootClass *> unknown_FootClass_list_00865f38;

// Member-wise cell sum: shared/coord.hpp.

// CoordStruct::operator- is a member of coord.hpp.

// Length of a two-short offset and of a coordinate (helpers; hypothesis; FootClass Compute_CRC and slot 37).
inline int Short_Length(short x, short y)
{
    double dy = y;
    double dx = x;
    return (int)unknown_sqrt_4ba410(dx * dx + dy * dy);
}

inline int Coord_Length(CoordStruct const &coord)
{
    double z = coord.Z;
    double y = coord.Y;
    double x = coord.X;
    return (int)unknown_sqrt_4ba410(x * x + y * y + z * z);
}

// The sum of two points (an inline helper, as BuildingClass's Point_Sum;
// Point2D's own operator+ is out of line; FootClass slot 246 and 0x004C9A40).
inline Point2D Point2D_Sum(Point2D const &a, Point2D const &b)
{
    return Point2D(a.X + b.X, a.Y + b.Y);
}

// The same length with the terms loaded Y, Z, X and summed X, Z, Y (FootClass
// slot 144; the order of Westwood's Distance() as BuildingClass expands it).
inline int Offset_Length(CoordStruct const &coord)
{
    double y = coord.Y;
    double z = coord.Z;
    double x = coord.X;
    return (int)unknown_sqrt_4ba410(x * x + z * z + y * y);
}

class EBolt;
// A unit (only the members FootClass slot 303 and TechnoClass 0x006CA130 use; stand-in for
// shared/unit.hpp, which defines RA2_SHARED_UNIT_HPP).
#ifndef RA2_UNIT_FULL
#ifndef RA2_SHARED_UNIT_TYPE_HPP
class UnitTypeClass : public TechnoTypeClass {
public:
    int ArrayIndex;                             // +0xB90 index in UnitTypes (TechnoClass slot 55)
    char unknown_b94[0xBA4 - 0xB94];
    bool Passive; // +0xBA4, owner-approved UnitType field
    char unknown_ba5;
    bool Harvester;                             // +0xBA6 (as shared/unit_type.hpp)
    char unknown_ba7[0xBAA - 0xBA7];
    bool DeployToFire;                          // +0xBAA
    char unknown_bab[0xBB0 - 0xBAB];
    bool SmallVisceroid;                        // +0xBB0 (as full UnitTypeClass)
    bool LargeVisceroid;                        // +0xBB1 (as full UnitTypeClass)
    char unknown_bb2[0xBD8 - 0xBB2];
    int FiringSyncFrame[2];                     // +0xBD8 (as full UnitTypeClass)
    int BurstDelay[4];                          // +0xBE0 (TechnoClass slot 187)
};
#endif
class UnitClass : public FootClass {
public:
    int unknown_5a8;                            // +0x5A8 (-1)
    UnitTypeClass *Type;                        // +0x5AC
    FootClass *unknown_5b0;                     // +0x5B0 the next unit of a convoy (FootClass 0x004C3000; hypothesis)
    int unknown_5b4;                            // +0x5B4 (-1; FootClass slot 303 halves the speed when set)
    bool unknown_5b8;                           // +0x5B8 (FootClass 0x004C3000: the convoy does not follow)
    bool unknown_5b9; // +0x5B9, owner-approved restart flag
    char unknown_5ba;
    bool unknown_5bb;                           // +0x5BB (composite surface; matches full UnitClass, TechnoClass 0x006D1510)
    char unknown_5bc[0x5C4 - 0x5BC];
    EBolt *unknown_5c4;                         // +0x5C4 the unit's electric bolt (TechnoClass 0x006CA130)
};
#endif

// Every unit (0x00866198; shared/unit.hpp has the full class).
class UnitClass;
extern DynamicVectorClass<UnitClass *> Units;

// The path a search returns (UnknownPathType): shared/path_estimator.hpp.
// The path estimator at 0x008315C8: shared/path_estimator.hpp.
#include "shared/path_estimator.hpp"
// Movement zones by MovementZone (0x007A1200; hypothesis).
extern int unknown_zone_table_7a1200[];

#endif
