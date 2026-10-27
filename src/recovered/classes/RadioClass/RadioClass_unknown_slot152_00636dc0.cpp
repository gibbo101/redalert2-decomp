// void RadioClass::unknown_slot152(int message) (0x00636DC0, slot 152): to every contact.
#include "shared/radio.hpp"

void RadioClass::unknown_slot152(int message)
{
    for (int index = 0; index < RadioLinks.Length(); index++) {
        if (RadioLinks[index] != 0) {
            unknown_slot151(message, &unknown_radio_param_a40be0, RadioLinks[index]);
        }
    }
}
