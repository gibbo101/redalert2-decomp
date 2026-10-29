// The parts of DirectDraw (DirectX 3+ ddraw.h) the surface code uses.
//
// The VC6 toolchain has no DirectX SDK headers, so the COM interfaces are
// declared here with their real method order (only the vtable offset of a
// method matters to the code) and DDSURFACEDESC with its real layout
// (0x6C bytes: dwSize, ddpfPixelFormat at +0x48, ddsCaps at +0x68).
#ifndef RA2_SHARED_DIRECTDRAW_HPP
#define RA2_SHARED_DIRECTDRAW_HPP

typedef long HRESULT;
typedef unsigned long DWORD;
typedef struct HDC__ *HDC;
struct RECT;

#define DD_OK 0
#define DDERR_SURFACELOST ((HRESULT)0x887601C2)

#define DDSD_CAPS 0x00000001
#define DDSD_HEIGHT 0x00000002
#define DDSD_WIDTH 0x00000004
#define DDSCAPS_OFFSCREENPLAIN 0x00000040
#define DDSCAPS_SYSTEMMEMORY 0x00000800
#define DDSCAPS_3DDEVICE 0x00002000
#define DDSCAPS_VIDEOMEMORY 0x00004000
#define DDLOCK_WAIT 0x00000001
#define DDGBS_CANBLT 0x00000001
#define DDBLT_COLORFILL 0x00000400
#define DDBLT_WAIT 0x01000000

// Blit effects (0x64 bytes; only the members used here are named).
struct DDBLTFX {
    DWORD dwSize;               // +0x00
    DWORD unknown_04[19];       // +0x04
    DWORD dwFillColor;          // +0x50
    DWORD unknown_54[4];        // +0x54
};

struct DDCOLORKEY {
    DWORD dwColorSpaceLowValue;
    DWORD dwColorSpaceHighValue;
};

struct DDPIXELFORMAT {
    DWORD dwSize;           // +0x00
    DWORD dwFlags;          // +0x04
    DWORD dwFourCC;         // +0x08
    DWORD dwRGBBitCount;    // +0x0C
    DWORD dwRBitMask;       // +0x10
    DWORD dwGBitMask;       // +0x14
    DWORD dwBBitMask;       // +0x18
    DWORD dwRGBAlphaBitMask;// +0x1C
};

struct DDSCAPS {
    DWORD dwCaps;
};

struct DDSURFACEDESC {
    DWORD dwSize;               // +0x00
    DWORD dwFlags;              // +0x04
    DWORD dwHeight;             // +0x08
    DWORD dwWidth;              // +0x0C
    long lPitch;                // +0x10
    DWORD dwBackBufferCount;    // +0x14
    DWORD dwRefreshRate;        // +0x18
    DWORD dwAlphaBitDepth;      // +0x1C
    DWORD dwReserved;           // +0x20
    void *lpSurface;            // +0x24
    DDCOLORKEY ddckCKDestOverlay;   // +0x28
    DDCOLORKEY ddckCKDestBlt;       // +0x30
    DDCOLORKEY ddckCKSrcOverlay;    // +0x38
    DDCOLORKEY ddckCKSrcBlt;        // +0x40
    DDPIXELFORMAT ddpfPixelFormat;  // +0x48
    DDSCAPS ddsCaps;                // +0x68
};

// Only the observed DX3 caps fields are named. All remaining bytes are opaque.
struct DDCAPS {
    DWORD dwSize;                 // +0x00; observed size 0x13C
    DWORD dwCaps;                 // +0x04; capability masks read by 00495FC0
    unsigned char unknown_08[0x3C - 0x08];
    DWORD dwVidMemTotal;           // +0x3C; read by Get_Performance_Profile 0051A880
    DWORD dwVidMemFree;            // +0x40; value returned by 00495F60
    unsigned char unknown_44[0x13C - 0x44];
};
typedef char DDCAPS_size_check[(sizeof(DDCAPS) == 0x13C) ? 1 : -1];
typedef HRESULT (__stdcall *DDEnumModesCallback)(DDSURFACEDESC *description, void *context);

