// ThemeType ThemeClass::Pick_Next_Song(ThemeType current) (0x006E7D80): the theme after current
// (unless it repeats or is flagged +0x289): with shuffle, up to 1000 random picks of a playable
// other theme (0 when none); otherwise the next playable theme in order (0 after a full cycle).
// Inline element access and count (Themes[current], Themes.Count()).
#ifndef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#endif
#include "shared/vector_class.hpp"
#include "shared/theme.hpp"
#include "shared/random2.hpp"
// @ref ?unknown_6e8440@ThemeClass@@QAE_NI@Z=006e8440

ThemeType ThemeClass::Pick_Next_Song(ThemeType current)
{
    if ((current > -1 && !Themes[current]->unknown_289 && !IsRepeat) || current < 0) {
        if (IsShuffle == 1) {
            int tries = 0;
            int pick;
            do {
                pick = unknown_random_839218(0, Themes.Count() - 1);
                tries++;
            } while (tries < 1000 && (pick == current || !unknown_6e8440(pick)));
            if (tries == 1000) {
                pick = 0;
            }
            return pick;
        }
        int remaining = Themes.Count() + 1;
        for (;;) {
            current++;
            if (current >= Themes.Count()) {
                current = 0;
            }
            remaining--;
            if (remaining == 0) {
                return 0;
            }
            if (unknown_6e8440(current)) {
                break;
            }
        }
    }
    return current;
}
