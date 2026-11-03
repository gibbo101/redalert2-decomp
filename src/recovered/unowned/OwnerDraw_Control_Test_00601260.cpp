// Tests edit classes, a registry-marked list box, or an editable combo.
// Original427code+5NOP; complete original-only171instruction closed CFG.
// @ref _control_edit_class_7e8df0=007e8df0
// @ref _control_new_edit_class_7e8de8=007e8de8
// @ref _control_list_class_7e8de0=007e8de0
// @ref _control_combo_class_7e8dd4=007e8dd4
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/crt_string.hpp"
extern "C" char const control_edit_class_7e8df0[];
extern "C" char const control_new_edit_class_7e8de8[];
extern "C" char const control_list_class_7e8de0[];
extern "C" char const control_combo_class_7e8dd4[];
namespace OwnerDraw {
bool __fastcall unknown_control_test_601260(HWND window)
{
    char name[128];
    GetClassNameA(window,name,sizeof(name));
    if(!strcmp(name,control_edit_class_7e8df0))return true;
    if(!strcmp(name,control_new_edit_class_7e8de8))return true;
    if(!strcmp(name,control_list_class_7e8de0)) {
        UnknownControlRecord *record=0;
        unsigned int const &key=(unsigned int const &)window;
        if(unknown_registry_a73640.Get(key,record))return record->unknown_68==1;
    }
    if(!strcmp(name,control_combo_class_7e8dd4))return (GetWindowLongA(window,-16)&3)!=3;
    return false;
}
}
