// @ref ?Get_Unicode@INIClass@@=0050edf0
// @ref ?Put_Unicode@INIClass@@=0050ecf0
// @ref ??_C@_09CKPM@RandomMap?$AA@=007e15dc
// @ref ??_C@_0M@FDHG@RandMap?4Sed?$AA@=007e16e8
// @ref ??_C@_0M@GOAP@lastmap?4sed?$AA@=007e16dc
#include "shared/map_seed.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ini_class.hpp"
extern wchar_t const unknown_empty_wide_839d4c[];
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
extern "C" int __cdecl _stricmp(char const *,char const *);
extern "C" char *__cdecl strncpy(char *,char const *,unsigned int);
extern "C" unsigned int __cdecl strlen(char const *);
extern "C" wchar_t *__cdecl wcsncpy(wchar_t *,wchar_t const *,unsigned int);
#pragma intrinsic(strlen)
// @ref __stricmp=00781f20
// @ref _strncpy=007823d0
// @ref _wcsncpy=00783622
bool MapSeedClass::Read_File_Description(FileEntryClass *entry,WIN32_FIND_DATA const *find)
{
    if(entry && find) {
        char const *filename=find->cFileName;
        if(_stricmp(filename,"RandMap.Sed") && _stricmp(filename,"lastmap.sed")) {
            CCFileClass file(filename);
            INIClass ini;
            if(ini.Load(file,false)) {
                wchar_t description[128];
                if(ini.Get_Unicode("RandomMap","Description",unknown_empty_wide_839d4c,description,128)>0) {
                    wcsncpy(entry->Description,description,128);
                    entry->NeedsDescription=false;
                    entry->HasDescription=true;
                } else {
                    entry->Description[0]=0;
                    entry->NeedsDescription=true;
                    entry->HasDescription=false;
                }
                entry->unknown_120=0;
                entry->unknown_124=0;
                strncpy(entry->Filename,filename,32);
                if(!strlen(entry->Filename))
                    strncpy(entry->Filename,find->cAlternateFileName,32);
                entry->LastWriteTime.dwHighDateTime=find->ftLastWriteTime.dwHighDateTime;
                entry->LastWriteTime.dwLowDateTime=find->ftLastWriteTime.dwLowDateTime;
                return true;
            }
        }
    }
    return false;
}
