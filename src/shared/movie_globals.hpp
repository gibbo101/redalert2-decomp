// Globals the movie unit uses that belong to other units (hypotheses).
#ifndef RA2_SHARED_MOVIE_GLOBALS_HPP
#define RA2_SHARED_MOVIE_GLOBALS_HPP

#include "shared/mouse.hpp"
#include "shared/surface.hpp"
#include "shared/theme.hpp"
#include "shared/win32_window.hpp"

// The mouse object at 0x00839C68 is WWMouse (shared/mouse.hpp).

// The movie unit queues a theme on the ThemeClass object at 0x00A35D78
// (shared/theme.hpp).

// Surfaces: the movie is blitted to the one at 0x00839950 at screen
// coordinates; the one at 0x00839958 is cleared first.
extern Surface *unknown_surface_839950;  // 0x00839950
extern Surface *unknown_surface_839958;  // 0x00839958
void __fastcall Unknown_004E0C90(bool unknown1, Surface *surface, int unknown2);  // 0x004E0C90

extern HWND MainWindow;               // 0x00B263D8

// The object at 0x00A40B18 rewrites a movie base name in place.
class UnknownClassA40B18 {
public:
    void Unknown_005DA3F0(char *name);   // 0x005DA3F0
};
extern UnknownClassA40B18 unknown_object_a40b18;   // 0x00A40B18

#endif
