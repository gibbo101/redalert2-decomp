// int RadioClass::unknown_slot149(int message) (0x00636D90, slot 149): to the first contact, if any.
#include "shared/radio.hpp"

int RadioClass::unknown_slot149(int message)
{
    if (RadioLinks[0] != 0) {
        return unknown_slot151(message, &unknown_radio_param_a40be0, RadioLinks[0]);
    }
    return 0;
}
