// ProgressScreenClass: the loading/connection progress screen (name
// hypothesis after Tiberian Sun's ProgressScreenClass; no RTTI). One global
// object, ProgressScreen (0x00A769E8), built by the unit's dynamic
// initializer 0x0061ECA0 and destroyed by its atexit thunk 0x0061ECC0.
// Vtable 0x007A843C has a single slot (0x006203E0).
// Layout from the constructor 0x0061ED00 and Init 0x0061ED80:
//   +0x00 vptr, +0x04 int, +0x08 double Progress[8] (one per player),
//   +0x48 double Total, +0x50 int, +0x54 the background shape and +0x58 its
//   allocated flag, +0x5C image, +0x60 bool, +0x61 char Count (players),
//   +0x62 bool, +0x64 int, +0x68..+0x80.
#ifndef RA2_SHARED_PROGRESS_SCREEN_HPP
#define RA2_SHARED_PROGRESS_SCREEN_HPP

#include "shared/rect.hpp"

struct ShapeFileStruct;
// Loads a shape file, noting whether it was allocated (0x00495270; also
// declared in shared/radar.hpp, which this header cannot include).
void const *__fastcall Unknown_Load_Shape_00495270(char const *filename, bool &allocated);

class ColorScheme;
// The colour scheme of a name (0x00663D30; kind 1 in every use here).
ColorScheme *__fastcall unknown_color_scheme_663d30(char const *name, int kind);

// Draws a background image on the primary surface (0x00515A80; clears the
// surface first; the flag presents it as well; hypothesis).
void __fastcall Unknown_00515A80(void const *image, bool present);

class ProgressScreenClass {
public:
    ProgressScreenClass();                                      // 0x0061ED00
    ~ProgressScreenClass();                                     // 0x0061ED50

    virtual void Set_unknown_04(int value);                     // 0x006203E0 slot 0

    void Init(double total, char count, int unknown);           // 0x0061ED80
    void Clear_unknown_60();                                    // 0x0061EDF0
    void Free_Shape();                                          // 0x0061EE00
    void Set_unknown_80(int value);                             // 0x0061EE30
    int Get_unknown_80();                                       // 0x0061EE40
    ColorScheme *Side_Color_Scheme();                           // 0x0061EE50 ("AlliedLoad"/"SovietLoad")
    ColorScheme *Text_Color_Scheme();                           // 0x0061EE80 ("LightGrey" for an observer)
    ColorScheme *Player_Color_Scheme(int player);               // 0x0061EED0
    void Load_Shape(char const *filename, void const *image, int unknown);   // 0x0061EF40
    void Set_unknown_78(int value);                             // 0x0061F150
    bool Is_unknown_64();                                       // 0x006203C0
    void Clear_unknown_64();                                    // 0x006203D0
    double Get_Progress(int player);                            // 0x006203F0
    // Sets a player's progress and redraws (0x006201C0; the serial game
    // code reports the other player's progress through it).
    void Set_Progress_006201c0(int index, double value, Point2D point);

    int unknown_04;                     // +0x04
    double Progress[8];                 // +0x08
    double Total;                       // +0x48
    int unknown_50;                     // +0x50
    ShapeFileStruct const *Shape;       // +0x54
    bool ShapeAllocated;                // +0x58
    void const *Image;                  // +0x5C
    bool unknown_60;                    // +0x60
    char Count;                         // +0x61
    bool unknown_62;                    // +0x62
    int unknown_64;                     // +0x64
    int unknown_68;                     // +0x68
    int unknown_6c;                     // +0x6C
    bool unknown_70;                    // +0x70
    int unknown_74;                     // +0x74
    int unknown_78;                     // +0x78
    int unknown_7c;                     // +0x7C
    int unknown_80;                     // +0x80
};

extern ProgressScreenClass ProgressScreen;     // 0x00A769E8

#endif
