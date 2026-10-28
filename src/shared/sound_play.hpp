// The sound play call (0x00713DB0), declared once for the screen layers
// (RadarClass, TabClass, sidebar) and the techno voice slots. Fastcall: the
// sound index in ECX and the flags (0x2000 from every caller) in EDX; the
// fourth argument is an object pointer or 0 (names are hypotheses).
#ifndef RA2_SHARED_SOUND_PLAY_HPP
#define RA2_SHARED_SOUND_PLAY_HPP

int __fastcall Unknown_00713DB0(int sound, float volume, int flags, int arg4);

#endif
