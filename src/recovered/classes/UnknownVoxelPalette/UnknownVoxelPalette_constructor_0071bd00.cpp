#pragma auto_inline(off)
UnknownVoxelPalette::UnknownVoxelPalette(unsigned char *palette, unsigned char *table)
{
    if (palette == 0) {
        Palette = (unsigned char *)operator new(0x300);
        unknown_18 = 1;
    } else {
        Palette = palette;
        unknown_18 = 0;
    }
    if (table == 0) {
        unknown_14 = (unsigned char *)operator new(0x8000);
        unknown_1c = 1;
    } else {
        unknown_14 = table;
        unknown_1c = 0;
    }
}

#pragma auto_inline(on)
