// AbstractTypeClass: the root of the INI-defined type classes (AbsType.cpp,
// members 0x00410580-0x00410A33; RTTI vtables 0x0079AE88 primary, 0x0079AE6C
// IRTTITypeInfo at +4, 0x0079AE64 INoticeSink, 0x0079AE5C INoticeSource).
//
// Layout (from the constructor 0x00410580, Read_INI 0x004107E0, Write_INI
// 0x00410910 and Compute_CRC 0x00410960):
//   +0x00  AbstractClass (0x24 bytes)
//   +0x24  FixedString<25> ID           the INI section name
//   +0x3D  FixedString<32> UINameLabel  string-table label ("UIName=")
//   +0x60  wchar_t const *UIName        the label's text, or an empty string
//   +0x64  FixedString<49> Name         "Name=", initially the ID
//   size 0x98 (0x95 rounded)
// Every constructed type is added to AbstractTypes (0x00A40928) and removed
// by the destructor.
#ifndef RA2_SHARED_ABSTRACT_TYPE_HPP
#define RA2_SHARED_ABSTRACT_TYPE_HPP

#include "shared/abstract.hpp"
#include "shared/ini_class.hpp"
#include "shared/string_table.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
extern "C" int __cdecl _stricmp(char const *left, char const *right);

#include "shared/fixed_string.hpp"

// The rules INI and its list readers.
#include "shared/ccini_class.hpp"

// The empty text a type without a UIName label shows (0x00839D4C).
extern wchar_t const unknown_empty_wide_839d4c[];

class AbstractTypeClass : public AbstractClass {
public:
    AbstractTypeClass(char const *ini_name);                     // 0x00410580
    AbstractTypeClass(NoInitClass const &noinit);                // 0x004106E0
    virtual ~AbstractTypeClass();                                // 0x00410740

    bool operator==(char const *ini_name) const;                 // 0x004107C0 (case-insensitive ID)

    virtual void Compute_CRC(WWCRCEngine &crc) const;            // 0x00410960 slot 13
    virtual void unknown_slot24(int value);                      // 0x004109A0 (nothing)
    virtual bool Read_INI(CCINIClass &ini);                      // 0x004107E0 slot 25
    virtual bool Write_INI(CCINIClass &ini) const;               // 0x00410910 slot 26

    FixedString<25> ID;             // +0x24
    FixedString<32> UINameLabel;    // +0x3D
    wchar_t const *UIName;          // +0x60
    FixedString<49> Name;           // +0x64
};

extern DynamicVectorClass<AbstractTypeClass *> AbstractTypes;   // 0x00A40928

#endif
