// void IonBlastClass::Draw_It() (0x00521CE0; TibSun ionblast.cpp): warps the logical surface through the
// blast's shockwave surface for this lifetime frame, depth masked, at the highest detail level.
#include "shared/ion_blast.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/surface.hpp"
#include "shared/blit.hpp"
#include "shared/tactical.hpp"
extern Rect unknown_rect_839630;        // 0x00839630 tactical X, Y, width, height
// @ref ?unknown_a40b2c@@3HA=00a40b2c
// @ref ?BlastSurfaces@@3PAPAVBSurface@@A=00a51e38
void IonBlastClass::Draw_It()
{
    Point2D point;
    if (unknown_a40b2c == 2 && unknown_tactical_83996c->Coord_To_Pixel(Coord, point)) {
        Surface *dest_surface = unknown_surface_83995c;
        Rect dcliprect = unknown_rect_839630;
        dcliprect.Height -= 7;
        Surface *source_surface = BlastSurfaces[Lifetime];
        int stride = dest_surface->Stride();
        bool overlapped = false;
        Rect srect(0, 0, 256, 128);
        Rect scliprect(0, 0, 256, 128);
        Rect drect(point.X - 128, point.Y - 64, 256, 128);
        char *sbuffer;
        short *dbuffer;

        if (Prep_For_Blit(*dest_surface, dcliprect, drect, *source_surface, scliprect, srect, overlapped, (void *&)dbuffer, (void *&)sbuffer)) {
            char *sptr;
            short *dest_row = dbuffer;
            short *dptr = dbuffer;
            char *source_row = sbuffer;
            sptr = sbuffer;

            int depth_z = Unknown_006A2970(Coord.Z);
            short base_z = (short)ABufferPtr->Get_Scroll() - depth_z;
            unsigned short draw_z = base_z;
            draw_z -= drect.Y;
            draw_z -= 3;

            unsigned short *zbuffer_base = ABufferPtr->Get_Buffer_Ptr(Point2D(0, drect.Y));
            int height = srect.Height + 1;
            int surface_width = unknown_surface_83995c->Get_Width();
            int buffer_width = ABufferPtr->Width;

            if (zbuffer_base + surface_width + height * buffer_width < (unsigned short *)ABufferPtr->BufferTail) {
                unsigned short *zptr = zbuffer_base + drect.X;
                int x;
                for (int y = 0; y < srect.Height; ++y) {
                    for (x = 0; x < srect.Width; ++x) {
                        int index = *sptr++;
                        if (index > 0 && *zptr > draw_z) {
                            *dptr = dptr[SpiralIndexToSurfaceLUT[index]];
                        }
                        dptr++;
                        zptr++;
                    }
                    dest_row = (short *)((char *)dest_row + stride);
                    dptr = dest_row;
                    source_row += 256;
                    draw_z--;
                    sptr = source_row;
                    zptr += buffer_width - x;
                }
            } else {
                short *pixel = dptr;
                for (int y = 0; y < srect.Height; ++y) {
                    for (int x = 0; x < srect.Width; ++x) {
                        int index = *sptr++;
                        if (index > 0 && *ABufferPtr->Get_Buffer_Ptr(Point2D(drect.X + x, drect.Y + y)) > draw_z) {
                            *pixel = pixel[SpiralIndexToSurfaceLUT[index]];
                        }
                        pixel++;
                    }
                    dest_row = (short *)((char *)dest_row + stride);
                    pixel = dest_row;
                    source_row += 256;
                    draw_z--;
                    sptr = source_row;
                }
            }

            dest_surface->Unlock();
            source_surface->Unlock();
        }
    }
}
