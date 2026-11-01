// InfantryClass: a soldier (Infantry.cpp, unit 0x004FF450-0x0050992F; RTTI
// vtables 0x007A3540 primary (312 slots: FootClass's 310 and 2 new),
// 0x007A3524 IRTTITypeInfo at +4, 0x007A351C INoticeSink, 0x007A3514
// INoticeSource). Built on build/class-work/Unit/shared/foot.hpp.
//
// Layout (constructor 0x004FF640, Load 0x00508570, Compute_CRC 0x005088A0;
// Size_Of returns 0x5D8). Names are hypotheses:
//   +0x5A8  InfantryTypeClass *Type      the constructor's first argument
//   +0x5AC  int Sequence (-1)            the animation being played (DoType;
//           slot 307 resets values 6, 3 and 0x11, slot 310 tests 0x1B/0x1C)
//   +0x5B0  CDTimerClass<FrameTimerClass> unknown_5b0 (started)
//   +0x5BC  int unknown_5bc
//   +0x5C0..+0x5C5  bools (+0x5C1..+0x5C5 hashed by Compute_CRC)
//   +0x5C8  int unknown_5c8, +0x5CC bool unknown_5cc (slot 308 clears it),
//   +0x5D0  int unknown_5d0 (2), +0x5D4 not constructed
// Every infantry is in the list at 0x00A35E48 and in the techno index.
#ifndef RA2_SHARED_INFANTRY_HPP
#define RA2_SHARED_INFANTRY_HPP

#include "shared/unknown_globals.hpp"
#include "shared/foot.hpp"
#define RA2_INFANTRY_FULL
#include "shared/infantry_type.hpp"
#include "shared/techno_index.hpp"
#include "shared/house.hpp"
#include "shared/fast_math.hpp"

// BuildingClass: shared/techno.hpp (its stand-in carries the member InfantryClass slot 132 calls).

extern "C" GUID const CLSID_InfantryClass;      // 0x007A1BF0

// Shared IPersist conversion used by the Infantry.cpp locomotor checks.
class UnknownPersistPtr {
public:
    UnknownPersistPtr(UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> const &other); // 0x00509870
    UnknownPersistPtr(ILocomotion *other) : Pointer(0)
    {
        HRESULT result = Query(other);
        if (FAILED(result) && result != E_NOINTERFACE) {
            _com_issue_error(result);
        }
    }
    ~UnknownPersistPtr()
    {
        if (Pointer != 0) {
            Pointer->Release();
        }
    }
    HRESULT Query(ILocomotion *other)
    {
        HRESULT result;
        if (other != 0) {
            IPersist *pointer;
            result = other->QueryInterface(unknown_uuid_IPersist_7cf208, (void **)&pointer);
            if (FAILED(result)) {
                Attach(0);
                return result;
            }
            Attach(pointer);
        } else {
            result = E_NOINTERFACE;
        }
        return result;
    }
    void Attach(IPersist *pointer)
    {
        Release_Held();
        Pointer = pointer;
    }
    void Release_Held();
    IPersist *operator->() const
    {
        if (Pointer == 0) {
            _com_issue_error(E_POINTER);
        }
        return Pointer;
    }
    IPersist *Pointer;
};

class CCINIClass;

#include "shared/options.hpp"

