// char *Random_Map_CRC_005c8420() (0x005C8420)
// The random map's identity text: the CRC of the map generator's seed options (0x140 bytes from Theater,
// with the description buffer cleared while it runs) as "%08X" in a new 12-character buffer.
#include "shared/lobby.hpp"
#include "shared/unknown_map_generator.hpp"
// @ref ?unknown_map_generator_a6fd68@@3VUnknownMapGenerator@@A=00a6fd68
// @ref ??_C@_04CLEA@?$CF08X?$AA@=007ce280

char *Random_Map_CRC_005c8420()
{
    unsigned long crc = 0;
    unsigned long const *data = (unsigned long const *)&unknown_map_generator_a6fd68.SeedOptions.Theater;
    int length = 0x140;
    wchar_t description[128];
    memcpy(description, unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer, sizeof(description));
    memset(unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer, 0, sizeof(description));
    do {
        unsigned long hibit = crc >> 31;
        if (length >= 4) {
            crc = (crc << 1) + *data++ + hibit;
            length -= 4;
        } else {
            unsigned long value = 0;
            unsigned char const *bytes = (unsigned char const *)data;
            while (length != 0) {
                value = (value << 8) | *bytes++;
                length--;
            }
            crc = (crc << 1) + value + hibit;
        }
    } while (length > 0);
    char *text = new char[12];
    sprintf(text, "%08X", crc);
    memcpy(unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer, description, sizeof(description));
    return text;
}
