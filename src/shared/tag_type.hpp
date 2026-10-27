// TagTypeClass: a scenario tag type (TagType.cpp, unit 0x006B4300; RTTI
// vtables 0x007AC7E4 primary (27 slots), 0x007AC7C8 IRTTITypeInfo at +4,
// 0x007AC7C0 INoticeSink, 0x007AC7B8 INoticeSource).
//
// Layout (from the constructor 0x006B4570, Read_INI 0x006B4A90 and
// Write_INI 0x006B4B70; names follow the "[Tags]" entry "persistence,
// name, trigger"):
//   +0x00  AbstractTypeClass (0x98)
//   +0x98  int ArrayIndex   (the index in TagTypes)
//   +0x9C  int Persistence  (0, 1, 2)
//   +0xA0  TriggerTypeClass *Triggers (chained through Next)
//   size 0xA4
// Every type is added to TagTypes (0x00ABFEA0) and the abstract list
// 0x00AC0CB0.
#ifndef RA2_SHARED_TAG_TYPE_HPP
#define RA2_SHARED_TAG_TYPE_HPP

#include "shared/trigger_type.hpp"

extern "C" GUID const CLSID_TagTypeClass;       // 0x007A1D40
// The scenario INI section of the tags ("Tags"; a pointer at 0x007AC770).
extern char const *const unknown_tags_section_7ac770;
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *buffer, char const *format, ...);
// A hexadecimal number written as text (the [Tags] entry names; 0x00412390).
long __fastcall Unknown_00412390(char const *text);
// The empty string INI readers default to (0x0083C55C).
extern char unknown_string_83c55c[];
extern "C" int __cdecl atoi(char const *string);
#include "shared/crt_tokens.hpp"

// Called first by the abstract destructors (0x006ECB90).

class TagTypeClass : public AbstractTypeClass {
public:
    TagTypeClass(char const *ini_name);                                 // 0x006B4570
    TagTypeClass(NoInitClass const &noinit) : AbstractTypeClass(noinit) {}
    virtual ~TagTypeClass();                                            // 0x006B46B0

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x006B4DB0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006B4E20 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006B4E80 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x006B4860 slot 10
    virtual int Kind_Of() const;                                        // 0x006B4EA0 slot 11
    virtual int Size_Of() const;                                        // 0x006B4EB0 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006B4DF0 slot 13
    virtual int unknown_slot16() const;                                 // 0x006B4EC0
    virtual bool Read_INI(CCINIClass &ini);                             // 0x006B4A90 slot 25
    virtual bool Write_INI(CCINIClass &ini) const;                      // 0x006B4B70 slot 26

    bool Attach_Trigger(TriggerTypeClass *trigger);                     // 0x006B47E0
    bool Detach_Trigger(TriggerTypeClass *trigger);                     // 0x006B4810
    int unknown_func_6b4c00() const;                                    // 0x006B4C00 (the triggers' flags)
    bool unknown_func_6b4c30() const;                                   // 0x006B4C30
    bool unknown_func_6b4c60() const;                                   // 0x006B4C60
    bool unknown_func_6b4c90() const;                                   // 0x006B4C90
    bool unknown_func_6b4cc0() const;                                   // 0x006B4CC0
    bool Is_Trigger_Attached(TriggerTypeClass *trigger) const;          // 0x006B4CF0

    static TagTypeClass *__fastcall From_Name(char const *name);        // 0x006B4880 (by ID or name)
    static void __fastcall Read_Scenario_INI(CCINIClass &ini);          // 0x006B48E0
    static void __fastcall Write_Scenario_INI(CCINIClass &ini);         // 0x006B49F0
    static TagTypeClass *__fastcall Find_Or_Make(char const *name);     // 0x006B4D20

    int ArrayIndex;                         // +0x98
    int Persistence;                        // +0x9C
    TriggerTypeClass *Triggers;             // +0xA0
};

// Every tag type (0x00ABFEA0; defined in this unit).
extern DynamicVectorClass<TagTypeClass *> unknown_TagTypeClass_list_00abfea0;

#endif
