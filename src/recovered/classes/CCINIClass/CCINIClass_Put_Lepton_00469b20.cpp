// CCINIClass::Put_Lepton (0x00469B20).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Put_Double@INIClass@@QAE_NPBD0N@Z=0050e540

bool CCINIClass::Put_Lepton(char const *section, char const *entry, int lepton)
{
    return Put_Double(section, entry, lepton / 256.0);
}
