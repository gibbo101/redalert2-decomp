// The nearest palette entry (1..255) inside the remap range when `remap`,
// outside it otherwise.
unsigned char UnknownVoxelPalette::unknown_71c250(float red, float green, float blue, bool remap)
{
    int best = remap ? Header.unknown_00 : 1;
    float best_distance = 100000.0f;
    for (int index = 1; index < 256; index++) {
        if (remap) {
            if (index < Header.unknown_00 || index > Header.unknown_04) {
                continue;
            }
        } else {
            if (index >= Header.unknown_00 && index <= Header.unknown_04) {
                continue;
            }
        }
        float dx = red - Palette[index * 3];
        float dy = green - Palette[index * 3 + 1];
        float dz = blue - Palette[index * 3 + 2];
        float distance = dx * dx + dy * dy + dz * dz;
        if (distance < best_distance) {
            best_distance = distance;
            best = index;
        }
    }
    return best;
}
