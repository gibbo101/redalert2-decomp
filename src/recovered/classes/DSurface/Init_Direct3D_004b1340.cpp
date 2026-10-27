// HRESULT Init_Direct3D() (0x004B1340)
// Creates the Direct3D device on the composing surface's DirectDraw surface:
// IDirect3D and IDirect3D2 from the DirectDraw object, a HAL device, and a
// viewport covering unknown_8523e0 x unknown_8523e4 that becomes the
// device's current viewport. Returns the first failing HRESULT (the
// viewport is released again when the device rejects it). The name is a
// hypothesis.
#include "shared/direct3d.hpp"
#include "shared/dsurface.hpp"
// @ref ?DirectDrawObject@@3PAUIDirectDraw@@A=008523cc
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ?unknown_direct3d_852fe8@@3PAUIDirect3D@@A=00852fe8
// @ref ?unknown_direct3d2_852fdc@@3PAUIDirect3D2@@A=00852fdc
// @ref ?unknown_device_852fe0@@3PAUIDirect3DDevice2@@A=00852fe0
// @ref ?unknown_viewport_852fe4@@3PAUIDirect3DViewport2@@A=00852fe4
// @ref _IID_IDirect3D=007afdb0
// @ref _IID_IDirect3D2=007b00c0
// @ref _IID_IDirect3DHALDevice=007b0100

HRESULT Init_Direct3D()
{
    IDirectDrawSurface *surface = ((DSurface *)unknown_surface_839964)->Get_DD_Surface();
    HRESULT result = DirectDrawObject->QueryInterface(&IID_IDirect3D, (void **)&unknown_direct3d_852fe8);
    if (result != DD_OK) {
        return result;
    }
    result = unknown_direct3d_852fe8->QueryInterface(IID_IDirect3D2, (void **)&unknown_direct3d2_852fdc);
    if (result != DD_OK) {
        return result;
    }
    result = unknown_direct3d2_852fdc->CreateDevice(IID_IDirect3DHALDevice, surface, &unknown_device_852fe0);
    if (result != DD_OK) {
        return result;
    }
    result = unknown_direct3d2_852fdc->CreateViewport(&unknown_viewport_852fe4, 0);
    if (result != DD_OK) {
        return result;
    }
    result = unknown_device_852fe0->AddViewport(unknown_viewport_852fe4);
    if (result != DD_OK) {
        unknown_viewport_852fe4->Release();
        unknown_viewport_852fe4 = 0;
        return result;
    }
    D3DVIEWPORT2 viewport;
    memset(&viewport, 0, sizeof(viewport));
    viewport.dwSize = sizeof(viewport);
    viewport.dwWidth = unknown_8523e0;
    viewport.dwHeight = unknown_8523e4;
    viewport.dvClipX = -1.0f;
    viewport.dvClipWidth = 2.0f;
    viewport.dvClipY = 1.0f;
    viewport.dvClipHeight = 2.0f;
    viewport.dvMaxZ = 1.0f;
    unknown_viewport_852fe4->SetViewport2(&viewport);
    return unknown_device_852fe0->SetCurrentViewport(unknown_viewport_852fe4);
}
