// TaskForceClass: a named group of techno types and counts that a team
// type builds (TaskForce.cpp, 0x006B6660-0x006B723D; RTTI vtables 0x007AC8A0
// primary, 0x007AC884 IRTTITypeInfo at +4, 0x007AC87C INoticeSink,
// 0x007AC874 INoticeSource).
//
// Layout (from the constructor 0x006B6850, the copy constructor 0x006B69D0,
// Read_INI 0x006B6DF0 and Load 0x006B7060):
//   +0x00  AbstractTypeClass (0x98 bytes)
//   +0x98  int Group            -1 when constructed; "Group="
//   +0x9C  int CountEntries     entries in use
//   +0xA0  int IsGlobal         set by Read_Scenario_INI's second argument
//   +0xA4  TaskForceEntryStruct Entries[6]   "0=" .. "5=": count,type
//   size 0xD4 (Size_Of)
// Every constructed task force is added to TaskForces (0x00A40890) and
// removed by the destructor. Names follow Westwood's TS/RA2 vocabulary;
// hypotheses throughout.
#ifndef RA2_SHARED_TASK_FORCE_HPP
#define RA2_SHARED_TASK_FORCE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/abstract_type.hpp"
#include "shared/techno_type.hpp"

class ObjectClass;

// Shared with object.hpp (same declaration): releases references to the
// object being destroyed (name unknown).

// Parses a hexadecimal ID as written by AbstractTypeClass's "%08X" names
// (name hypothesis).
long __fastcall unknown_hex_to_long_412390(char const *string);      // 0x00412390


extern "C" GUID const CLSID_TaskForceClass;                           // 0x007A1CE0

// One "N=count,TYPE" line of a task force.
struct TaskForceEntryStruct {
    TaskForceEntryStruct() {}
    TaskForceEntryStruct(int amount, TechnoTypeClass *type) : Amount(amount), Type(type) {}
    TaskForceEntryStruct(char const *text);     // 0x004B4860 (sscanf "%d,%s", type from the
                                                // infantry, unit and aircraft type lists)
    char const *Text() const;                   // 0x004B4900 ("%d,%s" into a static buffer)

    void Compute_CRC_004B4930(WWCRCEngine &crc) const;

    int Amount;                 // +0x00
    TechnoTypeClass *Type;      // +0x04
};

class TaskForceClass : public AbstractTypeClass {
public:
    TaskForceClass(char const *ini_name);                           // 0x006B6850
    TaskForceClass(NoInitClass const &noinit);                      // 0x006B6920
    virtual ~TaskForceClass();                                      // 0x006B6950
    TaskForceClass(TaskForceClass const &that);                     // 0x006B69D0
    TaskForceClass operator=(TaskForceClass const &that);           // 0x006B6AC0 (returns a copy)

    int Total_Amount() const;                                       // 0x006B6B30
    static TaskForceClass *__fastcall Find_By_ID(char const *name);     // 0x006B6B50
    static TaskForceClass *__fastcall Find_By_Name(char const *name);   // 0x006B6BA0
    static void __fastcall Read_Scenario_INI(CCINIClass &ini, int is_global);    // 0x006B6BF0
    static void __fastcall Write_Scenario_INI(CCINIClass &ini, int is_global);   // 0x006B6D10
    bool unknown_all_kind16_6b6f70() const;                         // 0x006B6F70 (every entry's type
                                                                    // has Kind_Of() == 16)
    static TaskForceClass *__fastcall Find_Or_Make(char const *name);   // 0x006B6FB0
    int Max_Tech_Level() const;                                     // 0x006B7140 (name hypothesis)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);              // 0x006B70D0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                // 0x006B7060 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006B7040 slot 6
    virtual int Kind_Of() const { return 0x21; }                    // 0x006B7190 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(TaskForceClass); }  // 0x006B71A0 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;               // 0x006B7110 slot 13
    virtual bool Read_INI(CCINIClass &ini);                         // 0x006B6DF0 slot 25
    virtual bool Write_INI(CCINIClass &ini) const;                  // 0x006B6ED0 slot 26

    int Group;                          // +0x98
    int CountEntries;                   // +0x9C
    int IsGlobal;                       // +0xA0
    TaskForceEntryStruct Entries[6];    // +0xA4
};

extern DynamicVectorClass<TaskForceClass *> TaskForces;     // 0x00A40890

#endif
