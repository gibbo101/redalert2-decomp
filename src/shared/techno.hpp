// TechnoClass: RadioClass with an owner, weapons, facings and the
// technology-level behaviour of every unit, infantry, aircraft and building
// (Techno.cpp, 0x006C0A50-0x006D9950; RTTI vtables 0x007ACB80 primary (280
// slots), 0x007ACB64 IRTTITypeInfo at +4, 0x007ACB5C INoticeSink,
// 0x007ACB54 INoticeSource). Abstract: slots 11, 12 and 216 are pure.
//
// Layout (constructor 0x006C0CD0, NoInitClass constructor 0x006C1F10,
// destructor 0x006C20B0, Load 0x006D6850; names are hypotheses unless
// they follow from the code):
//   +0x0D8  RadioClass ends; +0x0E0 UnknownStage AnimationStage
//   +0x114  int (the owner's +0x130 when constructed with an owner)
//   +0x118  UnknownTechnoPair (two cleared words, out-of-line ctor/dtor)
//   +0x120, +0x128  double 1.0
//   +0x130..+0x19C  frame timers (+0x148 starts at 45)
//   +0x1B4  HouseClass *House   the constructor argument (Owning_House)
//   +0x1BC  UnknownStage (value, timer, step 1; constructed by both
//           constructors)
//   +0x1E8, +0x21C  CoordStruct (the unit's zero coordinate)
//   +0x208, +0x230, +0x238  owned objects deleted by the destructor
//   +0x25C  ObjectClass *unknown_25c[8]   cleared, swizzled
//   +0x294  StorageClass, +0x2A8 UnknownTimed (out-of-line constructors)
//   +0x2C8, +0x2E0, +0x2F8  FacingClass (the first with rate 3)
//   +0x320  short: a random value from the scenario when constructed
//   +0x330, +0x350  UnknownTechnoBlock (constructed by both constructors)
//   +0x390  DynamicVectorClass<int>, +0x3A8/+0x3C0 DynamicVectorClass<
//           AbstractClass *> (constructed by both constructors)
//   +0x3D8  UnknownAudioController
//   +0x408  owned object (0x006130B0 releases it), size 0x418
// Every techno is added to Technos (0x00A40C20) and to the list at
// 0x00AC0D08, and removed from those and 0x00AC0BF8 when destroyed.
#ifndef RA2_SHARED_TECHNO_HPP
#define RA2_SHARED_TECHNO_HPP

#include "shared/unknown_globals.hpp"
#include "shared/rect.hpp"
#include "shared/storage_class.hpp"
#include "shared/sound_play.hpp"
#include "shared/stage.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/radio.hpp"
#include "shared/crt_memory.hpp"
#include "shared/random.hpp"
#include "shared/rgb_class.hpp"
#include "shared/system_timer.hpp"

class LaserDrawClass;
class BulletClass;
class EBolt;
class TechnoClass;
class FootClass;
class InfantryClass;

// Two words cleared together (constructor 0x00713340, destructor
// 0x00713350 are out of line).
class UnknownTechnoPair {
public:
    UnknownTechnoPair();                // 0x00713340
    UnknownTechnoPair(NoInitClass const &noinit) {}
    ~UnknownTechnoPair();               // 0x00713350
    int unknown_713580() const;         // 0x00713580 (hypothesis: written to the [Units] line)
    // Sets the first word to 0 and the second to 2.0f with the flag, else 0
    // (0x00713550; Create_Units with InitialVeteran).
    void Unknown_00713550(bool flag);
    void Unknown_00713590(int value);    // 0x00713590: signed int * 0.01 stored as an 8-byte FP value
    bool unknown_713420() const;        // 0x00713420
    void Unknown_00713360(int cost, int points);   // 0x00713360 (gains experience; TechnoClass slot 55)
    void unknown_713520(bool value);    // 0x00713520 (UnitClass constructor: veteran owners)
    bool unknown_7133a0() const;        // 0x007133A0 (veteran; hypothesis)
    bool unknown_713400() const;        // 0x00713400 (a third rank; TechnoClass slot 250 draws frame 18)
    int unknown_00;
    int unknown_04;
};

// UnknownStage: shared/stage.hpp.

// A timer whose NoInitClass constructor is out of line (0x00423F60).
class UnknownTimer423F60 {
public:
    UnknownTimer423F60(NoInitClass const &noinit);  // 0x00423F60
    UnknownTimer423F60(long set) : Started(Timer), DelayTime(set) {}
    long Started;
    FrameTimerClass Timer;
    long DelayTime;
};

// INTEG RESOLUTION CANDIDATE: codex1 r38's 16-byte duration timer (UnknownTimed +0x08),
// the 12-byte UnknownTimer423F60 plus the initial duration.
class UnknownDurationTimer423F60 : public UnknownTimer423F60 {
public:
    UnknownDurationTimer423F60() : UnknownTimer423F60(0L), TotalTime(0) {}
    UnknownDurationTimer423F60(long set) : UnknownTimer423F60(set), TotalTime(set) {}
    UnknownDurationTimer423F60(NoInitClass const &noinit) : UnknownTimer423F60(noinit) {}
    long Value() const
    {
        long remain = DelayTime;
        if (Started != -1) {
            long elapsed = Timer - Started;
            if (elapsed < remain) return remain - elapsed;
            return 0;
        }
        return remain;
    }
    double Percentage() const
    {
        if (!TotalTime) return 1.0;
        return (double)(TotalTime - Value()) / TotalTime;
    }
    void Reverse() { DelayTime = TotalTime - Value(); }
    long TotalTime;
};

// 0x20 bytes around a timer at +0x08 (constructor 0x00496A70 is out of line).
class UnknownTimed {
public:
    bool Is_Complete_00496AD0() const;
    void Reverse_00496C10();
    double Progress_00496C70() const;
    UnknownTimed();                     // 0x00496A70
    UnknownTimed(NoInitClass const &noinit) : Timer(noinit) {}
    bool unknown_496a90() const;        // 0x00496A90 (+0x18 and +0x19 set)
    bool unknown_496ab0() const;        // 0x00496AB0 (+0x18 set, +0x19 clear)
    bool unknown_496b30() const;        // 0x00496B30 (+0x18 set, or +0x19 is 1)
    bool unknown_496b50() const;        // 0x00496B50 (neither +0x18 nor +0x19 set)
    void unknown_496bc0(double time);   // 0x00496BC0 (starts a timed change; UnitClass slot 145 passes DeployTime)
    void unknown_496b70(double time);   // 0x00496B70 (the reverse timed change; AircraftClass slot 95 passes DeployTime)
    double FrameDuration;                 // +00 duration scaled to frames
    UnknownDurationTimer423F60 Timer;           // +0x08,16bytes including TotalTime at+14
    bool IsActive;
    bool IsReverse;
    int unknown_1c;
};

#include "shared/facing.hpp"

