// int RadioClass::unknown_slot151(int message, int *param, TechnoClass *to) (0x00636A50, slot 151)
// Sends a radio message (3 hangs up, 2 makes contact) to a recipient
// (the first contact when none is given) through the recipient's slot 95.
// Contact needs a free link: when all are taken the first is hung up.
// 0xA is the answer when the recipient does not accept.
#include "shared/radio.hpp"
#include "shared/techno.hpp"

int RadioClass::unknown_slot151(int message, int *param, TechnoClass *to)
{
    if (to == 0) {
        to = RadioLinks[0];
        if (to == 0) {
            return 0;
        }
    }
    if (message == 3) {
        for (int index = 0; index < RadioLinks.Length(); index++) {
            if (RadioLinks[index] == to) {
                RadioLinks[index] = 0;
            }
        }
    } else if (message == 2) {
        int free_link = -1;
        for (int index = 0; index < RadioLinks.Length(); index++) {
            if (free_link == -1 && RadioLinks[index] == 0) {
                free_link = index;
            }
            if (RadioLinks[index] == to) {
                return 1;
            }
        }
        if (free_link == -1) {
            unknown_slot150(3, RadioLinks[0]);
            free_link = 0;
        }
        if (to->unknown_slot95(As_Techno(), 2, (long &)*param) == 1) {
            RadioLinks[free_link] = to;
            return 1;
        }
        return 0xA;
    }
    return to->unknown_slot95(As_Techno(), message, (long &)*param);
}
