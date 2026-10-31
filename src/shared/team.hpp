// TeamClass: a live AI team (Team.cpp, 0x006B7240-0x006BE75D; RTTI vtables
// 0x007AC950 primary, 0x007AC934 IRTTITypeInfo at +4, 0x007AC92C
// INoticeSink, 0x007AC924 INoticeSource).
//
// Layout (from the constructor 0x006B7430, Load 0x006BAAE0 and Compute_CRC
// 0x006BAC30; names are hypotheses, the rest stays unknown_):
//   +0x24  TeamTypeClass *Class
//   +0x28  ScriptClass *Script        new ScriptClass(Class->Script)
//   +0x2C  HouseClass *Owner
//   +0x30..+0x4C  eight words (+0x44 the third constructor argument)
//   +0x50  int unknown_50            frame when created
//   +0x54  FootClass *Member         first member (chained at +0x4C8)
//   +0x58  CDTimerClass<FrameTimerClass>
//   +0x64  a timer of the same shape whose NoInitClass constructor is out of line
//   +0x70  TagClass *Tag             new TagClass(Class->Tag)
//   +0x74  16 bool flags (names from YRpp's TeamClass, hypotheses; the
//          constructor sets +0x7A, +0x7D and +0x80; script handlers set
//          StepCompleted +0x80)
//   +0x84  int unknown_84[6]         cleared by the constructor (CRC'd as 0x18 bytes)
//   size 0x9C (Size_Of)
#ifndef RA2_SHARED_TEAM_HPP
#define RA2_SHARED_TEAM_HPP

#include "shared/unknown_globals.hpp"
#include "shared/abstract_type.hpp"
#include "shared/cd_timer.hpp"
#include "shared/techno.hpp"   // UnknownTimer423F60
#include "shared/script.hpp"
#include "shared/lightning_storm.hpp"   // the storm calls (0x0051F930, 0x0051FBB0, 0x0051FC50)

class TeamTypeClass;
class ScriptClass;
class TagClass;
class FootClass;
class ScriptMissionClass;

// Free functions of other units the script handlers call (hypotheses).
void __fastcall Unknown_006D8FD0(FootClass *member, int arg2);       // 0x006D8FD0
int __fastcall Unknown_006220E0(int value);                          // 0x006220E0 (the target kind for a script argument; hypothesis)

class BuildingTypeClass;
// The enemy building of a type that rates best by mode (0x006BCF70: lowest or highest house
// value of its cell's block, nearest or farthest from member; see its source).
AbstractClass *__fastcall Unknown_006BCF70(BuildingTypeClass *type, HouseClass *enemy, FootClass *member, int arg4, bool arg5);
// The same pick among the member's own house's buildings (0x006BD240; hypothesis).
AbstractClass *__fastcall Unknown_006BD240(BuildingTypeClass *type, HouseClass *enemy, FootClass *member, int arg4, bool arg5);


class CellClass;
// The cell a target is (kind 0x0B), or 0.
inline CellClass *As_Cell(AbstractClass *target)
{
    if (target == 0) {
        return 0;
    }
    return target->Kind_Of() == 0xB ? (CellClass *)target : 0;
}

extern "C" GUID const CLSID_TeamClass;            // 0x007A1CD0

class TeamClass : public AbstractClass {
public:
    TeamClass(NoInitClass const &noinit) :                          // (inlined into Load)
        AbstractClass(noinit), unknown_58(noinit), unknown_64(noinit) {}
    virtual ~TeamClass();                                           // 0x006B7770 (scalar deleting 0x006BE740)

    bool Unknown_006B8FB0(FootClass *member, int slot, bool arg3);  // 0x006B8FB0 (removes a member: Red Alert's Remove; slot -1 finds it by type)
    bool Unknown_006BA990();                                        // 0x006BA990
    int Unknown_006BE6A0();                                         // 0x006BE6A0 (how far a member may stray; FootClass 0x004C3000)
    void Unknown_006B9AA0(FootClass *member, int result, TechnoClass *source);   // 0x006B9AA0 (a member was damaged; hypothesis)

