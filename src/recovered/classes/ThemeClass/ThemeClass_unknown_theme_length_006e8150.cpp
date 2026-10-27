// int ThemeClass::unknown_theme_length(unsigned theme) const -- 0x006E8150
// Purpose: the +0x284 value (a float, truncated) of theme `theme`'s
// control record, 0 for an unknown theme.
// Assumptions: the themes are a DynamicVectorClass of control records at
// +0x14 (elements +0x18, count +0x24); +0x284 is taken to be the length.
// @ref __ftol=0077f110

struct ThemeControl {
    char unknown_000[0x284];
    float unknown_284;                      // +0x284
};

class ThemeClass {
public:
    int unknown_theme_length(unsigned theme) const;

    char unknown_00[0x18];
    ThemeControl **Themes;                  // +0x18 (vector storage)
    int unknown_1c;
    int unknown_20;
    unsigned ThemeCount;                    // +0x24 (active count)
};

int ThemeClass::unknown_theme_length(unsigned theme) const
{
    if (theme < ThemeCount) {
        return (int)Themes[theme]->unknown_284;
    }
    return 0;
}
