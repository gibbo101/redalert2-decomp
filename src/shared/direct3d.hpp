// The parts of Direct3D (DirectX 5 d3d.h) the DirectDraw surface code uses
// to set up its 3D device (0x004B1340, 0x004B1470).
//
// As in directdraw.hpp the COM interfaces are declared with their real
// method order (only the vtable offsets matter to the code); methods that
// are not called keep placeholder names.
#ifndef RA2_SHARED_DIRECT3D_HPP
#define RA2_SHARED_DIRECT3D_HPP

#include "shared/directdraw.hpp"

typedef float D3DVALUE;

struct GUID;

// D3DVIEWPORT2 (0x2C bytes).
struct D3DVIEWPORT2 {
    DWORD dwSize;           // +0x00
    DWORD dwX;              // +0x04
    DWORD dwY;              // +0x08
    DWORD dwWidth;          // +0x0C
    DWORD dwHeight;         // +0x10
    D3DVALUE dvClipX;       // +0x14
    D3DVALUE dvClipY;       // +0x18
    D3DVALUE dvClipWidth;   // +0x1C
    D3DVALUE dvClipHeight;  // +0x20
    D3DVALUE dvMinZ;        // +0x24
    D3DVALUE dvMaxZ;        // +0x28
};

struct IDirect3DViewport2 {
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object) = 0;   // +0x00
    virtual DWORD __stdcall AddRef() = 0;                                           // +0x04
    virtual DWORD __stdcall Release() = 0;                                          // +0x08
    virtual HRESULT __stdcall Initialize(void *) = 0;                               // +0x0C
    virtual HRESULT __stdcall GetViewport(void *) = 0;                              // +0x10
    virtual HRESULT __stdcall SetViewport(void *) = 0;                              // +0x14
    virtual HRESULT __stdcall TransformVertices(DWORD, void *, DWORD, DWORD *) = 0; // +0x18
    virtual HRESULT __stdcall LightElements(DWORD, void *) = 0;                     // +0x1C
    virtual HRESULT __stdcall SetBackground(DWORD) = 0;                             // +0x20
    virtual HRESULT __stdcall GetBackground(DWORD *, int *) = 0;                    // +0x24
    virtual HRESULT __stdcall SetBackgroundDepth(IDirectDrawSurface *) = 0;         // +0x28
    virtual HRESULT __stdcall GetBackgroundDepth(IDirectDrawSurface **, int *) = 0; // +0x2C
    virtual HRESULT __stdcall Clear(DWORD, void *, DWORD) = 0;                      // +0x30
    virtual HRESULT __stdcall AddLight(void *) = 0;                                 // +0x34
    virtual HRESULT __stdcall DeleteLight(void *) = 0;                              // +0x38
    virtual HRESULT __stdcall NextLight(void *, void **, DWORD) = 0;                // +0x3C
    virtual HRESULT __stdcall GetViewport2(D3DVIEWPORT2 *) = 0;                     // +0x40
    virtual HRESULT __stdcall SetViewport2(D3DVIEWPORT2 *) = 0;                     // +0x44
};

struct IDirect3DDevice2 {
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object) = 0;   // +0x00
    virtual DWORD __stdcall AddRef() = 0;                                           // +0x04
    virtual DWORD __stdcall Release() = 0;                                          // +0x08
    virtual HRESULT __stdcall GetCaps(void *, void *) = 0;                          // +0x0C
    virtual HRESULT __stdcall SwapTextureHandles(void *, void *) = 0;               // +0x10
    virtual HRESULT __stdcall GetStats(void *) = 0;                                 // +0x14
    virtual HRESULT __stdcall AddViewport(IDirect3DViewport2 *viewport) = 0;        // +0x18
    virtual HRESULT __stdcall DeleteViewport(IDirect3DViewport2 *viewport) = 0;     // +0x1C
    virtual HRESULT __stdcall NextViewport(IDirect3DViewport2 *, IDirect3DViewport2 **, DWORD) = 0; // +0x20
    virtual HRESULT __stdcall EnumTextureFormats(void *, void *) = 0;               // +0x24
    virtual HRESULT __stdcall BeginScene() = 0;                                     // +0x28
    virtual HRESULT __stdcall EndScene() = 0;                                       // +0x2C
    virtual HRESULT __stdcall GetDirect3D(void **) = 0;                             // +0x30
    virtual HRESULT __stdcall SetCurrentViewport(IDirect3DViewport2 *viewport) = 0; // +0x34
};

struct IDirect3D {
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object) = 0;   // +0x00
    virtual DWORD __stdcall AddRef() = 0;                                           // +0x04
    virtual DWORD __stdcall Release() = 0;                                          // +0x08
};

struct IDirect3D2 {
    virtual HRESULT __stdcall QueryInterface(GUID const &iid, void **object) = 0;   // +0x00
    virtual DWORD __stdcall AddRef() = 0;                                           // +0x04
    virtual DWORD __stdcall Release() = 0;                                          // +0x08
    virtual HRESULT __stdcall EnumDevices(void *, void *) = 0;                      // +0x0C
    virtual HRESULT __stdcall CreateLight(void **, void *) = 0;                     // +0x10
    virtual HRESULT __stdcall CreateMaterial(void **, void *) = 0;                  // +0x14
    virtual HRESULT __stdcall CreateViewport(IDirect3DViewport2 **viewport, void *outer) = 0;   // +0x18
    virtual HRESULT __stdcall FindDevice(void *, void *) = 0;                       // +0x1C
    virtual HRESULT __stdcall CreateDevice(GUID const &clsid, IDirectDrawSurface *surface,
                                           IDirect3DDevice2 **device) = 0;          // +0x20
};

// Interface and device identifiers (DirectX dxguid data in the image).
extern "C" GUID const IID_IDirect3D;                // 0x007AFDB0
extern "C" GUID const IID_IDirect3D2;               // 0x007B00C0
extern "C" GUID const IID_IDirect3DHALDevice;       // 0x007B0100

// Direct3D state of the DirectDraw display (Init_Direct3D 0x004B1340).
extern IDirect3D *unknown_direct3d_852fe8;          // 0x00852FE8
extern IDirect3D2 *unknown_direct3d2_852fdc;        // 0x00852FDC
extern IDirect3DDevice2 *unknown_device_852fe0;     // 0x00852FE0 (gscreen.hpp: IUnknownDevice852FE0)
extern IDirect3DViewport2 *unknown_viewport_852fe4; // 0x00852FE4
// The surface GScreenClass::Render composes (gscreen.hpp; a DSurface here).
class Surface;
extern Surface *unknown_surface_839964;             // 0x00839964
extern int unknown_8523e0;                          // 0x008523E0 (ms_anim.hpp)
extern int unknown_8523e4;                          // 0x008523E4 (ms_anim.hpp)

#endif
