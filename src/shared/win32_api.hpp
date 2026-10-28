// Win32 API declarations used by recovered source, with their real signatures.
//
// The game links these from KERNEL32/USER32 through the import address table:
// `__declspec(dllimport)` makes VC6 emit `call dword ptr [__imp__Name@N]`,
// which acceptance binds to the original IAT slot (manifests/imports.json).
// Only what recovered code uses is declared; types are the Win32 widths.
#ifndef RA2_SHARED_WIN32_API_HPP
#define RA2_SHARED_WIN32_API_HPP

#define WINAPI __stdcall
#define WIN32_IMPORT extern "C" __declspec(dllimport)

typedef void *HANDLE;
typedef int BOOL;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;
typedef const char *LPCSTR;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef struct HWND__ *HWND;
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID parameter);

struct POINT { LONG x; LONG y; };
struct RECT { LONG left; LONG top; LONG right; LONG bottom; };

struct FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; };
struct BY_HANDLE_FILE_INFORMATION {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD dwVolumeSerialNumber;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD nNumberOfLinks;
    DWORD nFileIndexHigh;
    DWORD nFileIndexLow;
};

#define INVALID_HANDLE_VALUE ((HANDLE)-1)
#define GENERIC_READ 0x80000000u
#define GENERIC_WRITE 0x40000000u
#define FILE_SHARE_READ 1
#define FILE_SHARE_WRITE 2
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define FILE_ATTRIBUTE_NORMAL 0x80
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2

WIN32_IMPORT HANDLE WINAPI CreateFileA(LPCSTR name, DWORD access, DWORD share, void *security,
                                       DWORD disposition, DWORD flags, HANDLE templateFile);
WIN32_IMPORT BOOL WINAPI CloseHandle(HANDLE handle);
// Code page conversion (KERNEL32; Get_Savefile_Info 0x00657FA0, the house
// names, the application's BSTRs).
WIN32_IMPORT int WINAPI MultiByteToWideChar(unsigned int code_page, unsigned long flags, char const *text, int length,
                                            unsigned short *wide, int wide_length);
WIN32_IMPORT long WINAPI InterlockedIncrement(long *addend);
WIN32_IMPORT long WINAPI InterlockedDecrement(long *addend);
WIN32_IMPORT BOOL WINAPI DeleteFileA(LPCSTR name);
WIN32_IMPORT BOOL WINAPI ReadFile(HANDLE file, LPVOID buffer, DWORD size, DWORD *read, void *overlapped);
WIN32_IMPORT BOOL WINAPI WriteFile(HANDLE file, LPCVOID buffer, DWORD size, DWORD *written, void *overlapped);
WIN32_IMPORT DWORD WINAPI SetFilePointer(HANDLE file, LONG distance, LONG *distanceHigh, DWORD method);
WIN32_IMPORT DWORD WINAPI GetFileSize(HANDLE file, DWORD *sizeHigh);
WIN32_IMPORT DWORD WINAPI GetLastError(void);
WIN32_IMPORT BOOL WINAPI GetFileInformationByHandle(HANDLE file, BY_HANDLE_FILE_INFORMATION *info);
WIN32_IMPORT BOOL WINAPI FileTimeToDosDateTime(const FILETIME *time, WORD *dosDate, WORD *dosTime);
WIN32_IMPORT BOOL WINAPI DosDateTimeToFileTime(WORD dosDate, WORD dosTime, FILETIME *time);
WIN32_IMPORT BOOL WINAPI SetFileTime(HANDLE file, const FILETIME *created, const FILETIME *accessed,
                                     const FILETIME *written);

// Threads and synchronization (KERNEL32).
#define WAIT_TIMEOUT 0x102
#define THREAD_PRIORITY_TIME_CRITICAL 15
#define FORMAT_MESSAGE_FROM_SYSTEM 0x1000
WIN32_IMPORT HANDLE WINAPI CreateMutexA(void *security, BOOL initialowner, LPCSTR name);
WIN32_IMPORT BOOL WINAPI ReleaseMutex(HANDLE mutex);
WIN32_IMPORT DWORD WINAPI WaitForSingleObject(HANDLE handle, DWORD milliseconds);
WIN32_IMPORT void WINAPI Sleep(DWORD milliseconds);
WIN32_IMPORT HANDLE WINAPI CreateThread(void *security, DWORD stacksize, LPTHREAD_START_ROUTINE start,
                                        LPVOID parameter, DWORD flags, DWORD *threadid);
