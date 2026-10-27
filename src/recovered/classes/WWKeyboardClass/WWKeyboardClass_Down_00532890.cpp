// bool WWKeyboardClass::Down(KeyNumType key) (0x00532890)
// Whether the key is held now; the left and right mouse buttons are swapped
// when the system swaps them (SM_SWAPBUTTON).
#include "shared/keyboard.hpp"
// @ref __imp__GetSystemMetrics@4=0079a3dc
// @ref ?Unknown_005233F0@@YIFH@Z=005233f0

extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int index);

bool WWKeyboardClass::Down(KeyNumType key)
{
    key &= 0xFF;
    if (key == 1 || key == 2) {
        if (GetSystemMetrics(0x17) == 1) {
            key = key == 1 ? 2 : 1;
        }
    }
    return Unknown_005233F0(key) != 0;
}
