// CCINIClass::Put_SourceType (0x0046AE10).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?SourceNames@@3PAPBDA=0079ab50

bool CCINIClass::Put_SourceType(char const *section, char const *entry, SourceType source)
{
    return Put_String(section, entry, SourceNames[source]);
}
