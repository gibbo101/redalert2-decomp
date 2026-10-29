// void Selection::Clear_Screen() (0x00730230)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Clear_Screen()
{
    WWMouse->Hide_Mouse();
    Theme.Queue_Song(-3);
    unknown_surface_839958->Fill(0);
    unknown_surface_839954->Fill(0);
    while (WWMouse->Get_Mouse_State() < 0) {
        WWMouse->Show_Mouse();
    }
}
}
