// int __fastcall unknown_upgrade_from_name(char const *name) -- 0x00713300
// Purpose: the index of name (case-insensitive) in the 18 veteran/crate
// ability names at 0x007F9978 ("FASTER", "STRONGER", ... "CRUSHER");
// -1 when it is not listed.
// Assumptions: the owning type's name for this lookup is unknown.
// @ref _stricmp=00781f20
// @ref ?unknown_ability_names_7f9978@@3PAPBDA=007f9978

extern "C" int __cdecl _stricmp(char const *left, char const *right);
extern char const *unknown_ability_names_7f9978[18];

int __fastcall unknown_upgrade_from_name(char const *name)
{
    for (int index = 0; index < 18; index++) {
        if (_stricmp(unknown_ability_names_7f9978[index], name) == 0) {
            return index;
        }
    }
    return -1;
}
