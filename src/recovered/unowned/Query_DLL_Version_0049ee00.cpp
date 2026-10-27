#include "shared/win32_api.hpp"
#include "shared/crt_memory.hpp"
typedef struct HINSTANCE__ *HMODULE;
typedef int (WINAPI *FARPROC)();
WIN32_IMPORT HMODULE WINAPI LoadLibraryA(LPCSTR name);
WIN32_IMPORT FARPROC WINAPI GetProcAddress(HMODULE module, LPCSTR name);
WIN32_IMPORT BOOL WINAPI FreeLibrary(HMODULE module);
struct DLLVERSIONINFO {
    DWORD cbSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformID;
};
typedef long (WINAPI *DLLGETVERSIONPROC)(DLLVERSIONINFO *version);
extern char const dll_version_entry_name_007d5e9c[];
// @ref ?dll_version_entry_name_007d5e9c@@=007d5e9c
unsigned int __fastcall Query_DLL_Version_0049ee00(char const *name)
{
    unsigned int version = 0;
    HMODULE module = LoadLibraryA(name);
    if (module) {
        DLLGETVERSIONPROC getVersion = (DLLGETVERSIONPROC)GetProcAddress(module, dll_version_entry_name_007d5e9c);
        if (getVersion) {
            DLLVERSIONINFO info;
            memset(&info,0,sizeof(info));
            info.cbSize = sizeof(info);
            if (getVersion(&info) >= 0)
                version = (WORD)info.dwMinorVersion | ((DWORD)(WORD)info.dwMajorVersion << 16);
        }
        FreeLibrary(module);
    }
    return version;
}
