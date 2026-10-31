// void Tactical::Register_Dirty_Buildings(Rect area) (0x006AA090): every building
// of display layer 2 still waiting to be drawn (+0x75) whose drawn area,
// moved onto the screen, overlaps area goes to the dirty areas (0x006A3020)
// and is marked drawn (TibSun Tactical::Register_Dirty_Buildings).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?unknown_rect_839630@@3VRect@@A=00839630

void Tactical::Register_Dirty_Buildings(Rect area)
{
    for (int index = 0; index < DisplayClass::Layer[2].Count(); index++) {
        ObjectClass *object = DisplayClass::Layer[2][index];
        if (object->Kind_Of() == 6 && object->unknown_75) {
            Rect const &render = object->unknown_slot73();
            if (area.Is_Overlapping(render + Point2D(unknown_rect_839630.X, unknown_rect_839630.Y))) {
                Register_Dirty_Area(render, false);
                object->unknown_75 = false;
            }
        }
    }
}
