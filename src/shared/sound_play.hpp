// The sound play call (0x00713DB0), declared once for the screen layers
// (RadarClass, TabClass, sidebar), the techno voice slots and the VocClass
// unit. Fastcall: the sound effect index in ECX, the pan in EDX (0x2000, the
// centre, from every caller), the volume (0..1) and a handle that keeps the
// event on the stack (every caller passes 0). Returns the event (names are
// hypotheses).
#ifndef RA2_SHARED_SOUND_PLAY_HPP
#define RA2_SHARED_SOUND_PLAY_HPP

struct AudioEvent;
struct AudioEventHandle;

AudioEvent *__fastcall Voc_Play(int voc, float volume, int pan, AudioEventHandle *handle);

#endif
