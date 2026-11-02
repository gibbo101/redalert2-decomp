// int FirewallSettings::Connection_Weight_005baee0(unsigned char flags) (0x005BAEE0): the weighted sum of
// the connection flag bits (1, 2, 3, 10, 1, 2 for bits 0-5; name hypothesis; does not read this).
int FirewallSettings::Connection_Weight_005baee0(unsigned char flags)
{
    int weight = 0;
    if (flags & 1) weight = 1;
    if (flags & 2) weight += 2;
    if (flags & 4) weight += 3;
    if (flags & 8) weight += 10;
    if (flags & 0x10) ++weight;
    if (flags & 0x20) weight += 2;
    return weight;
}
