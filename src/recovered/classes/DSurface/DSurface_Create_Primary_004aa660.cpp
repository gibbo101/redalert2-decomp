// Creates the primary DirectDraw surface and optionally returns its back buffer.
// Full frozen baseline bound: 004AA660..004AAB5D, ret at 004AAB5D.
#include "shared/dsurface.hpp"
#include "shared/crt_memory.hpp"
#include "shared/hicolor.hpp"
#include "shared/win32_api.hpp"
WIN32_IMPORT HWND WINAPI GetActiveWindow();
void __cdecl Debug_Print_004068f0(char const *format, ...);
unsigned int Get_Device_Caps_00495fc0();
void __fastcall unknown_00495770(HRESULT result, int show_success);
extern IDirectDrawSurface *PrimarySurface_8523d8;
extern DDPIXELFORMAT PrimaryPixelFormat_852b38;
extern unsigned short unknown_eighth_mask_852fd4;
extern char const CreatePrimary[]; // @ref ?CreatePrimary@@3QBDB=007d63b0
extern char const AllowStretch[]; // @ref ?AllowStretch@@3QBDB=007d638c
extern char const AllowHWFill[]; // @ref ?AllowHWFill@@3QBDB=007d6370
extern char const CreateSurface[]; // @ref ?CreateSurface@@3QBDB=007d6340
extern char const CreateFailed[]; // @ref ?CreateFailed@@3QBDB=007d62b0
extern char const CreateOK[]; // @ref ?CreateOK@@3QBDB=007d632c
extern char const GetDescFailed[]; // @ref ?GetDescFailed@@3QBDB=007d62fc
extern char const CreateDone[]; // @ref ?CreateDone@@3QBDB=007d62dc
extern char const TrueText[]; // @ref ?TrueText@@3QBDB=007d24d8
extern char const FalseText[]; // @ref ?FalseText@@3QBDB=007d24d0
// @ref ?Debug_Print_004068f0@@YAXPBDZZ=004068f0
// @ref ?Get_Device_Caps_00495fc0@@YAIXZ=00495fc0
// @ref ?unknown_00495770@@YIXJH@Z=00495770
// @ref ?AllowStretchBlits_852fd6@@3_NA=00852fd6
// @ref ?PrimarySurface_8523d8@@3PAUIDirectDrawSurface@@A=008523d8
// @ref ?PrimaryPixelFormat_852b38@@3UDDPIXELFORMAT@@A=00852b38
// @ref ?unknown_flag_7d6294@@3_NA=007d6294
// @ref ?unknown_eighth_mask_852fd4@@3GA=00852fd4
inline bool Match_Primary_Format(int red_left, int red_right, int green_left, int green_right, int blue_left, int blue_right) {
    return unknown_shift_852fc0 == blue_left && unknown_shift_852fc4 == blue_right && unknown_shift_852fc8 == green_left && unknown_shift_852fcc == green_right && unknown_shift_852fb8 == red_left && unknown_shift_852fbc == red_right;
}
// Recognize the observed channel layouts; preserve the previous mode for an unknown layout.
inline void Select_Primary_Format(int red_left, int red_right, int green_left, int green_right, int blue_left, int blue_right) {
    if (blue_left==0 && blue_right==3 && green_left==5 && green_right==3 && red_left==10 && red_right==3) { unknown_7d6290=0; return; }
    if (blue_left==0 && blue_right==2 && green_left==6 && green_right==3 && red_left==11 && red_right==3) { unknown_7d6290=1; return; }
    if (blue_left==0 && blue_right==3 && green_left==5 && green_right==2 && red_left==11 && red_right==3) { unknown_7d6290=2; return; }
    if (blue_left==0 && blue_right==3 && green_left==5 && green_right==3 && red_left==11 && red_right==2) { unknown_7d6290=1; return; }
}
DSurface *__fastcall DSurface::Create_Primary(DSurface **back_buffer)
{
    Debug_Print_004068f0(CreatePrimary);
    unsigned int caps = Get_Device_Caps_00495fc0();
    AllowStretchBlits_852fd6 = false;
    if (caps & 0x40) AllowStretchBlits_852fd6 = true;
    Debug_Print_004068f0(AllowStretch, AllowStretchBlits_852fd6 ? TrueText : FalseText);
    if (!(caps & 0x10)) unknown_flag_7d6294 = false;
    Debug_Print_004068f0(AllowHWFill, unknown_flag_7d6294 == true ? TrueText : FalseText);
    DSurface *surface = new DSurface;
    int count = back_buffer != 0;
    surface->VideoSurfaceDescription->dwFlags = 1;
    if (unknown_flag_852fd7)
        surface->VideoSurfaceDescription->ddsCaps.dwCaps = 0x2200;
    else
        surface->VideoSurfaceDescription->ddsCaps.dwCaps = 0x200;
    if (count > 0) {
        surface->VideoSurfaceDescription->ddsCaps.dwCaps |= 0x18;
        surface->VideoSurfaceDescription->dwFlags |= 0x20;
        surface->VideoSurfaceDescription->dwBackBufferCount = count;
    }
    Debug_Print_004068f0(CreateSurface);
    HRESULT result = DirectDrawObject->CreateSurface(surface->VideoSurfaceDescription, &surface->VideoSurfacePtr, 0);
    if (result == DD_OK) {
    Debug_Print_004068f0(CreateOK);
    if (count > 0) {
        DDSCAPS attached_caps;
        attached_caps.dwCaps = 4;
        IDirectDrawSurface *attached;
        if (surface->VideoSurfacePtr->GetAttachedSurface(&attached_caps, &attached) == DD_OK)
            *back_buffer = new DSurface(attached);
    }
    memset(surface->VideoSurfaceDescription, 0, sizeof(DDSURFACEDESC));
    surface->VideoSurfaceDescription->dwSize = sizeof(DDSURFACEDESC);
    if (surface->VideoSurfacePtr->GetSurfaceDesc(surface->VideoSurfaceDescription) != DD_OK)
        Debug_Print_004068f0(GetDescFailed);
    surface->BytesPerPixel = (surface->VideoSurfaceDescription->ddpfPixelFormat.dwRGBBitCount + 7U) >> 3;
    surface->IsVideoRam = (surface->VideoSurfaceDescription->ddsCaps.dwCaps >> 14) & 1;
    surface->IsPrimary = true;
    surface->Width = surface->VideoSurfaceDescription->dwWidth;
    surface->Height = surface->VideoSurfaceDescription->dwHeight;
    PrimarySurface_8523d8 = surface->VideoSurfacePtr;
    if (DirectDrawObject->CreateClipper(0, &unknown_clipper_852fb4, 0) == DD_OK) {
        if (unknown_clipper_852fb4->SetHWnd(0, GetActiveWindow()) == DD_OK)
            surface->VideoSurfacePtr->SetClipper(unknown_clipper_852fb4);
    }
    PrimaryPixelFormat_852b38 = surface->VideoSurfaceDescription->ddpfPixelFormat;
    if (surface->Bytes_Per_Pixel() == 2) {
        unknown_shift_852fb8 = 0;
        unknown_shift_852fbc = 0;
        unsigned int red_mask = PrimaryPixelFormat_852b38.dwRBitMask;
        while (unknown_shift_852fb8 < 16) {
            if (red_mask & 1) break;
            red_mask = (int)red_mask >> 1;
            ++unknown_shift_852fb8;
        }
        while (unknown_shift_852fbc < 8) {
            if (red_mask & 0x80) break;
            red_mask <<= 1;
            ++unknown_shift_852fbc;
        }
        unknown_shift_852fc8 = 0;
        unknown_shift_852fcc = 0;
        unsigned int green_mask = PrimaryPixelFormat_852b38.dwGBitMask;
        while (unknown_shift_852fc8 < 16) {
            if (green_mask & 1) break;
            ++unknown_shift_852fc8;
            green_mask = (int)green_mask >> 1;
        }
        while (unknown_shift_852fcc < 8) {
            if (green_mask & 0x80) break;
            ++unknown_shift_852fcc;
            green_mask <<= 1;
        }
        unknown_shift_852fc0 = 0;
        unknown_shift_852fc4 = 0;
        unsigned int blue_mask = PrimaryPixelFormat_852b38.dwBBitMask;
        while (unknown_shift_852fc0 < 16) {
            if (blue_mask & 1) break;
            ++unknown_shift_852fc0;
            blue_mask = (int)blue_mask >> 1;
        }
        while (unknown_shift_852fc4 < 8) {
            if (blue_mask & 0x80) break;
            ++unknown_shift_852fc4;
            blue_mask <<= 1;
        }
        unknown_7d6290 = -1;
        unknown_half_mask_852fd0 =
            (unsigned short)((127 >> unknown_shift_852fc4) << unknown_shift_852fc0) |
            (unsigned short)((127 >> unknown_shift_852fcc) << unknown_shift_852fc8) |
            (unsigned short)((127 >> unknown_shift_852fbc) << unknown_shift_852fb8);
        unknown_quarter_mask_852fd2 =
            (unsigned short)((63 >> unknown_shift_852fc4) << unknown_shift_852fc0) |
            (unsigned short)((63 >> unknown_shift_852fcc) << unknown_shift_852fc8) |
            (unsigned short)((63 >> unknown_shift_852fbc) << unknown_shift_852fb8);
        unknown_eighth_mask_852fd4 =
            (unsigned short)((31 >> unknown_shift_852fc4) << unknown_shift_852fc0) |
            (unsigned short)((31 >> unknown_shift_852fcc) << unknown_shift_852fc8) |
            (unsigned short)((31 >> unknown_shift_852fbc) << unknown_shift_852fb8);
        Select_Primary_Format(unknown_shift_852fb8, unknown_shift_852fbc, unknown_shift_852fc8, unknown_shift_852fcc, unknown_shift_852fc0, unknown_shift_852fc4);
    }
done:
    Debug_Print_004068f0(CreateDone);
    return surface;
    }
    unknown_00495770(result, 1);
    Debug_Print_004068f0(CreateFailed, result);
    delete surface;
    return 0;
}