WIN32_IMPORT BOOL WINAPI SetThreadPriority(HANDLE thread, int priority);
WIN32_IMPORT DWORD WINAPI FormatMessageA(DWORD flags, LPCVOID source, DWORD messageid, DWORD languageid,
                                         char *buffer, DWORD size, void *arguments);

// Critical sections and the performance counter (KERNEL32), the multimedia
// clock (WINMM).
struct CRITICAL_SECTION {
    void *DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    DWORD SpinCount;
};
union LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    };
    __int64 QuadPart;
};
WIN32_IMPORT void WINAPI InitializeCriticalSection(CRITICAL_SECTION *section);
WIN32_IMPORT void WINAPI DeleteCriticalSection(CRITICAL_SECTION *section);
WIN32_IMPORT void WINAPI EnterCriticalSection(CRITICAL_SECTION *section);
WIN32_IMPORT void WINAPI LeaveCriticalSection(CRITICAL_SECTION *section);
WIN32_IMPORT BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *count);
WIN32_IMPORT BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *frequency);
WIN32_IMPORT DWORD WINAPI timeGetTime();

// Cursor and window coordinates (USER32).
WIN32_IMPORT int WINAPI ShowCursor(BOOL show);
WIN32_IMPORT BOOL WINAPI GetCursorPos(POINT *point);
WIN32_IMPORT BOOL WINAPI GetClientRect(HWND window, RECT *rect);
WIN32_IMPORT BOOL WINAPI ClientToScreen(HWND window, POINT *point);
WIN32_IMPORT BOOL WINAPI GetWindowRect(HWND window, RECT *rect);
WIN32_IMPORT BOOL WINAPI SetRect(RECT *rect, int left, int top, int right, int bottom);
WIN32_IMPORT BOOL WINAPI InvalidateRect(HWND window, RECT const *rect, BOOL erase);

// Key state (USER32).
WIN32_IMPORT short WINAPI GetKeyState(int key);
WIN32_IMPORT short WINAPI GetAsyncKeyState(int key);

// Dialog boxes (the main-screen message box, 0x005B46B0/0x005B48C0).
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef long LRESULT;
WIN32_IMPORT LONG WINAPI SetWindowLongA(HWND window, int index, LONG value);
WIN32_IMPORT LONG WINAPI GetWindowLongA(HWND window, int index);
WIN32_IMPORT HWND WINAPI GetDlgItem(HWND dialog, int id);
WIN32_IMPORT LRESULT WINAPI SendMessageA(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
typedef HANDLE HINSTANCE;
typedef BOOL (WINAPI *DLGPROC)(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam);
#define MAKEINTRESOURCEA(id) ((LPCSTR)(unsigned long)(unsigned short)(id))
WIN32_IMPORT HWND WINAPI CreateDialogParamA(HINSTANCE instance, LPCSTR name, HWND parent, DLGPROC procedure,
                                            LPARAM parameter);
WIN32_IMPORT BOOL WINAPI DestroyWindow(HWND window);

// Timers and message records (USER32; the tooltip manager, 0x006EB4E0).
typedef struct tagMSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
} MSG;
typedef void (WINAPI *TIMERPROC)(HWND window, UINT message, UINT id, DWORD time);
WIN32_IMPORT BOOL WINAPI KillTimer(HWND window, UINT id);
WIN32_IMPORT UINT WINAPI SetTimer(HWND window, UINT id, UINT elapse, TIMERPROC callback);
WIN32_IMPORT BOOL WINAPI ScreenToClient(HWND window, POINT *point);

// Registry keys (ADVAPI32) and KERNEL32 string helpers.
typedef struct HKEY__ *HKEY;
typedef unsigned char BYTE;
#define HKEY_CLASSES_ROOT ((HKEY)0x80000000)
#define KEY_ALL_ACCESS 0xF003F
#define REG_SZ 1
WIN32_IMPORT LONG WINAPI RegCreateKeyExA(HKEY key, LPCSTR subkey, DWORD reserved, char *keyclass, DWORD options,
                                         DWORD access, void *security, HKEY *result, DWORD *disposition);
WIN32_IMPORT LONG WINAPI RegSetValueExA(HKEY key, LPCSTR name, DWORD reserved, DWORD type, BYTE const *data,
                                        DWORD size);
