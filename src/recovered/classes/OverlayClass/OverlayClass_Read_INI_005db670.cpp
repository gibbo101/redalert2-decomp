// static void __fastcall OverlayClass::Read_INI(CCINIClass &ini) (0x005DB670)
// Reads [OverlayPack] (an overlay index per cell, LCW compressed) and
// [OverlayDataPack] (the overlay data byte per cell) of a scenario through a
// scratch 640 x 400 surface; every overlay with an image is created, and
// the wall and ore data bytes are restored.
#include "shared/overlay.hpp"
#include "shared/map_view.hpp"
#include "shared/surface.hpp"
#include "shared/lcw_straw.hpp"
#include "shared/buffer_straw.hpp"
// @ref ??_GStraw@@UAEPAXI@Z=0049ed40
// @ref ??_GBufferStraw@@UAEPAXI@Z=0049ed60
// @ref ?Can_Lock@Surface@@UAE_NHH@Z=00411270
// @ref ?Unknown_Slot26@Surface@@UAE_NHH@Z=00411280
// @ref ?Get_Rect@Surface@@UAE?AVRect@@XZ=00411290
// @ref ?Get_Width@Surface@@UAEHXZ=004112c0
// @ref ?Get_Height@Surface@@UAEHXZ=004112d0
// @ref ?Lock@XSurface@@UAEPAXUPoint2D@@@Z=004112e0
// @ref ?Unlock@XSurface@@UAE_NXZ=004112f0
// @ref ?Is_Locked@XSurface@@UAE_NXZ=00411300
// @ref ?Is_Direct_Draw@XSurface@@UAE_NXZ=00411310
// @ref ??_GXSurface@@UAEPAXI@Z=00411320
// @ref ?Is_Direct_Draw@Surface@@UAE_NXZ=00411340
// @ref ??_GSurface@@UAEPAXI@Z=00411350
// @ref ?Lock@BSurface@@UAEPAXUPoint2D@@@Z=00411370
// @ref ?Bytes_Per_Pixel@BSurface@@UAEHXZ=004113b0
// @ref ?Stride@BSurface@@UAEHXZ=004113c0
// @ref ??_GBSurface@@UAEPAXI@Z=004113d0
// @ref ??0XSurface@@QAE@HH@Z=0049f430
// @ref ??_7BufferStraw@@6B@=0079e9e8
// @ref ??_C@_0BA@KNFB@OverlayDataPack?$AA@=007e8b44
// @ref ??_C@_0M@GIDM@OverlayPack?$AA@=007e8b54
// @ref ?unknown_ini_format_a40d24@@3HA=00a40d24
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_006ECF10@@YAXXZ=006ecf10

void Unknown_006ECF10();            // 0x006ECF10

void __fastcall OverlayClass::Read_INI(CCINIClass &ini)
{
    if (unknown_ini_format_a40d24 > 1) {
        BSurface surface(640, 400, 2);
        surface.Fill(0);
        int length = ini.Get_UUBlock("OverlayPack", surface.Lock(), surface.Get_Width() * surface.Get_Height() * surface.Bytes_Per_Pixel());
        if (length > 0) {
            BufferStraw buffer_straw(surface.Lock(), length);
            LCWStraw lcw_straw(LCWStraw::DECOMPRESS, 0x2000);
            lcw_straw.Straw::Get_From(&buffer_straw);
            for (int y = 0; y < 512; y++) {
                for (int x = 0; x < 512; x++) {
                    Cell cell((short)x, (short)y);
                    unsigned int overlay = 0xFFFFFFFF;
                    lcw_straw.Get(&overlay, 1);
                    if (overlay != 0xFFFFFFFF) {
                        overlay &= 0xFF;
                        if (overlay != 0xFFFFFFFF) {
                            if ((OverlayTypes[overlay]->unknown_slot39() || OverlayTypes[overlay]->CellAnim) && (!unknown_game_mode_a3d298 || !OverlayTypes[overlay]->Crate)) {
                                if (Map.Unknown_0054AAB0(cell)) {
                                    unsigned char data = Map_Cell(cell).OverlayData;
                                    new OverlayClass(OverlayTypes[overlay], cell, -1);
                                    if (overlay == 0x18 || overlay == 0x19 || overlay == 0xED || overlay == 0xEE) {
                                        Map_Cell(cell).OverlayData = data;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            surface.Unlock();
        }
        surface.Unlock();
        int width = surface.Get_Width();
        int height = surface.Get_Height();
        length = ini.Get_UUBlock("OverlayDataPack", surface.Lock(), height * width);
        if (length > 0) {
            BufferStraw data_buffer_straw(surface.Lock(), length);
            LCWStraw data_lcw_straw(LCWStraw::DECOMPRESS, 0x2000);
            data_lcw_straw.Straw::Get_From(&data_buffer_straw);
            for (int y = 0; y < 512; y++) {
                for (int x = 0; x < 512; x++) {
                    Cell cell((short)x, (short)y);
                    unsigned char data = 0;
                    data_lcw_straw.Get(&data, 1);
                    if (Map.Unknown_0054AAB0(cell)) {
                        Map_Cell(cell).OverlayData = data;
                    }
                }
            }
            surface.Unlock();
        }
        surface.Unlock();
    }
    Unknown_006ECF10();
}
