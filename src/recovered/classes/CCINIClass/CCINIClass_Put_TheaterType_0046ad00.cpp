// CCINIClass::Put_TheaterType (0x0046AD00).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68

bool CCINIClass::Put_TheaterType(char const *section, char const *entry, TheaterType theater)
{
    return Put_String(section, entry, Theaters[theater].Name);
}