WIN32_IMPORT LONG WINAPI RegCloseKey(HKEY key);
// Serial ports (KERNEL32; WinModemClass, shared/win_modem.hpp).
struct OVERLAPPED {
    DWORD Internal;
    DWORD InternalHigh;
    DWORD Offset;
    DWORD OffsetHigh;
    HANDLE hEvent;
};
struct COMSTAT {
    DWORD fCtsHold : 1;
    DWORD fDsrHold : 1;
    DWORD fRlsdHold : 1;
    DWORD fXoffHold : 1;
    DWORD fXoffSent : 1;
    DWORD fEof : 1;
    DWORD fTxim : 1;
    DWORD fReserved : 25;
    DWORD cbInQue;
    DWORD cbOutQue;
};
struct DCB {
    DWORD DCBlength;
    DWORD BaudRate;
    DWORD fBinary : 1;
    DWORD fParity : 1;
    DWORD fOutxCtsFlow : 1;
    DWORD fOutxDsrFlow : 1;
    DWORD fDtrControl : 2;
    DWORD fDsrSensitivity : 1;
    DWORD fTXContinueOnXoff : 1;
    DWORD fOutX : 1;
    DWORD fInX : 1;
    DWORD fErrorChar : 1;
    DWORD fNull : 1;
    DWORD fRtsControl : 2;
    DWORD fAbortOnError : 1;
    DWORD fDummy2 : 17;
    WORD wReserved;
    WORD XonLim;
    WORD XoffLim;
    BYTE ByteSize;
    BYTE Parity;
    BYTE StopBits;
    char XonChar;
    char XoffChar;
    char ErrorChar;
    char EofChar;
    char EvtChar;
    WORD wReserved1;
};
struct COMMTIMEOUTS {
    DWORD ReadIntervalTimeout;
    DWORD ReadTotalTimeoutMultiplier;
    DWORD ReadTotalTimeoutConstant;
    DWORD WriteTotalTimeoutMultiplier;
    DWORD WriteTotalTimeoutConstant;
};
#define ERROR_IO_INCOMPLETE 996
#define ERROR_IO_PENDING 997
#define FILE_FLAG_OVERLAPPED 0x40000000
WIN32_IMPORT HANDLE WINAPI CreateEventA(void *security, BOOL manualreset, BOOL initialstate, LPCSTR name);
WIN32_IMPORT BOOL WINAPI ResetEvent(HANDLE event);
WIN32_IMPORT BOOL WINAPI GetOverlappedResult(HANDLE file, OVERLAPPED *overlapped, DWORD *transferred, BOOL wait);
WIN32_IMPORT BOOL WINAPI SetupComm(HANDLE file, DWORD inqueue, DWORD outqueue);
WIN32_IMPORT BOOL WINAPI PurgeComm(HANDLE file, DWORD flags);
WIN32_IMPORT BOOL WINAPI GetCommState(HANDLE file, DCB *dcb);
WIN32_IMPORT BOOL WINAPI SetCommState(HANDLE file, DCB *dcb);
WIN32_IMPORT BOOL WINAPI SetCommTimeouts(HANDLE file, COMMTIMEOUTS *timeouts);
WIN32_IMPORT BOOL WINAPI ClearCommError(HANDLE file, DWORD *errors, COMSTAT *status);
WIN32_IMPORT BOOL WINAPI GetCommModemStatus(HANDLE file, DWORD *status);
WIN32_IMPORT BOOL WINAPI GetCommMask(HANDLE file, DWORD *mask);
WIN32_IMPORT BOOL WINAPI EscapeCommFunction(HANDLE file, DWORD function);
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)
#define KEY_READ 0x20019
WIN32_IMPORT LONG WINAPI RegQueryInfoKeyA(HKEY key, char *keyclass, DWORD *class_size, DWORD *reserved,
                                          DWORD *subkeys, DWORD *max_subkey, DWORD *max_class, DWORD *values,
                                          DWORD *max_value_name, DWORD *max_value, DWORD *security,
                                          FILETIME *last_write);
WIN32_IMPORT LONG WINAPI RegEnumKeyExA(HKEY key, DWORD index, char *name, DWORD *name_size, DWORD *reserved,
                                       char *keyclass, DWORD *class_size, FILETIME *last_write);
WIN32_IMPORT LONG WINAPI RegOpenKeyExA(HKEY key, LPCSTR subkey, DWORD options, DWORD access, HKEY *result);
WIN32_IMPORT LONG WINAPI RegQueryValueExA(HKEY key, LPCSTR name, DWORD *reserved, DWORD *type, BYTE *data,
                                          DWORD *size);
WIN32_IMPORT char *WINAPI lstrcpyA(char *destination, LPCSTR source);
WIN32_IMPORT char *WINAPI lstrcatA(char *destination, LPCSTR source);
WIN32_IMPORT int WINAPI lstrlenA(LPCSTR string);

// USER32 printf into a buffer (cdecl, variable arguments).
WIN32_IMPORT int __cdecl wsprintfA(char *buffer, char const *format, ...);

#endif
