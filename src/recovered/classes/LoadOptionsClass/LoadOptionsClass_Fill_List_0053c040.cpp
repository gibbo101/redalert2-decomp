// void LoadOptionsClass::Fill_List_0053c040(HWND list) (0x0053C040)
// Full original 1396+12 body; nominal void/source name qualified by original
// receiver/RET4/caller evidence. No accepted foreign ABI changed.
#include "shared/load_dlg.hpp"
#include "shared/wol_ladder_list_cell.hpp"
#include "shared/house.hpp"
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"

// Existing canonical rotating-buffer conversion, repeated without broad IPX includes.
wchar_t *__fastcall Unknown_006FA180(char const *text);
// Documented Win32 imports absent from the small shared Win32 subset.
WIN32_IMPORT BOOL WINAPI SystemTimeToFileTime(SYSTEMTIME const *system_time, FILETIME *file_time);
WIN32_IMPORT BOOL WINAPI FileTimeToLocalFileTime(FILETIME const *file_time, FILETIME *local_time);
WIN32_IMPORT int WINAPI GetDateFormatA(DWORD locale, DWORD flags, SYSTEMTIME const *date,
                                      char const *format, char *output, int count);
WIN32_IMPORT int WINAPI GetTimeFormatA(DWORD locale, DWORD flags, SYSTEMTIME const *time,
                                      char const *format, char *output, int count);
extern "C" wchar_t *__cdecl wcscpy(wchar_t *destination, wchar_t const *source);

inline FileEntryClass::FileEntryClass()
    : unknown_120(0), unknown_124(-1), unknown_1a8(-1),
      HasDescription(true), NeedsDescription(false), unknown_1b8(0)
{
    Description[0] = 0;
    Filename[0] = 0;
    *(wchar_t *)unknown_128 = 0;
    LastWriteTime.dwHighDateTime = 0;
    LastWriteTime.dwLowDateTime = 0;
}

void LoadOptionsClass::Fill_List_0053c040(HWND list)
{
    WolLadderListCell cell;
    SYSTEMTIME system_time;
    FILETIME local_time;
    char text[128];
    wchar_t wide[128];
    WIN32_FIND_DATA find;

    for (int i = 0; i < Files.Count(); ++i) {
        delete Files[i];
    }
    Files.Clear();
    if (unknown_04 == 2) {
        FileEntryClass *entry = new FileEntryClass;
        swprintf(entry->Description, StringTable::Load_String("TXT_EMPTY_SLOT", 0, "D:\\Ra2\\LoadDlg.CPP", 0x2f8));
        if (unknown_player_a35db4 != 0) {
            entry->unknown_120 = unknown_id_source_a3d290->TechLevel;
            entry->unknown_124 = unknown_id_source_a3d290->unknown_11fc;
            entry->unknown_1a8 = unknown_id_source_a3d290->unknown_224c;
            wcscpy((wchar_t *)entry->unknown_128, unknown_player_a35db4->Type->UIName);
        } else {
            entry->unknown_120 = 0;
            entry->unknown_124 = unknown_a3d3bc;
            entry->unknown_1a8 = -1;
            swprintf((wchar_t *)entry->unknown_128, L"%s", Unknown_006FA180(unknown_name_a3d3a0));
        }
        GetSystemTime(&system_time);
        SystemTimeToFileTime(&system_time, &entry->LastWriteTime);
        int game_mode = unknown_game_mode_a3d298;
        entry->HasDescription = false;
        entry->unknown_1b8 = game_mode;
        Files.Add(entry);
    }
    sprintf(text, "*.%3s", Extension);
    HANDLE search = FindFirstFileA(text, &find);
    FileEntryClass *entry = 0;
    if (search != INVALID_HANDLE_VALUE) {
        do {
            if ((find.dwFileAttributes & 0x116) == 0) {
                if (entry == 0) {
                    entry = new FileEntryClass;
                }
                if (Read_File_Description(entry, &find) == true) {
                    Files.Add(entry);
                    entry = 0;
                }
            }
        } while (FindNextFileA(search, &find));
        if (entry != 0) {
            delete entry;
        }
        FindClose(search);
    }
    if (Files.Count() > 0) {
        qsort(&Files[0], Files.Count(), sizeof(FileEntryClass *),
              reinterpret_cast<int(__cdecl *)(void const *, void const *)>(Compare_Save_Times));
        SendMessageA(list, 0x184, 0, 0);
        for (int i = 0; i < Files.Count(); ++i) {
            FileEntryClass *file = Files[i];
            if (!file->NeedsDescription) {
                WPARAM row = SendMessageA(list, 0x4cd, 0, (LPARAM)file);
                if (file->unknown_1b8 != 0) {
                    cell.Flags = 1;
                    cell.Text.Set(L"*");
                    SendMessageA(list, 0x4a8, ((DWORD)(WORD)row << 16) | 200, (LPARAM)&cell);
                }
                if (file->LastWriteTime.dwHighDateTime != (DWORD)-1 &&
                    file->LastWriteTime.dwLowDateTime != (DWORD)-1) {
                    FileTimeToLocalFileTime(&file->LastWriteTime, &local_time);
                    FileTimeToSystemTime(&local_time, &system_time);
                    GetDateFormatA(0x400, 1, &system_time, 0, text, 128);
                    cell.Flags = 1;
                    int length = MultiByteToWideChar(0, 0, text, -1, wide, 128);
                    wide[127] = 0;
                    wide[length] = 0;
                    cell.Text.Set(wide);
                    SendMessageA(list, 0x4a8, ((DWORD)(WORD)row << 16) | 0xff, (LPARAM)&cell);
                    GetTimeFormatA(0x400, 0, &system_time, 0, text, 128);
                    cell.Flags = 1;
                    length = MultiByteToWideChar(0, 0, text, -1, wide, 128);
                    wide[127] = 0;
                    wide[length] = 0;
                    cell.Text.Set(wide);
                    SendMessageA(list, 0x4a8, ((DWORD)(WORD)row << 16) | 0x13b, (LPARAM)&cell);
                }
                SendMessageA(list, 0x19a, row, (LPARAM)file);
            }
        }
        switch (unknown_04) {
        case 1: {
            for (int i = 0; i < Files.Count(); ++i) {
                if (Files[i]->HasDescription && !Files[i]->NeedsDescription) {
                    SendMessageA(list, 0x186, i, 0);
                    SendMessageA(list, 0x197, i, 0);
                    break;
                }
            }
            break;
        }
        case 2:
        case 3:
            SendMessageA(list, 0x186, 0, 0);
            SendMessageA(list, 0x197, 0, 0);
            break;
        default:
            break;
        }
    }
}

// @ref ??_C@_05GHIA@?$CK?4?$CF3s?$AA@=007dfabc
// @ref ??_C@_0P@HAMI@TXT_EMPTY_SLOT?$AA@=007dfac4
// @ref ??_C@_13HGEN@?$AA?$CK?$AA?$AA@=007dfab8
