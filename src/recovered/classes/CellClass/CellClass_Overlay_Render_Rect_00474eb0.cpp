// Rect CellClass::unknown_474eb0() const (0x00474EB0): Westwood's
// Overlay_Render_Rect: the screen rectangle of the overlay image (the ore
// image of the cell's tiberium and ramp, or a rubble building's).
#include "shared/cell.hpp"
#include "shared/overlay.hpp"
#include "shared/overlay_type.hpp"
#include "shared/tiberium.hpp"
#include "shared/building_type_class.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"

Rect CellClass::unknown_474eb0() const
{
    if (OverlayIndex == -1) {
        return Rect(0, 0, 0, 0);
    }
    int frame = OverlayData;
    OverlayTypeClass *overlay = OverlayTypes[OverlayIndex];
    ShapeFileStruct *image = 0;
    if (overlay->Tiberium) {
        int tib = Get_Tiberium_Type();
        if (tib != -1) {
            TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[tib];
            if (unknown_11c != 0) {
                image = (ShapeFileStruct *)OverlayTypes[tiberium->Image->ArrayIndex + tiberium->NumFrames + tiberium->NumImages / 4 * (unknown_11c - 1) + MapCoords.X * MapCoords.Y % (tiberium->NumImages / 4)]->unknown_slot39();
            } else {
                image = (ShapeFileStruct *)OverlayTypes[tiberium->Image->ArrayIndex + MapCoords.X * MapCoords.Y % tiberium->NumFrames]->unknown_slot39();
            }
        }
    } else if (overlay->IsRubble) {
        image = 0;
        if (unknown_40 != 0) {
            ((BuildingTypeClass *)unknown_40)->unknown_func_458e00((void **)&image, &frame);
        }
    } else {
        image = (ShapeFileStruct *)overlay->unknown_slot39();
    }
    Point2D point;
    unknown_tactical_83996c->Unknown_006A29D0(Coord_Snap(Cell_Coord(MapCoords)), point);
    point += unknown_475440();
    point.X -= 30;
    if (image == 0) {
        return Rect(0, 0, 0, 0);
    }
    if (overlay->Crate) {
        frame = 0;
    }
    return image->Get_Frame_Rect(frame) + (point - Point2D(image->Get_Width() / 2, image->Get_Height() / 2));
}
