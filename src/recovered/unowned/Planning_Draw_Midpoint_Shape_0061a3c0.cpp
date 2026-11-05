#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Draw_Midpoint_Shape(Point2D start, Point2D end, int color, int fill, int frame) (0x0061A3C0)
// When two screen points are more than 36 pixels apart, outlines and fills a
// square on their midpoint and draws a mouse shape frame centred in it.
#include "shared/planning.hpp"
#include "shared/surface.hpp"
// @ref ?unknown_drawer_8323c8@@3PAVConvertClass@@A=008323c8
// @ref ?MouseShapes@MouseClass@@2PBUMouseShapeHeader@@B=00a70f64

class ConvertClass;
struct ShapeFileStruct;
struct MouseShapeHeader {
    short unknown_00;
    short Width;
    short Height;
    short FrameCount;
};
class MouseClass {
public:
    static MouseShapeHeader const *MouseShapes;
};
extern ConvertClass *unknown_drawer_8323c8;
void __fastcall CC_Draw_Shape(Surface *surface, ConvertClass *drawer, ShapeFileStruct const *shape, int frame,
                              Point2D const &point, Rect const &window, int flags, int unknown8,
                              int unknown9, int unknown10, int brightness, int unknown12,
                              int unknown13, Point2D offset);

void __fastcall Planning_Draw_Midpoint_Shape(Point2D start, Point2D end, int color, int fill, int frame)
{
    if ((start - end).Length() >= 37) {
        int x = (start.X + end.X) / 2;
        int y = (start.Y + end.Y) / 2;
        int left = x - 10;
        int top = y - 10;
        ::Rect view = Unknown_006F1F30();
        ::Rect square(left, top, 21, 21);
        Planning_Inflate(square, -1);
        unknown_surface_839964->Draw_Rect(view, square, color);
        Planning_Inflate(square, -1);
        unknown_surface_839964->Fill_Rect(view, square, fill);
        Point2D point(left, top);
        ::Rect window = view;
        MouseShapeHeader const *shape = MouseClass::MouseShapes;
        int width = shape->Width;
        int height = shape->Height;
        point.X = x - width / 2 - 1;
        point.Y = y - height / 2;
        CC_Draw_Shape(unknown_surface_839964, unknown_drawer_8323c8, (ShapeFileStruct const *)shape, frame, point, window,
                      0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    }
}
