#include "shared/win32_api.hpp"
typedef HANDLE HINSTANCE;
typedef HANDLE HRSRC;
typedef HANDLE HGLOBAL;
WIN32_IMPORT HRSRC WINAPI FindResourceA(HINSTANCE instance, LPCSTR name, LPCSTR type);
WIN32_IMPORT HGLOBAL WINAPI LoadResource(HINSTANCE instance, HRSRC resource);
WIN32_IMPORT LPVOID WINAPI LockResource(HGLOBAL resource);
extern HINSTANCE unknown_instance_00851ca8;
// @ref ?unknown_instance_00851ca8@@3PAXA=00851ca8
// @ref __imp__FindResourceA@12=0079a21c
// @ref __imp__LoadResource@8=0079a220
// @ref __imp__LockResource@4=0079a218
void *__fastcall Load_Resource_004954e0(unsigned int id, char const *type)
{
    HRSRC resource = FindResourceA(unknown_instance_00851ca8, (LPCSTR)(id & 0xffff), type);
    if (!resource) return 0;
    HGLOBAL data = LoadResource(unknown_instance_00851ca8, resource);
    if (!data) return 0;
    return LockResource(data);
}