class InfantryClass : public FootClass {
public:
    InfantryClass(InfantryTypeClass *type, HouseClass *house);        // 0x004FF640
    InfantryClass(NoInitClass const &noinit) : FootClass(noinit), unknown_5b0(noinit) {}   // inline (Load)
    virtual ~InfantryClass();                                         // 0x004FF980

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                 // slot 3 0x005097C0 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_InfantryClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);   // slot 5 0x00508570 ret 8
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);   // slot 6 0x00508710 ret 0xc
    virtual void Init();   // slot 9 0x004FF8B0 ret 0
    virtual void Detach(AbstractClass *target, bool all = true);   // slot 10 0x00501CB0 ret 8
    virtual int Kind_Of() const { return 0x0F; }   // slot 11 0x00509800 ret 0 (inline)
    virtual int Size_Of() const { return sizeof(InfantryClass); }   // slot 12 0x005097B0 ret 0 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;   // slot 13 0x005088A0 ret 4
    virtual void AI();   // slot 23 0x00502D20 ret 0
    virtual void *unknown_slot26();          // slot 26 0x00508310 ret 
    virtual int unknown_slot27(Cell const *cell, bool arg2, bool arg3);   // slot 27 0x00506650 ret 0xc
    virtual int unknown_slot28(ObjectClass *object, bool arg2);   // slot 28 0x00505390 ret 8
    virtual ObjectTypeClass * Class_Of() const;   // slot 33 0x00506950 ret 0
    virtual wchar_t const *unknown_slot35();   // slot 35 0x00506160 ret 0
    virtual bool unknown_slot49(HouseClass *house);   // slot 49 0x00509390 ret 4
    virtual ObjectTypeClass *unknown_slot50(bool arg1);   // slot 50 0x00509200 ret 4
    virtual HouseClass *unknown_slot51(bool arg1);   // slot 51 0x00509270 ret 4
    virtual bool unknown_slot52();  // slot 52 0x00504F00 ret 0
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);   // slot 53 0x00504FD0 ret 8
    virtual bool unknown_slot56(CoordStruct const &coord);   // slot 56 0x005083B0 ret 4
    virtual void unknown_slot58(CoordStruct const &coord);   // slot 58 0x00508410 ret 4
    virtual void unknown_slot59(CoordStruct const &coord);   // slot 59 0x005084A0 ret 4
    virtual void unknown_slot67(int arg1, int arg2);   // slot 67 0x00500550 ret 8
    virtual bool unknown_slot77(int arg1, int arg2, int arg3, bool arg4);   // slot 77 0x00506100 ret 0x10
    virtual bool unknown_slot78(int arg1, int arg2, bool arg3);   // slot 78 0x00506050 ret 0xc
    virtual void unknown_slot82(int arg1);   // slot 82 0x005091C0 ret 4
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6);   // slot 86 0x004FFB70 ret 0x18
    virtual void unknown_slot87(CoordStruct const &source, bool forced, bool nokidding);   // slot 87 0x00504120 ret 
    virtual void unknown_slot93(int arg1);   // slot 93 0x00500AA0 ret 4
    virtual int unknown_slot101(CellClass *arg1, int arg2, int arg3, int arg4, bool arg5);   // slot 101 0x00503190 ret 0x14
    virtual bool unknown_slot122();   // slot 122 0x00508770 ret 0
    virtual int unknown_slot126();   // slot 126 0x00506280 ret 0
    virtual int unknown_slot129();   // slot 129 0x00506470 ret 0
    virtual int unknown_slot130();   // slot 130 0x00506490 ret 0
    virtual int unknown_slot132();   // slot 132 0x005063E0 ret 0
    virtual int unknown_slot133();   // slot 133 0x005064B0 ret 0
    virtual int unknown_slot137();   // slot 137 0x00506530 ret 0
    virtual int unknown_slot174(AbstractClass *target);   // slot 174 0x00508530 ret 4
    virtual CoordStruct unknown_slot181(int arg1);   // slot 181 0x00508940 ret 8
    virtual bool unknown_slot193();   // slot 193 0x00509090 ret 0
    virtual bool unknown_slot204();   // slot 204 0x00509670 ret 0
    virtual void unknown_slot205();   // slot 205 0x005096B0 ret 0
    virtual int unknown_slot218(AbstractClass *target, int weapon, int arg3);   // slot 218 0x00503A60 ret 0xc
    virtual AbstractClass *unknown_slot219(int arg1, CoordStruct const *coord, bool arg3);   // slot 219 0x00505120 ret 0xc
    virtual void unknown_slot220(AbstractClass *target);   // slot 220 0x00502470 ret 4
    virtual BulletClass *unknown_slot221(AbstractClass *target, int arg2);   // slot 221 0x00504F50 ret 8
    virtual void unknown_slot240();   // slot 240 0x005061D0 ret 0
    virtual void unknown_slot255(TechnoClass *techno);   // slot 255 0x005092B0 ret 4
    virtual void unknown_slot256();   // slot 256 0x00509330 ret 0
    virtual bool unknown_slot257();   // slot 257 0x00508320 ret 0
    virtual bool unknown_slot258();   // slot 258 0x00503E00 ret 0
    virtual void unknown_slot260(AbstractClass *target, int arg2);   // slot 260 0x00501CE0 ret 8
    virtual bool unknown_slot261(bool arg1, bool arg2);   // slot 261 0x00503C00 ret 8
    virtual bool unknown_slot274();   // slot 274 0x00509450 ret 
    virtual bool unknown_slot275();   // slot 275 0x00509460 ret 
    virtual void unknown_slot288();   // slot 288 0x005089D0 ret 0
    virtual bool unknown_slot289();   // slot 289 0x00508AB0 ret 0
    virtual bool unknown_slot290(CoordStruct &coord);   // slot 290 0x00504BC0 ret 4
    virtual bool unknown_slot291();   // slot 291 0x00504AE0 ret 0
    virtual void unknown_slot294();   // slot 294 0x00508CF0 ret 0
    virtual void unknown_slot295();   // slot 295 0x00508820 ret 0
    virtual void unknown_slot296();   // slot 296 0x00508850 ret 0
    virtual void unknown_slot297(int arg1);   // slot 297 0x00508870 ret 4
    virtual int unknown_slot303();   // slot 303 0x00508980 ret 0
    virtual void unknown_slot304();   // slot 304 0x00508F30 ret 0
    virtual void unknown_slot307();   // slot 307 0x00508730 ret 0
    virtual void unknown_slot308();   // slot 308 0x00508750 ret 0

    // New virtuals (slots 310-311).
    virtual bool unknown_slot310();                                   // slot 310 0x00509470
    virtual bool unknown_slot311(int sequence, bool force, bool random_start);        // slot 311 0x00504740 (ret 0xC)

    // Sequence classification helpers; ownership inferred from Infantry.cpp and the receiver at 0x509760.
    bool Is_Prone_Sequence_005096e0(int sequence) const;
    bool Is_Busy_Sequence_00509710(int sequence) const;
    bool Is_Busy_00509760() const;

    static void __fastcall Read_INI(CCINIClass &ini);  // 0x00506960
    static void __fastcall Write_INI(CCINIClass &ini); // 0x00506D70

    void Update_Fire_00507530();

    void Update_Movement_00507b90();                  // 0x00507B90
    void unknown_5025c0();
    bool unknown_5070e0();
    bool unknown_507170();
    void Advance_Animation_005078b0();
    AnimTypeClass *Pick_Dead_Body(bool use_type) const;        // inline (a dead-body animation, one scenario draw)
    int Update_Deployed_Attack_00507f70();                       // 0x00507F70 (-1 when it does not apply)
    bool unknown_5090a0() const;                // 0x005090A0 (the type's Deployer flag)
    bool unknown_5090b0() const;                // 0x005090B0 (the type's UndeployDelay is set)
    bool unknown_509100() const;                // 0x00509100 (the type's DeployFire flag)
    bool unknown_5090d0() const;                // 0x005090D0 (deploying: sequence 27-30; TechnoClass slot 186 and UnitClass test al)
    bool unknown_508d00();                      // 0x00508D00 (JumpJet type flying with the jumpjet locomotor)
    bool unknown_508dd0(Cell const *from, Cell const *to);   // 0x00508DD0 (a move worth path-finding)
    int unknown_500350();                       // 0x00500350 (the shape frame of the current sequence; Westwood's Shape_Number)
    void unknown_506f30();                      // 0x00506F30 (fear: decays, goes prone or stands, a Fraidycat runs)
    virtual bool INoticeSink_Unknown(int code, int arg);   // INoticeSink (+8) slot 0 0x00509590 (vtable 0x007A351C)
    int unknown_509110();
    void unknown_5094b0(BuildingClass *building); // 0x005094B0 (enter a building: Occupier joins it, Assaulter attacks it)                       // 0x00509110 (deploy-fire start: sequence 27 when standing, else stop and a delay)

    InfantryTypeClass *Type;                    // +0x5A8
    int Sequence;                               // +0x5AC
    CDTimerClass<FrameTimerClass> unknown_5b0;  // +0x5B0
    int unknown_5bc;                            // +0x5BC
    bool unknown_5c0;                           // +0x5C0
    bool unknown_5c1;                           // +0x5C1
    bool unknown_5c2;                           // +0x5C2
    bool unknown_5c3;                           // +0x5C3
    bool unknown_5c4;                           // +0x5C4
    bool unknown_5c5;                           // +0x5C5
    int unknown_5c8;                            // +0x5C8
    bool unknown_5cc;                           // +0x5CC
    int unknown_5d0;                            // +0x5D0
    int unknown_5d4;                            // +0x5D4
};

