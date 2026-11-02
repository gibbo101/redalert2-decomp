// bool WDTState::unknown_72c3b0(void *data, int length) (0x0072C3B0): the HSVC field of the WOL
// state packet, four 2-bit values per byte (low bits first): one byte table of unknown_20 values
// per conflict in unknown_44 (ConflictCount rows), each row starting on a fresh byte. Fails when
// the field holds fewer than unknown_20 * ConflictCount values. Each switch case stores its value
// itself (a shared value local enregisters the bit counter, which the original keeps in memory).
#include "shared/wdt_state.hpp"

bool WDTState::unknown_72c3b0(void *data, int length)
{
    if ((unsigned)(length * 4) < unknown_20 * ConflictCount) {
        return false;
    }
    unknown_44 = new void *[ConflictCount];
    for (unsigned i = 0; i < ConflictCount; i++) {
        unknown_44[i] = new unsigned char[unknown_20];
    }
    unsigned char *bytes = (unsigned char *)data;
    int index = 0;
    int pair = 0;
    for (unsigned conflict = 0; conflict < ConflictCount; conflict++) {
        for (unsigned item = 0; item < unknown_20; item++) {
            switch (pair) {
                case 0:
                    ((unsigned char *)unknown_44[conflict])[item] = bytes[index] & 3;
                    break;
                case 1:
                    ((unsigned char *)unknown_44[conflict])[item] = (bytes[index] >> 2) & 3;
                    break;
                case 2:
                    ((unsigned char *)unknown_44[conflict])[item] = (bytes[index] >> 4) & 3;
                    break;
                default:
                    ((unsigned char *)unknown_44[conflict])[item] = bytes[index] >> 6;
                    break;
            }
            pair++;
            if (pair == 4) {
                pair = 0;
                index++;
            }
        }
        if (pair != 0) {
            pair = 0;
            index++;
        }
    }
    return true;
}
