// void Release_Direct3D() (0x004B1470)
// Releases the viewport, the device and the IDirect3D2 interface created by
// Init_Direct3D (0x004B1340). The name is a hypothesis; the IDirect3D
// interface (0x00852FE8) is not released here.
#include "shared/direct3d.hpp"

void Release_Direct3D()
{
    if (unknown_viewport_852fe4 != 0) {
        unknown_viewport_852fe4->Release();
        unknown_viewport_852fe4 = 0;
    }
    if (unknown_device_852fe0 != 0) {
        unknown_device_852fe0->Release();
        unknown_device_852fe0 = 0;
    }
    if (unknown_direct3d2_852fdc != 0) {
        unknown_direct3d2_852fdc->Release();
        unknown_direct3d2_852fdc = 0;
    }
}
