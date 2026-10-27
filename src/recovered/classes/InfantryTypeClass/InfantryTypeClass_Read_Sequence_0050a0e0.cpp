// void InfantryTypeClass::Read_Sequence() (0x0050A0E0)
// Reads the art INI's Sequence= section of this infantry's image: each named
// sequence is "frame,count,jump,facing" with the facing as a compass name
// (N, NE, E, SE, S, SW, W, NW); an unknown facing name keeps the old one.
#include "shared/infantry_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/crt_string.hpp"
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
// @ref ?unknown_sequence_names_7daf60@@3PAPBDA=007daf60
// @ref _sscanf=00783730
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01OAK@N?$AA@=007db220
// @ref ??_C@_01KFAL@E?$AA@=007db218
// @ref ??_C@_01PDAJ@S?$AA@=007db210
// @ref ??_C@_01FJFF@W?$AA@=007db208
// @ref ??_C@_02DBFL@NW?$AA@=007db204
// @ref ??_C@_02FOPI@SE?$AA@=007db214
// @ref ??_C@_02KCKG@SW?$AA@=007db20c
// @ref ??_C@_02MNAF@NE?$AA@=007db21c
// @ref ??_C@_08MIBH@Sequence?$AA@=007db230
// @ref ??_C@_0M@HGKD@?$CFd?0?$CFd?0?$CFd?0?$CFs?$AA@=007db224

extern "C" int __cdecl sscanf(char const *buffer, char const *format, ...);

// The sequence entry names (0x007DAF60: Ready, Guard, Prone, ..., Panic).
extern char const *unknown_sequence_names_7daf60[38];

void InfantryTypeClass::Read_Sequence()
{
    char section[32];
    if (ArtINI.Get_String(unknown_1c8, "Sequence", unknown_string_83c55c, section, sizeof(section)) > 0) {
        DoInfoStruct *controls = DoControls;
        for (int index = 0; index < 38; index++) {
            char facing[10] = "";
            char value[32];
            if (ArtINI.Get_String(section, unknown_sequence_names_7daf60[index], unknown_string_83c55c, value, sizeof(value)) > 0) {
                sscanf(value, "%d,%d,%d,%s", &controls[index].Frame, &controls[index].Count, &controls[index].Jump, facing);
                if (strcmp("N", facing) == 0) {
                    controls[index].Facing = 0;
                } else if (strcmp("NE", facing) == 0) {
                    controls[index].Facing = 1;
                } else if (strcmp("E", facing) == 0) {
                    controls[index].Facing = 2;
                } else if (strcmp("SE", facing) == 0) {
                    controls[index].Facing = 3;
                } else if (strcmp("S", facing) == 0) {
                    controls[index].Facing = 4;
                } else if (strcmp("SW", facing) == 0) {
                    controls[index].Facing = 5;
                } else if (strcmp("W", facing) == 0) {
                    controls[index].Facing = 6;
                } else if (strcmp("NW", facing) == 0) {
                    controls[index].Facing = 7;
                }
            }
        }
    }
}