    TeamClass(TeamTypeClass *type, HouseClass *owner, int arg3);    // 0x006B7430
    bool unknown_func_6b8bb0();                                     // 0x006B8BB0 (updates the strength flags after the members changed)
    bool unknown_func_6b8cc0(FootClass *member);                    // 0x006B8CC0 (adds a member)
    bool unknown_func_6b8dc0(FootClass *member, int *slot);         // 0x006B8DC0 (whether member may join; its task force slot)
    int unknown_func_6b91c0(int slot);                              // 0x006B91C0 (Red Alert's Recruit: adds the nearest object for a task force slot)
    void unknown_func_6b9610(AbstractClass **first, AbstractClass **second);   // 0x006B9610
    void unknown_func_6b8860();                                     // 0x006B8860
    void unknown_func_6b88b0();                                     // 0x006B88B0 (TS Regroup: back to the best unarmed own building)
    void unknown_func_6b79e0(AbstractClass *target);                // 0x006B79E0 (sets the team's target)
    void unknown_func_6baa30();                                     // 0x006BAA30 (clears the target of the team and its members)
    bool unknown_func_6be6e0();                                     // 0x006BE6E0 (whether any member has ammo or unlimited ammo)
    static bool __fastcall unknown_func_6bdd80(ObjectClass *object);  // 0x006BDD80
    bool unknown_func_6bd810();                                     // 0x006BD810 (whether the task force has a transporter that carries passengers)
    bool unknown_func_6b9f40();                                     // 0x006B9F40 (Red Alert's Coordinate_Regroup: whether no member had to move)
    void unknown_func_6b9bb0();                                     // 0x006B9BB0
    void unknown_func_6ba1a0();                                     // 0x006BA1A0
    FootClass *unknown_func_6baa60();                               // 0x006BAA60 (the best member for leading: highest LeadershipRating)
    void unknown_func_6bd870(DynamicVectorClass<TechnoTypeClass *> &types);   // 0x006BD870 (the techno types the task force still lacks)
    static void __fastcall unknown_func_6ba8e0(int priority, HouseClass *house);   // 0x006BA8E0 (disbands the lower-priority teams of a house)
    bool unknown_func_6ba7d0(FootClass *member);                    // 0x006BA7D0
    bool unknown_func_6ba600();                                     // 0x006BA600 (moves stray members back; returns and keeps whether any lags: Red Alert's Lagging_Units)
    bool unknown_func_6ba8b0(FootClass *object);                    // 0x006BA8B0 (whether object is a member)
    bool unknown_func_6baa00();                                     // 0x006BAA00 (whether every member has +0x32D set)
    void unknown_func_6bd990(int value);                            // 0x006BD990 (stores value in every member)

    // Script action handlers (second argument unknown).
    void TMission_unknown_6bbe60(ScriptMissionClass const &mission, int unknown);  // 0x006BBE60
    void TMission_unknown_6bbe90(ScriptMissionClass const &mission, int unknown);  // 0x006BBE90
    void TMission_unknown_6bbec0(ScriptMissionClass const &mission, int unknown);  // 0x006BBEC0
    void TMission_unknown_6bbef0(ScriptMissionClass const &mission, int unknown);  // 0x006BBEF0
    void TMission_unknown_6bc360(ScriptMissionClass const &mission, int unknown);  // 0x006BC360
    void TMission_unknown_6bc380(ScriptMissionClass const &mission, int unknown);  // 0x006BC380
    void TMission_unknown_6bc410(ScriptMissionClass const &mission, int unknown);  // 0x006BC410
    void TMission_unknown_6bc290(ScriptMissionClass const &mission, int unknown);  // 0x006BC290
    void TMission_unknown_6bc4a0(ScriptMissionClass const &mission, int unknown);  // 0x006BC4A0
    void TMission_unknown_6bc3a0(ScriptMissionClass const &mission, int unknown);  // 0x006BC3A0
    void TMission_unknown_6bc2e0(ScriptMissionClass const &mission, int unknown);  // 0x006BC2E0
    void TMission_unknown_6bc460(ScriptMissionClass const &mission, int unknown);  // 0x006BC460
    void TMission_unknown_6bc5b0(ScriptMissionClass const &mission, int unknown);  // 0x006BC5B0
    void TMission_unknown_6bc5f0(ScriptMissionClass const &mission, int unknown);  // 0x006BC5F0
    void TMission_unknown_6bc660(ScriptMissionClass const &mission, int unknown);  // 0x006BC660
    void TMission_unknown_6bc6d0(ScriptMissionClass const &mission, bool unknown);  // 0x006BC6D0
    void TMission_unknown_6bc070(ScriptMissionClass const &mission, int unknown);  // 0x006BC070
    void TMission_unknown_6bda70(ScriptMissionClass const &mission, bool unknown);  // 0x006BDA70
    void TMission_unknown_6bb350(ScriptMissionClass const &mission, int unknown);  // 0x006BB350
    void TMission_unknown_6bc4c0(ScriptMissionClass const &mission, int unknown);  // 0x006BC4C0
    void TMission_unknown_6badc0(ScriptMissionClass const &mission, bool unknown);  // 0x006BADC0
    void TMission_unknown_6bae00(ScriptMissionClass const &mission, bool unknown);  // 0x006BAE00
    void TMission_unknown_6bd9b0(ScriptMissionClass const &mission, bool unknown);  // 0x006BD9B0
    void TMission_unknown_6bb3b0(ScriptMissionClass const &mission, int unknown);  // 0x006BB3B0
    void TMission_unknown_6bb420(ScriptMissionClass const &mission, int unknown);  // 0x006BB420
    void TMission_unknown_6bbb40(ScriptMissionClass const &mission, bool unknown);  // 0x006BBB40
    void TMission_unknown_6bb260(ScriptMissionClass const &mission, bool unknown);  // 0x006BB260
    void TMission_unknown_6bb020(ScriptMissionClass const &mission, bool unknown);  // 0x006BB020
    void TMission_unknown_6bbf20(ScriptMissionClass const &mission, int unknown);  // 0x006BBF20
    void TMission_unknown_6bb0f0(ScriptMissionClass const &mission, bool unknown);  // 0x006BB0F0
    void TMission_unknown_6bb310(ScriptMissionClass const &mission, int unknown);  // 0x006BB310
    void TMission_unknown_6bc040(ScriptMissionClass const &mission, int unknown);  // 0x006BC040
    void TMission_unknown_6bc130(ScriptMissionClass const &mission, int unknown);  // 0x006BC130
    void TMission_unknown_6bc160(ScriptMissionClass const &mission, int unknown);  // 0x006BC160
    void TMission_unknown_6bc190(ScriptMissionClass const &mission, int unknown);  // 0x006BC190
    void TMission_unknown_6bc260(ScriptMissionClass const &mission, int unknown);  // 0x006BC260
    void TMission_unknown_6bc1e0(ScriptMissionClass const &mission, int unknown);  // 0x006BC1E0 (jump to line Data - 2)
    void TMission_unknown_6bc250(ScriptMissionClass const &mission, int unknown);  // 0x006BC250 (nothing)
    void TMission_unknown_6bd7f0(ScriptMissionClass const &mission, int unknown);  // 0x006BD7F0 (also sets IsSuspended)
    void TMission_unknown_6bae60(ScriptMissionClass const &mission, bool unknown);  // 0x006BAE60
    void TMission_unknown_6bc7b0(ScriptMissionClass const &mission, int unknown);  // 0x006BC7B0
    void TMission_unknown_6bb480(ScriptMissionClass const &mission, int unknown);  // 0x006BB480 (leader picks a target of kind Data; done once members are armed)
    void TMission_unknown_6bb8b0(ScriptMissionClass const &mission, int unknown);  // 0x006BB8B0 (Red Alert's TMission_Deploy)
    void TMission_unknown_6bbbb0(ScriptMissionClass const &mission, int unknown);  // 0x006BBBB0 (Red Alert's Coordinate_Do; mission Data)
    void TMission_unknown_6bd4b0(ScriptMissionClass const &mission, int unknown);  // 0x006BD4B0 (Red Alert's TMission_Unload)
    void TMission_unknown_6bddb0(ScriptMissionClass const &mission, bool unknown);  // 0x006BDDB0 (toward the enemy base from the own one)
    void TMission_unknown_6be1c0(ScriptMissionClass const &mission, int unknown);  // 0x006BE1C0 (fires super weapons 3 and 4: chronoshift)
    void TMission_unknown_6bc980(ScriptMissionClass const &mission, bool unknown);  // 0x006BC980 (as 0x006BC7B0 over the leader's own house, 0x006BD240)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);              // 0x006BABF0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                // 0x006BAAE0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006BABD0 slot 6

