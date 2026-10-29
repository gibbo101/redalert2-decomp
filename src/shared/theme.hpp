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

#include "shared/vector_class_decl.hpp"

// A theme record (0x290 bytes?); only the flags the player tests.
struct ThemeControl {
    char unknown_000[0x288];
    bool unknown_288;
    bool unknown_289;           // +0x289 (Pick_Next_Song skips repeating a theme with it set)
};

typedef int ThemeType;
#define THEME_NONE (-1)

class ThemeClass {
public:
    ThemeClass();                           // 0x006E7C60
    void Stop(bool fade = false);           // 0x006E81A0 (argument meaning unknown)
    void Queue_Song(ThemeType theme);       // 0x006E7E20
    int Play_Song(ThemeType theme);         // 0x006E7EB0 (name hypothesis after TS)
    void Scan();                            // 0x006E7AF0 (name hypothesis)
    void AI();                              // 0x006E7CD0 (name hypothesis: chooses and starts the next song)
    ThemeType Pick_Next_Song(ThemeType current);    // 0x006E7D80 (name hypothesis)
    bool unknown_6e8440(unsigned theme);            // 0x006E8440 (the theme may be played; hypothesis)
    // The theme whose file name is `name` (0x006E8510) and a theme's file
    // base name (0x006E7C40); CCINIClass reads and writes themes by name.
    int From_Name(char const *name) const;
    char const *Base_Name(int theme) const;
    char const *Name(int theme) const;      // 0x006E8570 (the theme's INI name; "none" out of range)
    void Unknown_006E7A70();                // 0x006E7A70 (frees every theme record; Prog_End)
    void Set_Volume(int volume);            // 0x006E8590 (at most 255)
    bool Still_Playing() const;             // 0x006E82D0 (name after Red Alert's ThemeClass)

    ThemeType Current;      // +0x00 playing theme
    ThemeType Score;        // +0x04 theme that should be playing
    ThemeType Pending;      // +0x08 queued theme
    int Volume;             // +0x0C 0-255 (Set_Volume clamps it)
    bool IsRepeat;          // +0x10 (OptionsClass IsScoreRepeat)
    bool unknown_11;        // +0x11
    bool IsShuffle;         // +0x12 (OptionsClass IsScoreShuffle)
    char unknown_13;
    DynamicVectorClass<ThemeControl *> Themes;  // +0x14 the theme records (vector storage +0x18, count +0x24;
                                                // Pick_Next_Song only matches through Count() and operator[])
    void *Sample;           // +0x2C the playing audio stream (0 when none)
};

// Set before the theme scan (0x00A40C18; Red Alert's ScoresPresent).
extern char unknown_sound_enabled_a40c18;
extern ThemeClass Theme;    // 0x00A35D78

#endif
