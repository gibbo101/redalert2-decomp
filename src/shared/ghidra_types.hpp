// Ghidra decompiler type names used by seed-generated sources.
//
// Sources produced by tools/original_target/seed_candidate.py keep Ghidra's
// width-only type names until a function's real types are understood. They
// describe storage width and signedness only, never meaning:
//
//   undefinedN / uintN  N-byte value of unknown meaning (unsigned)
//   intN               N-byte signed value (int3 is a 3-byte Ghidra artifact)
//   code               a function of unknown signature (used as `code *`)
//   float10            x87 80-bit temporary; VC6 `long double` is 64-bit
//
// The CONCAT/SUB/ZEXT/SEXT macros reproduce Ghidra's byte-assembly operators
// with explicit widths. When a function is understood, replace these names
// with real types (ideally from another shared header) and drop the include.
#ifndef RA2_SHARED_GHIDRA_TYPES_HPP
#define RA2_SHARED_GHIDRA_TYPES_HPP

typedef unsigned char undefined, undefined1, byte, uchar;
typedef signed char sbyte;
typedef unsigned short undefined2, ushort, word, wchar16;
typedef unsigned int undefined3, undefined4, uint, uint3, dword, ulong;
typedef int int3;
typedef unsigned __int64 undefined8, ulonglong, qword;
typedef __int64 longlong;
typedef long double float10;
typedef int code(...);

// Win32 names Ghidra emits for imported prototypes (layout-compatible).
typedef unsigned int UINT, DWORD, WPARAM, LPARAM, LRESULT;
typedef int BOOL;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef void *HWND, *HANDLE, *HINSTANCE, *HMODULE, *LPVOID, *HDC, *HKEY;
typedef char CHAR;
typedef unsigned int LCID;
typedef long LONG;
struct tagRECT { LONG left, top, right, bottom; };
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef tagRECT RECT;
typedef DWORD *LPDWORD;
typedef void *LPCRITICAL_SECTION, *LPSECURITY_ATTRIBUTES, *LPOVERLAPPED;
typedef wchar16 *LPWSTR;
typedef const wchar16 *LPCWSTR;
struct GUID { uint Data1; ushort Data2, Data3; uchar Data4[8]; };
typedef GUID IID;

#define CONCAT11(a, b) ((ushort)(((uint)(uchar)(a) << 8) | (uchar)(b)))
#define CONCAT22(a, b) (((uint)(ushort)(a) << 16) | (ushort)(b))
#define CONCAT12(a, b) (((uint)(uchar)(a) << 16) | (ushort)(b))
#define CONCAT21(a, b) (((uint)(ushort)(a) << 8) | (uchar)(b))
#define CONCAT31(a, b) (((uint)(a) << 8) | (uchar)(b))
#define CONCAT13(a, b) (((uint)(uchar)(a) << 24) | ((uint)(b) & 0xffffff))
#define CONCAT44(a, b) (((ulonglong)(uint)(a) << 32) | (uint)(b))
#define SUB41(x, n) ((uchar)((uint)(x) >> (8 * (n))))
#define SUB42(x, n) ((ushort)((uint)(x) >> (8 * (n))))
#define SUB84(x, n) ((uint)((ulonglong)(x) >> (8 * (n))))
#define CARRY1(a, b) ((uchar)((uchar)(a) + (uchar)(b)) < (uchar)(a))
#define SBORROW4(a, b) ((((int)(a) ^ (int)(b)) & ((int)(a) ^ (int)((int)(a) - (int)(b)))) < 0)
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define CARRY4(a, b) ((uint)(a) + (uint)(b) < (uint)(a))
#define ZEXT14(x) ((uint)(uchar)(x))
#define ZEXT24(x) ((uint)(ushort)(x))
#define SEXT14(x) ((int)(signed char)(x))
#define SEXT24(x) ((int)(short)(x))

#endif