// 0x20 bytes constructed by both constructors (2, 1, 1, 1, -, 0, 0).
// 0x006D8BC0 steps it: a value that rises over +0x0C frames (state 1),
// holds, then falls over +0x08 frames (state 2 -> 3) back to 0.
struct UnknownTechnoBlock {
    UnknownTechnoBlock() :
        unknown_00(2), unknown_04(1), unknown_08(1), unknown_0c(1),
        unknown_14(0), unknown_18(0) {}
    void unknown_6d8b90();              // 0x006D8B90
    void unknown_6d8bc0();              // 0x006D8BC0
    int unknown_00;                     // +0x00 amount
    int unknown_04;
    int unknown_08;                     // +0x08 frames to fall
    int unknown_0c;                     // +0x0C frames to hold
    float unknown_10;                   // +0x10 step per frame
    float unknown_14;                   // +0x14 current value
    int unknown_18;                     // +0x18 state (0 idle)
    int unknown_1c;                     // +0x1C frames left in the state
};

// A packed 5-byte object reference (hypothesis: Westwood's TargetClass, an
// ID and an RTTI byte; the byte is nonzero when set).
#pragma pack(push, 1)
struct UnknownTarget {
    AbstractClass *Unknown_006B5810() const;    // 0x006B5810 (the referenced object; hypothesis)
    int unknown_0;                      // +0x00
    char unknown_4;                     // +0x04
};

// The argument of slot 268 (hypothesis: an event record; +0x0C its kind,
// +0x0E and +0x13 two references).
struct UnknownSlot268Arg {
    char unknown_00[0x0C];
    char unknown_0c;                    // +0x0C (sign-extended)
    char unknown_0d;
    UnknownTarget unknown_0e;           // +0x0E
    UnknownTarget unknown_13;           // +0x13
};
#pragma pack(pop)

// The passengers (hypothesis: Westwood's CargoClass): a count and a chain of
// objects linked through ObjectClass +0x30.
class UnknownCargo {
public:
    UnknownCargo() : Count(0), Object(0) {}
    UnknownCargo(NoInitClass const &noinit) {}
    ObjectClass *unknown_468a10() const;    // 0x00468A10 (the first passenger)
    int Unknown_00468A20() const; // 0x00468A20; existing Scope12 ABI hypothesis
    ObjectClass *unknown_4689f0();          // 0x004689F0 (detaches the first passenger)
    void Unknown_00468960(FootClass *passenger);    // 0x00468960 (adds a passenger; InfantryClass slot 93)
    void Unknown_00468A70(FootClass *passenger);    // 0x00468A70 (removes a given passenger; FootClass 0x004CCF20)
    int Count;                              // +0x00
    ObjectClass *Object;                    // +0x04
};

// A passenger's team (stand-in for the team member TechnoClass 0x006D3040
// uses; proposal: TeamClass in shared/team.hpp) and the foot member that
// holds it.
class UnknownPassengerTeam {
public:
    void unknown_6b8fb0(ObjectClass *object, int arg2, bool arg3);  // 0x006B8FB0 (removes object)
};
struct UnknownPassengerView {
    char unknown_000[0x4C4];
    UnknownPassengerTeam *Team;             // +0x4C4 (FootClass)
};

// The owned object at +0x208.
class UnknownTechno208 : public AbstractClass {
public:
    void unknown_6e2500();              // 0x006E2500 (UnitClass slot 281, when +0x28 is set)
    void Unknown_006E24C0(AbstractClass *target);   // 0x006E24C0 (TechnoClass::Detach)
    int unknown_24;
    int unknown_28;                     // +0x28 (slot 113 tests it)
};

// A map cell (only the members used here).
class BuildingClass;

// A tube (Westwood's TubeClass: the entry cell's tube, 0x0047A130; layout
// from FootClass slot 77, hypothesis): the exit cell and the exit facing.
struct UnknownTube47A130 {
    char unknown_00[0x24];
    Cell unknown_24;              // +0x24 (the entry cell; InfantryClass slot 101 compares it with the exit)
    Cell unknown_28;              // +0x28 (the exit cell; hypothesis)
    int unknown_2c;                     // +0x2C (the exit facing; hypothesis)
};
// A cell's occupation flags (Westwood's OccupyStruct: bits and the byte).
union UnknownCellOccupy {
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
// An entry of a cell's +0x28 list (TechnoClass slot 27; meaning not recovered).
struct UnknownCellEntryType {
    char unknown_000[0x201];
    bool unknown_201;                   // +0x201 (attackable)
};
struct UnknownCellEntry28 {
    char unknown_00[0x24];
    int unknown_24;                     // +0x24 (an overlay type index when +0x30 is 0x14)
    HouseClass *unknown_28;             // +0x28 (an owner)
    char unknown_2c[0x30 - 0x2C];
    int unknown_30;                     // +0x30 (a kind: 0x14, 6)
    char unknown_34[0x74 - 0x34];
    bool unknown_74;                    // +0x74 (active)
};
// The entry's first type (0x004C2030: the first of the vector at +0x5C when its count, +0x6C, is positive).
UnknownCellEntryType *__fastcall Unknown_004C2030(UnknownCellEntry28 *entry);

class UnknownCellClass {
public:
    UnknownCellClass *Unknown_00476AC0(int facing);  // 0x00476AC0 (the adjacent cell toward a facing)
    int Unknown_0047CE70();             // 0x0047CE70 (the tiberium damage of the cell; FootClass::AI)
    bool unknown_47c2c0(int house) const;   // 0x0047C2C0 (CellClass::Is_House_Bit; TechnoClass slot 161)
    CoordStruct unknown_475d60() const;     // 0x00475D60 (CellClass: the centre at the middle's height; TechnoClass 0x006CA340)
    bool unknown_47c2e0(int house);     // 0x0047C2E0
    bool unknown_47c300(int house);     // 0x0047C300 (FootClass slot 26: the house's index)
    void unknown_47bb30();              // 0x0047BB30 (TechnoClass slot 93)
    void unknown_476b20(int house, int value);  // 0x00476B20 (TechnoClass 0x006D95A0/0x006D95D0)
    bool Unknown_0047C200();            // 0x0047C200 (FootClass 0x004C3000)
    bool Unknown_0047CDD0();            // 0x0047CDD0 (the land allows standing here; FootClass 0x004C4C30)
    bool Unknown_0047BB10();            // 0x0047BB10 (FootClass 0x004C4C30)
    bool Unknown_00479CF0();            // 0x00479CF0 (InfantryClass 0x00508DD0)
    int Unknown_0047CF10() const;       // 0x0047CF10 (the height level: +0x11B plus 4 when flag 0x80 is set)
    TechnoClass *Unknown_00471660(Point2D const &offset, int arg2, int arg3);   // 0x00471660 (an object in the cell; FootClass slot 309)
    bool Unknown_00478760(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);   // 0x00478760 (FootClass slot 309)
    int Unknown_0047A230();             // 0x0047A230 (a docking score; FootClass 0x004CB8F0)
    void Unknown_0047C360(int house);   // 0x0047C360 (FootClass slot 285)
    void Unknown_0047C370(int house);   // 0x0047C370 (FootClass slot 286)
    void Unknown_0047C380(int house);   // 0x0047C380 (BuildingClass slot 290)
    void Unknown_0047C390(int house);   // 0x0047C390 (BuildingClass slot 291)
    UnknownTube47A130 *Unknown_0047A130();  // 0x0047A130 (the cell's tube: index +0x116 into 0x008661CC)
    BuildingClass *Unknown_004717B0();  // 0x004717B0 (the building in the cell)
    CoordStruct Unknown_004764B0(CoordStruct const &coord, int alternate, bool arg3);  // 0x004764B0 (a free spot near coord; InfantryClass slot 53)

