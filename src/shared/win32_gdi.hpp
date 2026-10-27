// Win32 GDI declarations used by the observed DIB-section wrapper.
#ifndef RA2_WIN32_GDI_HPP
#define RA2_WIN32_GDI_HPP
#include "shared/win32_api.hpp"
typedef struct HDC__ *HDC;
typedef struct HBITMAP__ *HBITMAP;
typedef HANDLE HGDIOBJ;
struct RGBQUAD { unsigned char rgbBlue, rgbGreen, rgbRed, rgbReserved; };
struct BITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth, biHeight;
    WORD biPlanes, biBitCount;
    DWORD biCompression, biSizeImage;
    LONG biXPelsPerMeter, biYPelsPerMeter;
    DWORD biClrUsed, biClrImportant;
};
struct BITMAPINFO { BITMAPINFOHEADER bmiHeader; RGBQUAD bmiColors[1]; };
WIN32_IMPORT HDC WINAPI GetDC(HWND window);
WIN32_IMPORT int WINAPI ReleaseDC(HWND window, HDC dc);
WIN32_IMPORT HBITMAP WINAPI CreateDIBSection(HDC dc, BITMAPINFO const *info, unsigned int usage,
                                            void **bits, HANDLE section, DWORD offset);
WIN32_IMPORT BOOL WINAPI DeleteObject(HGDIOBJ object);
typedef DWORD COLORREF;
WIN32_IMPORT int WINAPI SetBkMode(HDC dc, int mode);
WIN32_IMPORT COLORREF WINAPI SetBkColor(HDC dc, COLORREF color);
WIN32_IMPORT COLORREF WINAPI SetTextColor(HDC dc, COLORREF color);
WIN32_IMPORT HGDIOBJ WINAPI SelectObject(HDC dc, HGDIOBJ object);
WIN32_IMPORT BOOL WINAPI TextOutA(HDC dc, int x, int y, LPCSTR text, int count);
#endif
