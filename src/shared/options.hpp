// OptionsClass: the player's game settings kept in RA2.INI (Options.cpp;
// the global Options at 0x00A40B18, a second instance at 0x00A6EC38). Layout
// from the constructor 0x005D8840 and Load_Settings 0x005D8B00; member names
// follow the INI entries and TS's OptionsClass. shared/movie_globals.hpp
// (UnknownClassA40B18) and shared/frame_rate_control.hpp
// (UnknownFrameRateControl) still view the same object.
#ifndef RA2_SHARED_OPTIONS_HPP
#define RA2_SHARED_OPTIONS_HPP

#include "shared/win32_api.hpp"

class OptionsClass {
public:
    OptionsClass();                         // 0x005D8840

    // Each setter clamps a volume to 1.0, applies it and logs it; feedback
    // plays Rules' GenericBeep at the new level (sound and voice only).
    void Set_Shuffle(bool on);                              // 0x005D8920
    void Set_Repeat(bool on);                               // 0x005D8950
    void Set_Score_Volume(float volume, bool feedback);     // 0x005D8980
    void Set_Sound_Volume(float volume, bool feedback);     // 0x005D89F0
    void Set_Voice_Volume(float volume, bool feedback);     // 0x005D8A70
    void Load_Settings();                                   // 0x005D8B00 (RA2.INI)
    void Save_Settings();                                   // 0x005D91B0 (RA2.INI)
    // Applies the [Network] settings: the IPX socket (0x8813 by default) and
    // the destination network from DestNet (0x005D94D0; name hypothesis).
    void Setup_Network();
    void Set();                                             // 0x005D95E0 (applies the settings; name after TS)
    int Normalize_Volume(int volume);                       // 0x005D9790 (volume times SoundVolume; name after TS)
    // Raises the unlocked movie of the campaign whose list holds the movie
    // name (0x005DA3F0).
    void Unlock_Movie(char const *name);
    // Adds the intro and the unlocked campaign movies to a movie list box
    // (0x005DA470).
    void Fill_Movie_List(HWND list);
    void One_Time();                                        // 0x005D8910 (empty; name after TS)
    int Get_Scroll_Method() const;                          // 0x005DA3E0
    int Normalize_Delay(int delay) const;                   // 0x005D9760 (name after TS)

    int GameSpeed;                          // +0x00 [Options] GameSpeed (3)
    int Difficulty;                         // +0x04 [Options] Difficulty, 0-4 (1; the campaign difficulty)
    int ScrollMethod;                       // +0x08 [Options] ScrollMethod (0)
    int ScrollRate;                         // +0x0C [Options] ScrollRate (3)
    bool AutoScroll;                        // +0x10 [Options] AutoScroll (true)
    int DetailLevel;                        // +0x14 [Options] DetailLevel, 0-2 (2)
    bool SidebarOn;                         // +0x18 ("SideBar on RIGHT"; always true)
    bool SidebarCameoText;                  // +0x19 [Options] SidebarCameoText (true)
    bool UnitActionLines;                   // +0x1A [Options] UnitActionLines (true)
    bool ShowHidden;                        // +0x1B [Options] ShowHidden (false)
    bool ToolTips;                          // +0x1C [Options] ToolTips (true)
    int ScreenWidth;                        // +0x20 [Video] ScreenWidth (-1)
    int ScreenHeight;                       // +0x24 [Video] ScreenHeight (-1)
    bool StretchMovies;                     // +0x28 [Video] StretchMovies (false)
    bool AllowHiResModes;                   // +0x29 [Video] AllowHiResModes (false)
    bool AllowVRAMSidebar;                  // +0x2A [Video] AllowVRAMSidebar (false)
    float SoundVolume;                      // +0x2C [Audio] SoundVolume (0.7)
    float VoiceVolume;                      // +0x30 [Audio] VoiceVolume (1.0)
    float ScoreVolume;                      // +0x34 [Audio] ScoreVolume (0.5)
    bool IsScoreRepeat;                     // +0x38 [Audio] IsScoreRepeat (false)
    bool InGameMusic;                       // +0x39 [Audio] InGameMusic (true)
    bool IsScoreShuffle;                    // +0x3A [Audio] IsScoreShuffle (false)
    unsigned short SoundLatency;            // +0x3C [Audio] SoundLatency (9)
    unsigned short Socket;                  // +0x3E [Network] Socket (0xFFFF)
    // The last campaign movie unlocked, Soviet ([0]) and Allied ([1]); -1 for
    // none. Kept as [Network] NetID, two numbers with inverted characters.
    int UnlockedMovie[2];                   // +0x40 (-1)
    int NetCard;                            // +0x48 [Network] NetCard (0)
    char DestNet[64];                       // +0x4C [Network] DestNet ("")
    int KeyForceMove1;                      // +0x8C (VK_MENU)
    int KeyForceMove2;                      // +0x90 (VK_MENU)
    int KeyForceAttack1;                    // +0x94 (VK_CONTROL)
    int KeyForceAttack2;                    // +0x98 (VK_CONTROL)
    int KeySelect1;                         // +0x9C (VK_SHIFT)
    int KeySelect2;                         // +0xA0 (VK_SHIFT)
    int KeyQueueMove1;                      // +0xA4 ('Q')
    int KeyQueueMove2;                      // +0xA8 ('Q')
};

// A campaign movie (12 bytes): its file base name, its string-table label and
// its campaign (-1 the intro, 0 Allied, 1 Soviet).
struct MovieEntryStruct {
    char const *Name;
    char const *Label;
    int Side;
};
extern MovieEntryStruct IntroMovie;                 // 0x007E8248
extern MovieEntryStruct AlliedMovies[];             // 0x007E8258 (ends with a null Name)
extern MovieEntryStruct SovietMovies[];             // 0x007E82F8 (ends with a null Name)

// Normalize_Delay's table for delays 1-4 by game speed (0x007E8394; in TS a
// static local of the function).
extern int const Delay_Adjust[4][8];

extern OptionsClass Options;                // 0x00A40B18

// [Video] AllowModeToggle (0x00A40D0B; not an OptionsClass member).
extern bool unknown_allow_mode_toggle_a40d0b;

#endif