    FootClass *Unknown_00473E30(bool alt);  // 0x00473E30 (the unit in the cell; Cell_Unit)
    FootClass *Unknown_00473E80(bool alt);  // 0x00473E80 (the aircraft in the cell; Cell_Aircraft)
    void Unknown_00476920(CoordStruct const *coord, bool arg2, bool arg3, bool alt);  // 0x00476920 (scatters the occupants)

    char unknown_000[0x24];
    Cell unknown_24;              // +0x024 (the cell's coordinates)
    DynamicVectorClass<struct UnknownCellEntry28 *> *unknown_28;   // +0x028 (owned entries; TechnoClass slot 27 scans them)
    char unknown_02c[0x38 - 0x2C];
    int unknown_38;                     // +0x038 (the iso tile index; InfantryClass slot 93 tests the bridge tiles)
    TagClass *unknown_3c;               // +0x03C (the cell's tag; FootClass slot 93 springs it)
    char unknown_040[0x44 - 0x40];
    int unknown_44;                     // +0x044 (the overlay, -1 none)
    char unknown_048[0x50 - 0x48];
    int unknown_50;                     // +0x050 (a house index: the overlay's owner; InfantryClass slot 101)
    int unknown_54;                     // +0x054 (a house index: the occupying owner, -1 none)
    int unknown_58;                     // +0x058 (the same on the bridge level)
    char unknown_05c[0xE4 - 0x5C];
    ObjectClass *unknown_e4;            // +0x0E4 (the first object in the cell; ObjectClass +0x30 links the rest)
    ObjectClass *unknown_e8;            // +0x0E8 (the first object on the bridge level)
    int unknown_ec;                     // +0x0EC (a land type)
    char unknown_0f0[0x10A - 0xF0];
    short unknown_10a;                  // +0x10A (ObjectClass slot 56 copies it into the placed animation's +0xE4)
    char unknown_10c[0x11B - 0x10C];
    char unknown_11b;                   // +0x11B (the height level)
    bool unknown_11c;                   // +0x11C (a ramp; FootClass slot 102)
    char unknown_11d;
    unsigned char unknown_11e;          // +0x11E
    char unknown_11f[0x122 - 0x11F];
    char unknown_122;                   // +0x122 (a count of units around; FootClass slot 52 decrements it)
    char unknown_123[0x124 - 0x123];
    UnknownCellOccupy unknown_124;      // +0x124 (occupation: 0x1C the three spots; InfantryClass slots 93, 101)
    UnknownCellOccupy unknown_128;      // +0x128 (the same on the bridge level)
    unsigned int unknown_12c;           // +0x12C flags (bit 4: TechnoClass slot 93 reveals to the player)
    char unknown_130[0x140 - 0x130];
    unsigned int Flags;                 // +0x140 (0x100: a bridge cell)
};

// Map_Cell (the cell object at a coordinate): shared/techno_map.hpp (it
// needs Map, and Techno.cpp includes gscreen.hpp after this header).

// 0x006D8F60 (fastcall; the kind in ECX, EDX and one stack word unused): maps kind 1 to 0x3E and kind 5 to 0x3F when 0x006F6670 holds.
int __fastcall Unknown_006D8F60(int kind, int unused_edx, int unused_stack);

// 0x006D7C80 (fastcall; many callers): every techno and team drops the target.
void __fastcall Unknown_006D7C80(AbstractClass *target);

// Sound effects: enabled flag (0x007D88D6), the effect generator
// (0x00839218); the play call 0x00713DB0 is shared/sound_play.hpp.
extern bool unknown_sound_enabled_7d88d6;
extern Random2Class unknown_random_839218;

// A double constant 0.0 (0x0079B610; slot 165 returns it).
extern double const unknown_double_79b610;
extern bool unknown_bool_7f7110;        // 0x007F7110
// unknown_timer_ac0178 (0x00AC0178): shared/cd_timer.hpp.
// The talk-bubble timer (0x00AC0168; a system-clock timer), techno
// (0x00AC01C4) and value (0x00AC01C8) that TechnoClass 0x006D8FD0 sets.
extern CDTimerClass<SystemTimerClass> unknown_timer_ac0168;    // 0x00AC0168
extern TechnoClass *unknown_talk_techno_ac01c4;                 // 0x00AC01C4
extern int unknown_talk_value_ac01c8;                           // 0x00AC01C8

// The owned object at +0x230 (only +0x24 is read here).
class UnknownTechno230 : public AbstractClass {
public:
    void Unknown_004681E0();            // 0x004681E0 (FootClass slot 60)
    void Unknown_00468120(AbstractClass *target);   // 0x00468120 (TechnoClass::Detach)
    int unknown_24;                     // +0x24
};

class SpawnManagerClass;               // the owned spawn manager at +0x238 (shared/spawn_manager.hpp)

// The object at +0x408 (released by 0x006130B0).
class UnknownTechno408 {
public:
    void unknown_6130b0();              // 0x006130B0
    int unknown_613b60();               // 0x00613B60
};


class InfantryTypeClass;

class TechnoClass : public RadioClass {
public:
    int Unknown_006C22A0(); // 0x006C22A0 (production time used by factories; hypothesis)

    TechnoClass(HouseClass *house);                             // 0x006C0CD0
    TechnoClass(NoInitClass const &noinit);                     // 0x006C1F10
    virtual ~TechnoClass();                                     // 0x006C20B0

    // Called by AircraftClass's destructor with 0 (0x006D3040; purpose unknown).
    void unknown_6d3040(TechnoClass *techno);

