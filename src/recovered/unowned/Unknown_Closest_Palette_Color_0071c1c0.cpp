// unsigned char UnknownPalette_0071c1c0::Closest_Color(float red, float green, float blue) (0x0071C1C0)
// The index of the entry of a 256-entry RGB byte palette (+0x10) nearest to a color (squared distance in
// float; the search starts at a distance of 100000). The owner class is not identified.
class UnknownPalette_0071c1c0 {
public:
    unsigned char Closest_Color(float red, float green, float blue);

    char unknown_00[0x10];
    unsigned char *Palette;         // +0x10 256 RGB byte triples
};

unsigned char UnknownPalette_0071c1c0::Closest_Color(float red, float green, float blue)
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
