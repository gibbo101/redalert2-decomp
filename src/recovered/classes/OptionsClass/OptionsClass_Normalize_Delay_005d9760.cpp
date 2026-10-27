// int OptionsClass::Normalize_Delay(int delay) const (0x005D9760)
// A delay adjusted for the game speed: from a table for delays 1-4, else
// scaled by 8 / (GameSpeed + 1) (name after TS).
// @ref ?Delay_Adjust@@3QAY07$$CBHA=007e8394
#include "shared/options.hpp"

int OptionsClass::Normalize_Delay(int delay) const
{
    if (delay) {
        if (delay < 5) {
            delay = Delay_Adjust[delay - 1][GameSpeed];
        } else {
            delay = (delay * 8) / (GameSpeed + 1);
        }
    }
    return delay;
}
