// Palette state and DirectDraw palette interface used at 00496120.
#ifndef RA2_SHARED_PALETTE_STATE_HPP
#define RA2_SHARED_PALETTE_STATE_HPP
#include "shared/convert.hpp"
#include "shared/directdraw.hpp"
#include "shared/com_api.hpp"
struct PALETTEENTRY {
    unsigned char peRed, peGreen, peBlue, peFlags;
};
struct IDirectDrawPalette : public IUnknown {
    virtual HRESULT __stdcall GetCaps(DWORD *caps) = 0;
    virtual HRESULT __stdcall GetEntries(DWORD flags, DWORD first, DWORD count, PALETTEENTRY *entries) = 0;
    virtual HRESULT __stdcall Initialize(IDirectDraw *draw, DWORD flags, PALETTEENTRY *entries) = 0;
    virtual HRESULT __stdcall SetEntries(DWORD flags, DWORD first, DWORD count, PALETTEENTRY *entries) = 0;
};
typedef char Palette_entry_size_check[sizeof(PALETTEENTRY) == 4 ? 1 : -1];
typedef char Palette_size_check[sizeof(PaletteClass) == 768 ? 1 : -1];
extern PaletteClass unknown_palette_00851cc8;
extern IDirectDrawPalette *unknown_palette_00851fc8;
extern PALETTEENTRY unknown_palette_entries_00851fcc[256];
extern IDirectDraw *DirectDrawObject;
extern bool unknown_palette_attached_008523d4;
extern IDirectDrawSurface *unknown_palette_surface_008523d8;
#endif
