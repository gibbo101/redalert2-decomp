#include "shared/firewall_settings.hpp"
int FirewallSettings::Connection_Step_005baf20(int flags)
{
    int step=2;
    if(flags & 1) step=3;
    if(flags & 2) ++step;
    if(flags & 4) ++step;
    if(flags & 0x20) step+=5;
    return step;
}
