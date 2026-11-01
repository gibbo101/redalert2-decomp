// @ref _?_addend@?1??unknown_71bf20@UnknownVoxelPalette@@QAEXPAMH@Z@4MB=007aea48
// @ref __real@4@3ffb8000000000000000=007a7b20
// @ref __real@4@3ffecccccd0000000000=007aea4c
// @ref __real@4@3ffdccccccd000000000=007a7b18
// @ref __real@4@4006ff00000000000000=0079b0a8
// Builds the lookup: for each section a brightness level (from `levels`, or
// 32 default levels, 0.6..1.35 and 1.4..3.275, built in place
// in unknown_levels_af8f10) scales every palette color
// 1..255, and the nearest color of the same remap kind is stored. The upper
// 16 default sections clamp each channel to 255.
void UnknownVoxelPalette::unknown_71bf20(float *levels, int count)
{
    int index;
    int entry;
    int pos;
    static const float _addend = 0.6f;     // 0x007AEA48 (a const static, not a merged literal)
    float *shades;
    if (levels && count) {
        Header.unknown_08 = count;
        shades = levels;
    } else {
        shades = unknown_levels_af8f10;
        Header.unknown_08 = 32;
        for (index = 0; index < 16; index++) {
            unknown_levels_af8f10[index] = (index * (1.0f / 16)) * 0.8f + _addend;
        }
        for (index = 16; index < 32; index++) {
            unknown_levels_af8f10[index] = (index - 16) / 16.0f + index / 16.0f + 0.4f;
        }
    }
    bool remap;
    remap = false;
    for (entry = 0; entry < 16; entry++) {
        for (index = 1; index < 256; index++) {
            remap = index >= Header.unknown_00 && index <= Header.unknown_04;
            float red = Palette[index * 3];
            red *= shades[entry];
            float green = Palette[index * 3 + 1];
            green *= shades[entry];
            float blue = Palette[index * 3 + 2];
            blue *= shades[entry];
            pos = (entry << 8) | index;
            unknown_14[pos] = unknown_71c250(red, green, blue, remap);
        }
    }
    remap = false;
    for (entry = 16; entry < 32; entry++) {
        for (index = 1; index < 256; index++) {
            remap = index >= Header.unknown_00 && index <= Header.unknown_04;
            float red = Palette[index * 3];
            red *= shades[entry];
            float green = Palette[index * 3 + 1];
            green *= shades[entry];
            float blue = Palette[index * 3 + 2];
            blue *= shades[entry];
            red = red <= 255 ? red : 255;
            green = green <= 255 ? green : 255;
            blue = blue <= 255 ? blue : 255;
            pos = (entry << 8) | index;
            unknown_14[pos] = unknown_71c250(red, green, blue, remap);
        }
    }
}
