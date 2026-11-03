// Modal dialog driven by the RTTI-confirmed DialogControl virtual interface.
// Original182code+10NOP; closed complete CFG, both returns RET4.
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/dialog_create.hpp"
#include "shared/keyboard.hpp"
#include "shared/ms_message_box.hpp"
namespace OwnerDraw {
HWND __fastcall unknown_controlled_dialog_6011a0(int resource,DialogProc procedure,DialogControl *control)
{
    HWND window=unknown_create_dialog_5ff610(resource,procedure,(int)control);
    if(!window) {
        control->Set_Window_006010f0(0,0);
        return 0;
    }
    ShowWindow(window,1);
    SetForegroundWindow(window);
    WWKeyboard->Clear();
    while(!control->unknown_slot2()&&!control->unknown_slot4()) {
        if(unknown_6000d0())break;
        unknown_517370(false);
    }
    unknown_dialog_5ff6e0(window);
    return control->Get_Window_00601180();
}
}
