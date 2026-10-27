// CCINIClass::Put_Listed_Name (0x0046AC60).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?unknown_names_a71050@@3V?$DynamicVectorClass@PBD@@A=00a71050

bool CCINIClass::Put_Listed_Name(char const *section, char const *entry, unsigned index)
{
    if (index >= (unsigned)unknown_names_a71050.Count()) {
        return Put_String(section, entry, "<none>");
    }
    return Put_String(section, entry, unknown_names_a71050[index]);
}