    virtual HRESULT __stdcall Load(IStream *stream);            // slot 5 0x006D6850
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // slot 6 0x006D6A80
    virtual void Init();                                        // slot 9 0x006C1C50
    bool unknown_6d7910(int ability);                           // 0x006D7910 (a veteran/elite ability of the type; Merge4c)
    void unknown_6d3400(TechnoClass *source);                   // 0x006D3400 (FootClass slot 86: a Whiner team member calls for help; hypothesis)
    void unknown_6d83f0(int index);                             // 0x006D83F0 (a weapon index 0..14; UnitClass constructor for Gunner types)
    virtual void Detach(AbstractClass *target, bool all = true);    // slot 10 0x006D2D10
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // slot 13 0x006D6AA0
    virtual int Owner() const;                                  // slot 14 0x006C7420
    virtual HouseClass *Owning_House() const;                   // slot 15 0x006C7430
    virtual void AI();                                          // slot 23 0x006C74C0
    virtual bool unknown_slot24();                              // slot 24 0x006C1320
    virtual int unknown_slot25(bool arg1, int arg2);             // slot 25 0x006CF3C0
    virtual int unknown_slot27(Cell const *cell, bool arg2, bool arg3);   // slot 27 0x006CCCE0
    virtual int unknown_slot28(ObjectClass *object, bool arg2);             // slot 28 0x006CC5D0
    virtual TechnoTypeClass *unknown_slot32();                  // slot 32 0x006C12C0 (Class_Of as a techno type)
    virtual int unknown_slot34();                               // slot 34 0x006D3E40
    virtual bool unknown_slot36();                              // slot 36 0x006CD690
    virtual bool unknown_slot38();                              // slot 38 0x006CD630
    virtual bool unknown_slot39();                              // slot 39 0x006CD290
    virtual CoordStruct unknown_slot43(int arg1);             // slot 43 0x006C1830
    virtual bool unknown_slot48() { return unknown_170; }       // slot 48 kept copy 0x0041B410
    virtual bool unknown_slot49(HouseClass *house) { return unknown_170; }   // slot 49 kept copy 0x0041B420
    virtual bool unknown_slot52();                               // slot 52 0x006C4480
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);             // slot 53 0x006C4610
    virtual void unknown_slot55(TechnoClass *techno);                      // slot 55 0x006CED90
    virtual void unknown_slot61();                              // slot 61 0x006CF3B0
    virtual int unknown_slot62(TechnoClass *techno);                       // slot 62 0x006D4880
    virtual void unknown_slot65(int arg1, int arg2);            // slot 65 0x006C3B30
    virtual void unknown_slot66(int arg1, int arg2);            // slot 66 0x006C2C40
    virtual void unknown_slot69();                              // slot 69 0x006C2520
    virtual void unknown_slot70(bool arg1, bool arg2);            // slot 70 0x006D5AA0
    virtual bool unknown_slot71(int arg1);                      // slot 71 0x006C2550
    virtual void unknown_slot79(int arg1);                      // slot 79 0x006C7440
    virtual bool unknown_slot80();                              // slot 80 0x006C91C0
    virtual void unknown_slot82(int arg1);                      // slot 82 0x006D86B0
    virtual bool unknown_slot84(CoordStruct const &coord, int weapon);  // slot 84 0x006C5240
    virtual int unknown_slot85(int arg1);                       // slot 85 0x006CD810
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6); // slot 86 0x006CDC40
    virtual int unknown_slot90();                               // slot 90 0x006D3150
    virtual void unknown_slot93(int arg1);                      // slot 93 0x006C2B40
    virtual int unknown_slot95(RadioClass *radio, int message, long &param);   // slot 95 0x006C2590
    virtual bool unknown_slot96(HouseClass *house);             // slot 96 0x006C2440
    virtual bool unknown_slot111();                             // slot 111 0x006D6DF0
    virtual bool unknown_slot112();                             // slot 112 0x006D6E00
    virtual bool unknown_slot113();                             // slot 113 0x006D6E10
    virtual bool unknown_slot114();                             // slot 114 0x006D6E30
    virtual int unknown_slot115();                              // slot 115 0x006D1480
    virtual void unknown_slot119(int mission, int unknown2, int unknown3);  // slot 119 0x006CD840
    virtual bool unknown_slot120();                             // slot 120 0x006CD880

    // New virtuals (slots 153-279); names, return types and parameters are
    // placeholders from the bodies (ret N) unless refined.
    virtual bool unknown_slot153();                                 // slot 153 (+0x264) 0x0041B360 (kept copy elsewhere)
    virtual bool unknown_slot154();                             // slot 154 (+0x268) 0x006D6DE0
    virtual bool unknown_slot155();                             // slot 155 (+0x26C) 0x006C12D0
    virtual bool unknown_slot156();                                 // slot 156 (+0x270) 0x00453B50 (kept copy elsewhere)
    virtual bool unknown_slot157();                                 // slot 157 (+0x274) 0x006D6780
    virtual bool unknown_slot158();                                 // slot 158 (+0x278) 0x006C7480
    virtual bool unknown_slot159() { return true; }                 // slot 159 (+0x27C) kept copy 0x0041B370
    virtual bool unknown_slot160();                                  // slot 160 (+0x280) 0x006C9020
    virtual bool unknown_slot161();                                  // slot 161 (+0x284) 0x006C8EF0
    virtual UnknownFacingDir unknown_slot162();                       // slot 162 (+0x288) 0x004CDDF0 (kept copy elsewhere)
    virtual bool unknown_slot163();                                   // slot 163 (+0x28C) 0x006CD670
    virtual int unknown_slot164();                                  // slot 164 (+0x290) 0x006D6E60 (returns in eax; Foot6 reads al in FootClass::AI)
    virtual double unknown_slot165();                           // slot 165 (+0x294) 0x006D3EA0
    virtual int unknown_slot166();                                  // slot 166 (+0x298) 0x006D3ED0
    virtual int unknown_slot167();                                  // slot 167 (+0x29C) 0x006D5850
    virtual int unknown_slot168();                              // slot 168 (+0x2A0) 0x006D3E50
    virtual bool unknown_slot169(AbstractClass *target);                         // slot 169 (+0x2A4) 0x00453B60 (kept copy elsewhere)
    virtual UnknownFacingDir unknown_slot170(AbstractClass *target);                // slot 170 (+0x2A8) 0x006CA540
    virtual bool unknown_slot171(CoordStruct const &coord);                          // slot 171 (+0x2AC) 0x006D32E0
    virtual int unknown_slot172();                              // slot 172 (+0x2B0) 0x006C16D0
    virtual void unknown_slot173();                             // slot 173 (+0x2B4) 0x006D8110
    virtual int unknown_slot174(AbstractClass *target);                      // slot 174 (+0x2B8) 0x006C1380
    virtual int unknown_slot175(ObjectClass *target);               // slot 175 (+0x2BC) 0x006C15D0
    virtual int unknown_slot176();                                  // slot 176 (+0x2C0) 0x006CFEA0
    virtual int unknown_slot177();                                  // slot 177 (+0x2C4) 0x00453B70 (kept copy elsewhere)
    virtual Cell unknown_slot178() { return unknown_geometry_k; }   // slot 178 (+0x2C8) kept copy 0x00453B80
    virtual void unknown_slot179(Cell cell) {}            // slot 179 (+0x2CC) kept copy 0x00453B90
    virtual Cell unknown_slot180(int arg1);               // slot 180 (+0x2D0) 0x006D5800
    virtual CoordStruct unknown_slot181(int arg1);                // slot 181 (+0x2D4) 0x006C1A70
    virtual int unknown_slot182(AbstractClass *object, Cell *cell);    // slot 182 (+0x2D8) 0x006D3EB0
    virtual UnknownFacingDir unknown_slot183();                   // slot 183 (+0x2DC) 0x006D3F80
    virtual InfantryTypeClass *unknown_slot184();                   // slot 184 (+0x2E0) 0x006D30B0 the crew type a crewed techno leaves
    virtual bool unknown_slot185();                                  // slot 185 (+0x2E4) 0x006CD300
    virtual bool unknown_slot186();                                 // slot 186 (+0x2E8) 0x006CD340 (returns al: xor al,al / sete al / mov al,1)
    virtual int unknown_slot187(int arg1);                          // slot 187 (+0x2EC) 0x006C9C00
    virtual int unknown_slot188(int arg1);                          // slot 188 (+0x2F0) 0x006D31E0
    virtual bool unknown_slot189();                                 // slot 189 (+0x2F4) 0x00453BA0 (kept copy elsewhere)
    virtual bool unknown_slot190(int *out_kind);                          // slot 190 (+0x2F8) 0x006D7A10
    virtual bool unknown_slot191();                             // slot 191 (+0x2FC) 0x006D7C00
    virtual bool unknown_slot192(HouseClass *house);            // slot 192 (+0x300) 0x006D7C40
    virtual bool unknown_slot193();                                 // slot 193 (+0x304) 0x0041B380 (kept copy elsewhere)
    virtual void unknown_slot194();                                 // slot 194 (+0x308) 0x00453BB0 (kept copy elsewhere)
    virtual bool unknown_slot195();                                 // slot 195 (+0x30C) 0x006CD6E0
    virtual void unknown_slot196();                             // slot 196 (+0x310) 0x006D3FA0
    virtual void unknown_slot197();                             // slot 197 (+0x314) 0x006D4000
    virtual void unknown_slot198();                             // slot 198 (+0x318) 0x006D4060
    virtual bool unknown_slot199(int type);                         // slot 199 (+0x31C) 0x006CC510
    virtual bool unknown_slot200(int arg1, AbstractClass *arg2, int arg3, int arg4); // slot 200 (+0x320) 0x006CC2A0
    virtual bool unknown_slot201() { return unknown_3fc > 0; } // slot 201 (+0x324) 0x006D8E80
    virtual bool unknown_slot202();                             // slot 202 (+0x328) 0x00453BC0 (kept copy elsewhere)
    virtual bool unknown_slot203() { return unknown_154.Value() > 0; }  // slot 203 (+0x32C) kept copy 0x0041B390 (the +0x154 timer still runs)
    virtual bool unknown_slot204();                                 // slot 204 (+0x330) 0x0041B3D0 (kept copy elsewhere)
    virtual void unknown_slot205();                                 // slot 205 (+0x334) 0x0041B3E0 (kept copy elsewhere)
    virtual int unknown_slot206() { TechnoTypeClass *type = unknown_slot32(); if (type) { return type->Speed; } return 0; } // slot 206 (+0x338) 0x006D8E90
    virtual void unknown_slot207();                             // slot 207 (+0x33C) 0x006D7E00
    virtual bool unknown_slot208(ObjectClass *target);              // slot 208 (+0x340) 0x006D8DB0
    virtual bool unknown_slot209(CoordStruct const *coord, int arg2);   // slot 209 (+0x344) 0x006D46D0
    virtual void unknown_slot210();                             // slot 210 (+0x348) 0x006C9A90
    virtual bool unknown_slot211(ObjectClass *target);              // slot 211 (+0x34C) 0x006C4F50
    virtual bool unknown_slot212(AbstractClass *target, int weapon);           // slot 212 (+0x350) 0x006C50A0
    virtual bool unknown_slot213(AbstractClass *target);                   // slot 213 (+0x354) 0x006C5070
    virtual bool unknown_slot214(CoordStruct const &coord);     // slot 214 (+0x358) 0x006C5200
    virtual bool unknown_slot215(AbstractClass *target);                        // slot 215 (+0x35C) 0x006C51A0
    virtual void unknown_slot216(int arg1) = 0;                                  // slot 216 (+0x360) 0x004B8960
    virtual int unknown_slot217(AbstractClass *target, int weapon);                // slot 217 (+0x364) 0x006C9240
    virtual int unknown_slot218(AbstractClass *target, int weapon, int arg3);      // slot 218 (+0x368) 0x006C9260
    virtual AbstractClass *unknown_slot219(int arg1, CoordStruct const *coord, bool arg3);      // slot 219 (+0x36C) 0x006C6530
    virtual void unknown_slot220(AbstractClass *target);                     // slot 220 (+0x370) 0x006C9AF0
    virtual BulletClass *unknown_slot221(AbstractClass *target, int arg2);                // slot 221 (+0x374) 0x006CA890
    virtual bool unknown_slot222(HouseClass *house, int arg2);                // slot 222 (+0x378) 0x006CD940
    virtual int unknown_slot223(int arg1, int arg2);                // slot 223 (+0x37C) 0x006D5F40
    virtual bool unknown_slot224(int arg1);                         // slot 224 (+0x380) 0x00453BD0 (kept copy elsewhere)
    virtual bool unknown_slot225();                             // slot 225 (+0x384) 0x006D84D0
    virtual int unknown_slot226();                              // slot 226 (+0x388) 0x006D84F0
    virtual int unknown_slot227();                              // slot 227 (+0x38C) 0x006D8500
    virtual int unknown_slot228();                              // slot 228 (+0x390) 0x006D8510
    virtual WeaponStruct *unknown_slot229();               // slot 229 (+0x394) 0x006D8520
    virtual WeaponStruct *unknown_slot230();               // slot 230 (+0x398) 0x006D85A0
    virtual WeaponStruct *unknown_slot231(int index);      // slot 231 (+0x39C) 0x006D8540
    virtual bool unknown_slot232();                                 // slot 232 (+0x3A0) 0x0041B3F0 (kept copy elsewhere)
    virtual void unknown_slot233();                                 // slot 233 (+0x3A4) 0x006CD8B0
    virtual void unknown_slot234(int arg1);                         // slot 234 (+0x3A8) 0x006C89C0
    virtual int unknown_slot235();                                  // slot 235 (+0x3AC) 0x006C83F0
    virtual int unknown_slot236();                                  // slot 236 (+0x3B0) 0x006C86F0
    virtual int unknown_slot237();                                  // slot 237 (+0x3B4) 0x006D6230
    virtual void unknown_slot238();                                  // slot 238 (+0x3B8) 0x006C2990
    virtual void unknown_slot239();                                 // slot 239 (+0x3BC) 0x006C8290
    virtual void unknown_slot240();                                 // slot 240 (+0x3C0) 0x0041B400 (kept copy elsewhere)
    virtual CoordStruct unknown_slot241();                      // slot 241 (+0x3C4) 0x006D13B0
    virtual bool unknown_slot242();                             // slot 242 (+0x3C8) 0x006D1460
    virtual void unknown_slot243(bool arg1, int arg2);               // slot 243 (+0x3CC) 0x00453BE0 (kept copy elsewhere)
    virtual int unknown_slot244(int arg1);                          // slot 244 (+0x3D0) 0x006D8C30
    virtual bool unknown_slot245(HouseClass *house);                // slot 245 (+0x3D4) 0x006D8CE0
    virtual int unknown_slot246(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9); // slot 246 (+0x3D8) 0x006D1D00
    virtual void unknown_slot247(int arg1, int arg2);           // slot 247 (+0x3DC) 0x006C3B20
    virtual int unknown_slot248(int arg1, int arg2, int arg3);      // slot 248 (+0x3E0) 0x006C3F00
    virtual int unknown_slot249();                                  // slot 249 (+0x3E4) 0x006D4920
    virtual void unknown_slot250(Point2D const &point, Rect const &window);  // slot 250 (+0x3E8) 0x006D5440
    virtual int unknown_slot251(int arg1, int arg2, int arg3);      // slot 251 (+0x3EC) 0x006D5510
    virtual void unknown_slot252(bool quiet);                   // slot 252 (+0x3F0) 0x006CF250
    virtual void unknown_slot253(bool quiet);                       // slot 253 (+0x3F4) 0x006CF300
    virtual int unknown_slot254(int arg1);                      // slot 254 (+0x3F8) 0x006D79D0
    virtual void unknown_slot255(TechnoClass *techno);                     // slot 255 (+0x3FC) 0x006D8680
    virtual void unknown_slot256();                             // slot 256 (+0x400) 0x0041B430 (kept copy elsewhere)
    virtual bool unknown_slot257();                             // slot 257 (+0x404) 0x006D4890
    virtual bool unknown_slot258();                                 // slot 258 (+0x408) 0x0041B440 (kept copy elsewhere)
    virtual void unknown_slot259(int arg1);                         // slot 259 (+0x40C) 0x006D48D0
    virtual void unknown_slot260(AbstractClass *target, int arg2);               // slot 260 (+0x410) 0x006D48E0
    virtual bool unknown_slot261(bool arg1, bool arg2);           // slot 261 (+0x414) 0x006D48F0
    virtual void unknown_slot262(bool arg1, bool arg2, bool arg3, HouseClass *house); // slot 262 (+0x418) 0x006D5C30 (the counterpart of slot 263: byte flags and a house, DisplayClass 0x0049DE00)
    virtual void unknown_slot263(bool arg1, bool arg2, bool arg3, HouseClass *house); // slot 263 (+0x41C) 0x006D5E90
    virtual void unknown_slot264();                             // slot 264 (+0x420) 0x006D74D0
    virtual void unknown_slot265();                             // slot 265 (+0x424) 0x006D7500
    virtual void unknown_slot266();                             // slot 266 (+0x428) 0x006D7530
    virtual void unknown_slot267(bool arg1);                        // slot 267 (+0x42C) 0x006D8120
    virtual int unknown_slot268(UnknownSlot268Arg const *arg) { return arg->unknown_0c; } // slot 268 (+0x430) 0x006D8EB0
    virtual void unknown_slot269() {}                          // slot 269 (+0x434) 0x006D8EC0
    virtual bool unknown_slot270() { return false; }           // slot 270 (+0x438) 0x006D8ED0
    virtual bool unknown_slot271() { return false; }           // slot 271 (+0x43C) 0x006D8EE0
    virtual int unknown_slot272() { return -1; }               // slot 272 (+0x440) 0x006D8EF0
    virtual CoordStruct unknown_slot273() { return CoordStruct(-1, -1, -1); } // slot 273 (+0x444) 0x006D8F00
    virtual bool unknown_slot274();  // slot 274 (+0x448) 0x006D8F20
    virtual bool unknown_slot275();  // slot 275 (+0x44C) 0x006D8F40
    virtual bool unknown_slot276() { return false; }           // slot 276 (+0x450) 0x006D8F90
    virtual bool unknown_slot277() { return false; }           // slot 277 (+0x454) 0x006D8FA0
    virtual void unknown_slot278() {}                          // slot 278 (+0x458) 0x006D8FB0
    virtual bool unknown_slot279() { return false; }           // slot 279 (+0x45C) 0x006D8FC0

    void unknown_6d1420(UnknownTechno408 *value);              // 0x006D1420
    void unknown_6d9670(long delay);                            // 0x006D9670 (restarts the +0x148 timer)
    UnknownTechno408 *unknown_6d1430() const;                   // 0x006D1430
    void unknown_6d6e50(AbstractClass *value);                  // 0x006D6E50
    void unknown_6d0990(CoordStruct from, CoordStruct to, RGBClass color);   // 0x006D0990 (draws a line; CaptureManagerClass 0x00468150)
    void Unknown_006D9610(AbstractClass *cell);                 // 0x006D9610 (InfantryClass slot 93: an occupied building, its cell)
    bool unknown_6d7f70();                                      // 0x006D7F70 (FootClass::AI, after the movement; the result is unused there)
    int unknown_6d7e20(int extra);                              // 0x006D7E20 (fires the death weapon at itself; returns the damage)
    int Unknown_006D21E0(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11);  // 0x006D21E0 (the shadow draw; FootClass 0x004C9A40)
    int unknown_6d6750();                                       // 0x006D6750
    bool unknown_6d83d0();                                      // 0x006D83D0
    bool unknown_6d83e0();                                      // 0x006D83E0
    bool unknown_6d8460() const;                                // 0x006D8460
    int unknown_6d8470() const;                                 // 0x006D8470
    int unknown_6d84a0();                                       // 0x006D84A0
    bool unknown_615360();                                      // 0x00615360 (out of this unit; returns al)
    static void __fastcall unknown_6d79c0(bool value);          // 0x006D79C0
    static void unknown_6d7990();                               // 0x006D7990 (restarts unknown_timer_ac0178 at 25)
    static void __fastcall unknown_6d8fd0(TechnoClass *techno, int value);   // 0x006D8FD0 (sets the talk-bubble techno and restarts its timer)
    void unknown_6145e0();                                      // 0x006145E0 (out of this unit)
    bool Unknown_006D8640(WeaponStruct *weapon);                // 0x006D8640 (InfantryClass slot 137)
    void unknown_6c8300();                                      // 0x006C8300
    void unknown_6d7f30();                                      // 0x006D7F30
    // Draws a shape frame (0x006D1510; ret 0x3C, fifteen arguments; names
    // hypotheses; BuildingClass slot 68).
    void unknown_6d1510(void const *shape, int drawer, Point2D const *point, Rect const *bounds, int arg5, int arg6,
                        int z, int arg8, int arg9, int height, int arg11, int arg12, int arg13, int arg14, int arg15);
    int unknown_6d86f0(int value);                              // 0x006D86F0 (adjusts the slot 254 value when slot 203 holds; BuildingClass slot 79)
    void unknown_6cdc00(HouseClass *house);                     // 0x006CDC00 (sets House; +0x372 when it is the player's)
    void unknown_6d95a0(UnknownCellClass *cell);                // 0x006D95A0
    void unknown_6d95d0(UnknownCellClass *cell);                // 0x006D95D0
    void unknown_6d2ca0(int x, int y);                           // 0x006D2CA0 (sets the draw depth +0x322; never called)
    int unknown_6d46b0(int mission);                            // 0x006D46B0 (mission neither 5 nor 6; never called)
    EBolt *unknown_6ca020(AbstractClass *target, WeaponTypeClass *weapon, CoordStruct const &source);   // 0x006CA020 (a new electric bolt from source to target)
    EBolt *unknown_6ca130(AbstractClass *target);               // 0x006CA130 (fires an electric bolt; never called)
    void unknown_6ca1d0(AbstractClass *target, int chrono);     // 0x006CA1D0 (draws a rad or chrono beam to the target)
    int unknown_6ca6c0(TechnoClass *target, WeaponTypeClass *weapon);   // 0x006CA6C0 (the damage a weapon would do to target)
    void unknown_6ca340(int spread);                            // 0x006CA340 (rad beams to the eight cells around at a spread)
    void unknown_6d4400();                                      // 0x006D4400 (DistributedFire target spreading; TechnoClass slot 209)
    bool unknown_6d7d20(int weapon);                            // 0x006D7D20 (TechnoClass slot 170)
    void unknown_6155e0();                                      // 0x006155E0 (out of this unit; TechnoClass slot 222)
    int unknown_6cd6f0();                                       // 0x006CD6F0 (the height bonus above the map's lowest level; never called)
    int unknown_6c6350(Cell const *cell);                       // 0x006C6350 (the threat of a wall cell to break; TechnoClass slot 219)
    bool unknown_6c5570(int method, int arg2, int arg3, ObjectClass *object, int *value, int arg6, CoordStruct const *coord);   // 0x006C5570 (rates an object as a target; TechnoClass slot 219)
    bool unknown_6c6130(int method, int arg2, Cell const *cell, int arg4, ObjectClass **object, int *value, int zone);   // 0x006C6130 (the best target in a cell; TechnoClass slot 219)
    LaserDrawClass *unknown_6c9df0(AbstractClass *target, int weapon_index, WeaponTypeClass *weapon, CoordStruct const &source);   // 0x006C9DF0 (draws the weapon's laser)
    bool unknown_6d9710() const;                                // 0x006D9710 (the +0x148 timer has run out)
    CoordStruct unknown_6d65b0();                               // 0x006D65B0 (FootClass slot 243: the far end of a line to draw)
    void unknown_6d0510(CoordStruct from, CoordStruct to, RGBClass color, int arg8, int arg9);   // 0x006D0510 (draws a line between two points)
    bool unknown_6d1440();                                      // 0x006D1440 (+0x408 set and its 0x00613B60 positive)
    int unknown_6d8480();                                       // 0x006D8480 (copies +0x100 into +0x104; whether it changed)
    bool unknown_6d1470();                                      // 0x006D1470 (0x00615360's result; Fly 0x004BF1F0 tests al)
    void unknown_6d96a0();                                      // 0x006D96A0 (restarts the +0x148 timer at 4-8 when over 10)
    int unknown_6d85e0(int index);                              // 0x006D85E0 (a valid weapon index)
    int unknown_6cf9d0();                                       // 0x006CF9D0 (FootClass slot 176: times ZFudgeColumn)
    int unknown_6cfb60();                                       // 0x006CFB60 (times ZFudgeTunnel)
    int unknown_6cfda0();                                       // 0x006CFDA0 (times ZFudgeCliff)
    int unknown_6c4a70(ObjectClass *other);                     // 0x006C4A70
    int unknown_6c48f0(ObjectClass *other);                     // 0x006C48F0
    bool unknown_6cf670();                                      // 0x006CF670 (ZFudgeBridge applies)
    bool unknown_6cf820();                                      // 0x006CF820
    bool unknown_6d4180();                                      // 0x006D4180
    bool unknown_6d4310();                                      // 0x006D4310
    int unknown_6d5870();                                       // 0x006D5870 (anti-air strength of the secondary weapon / 50)
    Cell unknown_6cf130(AbstractClass *target);           // 0x006CF130
    bool unknown_6d8080();                                      // 0x006D8080
    bool unknown_6d40c0();                                      // 0x006D40C0 (may look for a target now)
    int unknown_6c16f0(int weapon);                             // 0x006C16F0 (+0x98 plus +0xA4 of a weapon, or their average)
    bool unknown_6d3b60(TechnoClass *source, int arg2);         // 0x006D3B60 (whether to answer an attack by source; arg2 unused)
    double unknown_6d7550(ObjectClass *target, CoordStruct const &coord);   // 0x006D7550 (a threat value of the target; hypothesis)
    void unknown_6d8820();                                      // 0x006D8820 (steps the +0x16C state on the +0x160 timer while slot 203 holds; TechnoClass::AI)
    bool unknown_6c4bb0(CoordStruct const *coord, AbstractClass *target, WeaponTypeClass *weapon);   // 0x006C4BB0 (in range; hypothesis)
    int unknown_6d5900();                                       // 0x006D5900 (ground strength of the secondary weapon, Verses[4])
    int unknown_6d59d0();                                       // 0x006D59D0 (the same with Verses[0])

    int unknown_d8;                         // +0x0D8
    bool unknown_dc;                        // +0x0DC
    UnknownStage AnimationStage;                // +0x0E0 value, countdown, rate and step (through +0x0F7)
    UnknownCargo Cargo;                     // +0x0F8 (count, first object; swizzled)
    int unknown_100;                        // +0x100 (-1)
    int unknown_104;                        // +0x104 (-1)
    ObjectClass *unknown_108;               // +0x108 (swizzled; listed in 0x00AC0BF8)
    int unknown_10c;                        // +0x10C
    int unknown_110;                        // +0x110 (-1)
    int unknown_114;                        // +0x114 (-1)
    UnknownTechnoPair unknown_118;          // +0x118
    double unknown_120;                     // +0x120 (1.0)
    double unknown_128;                     // +0x128 (1.0)
    CDTimerClass<FrameTimerClass> unknown_130;  // +0x130
    CDTimerClass<FrameTimerClass> unknown_13c;  // +0x13C
    CDTimerClass<FrameTimerClass> unknown_148;  // +0x148 (45)
    CDTimerClass<FrameTimerClass> unknown_154;  // +0x154
    CDTimerClass<FrameTimerClass> unknown_160;  // +0x160
    int unknown_16c;                        // +0x16C
    bool unknown_170;                       // +0x170
    int unknown_174;                        // +0x174
    CDTimerClass<FrameTimerClass> unknown_178;  // +0x178
    CDTimerClass<FrameTimerClass> unknown_184;  // +0x184
    bool unknown_190;                       // +0x190
    CDTimerClass<FrameTimerClass> unknown_194;  // +0x194
    Point2D unknown_1a0;                    // +0x1A0 the point the radar tracks (slots 264-266)
    int unknown_1a8;                        // +0x1A8
    int unknown_1ac;                        // +0x1AC (-1)
    AbstractClass *unknown_1b0;             // +0x1B0 (swizzled)
    HouseClass *House;                      // +0x1B4
    int unknown_1b8;                        // +0x1B8
    UnknownStage unknown_1bc;               // +0x1BC
    CDTimerClass<FrameTimerClass> unknown_1d4;  // +0x1D4
    float unknown_1e0;                      // +0x1E0
    bool unknown_1e4;                       // +0x1E4
    CoordStruct unknown_1e8;                // +0x1E8
    int unknown_1f4;                        // +0x1F4
    int unknown_1f8;                        // +0x1F8
    bool unknown_1fc;                       // +0x1FC
    bool unknown_1fd;                       // +0x1FD
    int unknown_200;                        // +0x200
    bool unknown_204;                       // +0x204
    bool unknown_205;                       // +0x205
    bool unknown_206;                       // +0x206
    UnknownTechno208 *unknown_208;          // +0x208 (owned; swizzled)
    AbstractClass *unknown_20c;             // +0x20C (swizzled)
    bool unknown_210;                       // +0x210
    int unknown_214;                        // +0x214
    int unknown_218;                        // +0x218
    CoordStruct unknown_21c;                // +0x21C
    AbstractClass *unknown_228;             // +0x228 (swizzled)
    AbstractClass *unknown_22c;             // +0x22C (swizzled)
    AbstractClass *unknown_230;             // +0x230 (owned; swizzled)
    AbstractClass *unknown_234;             // +0x234 (swizzled)
    SpawnManagerClass *SpawnManager;          // +0x238 (owned; swizzled)
    AbstractClass *unknown_23c;             // +0x23C (swizzled)
    float unknown_240;                      // +0x240 (float: TechnoClass::Compute_CRC hashes it as one)
    CDTimerClass<FrameTimerClass> unknown_244;  // +0x244
    int unknown_250;                        // +0x250
    int unknown_254;                        // +0x254 (-1)
    int unknown_258;                        // +0x258
    ObjectClass *unknown_25c[8];            // +0x25C (swizzled; [3] gets slot 60 in 0x006D7F30)
    AbstractClass *unknown_27c;             // +0x27C (swizzled)
    float unknown_280;                      // +0x280 (float: Compute_CRC)
    float unknown_284;                      // +0x284 (float: Compute_CRC)
    float unknown_288;                      // +0x288 (a spin rate set when the unit dies; FootClass slot 224)
    float unknown_28c;                      // +0x28C (a second rate; FootClass slot 224)
    int unknown_290;                        // +0x290 (-1)
    StorageClass unknown_294;               // +0x294
    int unknown_2a4;                        // +0x2A4
    UnknownTimed unknown_2a8;               // +0x2A8
    FacingClass unknown_2c8;                // +0x2C8 (rate 3)
    FacingClass unknown_2e0;                // +0x2E0
    FacingClass unknown_2f8;                // +0x2F8
    int unknown_310;                        // +0x310
    CDTimerClass<FrameTimerClass> unknown_314;  // +0x314
    short unknown_320;                      // +0x320 (random when constructed)
    short unknown_322;                      // +0x322
    bool unknown_324;                       // +0x324
    bool unknown_325;                       // +0x325
    bool unknown_326;                       // +0x326
    bool unknown_327;                       // +0x327
    bool unknown_328;                       // +0x328
    bool unknown_329;                       // +0x329
    bool unknown_32a;                       // +0x32A
    bool unknown_32b;                       // +0x32B
    bool unknown_32c;                       // +0x32C
    bool unknown_32d;                       // +0x32D
    UnknownTechnoBlock unknown_330;         // +0x330
    UnknownTechnoBlock unknown_350;         // +0x350
    bool unknown_370;                       // +0x370
    bool unknown_371;                       // +0x371
    bool unknown_372;                       // +0x372
    bool unknown_373;                       // +0x373
    bool unknown_374;                       // +0x374
    bool unknown_375;                       // +0x375
    bool unknown_376;                       // +0x376
    bool unknown_377;                       // +0x377
    char unknown_378;                       // +0x378 (signed: the height level last revealed from; TechnoClass slot 70)
    bool unknown_379;                       // +0x379 (true)
    bool unknown_37a;                       // +0x37A (true)
    bool unknown_37b;                       // +0x37B
    bool unknown_37c;                       // +0x37C
    bool unknown_37d;                       // +0x37D
    bool unknown_37e;                       // +0x37E
    bool unknown_37f;                       // +0x37F
    bool unknown_380;                       // +0x380
    bool unknown_381;                       // +0x381
    AbstractClass *unknown_384;             // +0x384 (swizzled)
    bool unknown_388;                       // +0x388
    int unknown_38c;                        // +0x38C
    DynamicVectorClass<int> unknown_390;    // +0x390
    DynamicVectorClass<AbstractClass *> unknown_3a8;    // +0x3A8
    DynamicVectorClass<AbstractClass *> unknown_3c0;    // +0x3C0
    UnknownAudioController unknown_3d8;     // +0x3D8
    int unknown_3ec;                        // +0x3EC (1)
    int unknown_3f0;                        // +0x3F0
    int unknown_3f4;                        // +0x3F4 (the frame when constructed)
    AbstractClass *unknown_3f8;             // +0x3F8 (swizzled)
    int unknown_3fc;                        // +0x3FC
    int unknown_400;                        // +0x400
    bool unknown_404;                       // +0x404 (TechnoClass 0x006D4310 sets it)
    UnknownTechno408 *unknown_408;          // +0x408 (released by the destructor)
    ObjectTypeClass *unknown_40c;           // +0x40C (swizzled; a type: the disguise, InfantryClass slots 50/255/256)
    HouseClass *unknown_410;                // +0x410 (swizzled; a house: the disguise's, InfantryClass slots 51/256)
    int unknown_414;                        // +0x414
};

