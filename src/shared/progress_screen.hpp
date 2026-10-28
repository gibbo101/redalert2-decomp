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

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

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

class Surface;
class ConvertClass;
struct Unknown535910;
typedef struct HWND__ *HWND;
// A country's flag image (0x004D1120; "usai.pcx" ... "rusi.pcx", -2 "rani.pcx"
// for a random country, -3 "obsi.pcx" for an observer; null if none).
Surface *__fastcall Country_Flag_004d1120(int country);

class ProgressScreenClass {
public:
    ProgressScreenClass();                                      // 0x0061ED00
    ~ProgressScreenClass();                                     // 0x0061ED50

    virtual void Set_Listener(Unknown535910 *listener);         // 0x006203E0 slot 0

    void Init(double total, char count, HWND window);           // 0x0061ED80
    void Clear_unknown_60();                                    // 0x0061EDF0
    void Free_Shape();                                          // 0x0061EE00
    void Set_Side(int side);                                    // 0x0061EE30
    int Get_Side();                                             // 0x0061EE40
    ColorScheme *Side_Color_Scheme();                           // 0x0061EE50 ("AlliedLoad"/"SovietLoad" by Side)
    ColorScheme *Text_Color_Scheme();                           // 0x0061EE80 ("LightGrey" for an observer)
    ColorScheme *Player_Color_Scheme(int player);               // 0x0061EED0
    void Load_Shape(char const *filename, void const *image, ConvertClass *drawer);   // 0x0061EF40
    void Shape_Size(int *width, int *height);                   // 0x0061F160 (frame 0 plus a 6-pixel border)
    void Flag_Size(int *width, int *height);                    // 0x0061F1D0 (the first country's flag)
    // The size of a 15-character name in the progress font.
    static void __fastcall Text_Size(int *width, int *height);  // 0x0061F210
    // The size of the whole box for a number of rows (with or without flags).
    void Box_Size(int *width, int *height, int rows, bool flag);    // 0x0061F280
    // The top of a row: rows of the box height for one row.
    int Row_Y(int y, int row, bool flag);                       // 0x0061F3B0
    int Shape_Offset(bool flag);                                // 0x0061F4B0 (vertical centring in a row)
    int Flag_Offset(bool flag);                                 // 0x0061F630
    int Text_Offset(bool flag);                                 // 0x0061F770
    double Average_Progress();                                  // 0x0061F8C0
    // Draws a player's progress bar: the shape's frame filled to fraction,
    // in the scheme's colours (DarkRed without one), outlined when
    // unknown_71 is set.
    void Draw_Bar(Point2D xy, double fraction, Surface *surface, ColorScheme *scheme);     // 0x0061F8F0
    // Copies a flag image to xy, magenta transparent.
    void Draw_Flag(Point2D xy, Surface *flag);                  // 0x0061FAB0
    void Draw_Name(Point2D xy, wchar_t const *name, ColorScheme *scheme, int width);       // 0x0061FB70
    // Draws one player's row: bar, name and (with flags) the country flag.
    void Draw_Player(ColorScheme *scheme, wchar_t const *name, Point2D &xy, int player, bool flag);   // 0x0061FC20
    // Draws the screen: into the dialog's bar control when there is a
    // window, else every player's row from xy (Position when xy is -1,-1).
    void Draw_It(Point2D xy);                                   // 0x00620050
    void Set_Name_Width(int width);                             // 0x0061F150
    bool Has_Window();                                          // 0x006203C0
    void Clear_Window();                                        // 0x006203D0
    double Get_Progress(int player);                            // 0x006203F0
    // Sets a player's progress and redraws (0x006201C0; the serial game
    // code reports the other player's progress through it).
    void Set_Progress_006201c0(int index, double value, Point2D point);
    // Adds to a player's progress (percent of the total) and redraws as Set_Progress does.
    void Add_Progress(int index, double value, Point2D point);  // 0x006202C0

    Unknown535910 *Listener;            // +0x04 told the percent before and after each change
    double Progress[8];                 // +0x08
    double Total;                       // +0x48
    wchar_t const *Name;                // +0x50 the name shown for a single player
    ShapeFileStruct const *Shape;       // +0x54
    bool ShapeAllocated;                // +0x58
    void const *Image;                  // +0x5C
    bool unknown_60;                    // +0x60
    char Count;                         // +0x61
    bool unknown_62;                    // +0x62
    HWND Window;                        // +0x64 the dialog whose control 0x639 shows the bar
    Point2D Position;                   // +0x68
    bool ShowFlags;                     // +0x70 rows show the players' country flags
    bool unknown_71;                    // +0x71 outline the bars
    ConvertClass *Drawer;               // +0x74 the bars' drawer when set (Load_Shape)
    int NameWidth;                      // +0x78 the name column's width (-1: the box's)
    int unknown_7c;                     // +0x7C
    int Side;                           // +0x80 0 Allied, else Soviet colours
};

extern ProgressScreenClass ProgressScreen;     // 0x00A769E8

#endif
