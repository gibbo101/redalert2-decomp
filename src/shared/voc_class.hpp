// VocClass: the sound effect types (Sound.ini entries).
#ifndef RA2_SHARED_VOC_CLASS_HPP
#define RA2_SHARED_VOC_CLASS_HPP

struct AudioEventType;
class CCINIClass;

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

// A sound effect type: its audio event type, listed in the unit's VocClass
// list (0x00AD0818) while it exists.
class VocClass {
public:
    VocClass(char const *name);                                     // 0x00713810
    ~VocClass();                                                    // 0x00713880

    static int __fastcall From_Name(char const *name);              // 0x00714940 (-1 if none)

    bool Read_INI(CCINIClass &ini);                                 // 0x007138D0

    // The event type's name, "Invalid Voc" without one (inline).
    char const *Name() const { return Event != 0 ? Audio_Event_Type_Name(Event) : "Invalid Voc"; }

    AudioEventType *Event;                                          // +0x00
};

// The name of a VocType (0x00714A00; "<none>" when out of range).
char const *__fastcall Voc_Name(int voc);

#endif