// BuildingClass: shared/building.hpp (Building.CPP).
// A building (only the member used here; Building.cpp).
// The building type flag TechnoClass 0x006D40C0 reads (stand-in).
class UnknownTechnoBuildingType {
public:
    char unknown_0000[0x121E];
    bool unknown_121e;                  // +0x121E
};
// A building: only the members other units use. shared/building.hpp has the
// full class (Building.CPP) and defines RA2_BUILDING_FULL before including
// this header, so a unit that needs both includes building.hpp first.
#ifndef RA2_BUILDING_FULL
class BuildingClass : public TechnoClass {
public:
    int unknown_4532f0();               // 0x004532F0
    bool Unknown_00452EB0(TechnoClass *techno);     // 0x00452EB0 (whether techno may enter; InfantryClass slot 132)
    void Unknown_004536D0(InfantryClass *infantry);     // 0x004536D0 (an Assaulter enters; InfantryClass 0x005094B0)
    BuildingTypeClass *Type;            // +0x418 (AircraftClass slots 28/101)
    void unknown_44d070(int damaged);   // 0x0044D070 (TechnoClass slot 233: health at or below the rules' +0x1368)
    int unknown_449dd0();               // 0x00449DD0 (the power the building drains; as shared/building_class.hpp)
    char unknown_41c[0x434 - 0x41C];
    int unknown_434;                    // +0x434 (TechnoClass slot 55; the full class names it in shared/building.hpp)
    char unknown_438[0x4C0 - 0x438];
    TechnoTypeClass *unknown_4c0[3];    // +0x4C0 the upgrades (as shared/building_class.hpp; BaseClass::Get_Building)
    char unknown_4cc[0x4EC - 0x4CC];
    int unknown_4ec;                    // +0x4EC (a laser fence's state; FootClass slot 93: below 8 it hurts)
    char unknown_4f0[0x530 - 0x4F0];
    bool unknown_530;                   // +0x530 (HouseClass 0x004F2E50: a radar building counts only with it)
    bool unknown_531;                   // +0x531 (TechnoClass slot 174: always the secondary weapon)
    char unknown_532[0x554 - 0x532];
    DynamicVectorClass<InfantryClass *> unknown_554;    // +0x554 (the occupants; InfantryClass 0x005094B0)
};
#else
class BuildingClass;
#endif

