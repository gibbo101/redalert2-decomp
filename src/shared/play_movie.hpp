// Movie.cpp (unit 0x005A0060-0x005A0B4F): the full-screen movie players, the movie-name entry points and
// the radar's queued movies (TibSun movie.cpp names; RA2 plays Bink movies through BinkClass and VQA
// movies through the VQAMovie wrapper of shared/movie.hpp). Names are hypotheses from TibSun.
#ifndef RA2_SHARED_PLAY_MOVIE_HPP
#define RA2_SHARED_PLAY_MOVIE_HPP

#include "shared/rect.hpp"

class Surface;
class VQAMovie;
// The audio library's pause pair around the players (0x00406DE0, 0x00406E00).
void __fastcall Audio_Pause();
void Audio_Resume();
// Opens a VQA movie (0x005A1010; also declared by shared/ms_anim.hpp and Create_Movie_Handle).
VQAMovie *__fastcall VQA_Unknown_005A1010(char const *filename, Surface *surface, Rect unknown1, Rect area,
                                          int unknown2, int unknown3);
extern "C" char *__cdecl strrchr(char const *string, int character);

// Completes the symmetric 256 x 256 interpolation table from its stored triangle (0x005A0250).
void __fastcall Rebuild_Interpolated_Palette(unsigned char *interpal);
// Plays a movie file full screen (0x005A02D0): a ".bik" name through BinkClass, anything else as a VQA
// movie (stretched when asked and allowed); clrscrn_before/after clear the screen around it, bink_flag
// sets the Bink player's first byte. Nothing happens in a multiplayer game or without the file.
void __fastcall Play_Movie(char const *name, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before,
                           bool bink_flag);
// The same with bink_flag set (0x005A02B0).
void __fastcall Play_Movie(char const *name, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before);
// Plays a movie handle on the hidden surface with the game sound paused (0x005A0710).
void __fastcall Play_Movie_Handle(char const *name);
// Plays the movie of a movie-list index (0x005A07F0; no theme, unknown_flag_a40380 cleared meanwhile).
void __fastcall Play_Movie(int movie, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before);
// Queues the movie of a movie-list index for the radar (0x005A0920; Unknown_Queue_Movie_005a0840 expanded).
void __fastcall Play_Ingame_Movie(int movie, bool flag);
// Pauses or resumes the first queued movie (0x005A0A90).
void __fastcall Pause_Ingame_Movie(bool pause);

#endif
