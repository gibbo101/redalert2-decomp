// AnimTypeClass *__fastcall unknown_ini_anim_653df0(INIClass const &ini, char const *section, char const *entry, AnimTypeClass *defvalue) -- 0x00653DF0
// Purpose: the AnimTypeClass named by the INI value (read into a 128-byte buffer,
// Find_Or_Make 0x004264A0), or defvalue when the entry is absent or empty. 0x00653E40 is an identical copy.
// Callers: the Rules unit (0x0064635E and nine more).
// Assumptions: a Rules-unit helper (Westwood's per-type INI readers);
// its name is a placeholder.
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?Find_Or_Make@AnimTypeClass@@SIPAV1@PBD@Z=004264a0

class INIClass {
public:
    int Get_String(char const *section, char const *entry, char const *defvalue, char *buffer, int size) const;
};

class AnimTypeClass {
public:
    static AnimTypeClass *__fastcall Find_Or_Make(char const *name);
};

AnimTypeClass *__fastcall unknown_ini_anim_653df0(INIClass const &ini, char const *section, char const *entry, AnimTypeClass *defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, "", buffer, sizeof(buffer))) {
        return AnimTypeClass::Find_Or_Make(buffer);
    }
    return defvalue;
}