struct IDirectDrawClipper {
    virtual HRESULT __stdcall QueryInterface(void const *iid, void **object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual HRESULT __stdcall unknown_0c() = 0;
    virtual HRESULT __stdcall unknown_10() = 0;
    virtual HRESULT __stdcall unknown_14() = 0;
    virtual HRESULT __stdcall unknown_18() = 0;
    virtual HRESULT __stdcall unknown_1c() = 0;
    virtual HRESULT __stdcall SetHWnd(DWORD flags, void *window) = 0; // +20
};

struct IDirectDrawSurface {
    virtual HRESULT __stdcall QueryInterface(void const *iid, void **object) = 0;   // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                                   // +0x04
    virtual unsigned long __stdcall Release() = 0;                                  // +0x08
    virtual HRESULT __stdcall AddAttachedSurface(IDirectDrawSurface *surface) = 0;  // +0x0C
    virtual HRESULT __stdcall AddOverlayDirtyRect(RECT *rect) = 0;                  // +0x10
    virtual HRESULT __stdcall Blt(RECT *destrect, IDirectDrawSurface *source, RECT *sourcerect,
                                  DWORD flags, void *bltfx) = 0;                    // +0x14
    virtual HRESULT __stdcall BltBatch(void *batch, DWORD count, DWORD flags) = 0;  // +0x18
    virtual HRESULT __stdcall BltFast(DWORD x, DWORD y, IDirectDrawSurface *source, RECT *sourcerect,
                                      DWORD trans) = 0;                             // +0x1C
    virtual HRESULT __stdcall DeleteAttachedSurface(DWORD flags, IDirectDrawSurface *surface) = 0; // +0x20
    virtual HRESULT __stdcall EnumAttachedSurfaces(void *context, void *callback) = 0;   // +0x24
    virtual HRESULT __stdcall EnumOverlayZOrders(DWORD flags, void *context, void *callback) = 0; // +0x28
    virtual HRESULT __stdcall Flip(IDirectDrawSurface *target, DWORD flags) = 0;   // +0x2C
    virtual HRESULT __stdcall GetAttachedSurface(DDSCAPS *caps, IDirectDrawSurface **surface) = 0; // +0x30
    virtual HRESULT __stdcall GetBltStatus(DWORD flags) = 0;                       // +0x34
    virtual HRESULT __stdcall GetCaps(DDSCAPS *caps) = 0;                          // +0x38
    virtual HRESULT __stdcall GetClipper(IDirectDrawClipper **clipper) = 0;        // +0x3C
    virtual HRESULT __stdcall GetColorKey(DWORD flags, DDCOLORKEY *key) = 0;       // +0x40
    virtual HRESULT __stdcall GetDC(HDC *dc) = 0;                                  // +0x44
    virtual HRESULT __stdcall GetFlipStatus(DWORD flags) = 0;                      // +0x48
    virtual HRESULT __stdcall GetOverlayPosition(long *x, long *y) = 0;            // +0x4C
    virtual HRESULT __stdcall GetPalette(void **palette) = 0;                      // +0x50
    virtual HRESULT __stdcall GetPixelFormat(DDPIXELFORMAT *format) = 0;           // +0x54
    virtual HRESULT __stdcall GetSurfaceDesc(DDSURFACEDESC *desc) = 0;             // +0x58
    virtual HRESULT __stdcall Initialize(void *directdraw, DDSURFACEDESC *desc) = 0;    // +0x5C
    virtual HRESULT __stdcall IsLost() = 0;                                        // +0x60
    virtual HRESULT __stdcall Lock(RECT *rect, DDSURFACEDESC *desc, DWORD flags, void *event) = 0; // +0x64
    virtual HRESULT __stdcall ReleaseDC(HDC dc) = 0;                               // +0x68
    virtual HRESULT __stdcall Restore() = 0;                                       // +0x6C
    virtual HRESULT __stdcall SetClipper(IDirectDrawClipper *clipper) = 0;         // +0x70
    virtual HRESULT __stdcall SetColorKey(DWORD flags, DDCOLORKEY *key) = 0;       // +0x74
    virtual HRESULT __stdcall SetOverlayPosition(long x, long y) = 0;              // +0x78
    virtual HRESULT __stdcall SetPalette(void *palette) = 0;                       // +0x7C
    virtual HRESULT __stdcall Unlock(void *surfacedata) = 0;                       // +0x80
};

struct IDirectDraw {
    virtual HRESULT __stdcall QueryInterface(void const *iid, void **object) = 0;   // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                                   // +0x04
    virtual unsigned long __stdcall Release() = 0;                                  // +0x08
    virtual HRESULT __stdcall Compact() = 0;                                        // +0x0C
    virtual HRESULT __stdcall CreateClipper(DWORD flags, IDirectDrawClipper **clipper, void *outer) = 0; // +0x10
    virtual HRESULT __stdcall CreatePalette(DWORD flags, void *entries, void **palette, void *outer) = 0; // +0x14
    virtual HRESULT __stdcall CreateSurface(DDSURFACEDESC *desc, IDirectDrawSurface **surface, void *outer) = 0; // +0x18
    // Unused slots: signatures and return types are explicitly unproved placeholders.
    virtual void __stdcall Unknown_Slot7() = 0;                                  // +0x1C; never called here
    virtual HRESULT __stdcall EnumDisplayModes(DWORD flags, DDSURFACEDESC *description,
        void *context, DDEnumModesCallback callback) = 0;                         // +0x20
    virtual void __stdcall Unknown_Slot9() = 0;                                  // +0x24; never called here
    virtual void __stdcall Unknown_Slot10() = 0;                                 // +0x28; never called here
    virtual HRESULT __stdcall GetCaps(DDCAPS *driver, DDCAPS *emulation) = 0;       // +0x2C

    virtual void __stdcall Unknown_Slot12() = 0; // +0x30; unproved declaration, never called in this packet
    virtual void __stdcall Unknown_Slot13() = 0; // +0x34; unproved, never called here
    virtual void __stdcall Unknown_Slot14() = 0; // +0x38; unproved, never called here
    virtual void __stdcall Unknown_Slot15() = 0; // +0x3C; unproved, never called here
    virtual void __stdcall Unknown_Slot16() = 0; // +0x40; unproved, never called here
    virtual void __stdcall Unknown_Slot17() = 0; // +0x44; unproved, never called here
    virtual void __stdcall Unknown_Slot18() = 0; // +0x48; unproved, never called here
    virtual HRESULT __stdcall RestoreDisplayMode() = 0; // +0x4C
    virtual void __stdcall Unknown_Slot20() = 0; // +0x50; unproved declaration, never called in this packet
    virtual void __stdcall Unknown_Slot21() = 0; // +0x54; unproved declaration, never called in this packet
    virtual HRESULT __stdcall WaitForVerticalBlank(DWORD flags,void *event) = 0; // +0x58

};

#endif
