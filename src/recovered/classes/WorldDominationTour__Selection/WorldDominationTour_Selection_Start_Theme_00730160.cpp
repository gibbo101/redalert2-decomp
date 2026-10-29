// void Selection::Start_Theme() (0x00730160)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Start_Theme()
{
    unknown_flag_a40d44 = false;
    if (ThemeName != 0) {
        Theme.Play_Song(Theme.From_Name(ThemeName.Get()));
        Theme.IsRepeat = true;
    }
    WWMouse->Hide_Mouse();
    unknown_surface_839958->Fill(0);
    unknown_surface_839954->Fill(0);
    unknown_surface_839950->Copy_From(*unknown_surface_839954, false, true);
    WWKeyboard->Clear();
    TheMap->unknown_72a620(this, &TheVoices);
    while (WWMouse->Get_Mouse_State() < 0) {
        WWMouse->Show_Mouse();
    }
}
}
// @ref ?unknown_72a620@Map@WorldDominationTour@@QAEXPAVMSEngine@@PAVVoices@2@@Z=0072a620
// @ref ?From_Name@ThemeClass@@QBEHPBD@Z=006e8510
