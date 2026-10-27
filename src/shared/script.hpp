// ScriptTypeClass and ScriptClass: the AI team scripts (Script.cpp,
// 0x00668540-0x00669396; RTTI vtables ScriptClass 0x007A9328 primary /
// 0x007A930C / 0x007A9304 / 0x007A92FC, ScriptTypeClass 0x007A93B8 /
// 0x007A939C / 0x007A9394 / 0x007A938C).
//
// ScriptTypeClass layout (constructor 0x00668A20, Read_INI 0x00668C10):
//   +0x00  AbstractTypeClass (0x98 bytes)
//   +0x98  int ArrayIndex       ScriptTypes.ID(this) when constructed
//   +0x9C  int IsGlobal         set by Read_Scenario_INI's second argument
//   +0xA0  int MissionCount     lines in use
//   +0xA4  ScriptMissionClass MissionList[50]   "0=" .. "49=": action,argument
//   size 0x234 (Size_Of)
// ScriptClass layout (constructor 0x00668730):
//   +0x00  AbstractClass (0x24 bytes)
//   +0x24  ScriptTypeClass *Class
//   +0x28  int unknown_28       0 when constructed
//   +0x2C  int CurrentMission   -1 before the first line
//   size 0x30 (Size_Of)
// Names follow Westwood's TS vocabulary; hypotheses throughout.
#ifndef RA2_SHARED_SCRIPT_HPP
#define RA2_SHARED_SCRIPT_HPP

#include "shared/abstract_type.hpp"

class ObjectClass;
class TeamTypeClass;

// Shared with object.hpp (same declaration).

extern "C" GUID const CLSID_ScriptClass;          // 0x007A1D10
extern "C" GUID const CLSID_ScriptTypeClass;      // 0x007A1D20 (hypothesis: read from 0x006690C0)

// One script line: an action and its argument.
class ScriptMissionClass {
public:
    ScriptMissionClass() {}
    ScriptMissionClass(int mission, int data) : Mission(mission), Data(data) {}
    ScriptMissionClass(char const *text);       // 0x006EAF60 ("%d,%d")
    int Build_INI_Entry(char *buffer) const;    // 0x006EAFA0 ("%d,%d"; returns the length)

    int Mission;    // +0x00
    int Data;       // +0x04
};

class ScriptTypeClass : public AbstractTypeClass {
public:
    ScriptTypeClass(char const *ini_name);                          // 0x00668A20
    ScriptTypeClass(NoInitClass const &noinit) : AbstractTypeClass(noinit) {}   // (inlined into Load)
    virtual ~ScriptTypeClass();                                     // 0x00668AE0

    static void __fastcall Read_Scenario_INI(CCINIClass &ini, int is_global);   // 0x00668CE0
    static ScriptTypeClass *__fastcall Find_By_ID_Or_Name(char const *name);    // 0x00668EB0
    static ScriptTypeClass *__fastcall Find_By_Name(char const *name);          // 0x00668F20
    static ScriptTypeClass *__fastcall Find_Or_Make(char const *name);          // 0x00668F70

    virtual HRESULT __stdcall GetClassID(GUID *clsid);              // 0x006690C0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                // 0x00669100 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00669150 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);    // 0x006691A0 slot 10
    virtual int Kind_Of() const { return 0x1B; }                    // 0x006692E0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(ScriptTypeClass); } // 0x006692F0 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;               // 0x00669170 slot 13
    virtual int unknown_slot16() const { return ArrayIndex; }       // 0x00669300 (inline)
    virtual bool Read_INI(CCINIClass &ini);                         // 0x00668C10 slot 25
    virtual bool Write_INI(CCINIClass &ini) const;                  // 0x00668B60 slot 26

    int ArrayIndex;                         // +0x98
    int IsGlobal;                           // +0x9C
    int MissionCount;                       // +0xA0
    ScriptMissionClass MissionList[50];     // +0xA4
};

class ScriptClass : public AbstractClass {
public:
    ScriptClass(ScriptTypeClass *type);                             // 0x00668730
    ScriptClass(NoInitClass const &noinit) : AbstractClass(noinit) {}   // (inlined into Load)
    virtual ~ScriptClass();                                         // 0x006687D0

    ScriptMissionClass Get_Current_Mission() const;                 // 0x00668870
    ScriptMissionClass Get_Next_Mission() const;                    // 0x006688B0
    bool Reset();                                                   // 0x00668900
    bool Set_Mission(int mission);                                  // 0x00668910
    bool Next_Mission();                                            // 0x00668920
    bool Has_Mission() const;                                       // 0x00668940

    virtual HRESULT __stdcall GetClassID(GUID *clsid);              // 0x00668960 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                // 0x006689A0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00668A00 slot 6
    virtual int Kind_Of() const { return 0x1A; }                    // 0x00669230 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(ScriptClass); }     // 0x00669240 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;               // 0x00668850 slot 13

    ScriptTypeClass *Class;     // +0x24
    int unknown_28;             // +0x28
    int CurrentMission;         // +0x2C
};

extern DynamicVectorClass<ScriptTypeClass *> ScriptTypes;  // 0x00866258
extern DynamicVectorClass<ScriptClass *> Scripts;          // 0x00839900
extern DynamicVectorClass<TeamTypeClass *> TeamTypes;      // 0x00A40C48

#endif
