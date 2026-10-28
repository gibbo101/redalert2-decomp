// void Tactical::Unknown_006A9E10(bool arg1, Rect const &rect1, Rect const &rect2) (0x006A9E10):
// redraws the terrain objects of display layer 2 (not animated, slot 17 false,
// +0xB5 clear) whose drawn area, moved onto the tactical area, overlaps the
// intersection of the two rectangles: slot 63 with a copy of rect2, then +0x75
// cleared. Last object first (hypothesis).
#include "shared/tactical.hpp"
#include "shared/display.hpp"
#include "shared/terrain.hpp"
#include "shared/terrain_type.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// display.hpp's map chain emits VectorClass<SubzoneConnectionStruct>'s vtable:
// @ref ??8?$VectorClass@USubzoneConnectionStruct@@@@UBE_NABV0@@Z=0040b070
// @ref ??_7?$VectorClass@USubzoneConnectionStruct@@@@6B@=0079a76c
// @ref ??_E?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ??_G?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ?Clear@?$VectorClass@USubzoneConnectionStruct@@@@UAEXXZ=0040b1a0
// @ref ?Fetch@?$VectorClass@USubzoneConnectionStruct@@@@UBE?AUSubzoneConnectionStruct@@H@Z=0040b050
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHABUSubzoneConnectionStruct@@@Z=0040b1d0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHPBUSubzoneConnectionStruct@@@Z=0040b210
// @ref ?Resize@?$VectorClass@USubzoneConnectionStruct@@@@UAE_NHPBUSubzoneConnectionStruct@@@Z=0040b0b0

void Tactical::Unknown_006A9E10(bool arg1, Rect const &rect1, Rect const &rect2)
{
    Rect clip = Intersect(rect1, rect2);
    for (int index = DisplayClass::Layer[2].Count() - 1; index >= 0; index--) {
        ObjectClass *object = DisplayClass::Layer[2][index];
        if (object->Kind_Of() == 0x24 && !object->unknown_slot17()) {
            TerrainClass *terrain = (TerrainClass *)object;
            if (!terrain->Class->IsAnimated && !terrain->unknown_b5) {
                Point2D offset(unknown_rect_839630.X, unknown_rect_839630.Y);
                Rect area = Offset_Rect(object->unknown_slot73(), offset.X, offset.Y);
                if (Rects_Overlap(area, clip)) {
                    Rect bounds = rect2;
                    object->unknown_slot63(&bounds, arg1, false);
                    object->unknown_75 = false;
                }
            }
        }
    }
}