// Every techno (0x00A40C20) and two other lists it joins (0x00AC0D08) or
// may join (0x00AC0BF8, while unknown_108 is set).
extern DynamicVectorClass<TechnoClass *> Technos;                       // 0x00A40C20


// The tactical view's member TechnoClass slot 164 calls (proposal: declare
// it on shared/gscreen.hpp's Tactical).
class UnknownTacticalView {
public:
    Cell Unknown_006A6A50(CoordStruct const &coord);      // 0x006A6A50 (the cell a coordinate shows in)
};

// Voc_Play_At (0x00713E60): shared/sound_play.hpp.
// The cell 0x006CF130 returns when there is none (0x00AC0148).
extern Cell unknown_cell_ac0148;
// The object at 0x008322E0 whose 0x004366D0 TechnoClass slot 52 calls for a
// type with BombSight (+0x540; meaning not recovered).
class UnknownList8322E0 {
public:
    void Unknown_00436680(TechnoClass *techno);     // 0x00436680 (TechnoClass slot 53: joins)
    void Unknown_004366D0(TechnoClass *techno);     // 0x004366D0
};
extern UnknownList8322E0 unknown_list_8322e0;

extern unsigned int unknown_ac01cc;     // 0x00AC01CC (frames between target scans; TechnoClass 0x006D40C0)

// The overlay types (UnknownOverlayType, 0x00A35DE8): shared/overlay_view.hpp.
#include "shared/overlay_view.hpp"
struct UnknownTechnoCellView {
    char unknown_00[0x44];
    int Overlay;                            // +0x44 (-1 none)
};

#endif
