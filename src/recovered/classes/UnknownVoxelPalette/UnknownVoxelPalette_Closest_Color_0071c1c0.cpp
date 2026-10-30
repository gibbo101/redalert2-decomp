// The index of the palette entry nearest to a color (squared distance in
// float; the search starts at a distance of 100000).
unsigned char UnknownVoxelPalette::Closest_Color(float red, float green, float blue)
{
    unsigned char *entry = Palette;
    int best = 0;
    float best_distance = 100000.0f;
    for (int index = 0; index < 256; index++) {
        float dx = red - Palette[index * 3];
        float dy = green - Palette[index * 3 + 1];
        float dz = blue - Palette[index * 3 + 2];
        float distance = dx * dx + dy * dy + dz * dz;
        if (distance < best_distance) {
            best = index;
            best_distance = distance;
        }
    }
    return best;
}
