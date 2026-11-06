// Tactical occupier-link diagnostic, complete original 0x006AB810 (1036+4).
#include "shared/tactical.hpp"
#include "shared/map_view.hpp"
#include "shared/cell_class.hpp"
#include "shared/object.hpp"
#include "shared/object_lists.hpp"
#include "shared/surface.hpp"
#include "shared/hicolor.hpp"
#include "shared/unknown_globals.hpp"
extern Rect unknown_rect_839630;
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_objects_a40368@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40368

void Tactical::Debug_Draw_Occupier_Links()
{
    Map.Unknown_0055A550();
    CellClass *cell = Map.Unknown_0055A490();
    int ground_color = Build_Hicolor_Pixel(255,255,0);
    int link_color = Build_Hicolor_Pixel(255,0,255);
    int bridge_color = Build_Hicolor_Pixel(0,255,255);
    while (cell) {
        ObjectClass *object = cell->OccupierPtr;
        if (object) {
            CoordStruct cell_coord = cell->unknown_475d60();
            Point2D start;
            Coord_To_Pixel(cell_coord,start);
            CoordStruct object_coord = object->Center_Coord();
            Point2D end;
            Coord_To_Pixel(object_coord,end);
            Rect rect(start.X-1,start.Y-1,3,3);
            unknown_surface_83995c->Fill_Rect(unknown_rect_839630,rect,ground_color);
            unknown_surface_83995c->Draw_Line(unknown_rect_839630,start,end,ground_color);
        }
        object = cell->AltOccupierPtr;
        if (object) {
            CoordStruct cell_coord = cell->unknown_475d60();
            Point2D start;
            Coord_To_Pixel(cell_coord,start);
            start.Y -= 60;
            CoordStruct object_coord = object->Center_Coord();
            Point2D end;
            Coord_To_Pixel(object_coord,end);
            Rect rect(start.X-1,start.Y-1,3,3);
            unknown_surface_83995c->Fill_Rect(unknown_rect_839630,rect,bridge_color);
            unknown_surface_83995c->Draw_Line(unknown_rect_839630,start,end,bridge_color);
        }
        cell = Map.Unknown_0055A490();
    }
    for (int index=unknown_objects_a40368.Count()-1;index>=0;--index) {
        ObjectClass *object = unknown_objects_a40368[index];
        if (object->unknown_30) {
            CoordStruct first_coord = object->Center_Coord();
            Point2D start;
            Coord_To_Pixel(first_coord,start);
            CoordStruct next_coord = object->unknown_30->Center_Coord();
            Point2D end;
            Coord_To_Pixel(next_coord,end);
            unknown_surface_83995c->Draw_Line(unknown_rect_839630,start,end,link_color);
        }
    }
}
