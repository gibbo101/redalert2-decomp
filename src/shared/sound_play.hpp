// The sound play calls of the VocClass unit, declared once for the screen
// layers (RadarClass, TabClass, sidebar), the game objects and the VocClass
// unit, and the handle the game keeps on a playing sound (names are
// hypotheses).
#ifndef RA2_SHARED_SOUND_PLAY_HPP
#define RA2_SHARED_SOUND_PLAY_HPP

struct AudioEvent;
struct AudioEventType;
struct AudioBag;
struct CoordStruct;

// What the game holds for an event it started: the event, the serial
// (AudioEvent::unknown_138) and type it had then, and the address of the
// event bag variable as proof it came from this system. A handle only works
// while all of that still matches (initialized by 0x00405BF0).
struct AudioEventHandle {
    AudioEvent *Event;              // +0x00
    int Serial;                     // +0x04
    AudioEventType *Type;           // +0x08
    AudioBag **Token;               // +0x0C &Audio_Event_Bag
};

// The 0x14-byte sound handle the game objects and the static sounds hold: an
// AudioEventHandle and one more word (hypothesis). Methods are out of line in
// the audio library.
class UnknownAudioController : public AudioEventHandle {
public:
    void Init();                        // 0x00405BF0 (clears the three words, links 0x00830FAC)
    void Unknown_00405C10();            // 0x00405C10
    void Unknown_00405D50();            // 0x00405D50
    void Unknown_00405FE0();            // 0x00405FE0
    void Unknown_00406070();            // 0x00406070 (VoxelAnimClass destructor, before Unknown_00405C10)

    int unknown_10;
};

// Plays a sound effect (0x00713DB0). Fastcall: the sound effect index in ECX,
// the pan in EDX (0x2000, the centre, from every caller), the volume (0..1)
// and a handle that keeps the event on the stack (every caller passes 0).
// Returns the event.
AudioEvent *__fastcall Voc_Play(int voc, float volume, int pan, AudioEventHandle *handle);

// Plays a sound effect at a coordinate with the volume and pan it has there
// (0x00713E60); a handle keeps the event, which a silent result stops.
AudioEvent *__fastcall Voc_Play_At(int voc, CoordStruct const &coord, AudioEventHandle *handle);

// Moves a handle's playing sound to a coordinate: its volume and pan from
// 0x00713F30; a silent sound is stopped, a forever-looping one restarted when
// audible again (0x007141B0).
AudioEvent *__fastcall Voc_Update_At(CoordStruct const &coord, AudioEventHandle *handle);

// Adds a static sound: a sound effect kept playing at a coordinate, with
// flags that Voc_Static_Finish_At matches (0x00714290; shared/voc_static.hpp).
AudioEvent *__fastcall Voc_Static_Add(int voc, CoordStruct const &coord, unsigned int flags);

#endif
