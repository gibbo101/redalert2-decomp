// AudioBag *__fastcall Audio_Bag_Create(char const *path, char const *directory) -- 0x004011C0
// Purpose: opens the sound bag named path (its extension replaced: ".idx"
// for the index, ".bag" for the sounds): reads the index header (an id, a
// version and the entry count) and the entry table, sorts the table by name,
// and when directory names an existing directory remembers it (with a
// trailing backslash) for loose sound files. Returns 0 (deleting what was
// made) when a file is missing or short.
// @ref _qsort=00781d46
// @ref _strrchr=00781ff0
// @ref __stricmp=00781f20
// @ref ??_C@_04HFFH@?4idx?$AA@=007cc950
// @ref ??_C@_04PHPE@?4bag?$AA@=007cc948
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ?Open@CCFileClass@@UAEHPBDH@Z=00401980
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
#include "shared/crt_memory.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/win32_find.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/audio.hpp"

extern "C" char *__cdecl strrchr(char const *string, int character);
extern "C" void __cdecl qsort(void *base, unsigned int count, unsigned int width,
                              int (__cdecl *compare)(void const *, void const *));
extern "C" int __cdecl _stricmp(char const *left, char const *right);

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

AudioBag *__fastcall Audio_Bag_Create(char const *path, char const *directory)
{
    AudioBag *bag = (AudioBag *)operator new(sizeof(AudioBag));
    memset(bag, 0, sizeof(AudioBag));
    int header[3];
    char name[_MAX_PATH];
    WIN32_FIND_DATA found;
    strcpy(name, path);
    char *extension = strrchr(name, '.');
    if (extension != 0) {
        *extension = 0;
    }
    strcat(name, ".idx");
    CCFileClass idx(name);
    if (!idx.Is_Available(0)) {
        goto fail;
    }
    extension = strrchr(name, '.');
    if (extension != 0) {
        *extension = 0;
    }
    strcat(name, ".bag");
    bag->BagFile = new CCFileClass(name);
    if (!bag->BagFile->Is_Available(0)) {
        goto fail;
    }
    idx.Open(1);
    bag->BagFile->Open(1);
    if (idx.Read(header, 12) != 12) {
        goto fail;
    }
    bag->Count = header[2];
    if (bag->Count > 0) {
        bag->Entries = (AudioBagEntry *)operator new(bag->Count * sizeof(AudioBagEntry));
        memset(bag->Entries, 0, bag->Count * sizeof(AudioBagEntry));
        if (header[1] == 1) {
            for (int i = 0; i < bag->Count; i++) {
                if (idx.Read(&bag->Entries[i], 0x20) != 0x20) {
                    goto fail;
                }
                bag->Entries[i].BlockSize = 0;
            }
        } else if (idx.Read(bag->Entries, bag->Count * sizeof(AudioBagEntry)) != (long)(bag->Count * sizeof(AudioBagEntry))) {
            goto fail;
        }
    }
    qsort(bag->Entries, bag->Count, sizeof(AudioBagEntry), (int (__cdecl *)(void const *, void const *))_stricmp);
    bag->Loose = 0;
    if (directory != 0) {
        strcpy(bag->Path, directory);
        if (bag->Path[strlen(bag->Path)] == '\\') {
            bag->Path[strlen(bag->Path)] = 0;
        }
        HANDLE handle = FindFirstFileA(bag->Path, &found);
        if (handle != INVALID_HANDLE_VALUE) {
            while (!(found.dwFileAttributes & 0x10)) {
                if (!FindNextFileA(handle, &found)) {
                    goto close;
                }
            }
            bag->Loose = 1;
close:
            FindClose(handle);
        }
        if (bag->Path[strlen(bag->Path)] != '\\') {
            strcat(bag->Path, "\\");
        }
    }
    return bag;
fail:
    if (bag != 0) {
        if (bag->BagFile != 0) {
            delete bag->BagFile;
        }
        if (bag->File != 0) {
            delete bag->File;
        }
        if (bag->Entries != 0) {
            operator delete(bag->Entries);
        }
        operator delete(bag);
    }
    return 0;
}
