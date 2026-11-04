#define RA2_WOL_SERVER_ARRAY_GET_SOURCE
// int __fastcall unknown_quarry_from_name(char const *name) -- 0x00622090
// Purpose: the index of name (case-insensitive) in the 12 quarry (target category)
// names at 0x007A8620 ("N/A", ...); 0 when it is not listed.
// Assumptions: the owning type's name for this lookup is unknown.
// @ref _stricmp=00781f20
// @ref ?unknown_quarry_names_7a8620@@3PAPBDA=007a8620

extern "C" int __cdecl _stricmp(char const *left, char const *right);
extern char const *unknown_quarry_names_7a8620[12];

int __fastcall unknown_quarry_from_name(char const *name)
{
    for (int index = 0; index < 12; index++) {
        if (_stricmp(name, unknown_quarry_names_7a8620[index]) == 0) {
            return index;
        }
    }
    return 0;
}
