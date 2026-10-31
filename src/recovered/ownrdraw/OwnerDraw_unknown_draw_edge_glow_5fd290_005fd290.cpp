// @ref ?color_alpha@?1??Blend_Color@OwnerDraw@@YAGGGE@Z@4IA=00b2b634
// @ref ?pixel_alpha@?1??Blend_Color@OwnerDraw@@YAGGGE@Z@4IA=00b2b638
#include "shared/win32_api.hpp"
#include "shared/crt_memory.hpp"
#include "shared/surface.hpp"
#include "shared/owner_draw_dialog_control.hpp"

template<class T>
inline void swap(T &left, T &right)
{
    T temp = left;
    left = right;
    right = temp;
}

namespace OwnerDraw {

// Draws a line from start to end over surface, blending color into each pixel by alpha (a plain colour fill
// on an 8-bit surface).
bool __fastcall unknown_draw_edge_glow_5fd290(Surface *surface, Point2D const &start, Point2D const &end, int color,
                                              int alpha)
{
    Point2D startpoint = start;
    Point2D endpoint = end;
    if (startpoint.X > endpoint.X) {
        swap(startpoint, endpoint);
    }
    int bpp = surface->Bytes_Per_Pixel();
    void *buffer = surface->Lock(startpoint);
    if (buffer != 0) {
        if (startpoint.Y == endpoint.Y) {
            if (bpp == 1) {
                memset(buffer, color, endpoint.X - startpoint.X + 1);
            } else {
                for (int i = 0; i <= endpoint.X - startpoint.X; i++) {
                    *((unsigned short *)buffer + i) = Blend_Color(*((unsigned short *)buffer + i), color, alpha);
                }
            }
        } else if (startpoint.X == endpoint.X) {
            int pitch = startpoint.Y > endpoint.Y ? -surface->Stride() : surface->Stride();
            int dy = abs(endpoint.Y - startpoint.Y);
            for (int i = 0; i <= dy; i++) {
                if (bpp == 1) {
                    *(unsigned char *)buffer = color;
                } else {
                    *(unsigned short *)buffer = Blend_Color(*(unsigned short *)buffer, color, alpha);
                }
                buffer = (unsigned char *)buffer + pitch;
            }
        } else {
            int dx = endpoint.X - startpoint.X;
            int dy = endpoint.Y - startpoint.Y;
            int pitch = surface->Stride();
            if (dy < 0) {
                pitch = -pitch;
            }
            dy = abs(dy);
            int dx2 = 2 * dx;
            int dy2 = 2 * dy;
            if (dx > dy) {
                int delta = dy2 - dx;
                for (int i = 0; i < dx; i++) {
                    if (bpp == 1) {
                        *((unsigned char *)buffer + i) = color;
                    } else {
                        *((unsigned short *)buffer + i) = Blend_Color(*((unsigned short *)buffer + i), color, alpha);
                    }
                    if (delta > 0) {
                        buffer = (unsigned char *)buffer + pitch;
                        delta -= dx2;
                    }
                    delta += dy2;
                }
            } else {
                int delta = dx2 - dy;
                int k = 0;
                for (int i = 0; i < dy; i++) {
                    if (bpp == 1) {
                        *((unsigned char *)buffer + k) = color;
                    } else {
                        *((unsigned short *)buffer + k) = Blend_Color(*((unsigned short *)buffer + k), color, alpha);
                    }
                    if (delta > 0) {
                        k++;
                        delta -= dy2;
                    }
                    delta += dx2;
                    buffer = (unsigned char *)buffer + pitch;
                }
            }
        }
        surface->Unlock();
        return true;
    }
    return false;
}

}
