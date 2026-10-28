// ThemeClass: the music player (hypothesis; the object at 0x00A35D78).
//
// Westwood's ThemeClass keeps the playing theme, the theme that should be
// playing and the queued one. Evidence: 0x006E7E20 stores its argument at
// +0x08 (Queue_Song), 0x006E81A0 tests +0x00 against -1 (Stop), and the CD
// swap code saves +0x04, falling back to +0x08, to restart the music after a
// disk change. 0x006E7AF0 (no arguments) is called after THEME.MIX has been
// reopened (hypothesis: rescans the theme list). Names are Westwood's RA1
// vocabulary, not verified on this binary.
#ifndef RA2_SHARED_THEME_HPP
#define RA2_SHARED_THEME_HPP

typedef int ThemeType;
#define THEME_NONE (-1)

class ThemeClass {
public:
    void Stop(bool fade = false);           // 0x006E81A0 (argument meaning unknown)
    void Queue_Song(ThemeType theme);       // 0x006E7E20
    int Play_Song(ThemeType theme);         // 0x006E7EB0 (name hypothesis after TS)
    void Scan();                            // 0x006E7AF0 (name hypothesis)
    // The theme whose file name is `name` (0x006E8510) and a theme's file
    // base name (0x006E7C40); CCINIClass reads and writes themes by name.
    int From_Name(char const *name) const;
    char const *Base_Name(int theme) const;
    char const *Name(int theme) const;      // 0x006E8570 (the theme's INI name; "none" out of range)
    void Set_Volume(int volume);            // 0x006E8590 (at most 255)

    ThemeType Current;      // +0x00 playing theme
    ThemeType Score;        // +0x04 theme that should be playing
    ThemeType Pending;      // +0x08 queued theme
    int Volume;             // +0x0C 0-255 (Set_Volume clamps it)
    bool IsRepeat;          // +0x10 (OptionsClass IsScoreRepeat)
    bool unknown_11;        // +0x11
    bool IsShuffle;         // +0x12 (OptionsClass IsScoreShuffle)
};

extern ThemeClass Theme;    // 0x00A35D78

#endif
