// CCINIClass::Put_RTTIType (0x0046A4F0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_RTTIType(char const *section, char const *entry, RTTIType rtti)
{
    return Put_String(section, entry, Name_From_RTTI(rtti));
}
