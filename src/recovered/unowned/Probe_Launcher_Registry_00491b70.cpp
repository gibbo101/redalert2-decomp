#include "shared/launcher_validation.hpp"
WIN32_IMPORT LONG WINAPI RegQueryValueExA(HKEY key,LPCSTR name,DWORD *reserved,DWORD *type,unsigned char *data,DWORD *size);
struct UnknownVersionObject;
extern UnknownVersionObject version_object_00a40c88;
unsigned int __fastcall Unknown_Version_ID_00712b50(UnknownVersionObject *object);
// @ref __imp__RegQueryValueExA@24=0079a008
// @ref ?version_object_00a40c88@@=00a40c88
// @ref ?Unknown_Version_ID_00712b50@@=00712b50
// @ref ?launcher_registry_key_007d52ac@@=007d52ac
// @ref ?launcher_registry_value_007d52a8@@=007d52a8
// Original zero-argument convention and AL result spelling remain hypotheses.
bool __fastcall Probe_Launcher_Registry_00491b70()
{
    HKEY key;
    if(RegOpenKeyExA((HKEY)0x80000000,launcher_registry_key_007d52ac,0,0x20019,&key)==0) {
        DWORD size=4;
        DWORD type,value;
        LONG status=RegQueryValueExA(key,launcher_registry_value_007d52a8,0,&type,(unsigned char *)&value,&size);
        RegCloseKey(key);
        if(status==0 && type==4) return value==Unknown_Version_ID_00712b50(&version_object_00a40c88);
    }
    return false;
}
