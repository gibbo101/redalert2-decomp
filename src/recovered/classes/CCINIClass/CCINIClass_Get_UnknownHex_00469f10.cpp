// CCINIClass::Get_UnknownHex_469f10 (0x00469F10): the entry read with Get_Hex
// as an UnknownHexValue. Unreferenced in the original.

UnknownHexValue CCINIClass::Get_UnknownHex_469f10(char const *section, char const *entry, int defvalue) const
{
    return UnknownHexValue(Get_Hex(section, entry, defvalue));
}
