bool UnknownPreview_0061D430::Read_INI(CCINIClass const &ini)
{
    static char const * const PREVIEW = "Preview";
    static char const * const PREVIEWPACK = "PreviewPack";

    if (unknown_00 != 0) {
        delete unknown_00;
        unknown_00 = 0;
    }

    INIRect rect = ini.Get_Rect(PREVIEW, "Size", (INIRect const &)Map.MapLocalSize);

    unknown_00 = new DSurface(rect.Width, rect.Height, true);
    unknown_00->Fill(0);

    int size = unknown_surface_839958->Get_Width() * unknown_surface_839958->Get_Height() * unknown_surface_839958->Bytes_Per_Pixel();
    int length = ini.Get_UUBlock(PREVIEWPACK, unknown_surface_839958->Lock(), size);

    if (length > 0) {
        unsigned char *buffer = (unsigned char *)unknown_surface_839958->Lock();
        BufferStraw bstraw(buffer, length);
        LZOStraw uncomp(LZOStraw::DECOMPRESS, 0x2000);
        uncomp.Get_From(&bstraw);
        unsigned char rgb[3] = {0, 0, 0};
        unknown_00->Lock();

        for (int y = 0; y < unknown_00->Get_Height(); y++) {
            for (int x = 0; x < unknown_00->Get_Width(); x++) {
                if (uncomp.Get(rgb, sizeof(rgb)) != sizeof(rgb)) {
                    unknown_00->Unlock();
                    unknown_surface_839958->Unlock();
                    unknown_surface_839958->Unlock();
                    return false;
                }
                unknown_00->Put_Pixel(Point2D(x, y), Build_Hicolor_Pixel(rgb[0], rgb[1], rgb[2]));
            }
        }

        unknown_00->Unlock();
        unknown_surface_839958->Unlock();
    }
    unknown_surface_839958->Unlock();
    return true;
}
// @ref _?PREVIEW@?1??Read_INI@UnknownPreview_0061D430@@QAE_NABVCCINIClass@@@Z@4QBDB=007a8420
// @ref _?PREVIEWPACK@?1??Read_INI@UnknownPreview_0061D430@@QAE_NABVCCINIClass@@@Z@4QBDB=007a8424
// @ref ??_GStraw@@UAEPAXI@Z=0049ed40
// @ref ??_GBufferStraw@@UAEPAXI@Z=0049ed60
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??0DSurface@@QAE@HHE@Z=004aa4a0
// @ref ??0LZOStraw@@QAE@W4CompControl@0@H@Z=0053efb0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1LZOStraw@@UAE@XZ=0053f010
// @ref ??1Straw@@UAE@XZ=0069b010
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_7BufferStraw@@6B@=0079e9e8
// @ref ??_7Straw@@6B@=0079e9f8
// @ref ?Get@LZOStraw@@UAEHPAXH@Z=0053f050
// @ref ?Get_From@Straw@@UAEXPAV1@@Z=0069b050
// @ref ?Get_Rect@INIClass@@QBE?AUINIRect@@PBD0ABU2@@Z=0050dd50
// @ref ?Get_UUBlock@INIClass@@QBEHPBDPAXH@Z=0050d0f0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
