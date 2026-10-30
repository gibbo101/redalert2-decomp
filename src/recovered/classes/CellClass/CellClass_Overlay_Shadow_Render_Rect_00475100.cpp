// Rect CellClass::unknown_475100() const (0x00475100): Westwood's
// Overlay_Shadow_Render_Rect: the screen rectangle of the overlay's shadow frame.
#include "shared/cell.hpp"
#include "shared/overlay_type.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"

Rect CellClass::unknown_475100() const
{
    if (OverlayIndex == -1) {
        return Rect(0, 0, 0, 0);
    }
    OverlayTypeClass *overlay = OverlayTypes[OverlayIndex];
    ShapeFileStruct *image = (ShapeFileStruct *)overlay->unknown_slot39();
    if (image == 0) {
        return Rect(0, 0, 0, 0);
    }
    unsigned char frame = OverlayData;
    if (overlay->Crate) {
        frame = 0;
    }
    int shadow = frame + image->FrameCount / 2;
    Point2D point;
    unknown_tactical_83996c->Unknown_006A29D0(Coord_Snap(Cell_Coord(MapCoords)), point);
    point += unknown_475440();
    point.X -= 30;
    if (unknown_140 & 0x80) {
        if (OverlayData >= 9 && OverlayData <= 17) {
            point += Point2D(-15, 7);
        }
    }
    return image->Get_Frame_Rect(shadow) + (point - Point2D(image->Get_Width() / 2, image->Get_Height() / 2));
}
