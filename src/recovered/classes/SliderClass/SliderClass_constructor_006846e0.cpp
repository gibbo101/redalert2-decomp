// SliderClass::SliderClass(unsigned id, int x, int y, int w, int h, int no_buttons) (0x006846E0)
// A gauge with a thumb; unless no_buttons, a plus button right of it and a minus button left of it
// become its peers. The thumb starts one value wide.
#include "shared/gadget.hpp"
#include "shared/mix_file_class.hpp"
// @ref ??_C@_0N@NIHK@BTN?9PLUS?4SHP?$AA@=007f4024
// @ref ??_C@_0N@KOFD@BTN?9MINS?4SHP?$AA@=007f4014

SliderClass::SliderClass(unsigned id, int x, int y, int w, int h, int no_buttons)
    : GaugeClass(id, x, y, w, h)
{
    NoButtons = no_buttons ? true : false;

    PlusGadget = 0;
    MinusGadget = 0;
    if (!NoButtons) {
        PlusGadget = new ShapeButtonClass(id, MixFileClass::Retrieve("BTN-PLUS.SHP"), X + Width + 2, Y);
        MinusGadget = new ShapeButtonClass(id, MixFileClass::Retrieve("BTN-MINS.SHP"), X - 6, Y);

        if (PlusGadget) {
            PlusGadget->Make_Peer(*this);
            PlusGadget->Add(*this);
            PlusGadget->Flag_To_Redraw();
        }
        if (MinusGadget) {
            MinusGadget->Make_Peer(*this);
            MinusGadget->Add(*this);
            MinusGadget->Flag_To_Redraw();
        }
    }
    Set_Thumb_Size(1);
    Recalc_Thumb();

    IsColorized = 0;
}
