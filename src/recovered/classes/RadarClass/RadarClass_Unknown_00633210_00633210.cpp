// void RadarClass::Unknown_00633210() (0x00633210): TibSun Render_Radar. Redraws the radar view,
// its old outline, pending cells and events, then copies the dirty area to the sidebar surface.
#include "shared/radar.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
#include "shared/palette.hpp"
#include "shared/radar_event_class.hpp"
#include "shared/crt_memory.hpp"
bool RadarEventClass_unknown_none();
// @ref ?RadarEventClass_unknown_none@@YA_NXZ=0063c070
// @ref ?Draw_Events@RadarEventClass@@SAXXZ=0063bb40
// @ref ?Remove_Finished@RadarEventClass@@SAXXZ=0063bef0
// @ref __ftol=0077f110
// @ref __real@4@4003f000000000000000=007a8840
void RadarClass::Unknown_00633210()
{
    int edge;
    Rect previous = unknown_1208;
    bool tactical = unknown_14ac == 1 && unknown_14a8 == 1;
    Cell center = Map[unknown_tactical_83996c->Unknown_006A6BD0(Point2D(
        unknown_rect_839630.X + unknown_rect_839630.Width / 2,
        unknown_rect_839630.Y + unknown_rect_839630.Height / 2))].Fetch_CellID();
    unknown_14d8 = Unknown_00631470(center);
    unknown_14d8.Width = (2 * unknown_rect_839630.Width) / (60.0f / unknown_1484) + 1.0f;
    unknown_14d8.Height = (2 * unknown_rect_839630.Height) / (30.0f / unknown_1484);
    unknown_14d8 -= Point2D(unknown_rect_839630.Width / (60.0f / unknown_1484),
        (2 * unknown_rect_839630.Height) / (30.0f / unknown_1484) * 0.5f);
    if (unknown_14d8.X < unknown_1498.X) unknown_14d8.X = unknown_1498.X;
    else if (unknown_14d8.X + unknown_14d8.Width >= unknown_1498.X + unknown_1498.Width)
        unknown_14d8.X = unknown_1498.X - (unknown_14d8.Width - unknown_1498.Width) - 1;
    if (unknown_14d8.Y < unknown_1498.Y) unknown_14d8.Y = unknown_1498.Y;
    else if (unknown_14d8.Y + unknown_14d8.Height >= unknown_1498.Y + unknown_1498.Height)
        unknown_14d8.Y = unknown_1498.Y - (unknown_14d8.Height - unknown_1498.Height) - 1;
    if (unknown_14d6) unknown_14e8 = unknown_14d8;
    if (unknown_14d5 || unknown_14e8 != unknown_14d8 || !RadarEventClass_unknown_none()
        || unknown_1258.Count() > 0 || unknown_1220.Count() > 0 || unknown_object_84e8d0.Unknown_0042EFD0()) {
        if (tactical) unknown_14d5 = false;
        Unknown_00631600();
        bool moved = false;
        if (unknown_14e8 != unknown_14d8) {
            Point2D pixel;
            for (edge = 0; edge < unknown_14e8.Height; ++edge) {
                pixel = Point2D(unknown_14e8.X, edge + unknown_14e8.Y) - Point2D(unknown_1498.X, unknown_1498.Y);
                Unknown_00632620(pixel);
                pixel = Point2D(unknown_14e8.X + unknown_14e8.Width - 1, edge + unknown_14e8.Y) - Point2D(unknown_1498.X, unknown_1498.Y);
                Unknown_00632620(pixel);
            }
            for (edge = 0; edge < unknown_14e8.Width; ++edge) {
                pixel = Point2D(edge + unknown_14e8.X, unknown_14e8.Y) - Point2D(unknown_1498.X, unknown_1498.Y);
                Unknown_00632620(pixel);
                pixel = Point2D(edge + unknown_14e8.X, unknown_14e8.Height + unknown_14e8.Y - 1) - Point2D(unknown_1498.X, unknown_1498.Y);
                Unknown_00632620(pixel);
            }
            moved = true;
        }
        if (unknown_1244.Is_Valid()) {
            unknown_1218->Copy_From(unknown_1244, *unknown_121c, unknown_1244, false, true);
            unknown_1208 = Union(unknown_1208, unknown_1244 + unknown_1498.Top_Left());
            for (int x = unknown_1244.X; x < unknown_1244.X + unknown_1244.Width; ++x) {
                for (int y = unknown_1244.Y; y < unknown_1244.Y + unknown_1244.Height; ++y) Unknown_00632000(Point2D(x, y));
            }
            unknown_1244 = Rect(0, 0, 0, 0);
        }
        for (edge = unknown_1258.Count() - 1; edge >= 0; --edge) Unknown_00632000(unknown_1258[edge]);
        unknown_1258.Clear();
        RadarEventClass::Draw_Events();
        unknown_object_84e8d0.Unknown_0042EED0(unknown_1218, unknown_1218->Get_Rect());
        if (tactical) {
            if (unknown_14d6) {
                unknown_1208 = unknown_1498;
                CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shape_ab64a0, 32,
                    Point2D(unknown_11e0, unknown_11e8), unknown_surface_839948->Get_Rect(), 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            }
            if (unknown_1208.Is_Valid()) {
                Rect from = unknown_1208 - RectPoint2D(unknown_1498.X, unknown_1498.Y);
                unknown_surface_839948->Copy_From(unknown_1208, *unknown_1218, from, false, true);
            }
            unknown_surface_839948->Draw_Rect(unknown_14d8, unknown_1204);
            Rect area = unknown_1498;
            Rect border(area.X - 1, area.Y - 1, area.Width + 2, area.Height + 2);
            unknown_surface_839948->Draw_Rect(border, unknown_1204);
        }
        if (moved) {
            Rect const &inner = Union(unknown_14e8, unknown_1208);
            unknown_1208 = Union(unknown_14d8, inner);
        }
        unknown_14e8 = unknown_14d8;
        RadarEventClass::Remove_Finished();
    }
    if (unknown_1270) memset(unknown_1270, 0, unknown_1218->Get_Height() * unknown_1218->Get_Width() / 8 + 1);
    if (!tactical) unknown_1208 = previous;
}
