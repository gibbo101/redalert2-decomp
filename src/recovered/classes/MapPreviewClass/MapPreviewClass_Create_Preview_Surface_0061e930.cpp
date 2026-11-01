void UnknownPreview_0061D430::Unknown_0061E930(unsigned short const *image)
{
    int *header = (int *)image;

    int width = *header++;
    int height = *header++;
    int colorcount = *header;
    unsigned short *palette = (unsigned short *)header;

    if (unknown_00 != 0) {
        delete unknown_00;
    }
    unknown_00 = new DSurface(width, height, true);
    unknown_00->Fill(0);

    int offset = (colorcount * sizeof(unsigned short)) + 2 * sizeof(int) + sizeof(int);
    unsigned char *indexptr = (unsigned char *)image + offset;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned short entry = palette[*indexptr++ + 2];
            int color = Build_Hicolor_Pixel((entry >> 4) & 0x00F0, entry & 0x00F0, 16 * (entry & 0x000F));

            unknown_00->Put_Pixel(Point2D(x, y), color, unknown_00->Get_Rect());
        }
    }
}
// @ref ??0DSurface@@QAE@HH_N@Z=004aa4a0
// @ref ??2@YAPAXI@Z=00782017
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
