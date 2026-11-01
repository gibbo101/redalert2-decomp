
bool UnknownPreview_0061D430::Write_INI_0061DC80(CCINIClass &ini)
{
    static char const * const PREVIEW = "Preview";
    static char const * const PREVIEWPACK = "PreviewPack";

    bool created = false;
    if (unknown_00 == 0) {
        Unknown_0061D660();
        created = true;
    }

    ini.Clear(PREVIEW);

    ini.Put_Rect(PREVIEW, "Size", (INIRect const &)unknown_00->Get_Rect());

    BufferPipe bpipe(unknown_surface_839958->Lock(), unknown_surface_839958->Get_Width() * unknown_surface_839958->Get_Height() * unknown_surface_839958->Bytes_Per_Pixel());
    LZOPipe comp(LZOPipe::COMPRESS, 0x2000);
    comp.Put_To(&bpipe);

    int total = 0;
    RGBClass rgb(0, 0, 0);

    unknown_00->Lock();
    for (int y = 0; y < unknown_00->Get_Height(); y++) {
        for (int x = 0; x < unknown_00->Get_Width(); x++) {
            int pixel = unknown_00->Get_Pixel(Point2D(x, y));
            rgb = Pixel_To_RGB(pixel);

            total += comp.Put(&rgb, sizeof(rgb));
        }
    }
    unknown_00->Unlock();

    total += comp.End();
    ini.Clear(PREVIEWPACK);
    if (total > 0) {
        ini.Put_UUBlock(PREVIEWPACK, unknown_surface_839958->Lock(), total);
        unknown_surface_839958->Unlock();
    }

    unknown_surface_839958->Unlock();

    if (created) {
        delete unknown_00;
        unknown_00 = 0;
    }
    return total > 0;
}
// @ref _?PREVIEW@?1??Write_INI_0061DC80@UnknownPreview_0061D430@@QAE_NAAVCCINIClass@@@Z@4QBDB=007a8418
// @ref _?PREVIEWPACK@?1??Write_INI_0061DC80@UnknownPreview_0061D430@@QAE_NAAVCCINIClass@@@Z@4QBDB=007a841c
// @ref ??_C@_07IFKH@Preview?$AA@=007ebf48
// @ref ??_C@_0M@BNBE@PreviewPack?$AA@=007ebf3c
// @ref ??_C@_04BBDK@Size?$AA@=007d5e28
// @ref ?End@Pipe@@UAEHXZ=0046cb80
// @ref ??_GPipe@@UAEPAXI@Z=0049edb0
// @ref ??_GBufferPipe@@UAEPAXI@Z=0049edd0
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??0LZOPipe@@QAE@W4CompControl@0@H@Z=0053eb40
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1LZOPipe@@UAE@XZ=0053eba0
// @ref ??1Pipe@@UAE@XZ=0060ea60
// @ref ??_7BufferPipe@@6B@=0079ea08
// @ref ??_7Pipe@@6B@=0079ea20
// @ref ?Clear@INIClass@@QAE_NPBD0@Z=0050b9a0
// @ref ?Put@LZOPipe@@UAEHPBXH@Z=0053ebe0
// @ref ?Put_Rect@INIClass@@QAE_NPBD0ABUINIRect@@@Z=0050dca0
// @ref ?Put_To@Pipe@@UAEXPAV1@@Z=0060eaa0
// @ref ?Put_UUBlock@INIClass@@QAE_NPBDPBXH@Z=0050cfc0
// @ref ?Unknown_0061D660@UnknownPreview_0061D430@@QAEXXZ=0061d660
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
