// 0x0078fb6b: function not yet identified
//
// Body: 54 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: undefined4 FUN_0078fb6b(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0078fb6b {

typedef long HRESULT, LSTATUS, INT_PTR;   // LPARAM, LRESULT come from ghidra_types.hpp (unsigned)
typedef unsigned int SIZE_T, ULONG_PTR, UINT_PTR, DWORD_PTR, REGSAM, COLORREF, MMRESULT;
typedef short SHORT;
typedef unsigned short ATOM, WCHAR;
typedef int *LPBOOL;
typedef byte *LPBYTE;
typedef WORD *LPWORD;
typedef DWORD *PDWORD;
typedef UINT *PUINT;
typedef LONG *PLONG;
typedef void *PVOID;
typedef const void *LPCVOID;
typedef char *LPCH;
typedef const char *PCNZCH;
typedef wchar16 *LPWCH, *LPOLESTR;
typedef const wchar16 *PCNZWCH, *LPCOLESTR;
typedef wchar16 **SNB;
typedef void *HACCEL, *HBITMAP, *HBRUSH, *HCURSOR, *HFONT, *HGDIOBJ, *HGLOBAL;
typedef void *HICON, *HIMAGELIST, *HIMC, *HLOCAL, *HMENU, *HRGN, *HRSRC;
typedef HKEY *PHKEY;
typedef GUID CLSID;
typedef CLSID *LPCLSID;
typedef RECT *LPRECT;
struct POINT { LONG x, y; };
typedef POINT *LPPOINT;
struct FILETIME { DWORD dwLowDateTime, dwHighDateTime; };
typedef FILETIME *LPFILETIME, *PFILETIME;
struct SYSTEMTIME { WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds; };
typedef SYSTEMTIME *LPSYSTEMTIME;
union LARGE_INTEGER { struct { DWORD LowPart; LONG HighPart; }; __int64 QuadPart; };
struct MEMORYSTATUS { DWORD dwLength, dwMemoryLoad, dwTotalPhys, dwAvailPhys, dwTotalPageFile, dwAvailPageFile, dwTotalVirtual, dwAvailVirtual; };
typedef MEMORYSTATUS *LPMEMORYSTATUS;
struct MEMORY_BASIC_INFORMATION { void *BaseAddress, *AllocationBase; DWORD AllocationProtect; SIZE_T RegionSize; DWORD State, Protect, Type; };
typedef MEMORY_BASIC_INFORMATION *PMEMORY_BASIC_INFORMATION;
struct MSG { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; };
typedef MSG *LPMSG;
struct PAINTSTRUCT { HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore, fIncUpdate; BYTE rgbReserved[32]; };
typedef PAINTSTRUCT *LPPAINTSTRUCT;
struct XFORM { float eM11, eM12, eM21, eM22, eDx, eDy; };
typedef int (__stdcall *FARPROC)();
typedef LRESULT (__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef INT_PTR (__stdcall *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef BOOL (__stdcall *WNDENUMPROC)(HWND, LPARAM);
typedef BOOL (__stdcall *LOCALE_ENUMPROCA)(LPSTR);
typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE)(LPVOID);
typedef void (__stdcall *TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
typedef void (__stdcall *LPTIMECALLBACK)(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);
typedef BOOL (__stdcall *PHANDLER_ROUTINE)(DWORD);
struct EXCEPTION_POINTERS;
typedef LONG (__stdcall *LPTOP_LEVEL_EXCEPTION_FILTER)(EXCEPTION_POINTERS *);
struct IUnknown; typedef IUnknown *LPUNKNOWN;
struct IStream; typedef IStream *LPSTREAM;
struct IPersistStream; typedef IPersistStream *LPPERSISTSTREAM;
struct IStorage;
struct BY_HANDLE_FILE_INFORMATION; typedef BY_HANDLE_FILE_INFORMATION *LPBY_HANDLE_FILE_INFORMATION;
struct CANDIDATELIST; typedef CANDIDATELIST *LPCANDIDATELIST;
struct COMMTIMEOUTS; typedef COMMTIMEOUTS *LPCOMMTIMEOUTS;
struct COMSTAT; typedef COMSTAT *LPCOMSTAT;
struct CPINFO; typedef CPINFO *LPCPINFO;
struct DCB; typedef DCB *LPDCB;
struct DLGTEMPLATE; typedef DLGTEMPLATE *LPCDLGTEMPLATEA;
struct EXCEPTION_RECORD; typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;
struct INPUT_RECORD; typedef INPUT_RECORD *PINPUT_RECORD;
struct _OSVERSIONINFOA {
    DWORD dwOSVersionInfoSize, dwMajorVersion, dwMinorVersion, dwBuildNumber, dwPlatformId;
    CHAR szCSDVersion[128];
};
typedef _OSVERSIONINFOA OSVERSIONINFOA;
typedef OSVERSIONINFOA *POSVERSIONINFOA, *LPOSVERSIONINFOA;
struct PROCESS_INFORMATION; typedef PROCESS_INFORMATION *LPPROCESS_INFORMATION;
struct STARTUPINFOA; typedef STARTUPINFOA *LPSTARTUPINFOA;
struct TEXTMETRICA; typedef TEXTMETRICA *LPTEXTMETRICA;
struct TIME_ZONE_INFORMATION; typedef TIME_ZONE_INFORMATION *LPTIME_ZONE_INFORMATION;
struct WIN32_FIND_DATAA; typedef WIN32_FIND_DATAA *LPWIN32_FIND_DATAA;
struct BITMAPINFO; struct LOGFONTA; struct MSGBOXPARAMSA; struct WNDCLASSA;

extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(LPOSVERSIONINFOA lpVersionInformation); // @ref __imp__GetVersionExA@4=0079a17c

undefined4  FUN_0078fb6b(void)
{
    BOOL BVar1;
    _OSVERSIONINFOA local_98;

    local_98.dwOSVersionInfoSize = 0x94;
    BVar1 = (BOOL)(GetVersionExA((LPOSVERSIONINFOA)(&local_98)));
    if ((BVar1 != 0) && (local_98.dwPlatformId == 2)) {
        return (undefined4)(1);
    }
    return (undefined4)(0);
}

}  // namespace seed_0078fb6b
