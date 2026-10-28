// EVA voices (VoxClass): Find_Index 0x00716640 (-1 for a null name).
// shared/radar.hpp and shared/wdt_voices.hpp declare the same function as
// Unknown_00716640 (proposal: use this declaration).
#ifndef RA2_SHARED_VOX_CLASS_HPP
#define RA2_SHARED_VOX_CLASS_HPP

class CCINIClass;

class VoxClass {
public:
    VoxClass(char const *name);                            // 0x007160E0 (added to the unit's VoxClass list)
    ~VoxClass();                                           // 0x00716190

    static int __fastcall Find_Index(char const *name);    // 0x00716640
    static char const *__fastcall Name_From(int index);    // 0x007158A0 ("none" out of range; name hypothesis)
    static VoxClass *__fastcall Find(char const *name);    // 0x007166C0 (0 for none or "<none>"; name hypothesis)
    static int __fastcall Index_Of(VoxClass *vox);         // 0x00716740 (-1 for none; name hypothesis)
    static void __fastcall Set_Volume(int volume);         // 0x00715EF0 (at most 255; OptionsClass voice volume)

    // Reads the VoxClass's EVA.ini section: volume, type, priority and the two
    // file names; false without the section (0x007161E0).
    bool Read_INI(CCINIClass &ini);

    char Name[0x28];                // +0x00 the EVA.ini section
    float Volume;                   // +0x28
    char Russian[9];                // +0x2C the Soviet speech file ("Russian"; played with ".WAV")
    char Allied[9];                 // +0x35 the Allied speech file ("Allied")
    int Priority;                   // +0x40 (0..3)
    int Type;                       // +0x44 (0..3; 2 interrupts, 3 is queued first)
    int State;                      // +0x48 0 playing, 1 queued, 2 neither
};

// Plays the VoxClass of a name (nothing for a null name; 0x00715B40; name
// hypothesis): Speech_Play(VoxClass::Find_Index(name), type, priority).
void __fastcall Speech_Play_Name(char const *name, int type, int priority);
// Stops the voice (EVA) speech (0x00715DE0; argument meaning unknown) and
// whether a voice is playing (0x00715E20). Names are hypotheses.
void __fastcall Speech_Stop(bool clear);
bool Speech_Is_Playing();
// The EVA speech queue (shared/vox_speech.hpp): drops every waiting speech
// (0x007157B0); clears it and destroys the stream (0x00715780); plays the
// VoxClass at an index, -1 for the type or priority taking its own (0x007158C0).
void Speech_Clear();
void Speech_Shutdown();
void __fastcall Speech_Play(int index, int type, int priority);
// Speech queue helpers (0x00714410 releases the queued entries of the list at
// 0x00AD07D0; 0x007160D0 calls 0x00407E60 on the object at 0x00AD0968; Do_Restart
// and Clear_Scenario call them); meanings not recovered.
void Unknown_00714410();
void __fastcall Unknown_007160D0();

#endif