    virtual void Detach(AbstractClass *target, bool all = true);    // 0x006B9590 slot 10
    virtual int Kind_Of() const { return 0x22; }                    // 0x006BE730 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(TeamClass); }       // 0x006BE720 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;               // 0x006BAC30 slot 13
    virtual void AI();                                              // 0x006B7AD0 slot 23

    TeamTypeClass *Class;           // +0x24
    ScriptClass *Script;            // +0x28
    HouseClass *Owner;              // +0x2C
    AbstractClass *unknown_30;      // +0x30 (swizzled; class unknown)
    AbstractClass *unknown_34;      // +0x34 (swizzled; class unknown)
    AbstractClass *unknown_38;      // +0x38 (swizzled; class unknown)
    AbstractClass *unknown_3c;      // +0x3C (swizzled; class unknown)
    AbstractClass *unknown_40;      // +0x40 (swizzled; class unknown)
    AbstractClass *unknown_44;      // +0x44 (swizzled; class unknown)
    int unknown_48;                 // +0x48
    int unknown_4c;                 // +0x4C
    int unknown_50;                 // +0x50
    FootClass *Member;              // +0x54
    CDTimerClass<FrameTimerClass> unknown_58;   // +0x58
    UnknownTimer423F60 unknown_64;              // +0x64 (NoInitClass constructor out of line)
    TagClass *Tag;                  // +0x70
    bool IsTransient;                  // +0x74
    bool NeedsReGrouping;              // +0x75
    bool GuardSlowerIsNotUnderStrength;// +0x76
    bool IsForcedActive;               // +0x77
    bool IsHasBeen;                    // +0x78
    bool IsFullStrength;               // +0x79
    bool IsUnderStrength;              // +0x7A
    bool IsReforming;                  // +0x7B
    bool IsLagging;                    // +0x7C
    bool NeedsToDisappear;             // +0x7D
    bool JustDisappeared;              // +0x7E
    bool IsMoving;                     // +0x7F
    bool StepCompleted;                // +0x80
    bool TargetNotAssigned;            // +0x81
    bool IsLeavingMap;                 // +0x82
    bool IsSuspended;                  // +0x83
    int unknown_84[6];              // +0x84
};

extern DynamicVectorClass<TeamClass *> Teams;      // 0x00866178

#endif
