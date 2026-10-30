// static void __fastcall OverlayClass::Write_INI(CCINIClass &ini) (0x005DBA30)
// Rewrites [OverlayPack] and [OverlayDataPack]: the overlay index and the
// overlay data byte of every cell of the 512 x 512 map, LCW compressed into
// the hidden surface's memory and stored as UU blocks.
#include "shared/overlay.hpp"
#include "shared/map_view.hpp"
#include "shared/lcw_pipe.hpp"
#include "shared/buffer_pipe.hpp"
#include "shared/movie_globals.hpp"
// @ref ?unknown_overlay_section_7a77c0@@3PBDB=007a77c0
// @ref ??_7BufferPipe@@6B@=0079ea08
// @ref ??_C@_0BA@KNFB@OverlayDataPack?$AA@=007e8b44
// @ref ??_C@_0M@GIDM@OverlayPack?$AA@=007e8b54
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
void __fastcall OverlayClass::Write_INI(CCINIClass &ini)
{
    ini.Clear(unknown_overlay_section_7a77c0);
    ini.Clear("OverlayPack");

    BufferPipe bpipe(unknown_surface_839958->Lock(), unknown_surface_839958->Get_Width() * unknown_surface_839958->Get_Height());
    LCWPipe comppipe(LCWPipe::COMPRESS, 0x2000);

    comppipe.Put_To(&bpipe);

    int total = 0;
    int y;
    for (y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            total += comppipe.Put(&Map_Cell(Cell((short)x, (short)y)).OverlayIndex, 1);
        }
    }
    if (total) {
        ini.Put_UUBlock("OverlayPack", unknown_surface_839958->Lock(), total);
        unknown_surface_839958->Unlock();
    }
    unknown_surface_839958->Unlock();

    ini.Clear("OverlayDataPack");

    BufferPipe databpipe(unknown_surface_839958->Lock(), unknown_surface_839958->Get_Width() * unknown_surface_839958->Get_Height());
    LCWPipe datacomppipe(LCWPipe::COMPRESS, 0x2000);

    datacomppipe.Put_To(&databpipe);

    total = 0;
    for (y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            total += datacomppipe.Put(&Map_Cell(Cell((short)x, (short)y)).OverlayData, 1);
        }
    }
    if (total) {
        ini.Put_UUBlock("OverlayDataPack", unknown_surface_839958->Lock(), total);
        unknown_surface_839958->Unlock();
    }
    unknown_surface_839958->Unlock();
}
