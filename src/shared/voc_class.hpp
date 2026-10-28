// VocClass: the sound effect types (Sound.ini entries).
#ifndef RA2_SHARED_VOC_CLASS_HPP
#define RA2_SHARED_VOC_CLASS_HPP

struct AudioEventType;

// The audio event type with this name, made with the default settings when
// there is none (0x004063C0, the audio library).
AudioEventType *__fastcall Audio_Event_Type_Find(char const *name);

// A sound effect type: its audio event type, listed in the unit's VocClass
// list (0x00AD0818) while it exists.
class VocClass {
public:
    VocClass(char const *name);                                     // 0x00713810
    ~VocClass();                                                    // 0x00713880

    static int __fastcall From_Name(char const *name);              // 0x00714940 (-1 if none)

    AudioEventType *Event;                                          // +0x00
};

// The name of a VocType (0x00714A00; "<none>" when out of range).
char const *__fastcall Voc_Name(int voc);

#endif
