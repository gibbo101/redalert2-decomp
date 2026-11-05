// Radar blink marker and dirty pixels, original0042DE20. Field names remain hypotheses.
#include "shared/beacon.hpp"
#include "shared/house.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/palette.hpp"
#include "shared/cd_timer.hpp"

extern Rect unknown_rect_8336e8;
extern Rect unknown_radar_rect_833978;
// @ref ?unknown_rect_8336e8@@3VRect@@A=008336e8
// @ref ?unknown_radar_rect_833978@@3VRect@@A=00833978

void UnknownBeacon::Unknown_0042DE20(Surface *surface, Rect window, bool forced)
{
    int frame = Frame % unknown_object_84e8d0.unknown_7c;
    if (frame < unknown_object_84e8d0.unknown_78 + 1 || forced) {
        // The canonical radar interface reads only the X/Y prefix; Z is not read.
        Point2D pixel = Map.Unknown_00631BA0((Point2D const &)unknown_coord, true);
        if (frame < unknown_object_84e8d0.unknown_78 && !forced) {
            CC_Draw_Shape(surface, ColorSchemes[Houses[unknown_house]->ColorSchemeIndex]->Converter,
                unknown_radar_beacon_shape_84e990, frame, pixel, window, 0x600, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        }
        int width = unknown_object_84e8d0.unknown_70;
        int height = unknown_object_84e8d0.unknown_74;
        Rect marker(pixel.X - width / 2, pixel.Y - height / 2, width, height);
        Rect dirty = marker + Point2D(unknown_radar_rect_833978.X, unknown_radar_rect_833978.Y);
        unknown_rect_8336e8 = Intersect(Union(unknown_rect_8336e8, dirty), unknown_radar_rect_833978);
        for (int y = marker.Y; y < marker.Y + marker.Height; ++y) {
            for (int x = marker.X; x < marker.X + marker.Width; ++x) {
                Point2D point(x, y);
                Map.Unknown_00632620(point);
            }
        }
    }
}
