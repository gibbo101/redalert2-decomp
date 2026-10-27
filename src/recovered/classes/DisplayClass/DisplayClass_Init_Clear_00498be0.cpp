// void DisplayClass::Init_Clear() (0x00498BE0, slot 7)
// Clears the map, then the display's pending state and every layer.
#include "shared/display.hpp"
// @ref ?Init_Clear@MapClass@@UAEXXZ=005482c0
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578

void DisplayClass::Init_Clear()
{
    MapClass::Init_Clear();
    unknown_11a0 = 0;
    unknown_11a4 = 0;
    unknown_11a8 = -1;
    unknown_1178 = 0;
    unknown_11b4 = -1;
    unknown_11ac = false;
    unknown_11cb = false;
    unknown_11cc = false;
    unknown_11ad = false;
    unknown_11ae = false;
    for (int layer = 0; layer < 5; layer++) {
        LayerClass &list = Layer[layer];
        list.Clear();
    }
}
