#ifndef RA2_SHARED_LAUNCHER_VALIDATION_HPP
#define RA2_SHARED_LAUNCHER_VALIDATION_HPP
#include "shared/win32_api.hpp"
typedef struct HKEY__ *HKEY;
WIN32_IMPORT BOOL WINAPI PeekMessageA(MSG *message, HWND window, UINT minimum, UINT maximum, UINT remove);
WIN32_IMPORT HANDLE WINAPI OpenEventA(DWORD access, BOOL inherit, LPCSTR name);
WIN32_IMPORT BOOL WINAPI SetEvent(HANDLE event);
WIN32_IMPORT LPVOID WINAPI MapViewOfFileEx(HANDLE mapping,DWORD access,DWORD high,DWORD low,unsigned int bytes,LPVOID address);
WIN32_IMPORT BOOL WINAPI UnmapViewOfFile(LPCVOID address);
WIN32_IMPORT LONG WINAPI RegOpenKeyExA(HKEY root,LPCSTR subkey,DWORD options,DWORD access,HKEY *key);
WIN32_IMPORT LONG WINAPI RegCloseKey(HKEY key);
WIN32_IMPORT LONG WINAPI RegDeleteValueA(HKEY key,LPCSTR name);
#include "shared/debug_printf.hpp"
extern char const *launcher_message_00851b3c;
extern char const launcher_notify_log_007d5218[],launcher_event_007d51f0[],launcher_notified_log_007d51dc[],launcher_notify_failed_log_007d51b8[];
extern char const launcher_received_log_007d5274[],launcher_map_failed_log_007d5254[],launcher_message_log_007d523c[];
extern char const launcher_registry_key_007d52ac[],launcher_registry_value_007d52a8[],launcher_shutdown_log_007d530c[];
#endif
