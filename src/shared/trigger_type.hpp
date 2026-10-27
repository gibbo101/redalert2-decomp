// TriggerTypeClass: a scenario trigger type (TriggerType.cpp; RTTI vtables
// 0x007ADA8C primary (27 slots), 0x007ADA70 IRTTITypeInfo at +4,
// 0x007ADA68 INoticeSink, 0x007ADA60 INoticeSource).
//
// Layout (from the constructor 0x006EDEB0; names are hypotheses):
//   +0x00  AbstractTypeClass (0x98)
//   +0x98  int ArrayIndex (-1), +0x9C..+0x9F bools (true), +0xA0 bool
//   +0xA4  AbstractTypeClass *unknown_a4 (swizzled; CRC'd by ID)
//   +0xA8  TriggerTypeClass *Next (the tag type's chain)
//   +0xAC  TEventClass *Events, +0xB0 TActionClass *Actions (chained)
// Every type is added to the abstract lists 0x00AC0C98 and 0x00AC0CB0.
#ifndef RA2_SHARED_TRIGGER_TYPE_HPP
#define RA2_SHARED_TRIGGER_TYPE_HPP

#include "shared/abstract_type.hpp"
#include "shared/tevent.hpp"
#include "shared/taction.hpp"

// The persistence names (0x007F85C0: "Volatile", "Semi-persistant",
// "Persistent").
extern char const *PersistenceNames[3];
// Leading and trailing white space removed in place (0x006EEF10 and the
// wide copy 0x006EEF80; Westwood's strtrim).
char *__fastcall strtrim(char *buffer);
wchar_t *__fastcall wcstrim(wchar_t *buffer);
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);
extern "C" unsigned int __cdecl wcslen(wchar_t const *string);
extern "C" char *__cdecl strcpy(char *destination, char const *source);
#pragma intrinsic(strcpy)

class TriggerTypeClass : public AbstractTypeClass {
public:
    TriggerTypeClass(char const *ini_name);                             // 0x006EDEB0
    TriggerTypeClass(NoInitClass const &noinit) : AbstractTypeClass(noinit) {}
    virtual ~TriggerTypeClass();                                        // 0x006EE030

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x006EEDD0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006EEE10 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006EEEA0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x006EE2C0 slot 10
    virtual int Kind_Of() const;                                        // 0x006EEEC0 slot 11
    virtual int Size_Of() const;                                        // 0x006EEED0 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006EED50 slot 13
    virtual int unknown_slot16() const;                                 // 0x006EEEE0
    virtual bool Read_INI(CCINIClass &ini);                             // 0x006EE470 slot 25
    virtual bool Write_INI(CCINIClass &ini) const;                      // 0x006EE8C0 slot 26

    bool Remove_Event(TEventClass *event);                              // 0x006EEC60 (deletes it)
    static TriggerTypeClass *__fastcall From_Name(char const *name);    // 0x006EE350 (by ID or name)
    static int __fastcall Persistence_From_Name(char const *name);      // 0x006EE3C0

    int unknown_func_6ee410() const;                                    // 0x006EE410 (event flags)
    bool unknown_func_6ee180() const;                                   // 0x006EE180
    bool unknown_func_6ee1b0() const;                                   // 0x006EE1B0
    bool unknown_func_6ee1e0() const;                                   // 0x006EE1E0
    bool unknown_func_6ee210() const;                                   // 0x006EE210
    bool unknown_func_6ee240(int value) const;                          // 0x006EE240
    bool unknown_func_6ee280(int value) const;                          // 0x006EE280
    static TriggerTypeClass *__fastcall Find_Or_Make(char const *name); // 0x006EECC0
    static char const *__fastcall Name_From_Persistence(int persistence);   // 0x006EE400
    static void __fastcall Read_Scenario_INI(CCINIClass &ini);          // 0x006EE7F0
    static void __fastcall Write_Scenario_INI(CCINIClass &ini);         // 0x006EEAA0

    int ArrayIndex;                         // +0x98
    bool IsEasy;                            // +0x9C enabled on easy (hypothesis)
    bool IsNormal;                          // +0x9D enabled on normal
    bool IsHard;                            // +0x9E enabled on hard
    bool IsEnabled;                         // +0x9F
    bool unknown_a0;                        // +0xA0
    AbstractTypeClass *unknown_a4;          // +0xA4
    TriggerTypeClass *Next;                 // +0xA8
    TEventClass *Events;                    // +0xAC
    TActionClass *Actions;                  // +0xB0
};

// The scenario INI sections of triggers (0x007ADA50 "Triggers", 0x007ADA54
// "Actions", 0x007ADA58 "Events"; names from the readers).
extern char const *unknown_triggers_section_7ada50;
extern char const *unknown_actions_section_7ada54;
extern char const *unknown_events_section_7ada58;

// Every trigger type (0x00866208; defined in the globals unit).
extern DynamicVectorClass<TriggerTypeClass *> TriggerTypes;
extern "C" GUID const CLSID_TriggerTypeClass;   // 0x007A1D60

#endif
