// TeamTypeClass: an INI-defined AI team recipe (TeamType.cpp,
// 0x006BE760-0x006C0365; RTTI vtables 0x007AC9F0 primary, 0x007AC9D4
// IRTTITypeInfo at +4, 0x007AC9CC INoticeSink, 0x007AC9C4 INoticeSource).
//
// Layout (from the constructor 0x006BE9B0, Read_INI 0x006BF330, Load
// 0x006BFDA0, Detach 0x006BF2D0 and Compute_CRC 0x006BFE70; INI key names
// give most field names):
//   +0x00  AbstractTypeClass (0x98 bytes)
//   +0x98  int ArrayIndex            TeamTypes.ID(this)
//   +0x9C  int Group                 -1; "Group=" (-1: the task force's)
//   +0xA0  int VeteranLevel          1
//   +0xA4  16 bool flags             "Loadable=" .. "OnTransOnly=" (+0xB2 not read)
//   +0xB4  int Priority              7
//   +0xB8  int Max                   -1
//   +0xBC  int unknown_bc
//   +0xC0  HouseClass *Owner         "House="
//   +0xC4  int TechLevel
//   +0xC8  TagTypeClass *Tag         "Tag="
//   +0xCC  int Waypoint              -1
//   +0xD0  int TransportWaypoint     -1
//   +0xD4  int unknown_d4            teams alive of this type
//   +0xD8  ScriptTypeClass *Script
//   +0xDC  TaskForceClass *TaskForce
//   +0xE0  int IsGlobal
//   +0xE4  int unknown_e4            9
//   +0xE8  8 bool flags              (+0xEA AvoidThreats .. +0xEF OnlyTargetHouseEnemy)
//   size 0xF0 (Size_Of)
// Every team type is added to TeamTypes (0x00A40C48) and to the abstract
// list 0x00AC0CB0. Hypotheses throughout.
#ifndef RA2_SHARED_TEAM_TYPE_HPP
#define RA2_SHARED_TEAM_TYPE_HPP

#include "shared/abstract_type.hpp"

class ObjectClass;
class FootClass;
class HouseClass;       // derives from AbstractClass (RTTI); the shared stand-in does not yet
class TagTypeClass;
class ScriptTypeClass;
class TaskForceClass;
class TeamClass;
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0cb0;   // 0x00AC0CB0 (shared/object.hpp)

class TeamTypeClass;

extern DynamicVectorClass<TeamTypeClass *> TeamTypes;      // 0x00A40C48

// Shared with object.hpp (same declarations).

extern "C" GUID const CLSID_TeamTypeClass;        // 0x007A1CF0

extern "C" int __cdecl isxdigit(int character);   // 0x00782BB4
extern "C" int __cdecl isdigit(int character);    // 0x00782B8C

class TeamTypeClass : public AbstractTypeClass {
public:
    Cell Unknown_006BFA90() const;                 // 0x006BFA90 (the team's waypoint cell; FootClass slot 134)
    TeamTypeClass(char const *ini_name);                            // 0x006BE9B0
    TeamTypeClass(NoInitClass const &noinit) : AbstractTypeClass(noinit) {}   // (inlined into Load)
    virtual ~TeamTypeClass();                                       // 0x006BEBB0 (also expanded into 0x006C0280)

    void Destroy_All_Of() const;                                    // 0x006BED10
    static TeamTypeClass *__fastcall Find_By_ID_Or_Name(char const *name);  // 0x006BF260
    int Get_Group() const;                                          // 0x006BFA60
    static TeamTypeClass *__fastcall Find_Or_Make(char const *name);    // 0x006BFB10
    static void __fastcall Read_Scenario_INI(CCINIClass &ini, int is_global);   // 0x006BFBA0
    static void __fastcall Write_Scenario_INI(CCINIClass &ini, int is_global);  // 0x006BFCA0
    Cell Waypoint_Location() const;                               // 0x006BFA90 (the waypoint's cell; hypothesis)
    TeamClass *Create_One_Of(HouseClass *house);                  // 0x006BEC80 (a new team of this type; hypothesis)
    Cell Transport_Waypoint_Location() const;                     // 0x006BFAD0 (the transport waypoint's cell; hypothesis)
    bool unknown_func_6c0010(FootClass *foot, HouseClass *house);      // 0x006C0010 (the foot may join a team of this type; HouseClass::Can_Build_Team)
    void unknown_func_6c0110(int value) const;                      // 0x006C0110 (each team of this type)
    TeamClass *Find_Team() const;                                   // 0x006C0150 (first team of this type)
    void unknown_func_6c0180();                                     // 0x006C0180 (+0xE4/+0xE8/+0xE9 from the task force: movement zones, naval transports)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);              // 0x006BFE30 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                // 0x006BFDA0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006BFD80 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);    // 0x006BF2D0 slot 10
    virtual int Kind_Of() const { return 0x23; }                    // 0x006C0250 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(TeamTypeClass); }   // 0x006C0260 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;               // 0x006BFE70 slot 13
    virtual int unknown_slot16() const { return ArrayIndex; }       // 0x006C0270 (inline)
    virtual bool Read_INI(CCINIClass &ini);                         // 0x006BF330 slot 25
    virtual bool Write_INI(CCINIClass &ini) const;                  // 0x006BF770 slot 26

    int ArrayIndex;                 // +0x98
    int Group;                      // +0x9C
    int VeteranLevel;               // +0xA0
    bool Loadable;                  // +0xA4
    bool Full;                      // +0xA5
    bool Annoyance;                 // +0xA6
    bool GuardSlower;               // +0xA7
    bool Recruiter;                 // +0xA8
    bool Autocreate;                // +0xA9
    bool Prebuild;                  // +0xAA
    bool Reinforce;                 // +0xAB
    bool Whiner;                    // +0xAC
    bool Aggressive;                // +0xAD
    bool LooseRecruit;              // +0xAE
    bool Suicide;                   // +0xAF
    bool Droppod;                   // +0xB0
    bool UseTransportOrigin;        // +0xB1
    bool unknown_b2;                // +0xB2
    bool OnTransOnly;               // +0xB3
    int Priority;                   // +0xB4
    int Max;                        // +0xB8
    int unknown_bc;                 // +0xBC
    HouseClass *Owner;              // +0xC0
    int TechLevel;                  // +0xC4
    TagTypeClass *Tag;              // +0xC8
    int Waypoint;                   // +0xCC
    int TransportWaypoint;          // +0xD0
    int unknown_d4;                 // +0xD4
    ScriptTypeClass *Script;        // +0xD8
    TaskForceClass *TaskForce;      // +0xDC
    int IsGlobal;                   // +0xE0
    int unknown_e4;                 // +0xE4
    bool unknown_e8;                // +0xE8
    bool unknown_e9;                // +0xE9
    bool AvoidThreats;              // +0xEA
    bool IonImmune;                 // +0xEB
    bool TransportsReturnOnUnload;  // +0xEC
    bool AreTeamMembersRecruitable; // +0xED
    bool IsBaseDefense;             // +0xEE
    bool OnlyTargetHouseEnemy;      // +0xEF
};


#endif
