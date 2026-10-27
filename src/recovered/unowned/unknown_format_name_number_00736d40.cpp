// char const *__fastcall unknown_format_name_number(char const *name, int number) -- 0x00736D40
// Purpose: formats "<name><number>" (or just the number without a name)
// into the shared buffer at 0x00B25EF0 and returns it.
// Assumptions: what the names are (WOL area) is unknown.
// @ref __imp__wsprintfA=0079a4a4
// @ref ?unknown_buffer_b25ef0@@3PADA=00b25ef0
// @ref ??_C@_04MOFI@?$CFs?$CFd?$AA@=007fd0d4
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *buffer, char const *format, ...);
extern char unknown_buffer_b25ef0[];

char const *__fastcall unknown_format_name_number(char const *name, int number)
{
    if (name != 0) {
        wsprintfA(unknown_buffer_b25ef0, "%s%d", name, number);
        return unknown_buffer_b25ef0;
    }
    wsprintfA(unknown_buffer_b25ef0, "%d", number);
    return unknown_buffer_b25ef0;
}
