// void Selection::Check_Escape() (0x0072FC80)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Check_Escape()
{
    Check_Focus();
    while (WWKeyboard->Check()) {
        if (WWKeyboard->Get() == 0x1B) {
            Escaped = true;
        }
    }
}
}
