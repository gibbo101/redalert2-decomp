// bool TabClass::INoticeSink_Unknown(int code, int arg) (0x006A2020; the
// INoticeSink vtable 0x007A64DC)
// Notice 0x11C7 turns the planning-mode button on and 0x11C8 turns it off
// (the button of slot 0x00ABE36C, when it is not already in that state).
// True when handled.
#include "shared/tab.hpp"
// @ref ?Unknown_006A0600@TabClass@@SIPAVShapeButtonClass@@H@Z=006a0600
// @ref ?unknown_int_abe36c@@3HA=00abe36c
// @ref ?Turn_On@ToggleClass@@QAEXXZ=006eb160
// @ref ?Turn_Off@ToggleClass@@QAEXXZ=006eb170

bool TabClass::INoticeSink_Unknown(int code, int arg)
{
    if (code == 0x11C7) {
        ShapeButtonClass *button = Unknown_006A0600(unknown_int_abe36c);
        if (button != 0 && !button->IsOn) {
            button->Turn_On();
        }
        return true;
    }
    if (code == 0x11C8) {
        ShapeButtonClass *button = Unknown_006A0600(unknown_int_abe36c);
        if (button != 0 && button->IsOn) {
            button->Turn_Off();
        }
        return true;
    }
    return false;
}
