// Clears the shared online identifier after changing network settings.
#define FIREWALL_SETTINGS_DECLARE_CLEAR
#include "shared/wol_chat.hpp"

void FirewallSettings::Clear_005b9e70()
{
    unknown_00 = 0;
}
