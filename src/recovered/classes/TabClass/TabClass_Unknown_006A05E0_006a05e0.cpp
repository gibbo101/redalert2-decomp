// void __fastcall TabClass::Unknown_006A05E0(int slot, int button) (0x006A05E0)
// Maps slot to button.
#include "shared/tab.hpp"
// @ref ?SlotButton@TabClass@@2PAHA=00abe2c8

void __fastcall TabClass::Unknown_006A05E0(int slot, int button)
{
    SlotButton[slot] = button;
}
