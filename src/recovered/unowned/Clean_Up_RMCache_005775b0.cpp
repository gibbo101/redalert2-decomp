// @ref ??0?$VectorClass@PAUWIN32_FIND_DATA@@@@QAE@IPBQAUWIN32_FIND_DATA@@@Z=0058f210
// @ref ??_7?$DynamicVectorClass@PAUWIN32_FIND_DATA@@@@6B@=007a5e8c
// @ref ??_E?$DynamicVectorClass@PAUWIN32_FIND_DATA@@@@UAEPAXI@Z=0058ecf0
// @ref ??8?$VectorClass@PAUWIN32_FIND_DATA@@@@UBE_NABV0@@Z=0058e2d0
// @ref ?Resize@?$DynamicVectorClass@PAUWIN32_FIND_DATA@@@@UAE_NHPBQAUWIN32_FIND_DATA@@@Z=0058e450
// @ref ?Clear@?$DynamicVectorClass@PAUWIN32_FIND_DATA@@@@UAEXXZ=0058dd30
// @ref ?ID@?$DynamicVectorClass@PAUWIN32_FIND_DATA@@@@UAEHABQAUWIN32_FIND_DATA@@@Z=0058e500
// @ref ?ID@?$DynamicVectorClass@PAUWIN32_FIND_DATA@@@@UAEHPBQAUWIN32_FIND_DATA@@@Z=0058dd60
// @ref ?Fetch@?$VectorClass@PAUWIN32_FIND_DATA@@@@UBEPAUWIN32_FIND_DATA@@H@Z=0058dd80
// @ref ??_7?$VectorClass@PAUWIN32_FIND_DATA@@@@6B@=007a5e6c
// @ref ??_E?$VectorClass@PAUWIN32_FIND_DATA@@@@UAEPAXI@Z=0058eca0
// @ref ?Resize@?$VectorClass@PAUWIN32_FIND_DATA@@@@UAE_NHPBQAUWIN32_FIND_DATA@@@Z=0058e310
// @ref ?Clear@?$VectorClass@PAUWIN32_FIND_DATA@@@@UAEXXZ=0058e3c0
// @ref ?ID@?$VectorClass@PAUWIN32_FIND_DATA@@@@UAEHABQAUWIN32_FIND_DATA@@@Z=0058e3f0
// @ref ?ID@?$VectorClass@PAUWIN32_FIND_DATA@@@@UAEHPBQAUWIN32_FIND_DATA@@@Z=0058e430
#include "shared/map_seed.hpp"
#include "shared/win32_find.hpp"
WIN32_IMPORT LONG WINAPI CompareFileTime(FILETIME const *first,FILETIME const *second);
extern char const rmg_cache_pattern_7e15c4[];
// @ref ?rmg_cache_pattern_7e15c4@@=007e15c4
// Prune cached map previews by last access, creation, then write time.
void __fastcall Clean_Up_RMCache_005775b0()
{
    WIN32_FIND_DATA *record;
    DynamicVectorClass<WIN32_FIND_DATA *> files;
    record=new WIN32_FIND_DATA;
    HANDLE search=FindFirstFileA(rmg_cache_pattern_7e15c4,record);
    if(search!=INVALID_HANDLE_VALUE) {
        files.Add(record);
        record=new WIN32_FIND_DATA;
        while(FindNextFileA(search,record)!=0) {
            files.Add(record);
            record=new WIN32_FIND_DATA;
        }
        FindClose(search);
    }
    delete record;
    while(files.Count()>70) {
        FILETIME oldestTime;
        oldestTime.dwLowDateTime=0xffffffff;
        oldestTime.dwHighDateTime=0x7fffffff;
        int oldest=-1;
        for(int index=0;index<files.Count();++index) {
            WIN32_FIND_DATA *file=files[index];
            if(file->ftLastAccessTime.dwHighDateTime!=0) {
                if(CompareFileTime(&file->ftLastAccessTime,&oldestTime)==-1) {
                    oldest=index;
                    oldestTime.dwLowDateTime=files[index]->ftLastAccessTime.dwLowDateTime;
                    oldestTime.dwHighDateTime=files[index]->ftLastAccessTime.dwHighDateTime;
                }
            } else if(file->ftCreationTime.dwHighDateTime!=0) {
                if(CompareFileTime(&file->ftCreationTime,&oldestTime)==-1) {
                    oldest=index;
                    oldestTime.dwLowDateTime=files[index]->ftCreationTime.dwLowDateTime;
                    oldestTime.dwHighDateTime=files[index]->ftCreationTime.dwHighDateTime;
                }
            } else if(file->ftLastWriteTime.dwHighDateTime!=0) {
                if(CompareFileTime(&file->ftLastWriteTime,&oldestTime)==-1) {
                    oldest=index;
                    oldestTime.dwLowDateTime=files[index]->ftLastWriteTime.dwLowDateTime;
                    oldestTime.dwHighDateTime=files[index]->ftLastWriteTime.dwHighDateTime;
                }
            }
        }
        if(oldest==-1)break;
        if(!DeleteFileA(files[oldest]->cFileName))break;
        delete files[oldest];
        files.Delete(oldest);
    }
    while(files.Count()!=0) {
        delete files[0];
        files.Delete(0);
    }
}
