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

// Dialog boxes (the main-screen message box, 0x005B46B0/0x005B48C0).
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef long LRESULT;
WIN32_IMPORT LONG WINAPI SetWindowLongA(HWND window, int index, LONG value);
WIN32_IMPORT LONG WINAPI GetWindowLongA(HWND window, int index);
WIN32_IMPORT HWND WINAPI GetDlgItem(HWND dialog, int id);
WIN32_IMPORT LRESULT WINAPI SendMessageA(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

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

// USER32 printf into a buffer (cdecl, variable arguments).
WIN32_IMPORT int __cdecl wsprintfA(char *buffer, char const *format, ...);

#endif
