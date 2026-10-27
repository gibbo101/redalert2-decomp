// int RadioClass::unknown_slot150(int message, TechnoClass *techno) (0x00636B80, slot 150)
#include "shared/radio.hpp"

int RadioClass::unknown_slot150(int message, TechnoClass *techno)
{
    return unknown_slot151(message, &unknown_radio_param_a40be0, techno);
}
