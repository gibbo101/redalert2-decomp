// Win32 file-search API (KERNEL32 FindFirstFileA / FindClose) with the real
// WIN32_FIND_DATAA layout (0x140 bytes).
#ifndef RA2_SHARED_WIN32_FIND_HPP
#define RA2_SHARED_WIN32_FIND_HPP

#include "shared/win32_api.hpp"

struct WIN32_FIND_DATA {
    DWORD dwFileAttributes;     // +0x00
    FILETIME ftCreationTime;    // +0x04
    FILETIME ftLastAccessTime;  // +0x0C
    FILETIME ftLastWriteTime;   // +0x14
    DWORD nFileSizeHigh;        // +0x1C
    DWORD nFileSizeLow;         // +0x20
    DWORD dwReserved0;          // +0x24
    DWORD dwReserved1;          // +0x28
    char cFileName[260];        // +0x2C
    char cAlternateFileName[14];// +0x130
};

WIN32_IMPORT HANDLE WINAPI FindFirstFileA(LPCSTR filename, WIN32_FIND_DATA *finddata);
WIN32_IMPORT BOOL WINAPI FindNextFileA(HANDLE handle, WIN32_FIND_DATA *finddata);
WIN32_IMPORT BOOL WINAPI FindClose(HANDLE handle);

#endif
