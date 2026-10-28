// VocClass: the sound effect types (Sound.ini entries).
#ifndef RA2_SHARED_VOC_CLASS_HPP
#define RA2_SHARED_VOC_CLASS_HPP

struct AudioEventType;
struct AudioEvent;
struct AudioEventHandle;
struct CoordStruct;
class CCINIClass;

#include "shared/sound_play.hpp"

// The audio event type with this name, made with the default settings when
// there is none (0x004063C0, the audio library).
AudioEventType *__fastcall Audio_Event_Type_Find(char const *name);

// The audio library's event type settings (0x00405150-0x00406880) as
// VocClass::Read_INI (0x007138D0) sets them from a Sound.ini section.
char *__fastcall Audio_Event_Type_Name(AudioEventType *type);                            // 0x00405150
int __fastcall Audio_Event_Type_Add_Sample(AudioEventType *type, char const *name);      // 0x004064B0
void __fastcall Audio_Event_Type_Set_Intro(AudioEventType *type, int count);             // 0x00406530 (+0x138; "Attack")
void __fastcall Audio_Event_Type_Set_Outro(AudioEventType *type, int count);             // 0x00406540 (+0x13C; "Decay")
void __fastcall Audio_Event_Type_Set_Priority(AudioEventType *type, int priority);       // 0x00406550 (+0x40)
void __fastcall Audio_Event_Type_Set_Volume(AudioEventType *type, int volume);           // 0x00406560
void __fastcall Audio_Event_Type_Set_Flags(AudioEventType *type, unsigned int flags);    // 0x00406580
void __fastcall Audio_Event_Type_Set_Type(AudioEventType *type, unsigned int flags);     // 0x004065D0 (+0x14; "Type")
void __fastcall Audio_Event_Type_Set_Limit(AudioEventType *type, int limit);             // 0x004065E0 (+0x48)
void __fastcall Audio_Event_Type_Set_Range(AudioEventType *type, int range);             // 0x004065F0 (+0x50)
void __fastcall Audio_Event_Type_Set_Min_Volume(AudioEventType *type, float volume);     // 0x00406600 (+0x54)
void __fastcall Audio_Event_Type_Set_Delay(AudioEventType *type, int low, int high);     // 0x00406610 (+0x58, +0x5C)
void __fastcall Audio_Event_Type_Set_FShift(AudioEventType *type, int low, int high);    // 0x00406620 (+0x60, +0x64)
void __fastcall Audio_Event_Type_Set_Percent(AudioEventType *type, int percent);         // 0x00406630 (+0x68; "VShift")
void __fastcall Audio_Event_Type_Set_Loop(AudioEventType *type, int count);              // 0x00406650 (+0x4C)
bool __fastcall Audio_Priority_From_Name(char const *name, int *priority);              // 0x004067E0
bool __fastcall Audio_Control_Apply_Keyword(unsigned int *flags, char const *name);     // 0x00406830
int __fastcall Audio_Event_Apply_Keyword(unsigned int *flags, char const *name);        // 0x00406880

// An event type's range in cells (0x00405110, +0x50), minimum volume
// (0x00405120, +0x54) and type flags (0x00405140, +0x14); 0 while the event
// system is off; whether it loops forever (0x00406660).
int __fastcall Audio_Event_Type_Range(AudioEventType *type);                             // 0x00405110
float __fastcall Audio_Event_Type_Min_Volume(AudioEventType *type);                      // 0x00405120
unsigned int __fastcall Audio_Event_Type_Flags(AudioEventType *type);                    // 0x00405140
int __fastcall Audio_Event_Type_Loops_Forever(AudioEventType *type);                     // 0x00406660

// The events the sound effects start (audio library; Audio_Event_Create and
// Audio_Event_Stop are in shared/audio.hpp).
void __fastcall Audio_Event_Set_Flag_8(AudioEvent *event);                               // 0x004052F0 (Flags |= 8; hypothesis)
void __fastcall Audio_Event_Set_Volume(AudioEvent *event, int volume);                   // 0x004061E0
void __fastcall Audio_Event_Set_Pan(AudioEvent *event, int pan);                         // 0x00406280
AudioEventType *__fastcall Audio_Event_Type_Of(AudioEvent *event);                       // 0x00406320 (+0x24)
// A handle the game keeps on an event: its event while the handle still
// matches (0x00406140, Audio_Event_Resolve out of line), its type (0x00406180),
// setting both (0x00406100), stopping (0x00405D50) or letting the event end
// (0x00405FE0, flags 0x60; hypothesis).
AudioEvent *__fastcall Audio_Event_Handle_Event(AudioEventHandle *handle);               // 0x00406140
AudioEventType *__fastcall Audio_Event_Handle_Type(AudioEventHandle *handle);            // 0x00406180
void __fastcall Audio_Event_Handle_Set(AudioEventHandle *handle, AudioEvent *event, AudioEventType *type);  // 0x00406100
void __fastcall Audio_Event_Handle_Stop(AudioEventHandle *handle);                        // 0x00405D50
void __fastcall Audio_Event_Handle_Finish(AudioEventHandle *handle);                      // 0x00405FE0

// A sound effect type: its audio event type, listed in the unit's VocClass
// list (0x00AD0818) while it exists.
class VocClass {
public:
    VocClass(char const *name);                                     // 0x00713810
    ~VocClass();                                                    // 0x00713880

    static int __fastcall From_Name(char const *name);              // 0x00714940 (-1 if none)
    static VocClass *__fastcall Find(char const *name);             // 0x00714990 (0 for none or "<none>"; name hypothesis)

    bool Read_INI(CCINIClass &ini);                                 // 0x007138D0
    // Reads Sound.ini: the [Defaults] and a type for each [SoundList] entry; resets the static sounds (0x00714540).
    static void __fastcall Process(CCINIClass &ini);

    // The event type's name, "Invalid Voc" without one (inline).
    char const *Name() const { return Event != 0 ? Audio_Event_Type_Name(Event) : "Invalid Voc"; }

    AudioEventType *Event;                                          // +0x00
};

// The Sound.ini defaults ([Defaults]; hypothesis: file statics of the unit).
extern int unknown_voc_priority_7f9a6c;
extern float unknown_voc_volume_7f9a70;
extern float unknown_voc_min_volume_7f9a74;
extern unsigned int unknown_voc_type_7f9a78;
extern int unknown_voc_range_7f9a7c;
extern int unknown_voc_limit_7f9a80;
extern unsigned int unknown_voc_control_ad0850;

// The volume (0..1) and pan of a sound of a type at a coordinate, seen from
// the tactical view (0x00713F30; hypothesis).
float __fastcall Voc_Volume_At(CoordStruct const &coord, int *pan, AudioEventType *type);

// Voc_Play, Voc_Play_At, Voc_Update_At and Voc_Static_Add: shared/sound_play.hpp.

// The name of a VocType (0x00714A00; "<none>" when out of range).
char const *__fastcall Voc_Name(int voc);

#endif
