// void CellClass::Draw_Fog_Shape(Point2D const &point, Rect const &clip, int frame) (0x00474510):
// TibSun's Draw_Fog_Shape: blends FOG.SHP frame `frame` (values below 0x80) into the
// depth buffer at point, clipped to clip; 0x7F entries take the shape value, others
// add value - 0x7F, floored at 0. The ring-wrapping loop runs only when the block can
// reach the buffer end.
#include "shared/cell.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/blit.hpp"
#include "shared/display.hpp"
// @ref ?Get_Buffer_Ptr@ZBuffer@@QAEPAGUPoint2D@@@Z=00411230
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ??_C@_07BIFH@FOG?4SHP?$AA@=007d2c70
// @ref _?shapes@?1??Draw_Fog_Shape@CellClass@@QAEXABUPoint2D@@ABVRect@@H@Z@4PBUShapeFileStruct@@B=00850bf0
// @ref _?shapes_loaded@?1??Draw_Fog_Shape@CellClass@@QAEXABUPoint2D@@ABVRect@@H@Z@4_NA=00850c46
void CellClass::Draw_Fog_Shape(Point2D const &point, Rect const &clip, int frame)
{
    static bool shapes_loaded = false;
    static ShapeFileStruct const *shapes = 0;

    if (!shapes_loaded) {
        shapes_loaded = true;
        shapes = (ShapeFileStruct const *)MixFileClass<CCFileClass>::Retrieve("FOG.SHP");
    }

    Rect shaperect = shapes->Get_Frame_Rect(frame);

    if (point.Y + shaperect.Y + shaperect.Height < clip.Y + 1) return;
    if (point.Y >= clip.Height + clip.Y) return;
    if (point.X + shaperect.X + shaperect.Width < clip.X + 1) return;
    if (point.X >= clip.X + clip.Width) return;

    int top = clip.Y > point.Y + shaperect.Y ? clip.Y : point.Y + shaperect.Y;
    int src_y = top - point.Y - shaperect.Y;
    int bottom = clip.Y + clip.Height < point.Y + shaperect.Y + shaperect.Height ? clip.Y + clip.Height : point.Y + shaperect.Y + shaperect.Height;

    int left = clip.X > point.X + shaperect.X ? clip.X : point.X + shaperect.X;
    int src_x = left - point.X - shaperect.X;
    int right = clip.X + clip.Width < point.X + shaperect.X + shaperect.Width ? clip.X + clip.Width : point.X + shaperect.X + shaperect.Width;

    int shape_skip = point.X - right + shaperect.X + shaperect.Width + src_x;
    int depth_skip = left - right + ZBufferPtr->Width;

    unsigned char const *shapeptr = (unsigned char const *)shapes->Get_Frame_Data(frame);
    unsigned short *depth = ZBufferPtr->Get_Buffer_Ptr(Point2D(left, top - unknown_rect_839630.Y));

    shapeptr += src_x + src_y * shaperect.Width;
    if (&depth[right - left + (bottom - top) * ZBufferPtr->Width + 2] >= (unsigned short *)ZBufferPtr->BufferTail) {
        for (int i = top; i < bottom; i++) {
            for (int j = left; j < right; j++) {
                unsigned char pixel = *shapeptr++;
                if (pixel <= 0x7F) {
                    if (*depth == 127) {
                        *depth = pixel;
                    } else {
                        *depth = ((unsigned short)*depth + pixel - 127 <= 0) ? 0 : (unsigned short)*depth + pixel - 127;
                    }
                }
                depth++;
                depth = ZBufferPtr->Wrap_Pointer(depth);
            }
            shapeptr += shape_skip;
            depth += depth_skip;
            depth = ZBufferPtr->Wrap_Pointer(depth);
        }
    } else {
        for (int i = top; i < bottom; i++) {
            for (int j = left; j < right; j++) {
                unsigned char pixel = *shapeptr++;
                if (pixel <= 0x7F) {
                    if (*depth == 127) {
                        *depth = pixel;
                    } else {
                        *depth = ((unsigned short)*depth + pixel - 127 <= 0) ? 0 : (unsigned short)*depth + pixel - 127;
                    }
                }
                ++depth;
            }
            shapeptr += shape_skip;
            depth += depth_skip;
        }
    }
}
