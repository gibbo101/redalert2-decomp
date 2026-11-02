// bool WDTState::unknown_72c490(void *data, int length) (0x0072C490): the MPVC field of the WOL
// state packet, one territory per record (44 bytes read, 0x1C checked). Each record makes a counted
// WDTTerritory through the factory WDTTerritory::Create 0x0072BDC0 (expanded here; its rc_ptr
// constructor stays out of line at 0x0072CAA0), numbers it with unknown_20 and appends it to
// Territories. Most bytes carry a +0x80 bias; the battle-setting triples from +0x1F only drop
// the high bit (Unbias_72c490, read in the packet's 0,1,2,4,5,3,6,7 triple order).
// @ref ??0?$rc_ptr@VWDTTerritory@@@@QAE@PAVWDTTerritory@@@Z=0072caa0
#include "shared/wdt_state.hpp"
#include "shared/wdt_territory.hpp"

inline unsigned char Unbias_72c490(unsigned char const &value)
{
    return value > 0x7F ? value - 0x80 : value;
}

bool WDTState::unknown_72c490(void *data, int length)
{
    unsigned char *bytes = (unsigned char *)data;
    unknown_20 = 0;
    if (length < 0x1C) {
        return false;
    }
    for (int i = 0; i < length; ) {
        if (i + 0x1C > length) {
            return false;
        }
        rc_ptr<WDTTerritory> territory = WDTTerritory::Create();
        territory->unknown_08 = unknown_20;
        *(unsigned short *)territory->unknown_0c = bytes[i++] << 8;
        *(unsigned short *)territory->unknown_0c += bytes[i++];
        territory->UnitCount = bytes[i++] + 0x80;
        territory->TechLevel = bytes[i++] + 0x80;
        territory->unknown_10 = bytes[i++] << 8;
        territory->unknown_10 += bytes[i++];
        unsigned kind = bytes[i++] - 0x80;
        territory->unknown_15[0x1C - 0x15] = kind & 0x0F;
        territory->unknown_15[0x1D - 0x15] = (kind >> 4) & 0x0F;
        territory->unknown_15[0x1E - 0x15] = bytes[i++] + 0x80;
        territory->unknown_12 = bytes[i++] + 0x80;
        territory->unknown_13 = bytes[i++] + 0x80;
        territory->PlayerCount = bytes[i++] + 0x80;
        *(int *)&territory->unknown_15[0x18 - 0x15] = bytes[i++] - 0x80;
        territory->unknown_15[0x1F - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x20 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x21 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x22 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x23 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x24 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x25 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x26 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x27 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x2B - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x2C - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x2D - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x2E - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x2F - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x30 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x28 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x29 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x2A - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x31 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x32 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x33 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x34 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x35 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_15[0x36 - 0x15] = Unbias_72c490(bytes[i]); i++;
        territory->unknown_3c = bytes[i++] << 24;
        territory->unknown_3c += bytes[i++] << 16;
        territory->unknown_3c += bytes[i++] << 8;
        territory->unknown_3c += bytes[i++];
        territory->OptionFlags = bytes[i++] << 24;
        territory->OptionFlags += bytes[i++] << 16;
        territory->OptionFlags += bytes[i++] << 8;
        territory->OptionFlags += bytes[i++];
        Territories.Add(territory);
        unknown_20++;
    }
    return true;
}