// Every infantry (0x00A35E48): shared/techno.hpp.

// The spot (sub-cell) index of a coordinate (0x004763D0; ECX = &coord, so
// declared fastcall; owner hypothesis CellClass static).
int __fastcall Unknown_004763D0(CoordStruct const &coord);
// The height above ground at which an object is on a bridge (0x00A41120).
extern int unknown_bridge_height_a41120;

// Per-sequence controls (0x007A3474, 38 entries indexed by Sequence; RA's
// MasterDoControls: interruptible, mobile, random start, frame rate).
struct DoStruct {
    bool Interrupt;
    bool IsMobile;
    bool RandomStart;
    unsigned char Rate;
};
extern DoStruct unknown_do_controls_7a3474[];

// The coordinate returned when no spot is free (0x00A410F8).
extern CoordStruct unknown_invalid_coord_a410f8;

// Sequences that block firing (an inline helper: InfantryClass slot 218 returns 6 for them; hypothesis).
inline bool Is_Busy_Sequence(int sequence)
{
    return sequence == 11 || sequence == 12 || sequence == 13 || sequence == 14 || sequence == 15
        || sequence == 34 || sequence == 35 || sequence == 36 || sequence == 20 || sequence == 21;
}

// The cell offsets of the eight facings (0x00851A70; Westwood's AdjacentCell).
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
// The cell next to `cell` toward an 8-way facing.
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    return AdjacentCell[facing & 7] + cell;   // Westwood's form: the offset is the left operand (FootClass 0x004C45B0, slot 129)
}
#endif
// Cell_Coord: shared/coord.hpp.
// The direction from one coordinate to another (hypothesis: Westwood's
// Direction, by value; as in BulletClass slot 116).
inline UnknownFacingDir Direction_Of(CoordStruct from, CoordStruct to)
{
    return UnknownFacingDir((unsigned short)((Fast_Atan2((double)from.Y - to.Y, (double)to.X - from.X)
        - 1.5707963267948966) * -10430.060040584269));
}
// The cell returned when none is found (0x00A410D8).
extern Cell unknown_invalid_cell_a410d8;
// The height of one level (0x00A41130).
extern int unknown_level_height_a41130;


// The unit as an infantry unit (kind 15), or null.
inline InfantryClass *As_Infantry(FootClass *foot)
{
    if (foot == 0) {
        return 0;
    }
    return foot->Kind_Of() == 15 ? (InfantryClass *)foot : 0;
}



// Foot6 additions (InfantryClass slot 93, 0x00500AA0).
// Damage around a coordinate (0x0047E2C0, __fastcall; hypothesis; as in
// build/class-work/Effects/shared/anim.hpp).
int __fastcall Unknown_0047E2C0(CoordStruct const &coord, int damage, TechnoClass *source, WarheadTypeClass *warhead, bool arg5);   // returns 2 when the warhead was nullified (BulletClass 0x00462110), 0 when nothing was hit
// Coordinate offsets of the eight facings (0x00851AC0; X and Y leptons).
struct UnknownFacingOffset {
    int X;
    int Y;
};
extern UnknownFacingOffset const unknown_facing_offsets_851ac0[8];

#endif
