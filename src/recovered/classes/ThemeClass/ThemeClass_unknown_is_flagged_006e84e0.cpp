// bool ThemeClass::unknown_is_flagged(unsigned theme) const -- 0x006E84E0
// Purpose: the +0x288 flag of theme `theme`'s control record; false for
// the special values -3 and -2 and for an unknown theme.
// Assumptions: the layout of 0x006E8150 (records at +0x18, count +0x24);
// the flag's meaning (e.g. available/normal play) and the name are
// hypotheses.

struct ThemeControl {
    char unknown_000[0x288];
    bool unknown_288;                       // +0x288
};

class ThemeClass {
public:
    bool unknown_is_flagged(unsigned theme) const;

    char unknown_00[0x18];
    ThemeControl **Themes;                  // +0x18 (vector storage)
    int unknown_1c;
    int unknown_20;
    unsigned ThemeCount;                    // +0x24 (active count)
};

bool ThemeClass::unknown_is_flagged(unsigned theme) const
{
    if (theme == (unsigned)-3 || theme == (unsigned)-2 || theme >= ThemeCount) {
        return false;
    }
    return Themes[theme]->unknown_288 ? true : false;
}
