#include "shared/session_state.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/buffer_straw.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/lobby.hpp"

// Reads a map file's [Basic] section (players, game modes, name, official flag) from the
// first part of the file and its [Digest] from the last part (0x006707D0; Read_Scenario_Descriptions).
void __fastcall Read_Map_Header_006707d0(char const *filename, unsigned short *description, char *digest, char *modes,
                                         bool *official, int *min_players, int *max_players)
{
    CCFileClass file(filename);
    if (!file.Is_Available() || !file.Open(FILE_RIGHTS_READ)) {
        return;
    }

    int percent = 0;
    int size;
    char *head = 0;
    char *end;
    do {
        percent += 5;
        size = file.Size() * percent / 100;
        if (head) {
            delete head;
        }
        head = new char[size + 1];
        if (!head) {
            return;
        }
        file.Seek(0, 0);
        file.Read(head, size);
        head[size] = '\0';
        char *start = strstr(head, "[Basic]");
        if (start) {
            end = strstr(start + 5, "\n[");
            if (end > start) {
                break;
            }
        }
        if (percent >= 100) {
            delete head;
            return;
        }
    } while (true);
    end[1] = '\0';
    Debug_Printf("Read first %d%% of file looking for [Basic] section\n", percent);

    percent = 0;
    char *tail = 0;
    int length;
    do {
        percent++;
        length = file.Size() * percent / 100;
        if (tail) {
            delete tail;
        }
        tail = new char[length + 1];
        if (!tail) {
            return;
        }
        file.Seek(-length, 2);
        file.Read(tail, length);
        tail[length] = '\0';
        if (strstr(tail, "[Digest]")) {
            break;
        }
        if (percent >= 100) {
            delete head;
            delete tail;
            return;
        }
    } while (true);
    Debug_Printf("Read last  %d%% of file looking for [Digest] section\n", percent);

    CCINIClass ini;
    BufferStraw straw(head, end - head);
    ini.Load(straw, false, false);
    CCINIClass digest_ini;
    BufferStraw digest_straw(tail, strlen(tail) + 1);
    digest_ini.Load(digest_straw, false, false);

    int min = ini.Get_Int("Basic", "MinPlayers", *min_players);
    *min_players = min;
    int max = ini.Get_Int("Basic", "MaxPlayers", *max_players);
    *max_players = max;
    ini.Get_String("Basic", "GameMode", "", modes, 0x100);
    char name[0x40];
    ini.Get_String("Basic", "Name", "No Name", name, 0x40);
    Unknown_006FA0C0(description, name, -1);
    digest_ini.Get_String("Digest", "1", "No Digest", digest, 0x20);
    *official = ini.Get_Bool("Basic", "Official", false);
    Debug_Printf("MPR %s (%d/%d): official: %d, desc: %s\n", filename, *min_players, *max_players, *official, name);
    Debug_Printf("\t\tGameModes: %s\n", modes);
    delete head;
    delete tail;
}
// @ref ??_C@_07HILE@?$FLBasic?$FN?$AA@=007f3990
// @ref ??_C@_02DPLA@?6?$FL?$AA@=007f398c
// @ref ??_C@_0DF@EGHB@Read?5first?5?$CFd?$CF?$CF?5of?5file?5looking?5@=007f3954
// @ref ??_C@_08MPBJ@?$FLDigest?$FN?$AA@=007f3948
// @ref ??_C@_0DG@CELE@Read?5last?5?5?$CFd?$CF?$CF?5of?5file?5looking?5@=007f3910
// @ref ??_C@_0L@OMDI@MinPlayers?$AA@=007f3904
// @ref ??_C@_0L@MMHH@MaxPlayers?$AA@=007f38f8
// @ref ??_C@_07OOKG@No?5Name?$AA@=007dee7c
// @ref ??_C@_0CI@NPHO@MPR?5?$CFs?5?$CI?$CFd?1?$CFd?$CJ?3?5official?3?5?$CFd?0?5de@=007f38c4
// @ref ??_C@_0BB@LNNO@?7?7GameModes?3?5?$CFs?6?$AA@=007f38b0
// @ref ??_C@_08NLPB@Official?$AA@=007f21d0
// @ref ??_C@_05FGDF@Basic?$AA@=007e1a50
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_08MAFF@GameMode?$AA@=007f34d8
// @ref ??_C@_04EFNI@Name?$AA@=007ce2a4
// @ref ??_C@_09PJBL@No?5Digest?$AA@=007f38ec
// @ref ??_C@_01FBAH@1?$AA@=007e6f6c
// @ref ??_C@_06JBJP@Digest?$AA@=007d1ef0
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??0GenericList@@QAE@XZ=00490e80
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
