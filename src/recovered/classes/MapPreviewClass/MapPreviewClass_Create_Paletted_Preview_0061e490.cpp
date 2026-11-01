unsigned short *UnknownPreview_0061D430::Unknown_0061E490(int colorcount, int *size)
{
    int i;
    int k;
    int x;
    int y;

    if (unknown_00 == 0) {
        return 0;
    }

    DSurface surf(unknown_00->Get_Width() / 2, unknown_00->Get_Height() / 2, false);
    surf.Copy_From(surf.Get_Rect(), *unknown_00, unknown_00->Get_Rect(), false, false);

    int *counts = new int[4096];
    memset(counts, 0, 4096 * sizeof(int));
    int colorsused = 0;

    surf.Lock();
    for (y = 0; y < surf.Get_Height(); y++) {
        for (x = 0; x < surf.Get_Width(); x++) {
            int pixel = surf.Get_Pixel(Point2D(x, y));
            RGBClass color = Pixel_To_RGB(pixel);
            int red = color.Get_Red() & 0xF0;
            int green = color.Get_Green() & 0xF0;
            int blue = color.Get_Blue() & 0xF0;
            surf.Put_Pixel(Point2D(x, y), Build_Hicolor_Pixel(red, green, blue));
            int colorindex = (red << 4) | green | (blue >> 4);
            int count = counts[colorindex];
            if (count == 0) {
                colorsused++;
            }
            counts[colorindex] = count + 1;
        }
    }
    surf.Unlock();

    unsigned short *palette = new unsigned short[colorcount];
    for (i = 0; i < colorcount; i++) {
        int bestcolor = -1;
        int bestcount = 0;
        for (k = 0; k < 4096; k++) {
            if (counts[k] > bestcount) {
                bestcount = counts[k];
                bestcolor = k;
            }
        }
        if (bestcolor == -1) {
            break;
        }
        counts[bestcolor] = 0;
        palette[i] = bestcolor;
    }

    unsigned char *indexbuf = new unsigned char[surf.Get_Width() * surf.Get_Height()];
    unsigned char *indexptr = indexbuf;

    surf.Lock();
    for (y = 0; y < surf.Get_Height(); y++) {
        for (x = 0; x < surf.Get_Width(); x++) {
            int pixel = surf.Get_Pixel(Point2D(x, y));
            RGBClass color = Pixel_To_RGB(pixel);

            int bestindex = -1;
            int bestdist = 0xFFFF;
            for (k = 0; k < colorcount; k++) {
                unsigned short entry = palette[k];
                int dist = abs(((entry >> 4) & 0xF0) - color.Get_Red()) + abs((16 * (entry & 0x000F)) - color.Get_Blue()) + abs((entry & 0x00F0) - color.Get_Green());
                if (dist == 0) {
                    bestindex = k;
                    break;
                }
                if (dist < bestdist) {
                    bestdist = dist;
                    bestindex = k;
                }
            }
            *indexptr++ = (unsigned char)bestindex;
        }
    }
    surf.Unlock();

    int offset = (colorcount * sizeof(unsigned short)) + 2 * sizeof(int) + sizeof(int);
    int bytes = offset + surf.Get_Width() * surf.Get_Height();
    int *block = (int *)new unsigned char[bytes];
    block[0] = surf.Get_Width();
    block[1] = surf.Get_Height();
    block[2] = colorcount;
    memcpy((unsigned char *)block + 2 * sizeof(int) + sizeof(int), palette, colorcount << 1);
    memcpy(((unsigned char *)block) + offset, indexbuf, surf.Get_Width() * surf.Get_Height());
    delete [] palette;
    delete [] indexbuf;
    delete [] counts;
    *size = bytes;
    Debug_Printf("Created paletted preview of size %d bytes\n", bytes);

    return (unsigned short *)block;
}
// @ref ??_C@_0CL@BBNC@Created?5paletted?5preview?5of?5size@=007ebf58
// @ref ??1DSurface@@UAE@XZ=004aa5a0
// @ref ?Copy_From@DSurface@@UAE_NABVRect@@AAVSurface@@0_N2@Z=004aaf80
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Get_Pixel@XSurface@@UAEHABUPoint2D@@@Z=007741d0
// @ref ?Lock@DSurface@@UAEPAXUPoint2D@@@Z=004aac80
// @ref ?Put_Pixel@XSurface@@UAE_NABUPoint2D@@H@Z=00774220
// @ref ?Unlock@DSurface@@UAE_NXZ=004aae40
