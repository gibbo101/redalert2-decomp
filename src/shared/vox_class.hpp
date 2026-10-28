// EVA voices (VoxClass): Find_Index 0x00716640 (-1 for a null name).
// shared/radar.hpp and shared/wdt_voices.hpp declare the same function as
// Unknown_00716640 (proposal: use this declaration).
#ifndef RA2_SHARED_VOX_CLASS_HPP
#define RA2_SHARED_VOX_CLASS_HPP

class VoxClass {
public:
    static int __fastcall Find_Index(char const *name);    // 0x00716640
    static char const *__fastcall Name_From(int index);    // 0x007158A0 ("none" out of range; name hypothesis)
    static void __fastcall Set_Volume(int volume);         // 0x00715EF0 (at most 255; OptionsClass voice volume)
};

// Speech by name (0x00715B40; hypothesis: VoxClass::Speak; returns what the
// play call 0x007158C0 returns). Was void in shared/foot.hpp.
int __fastcall Unknown_00715B40(char const *name, int arg2, int arg3);
// Stops the voice (EVA) speech (0x00715DE0; argument meaning unknown) and
// whether a voice is playing (0x00715E20). Names are hypotheses.
void __fastcall Speech_Stop(bool unknown);
bool Speech_Is_Playing();
// Speech queue helpers (0x00714410 releases the queued entries of the list at
// 0x00AD07D0; 0x007160D0 calls 0x00407E60 on the object at 0x00AD0968; Do_Restart
// and Clear_Scenario call them); meanings not recovered.
void Unknown_00714410();
void __fastcall Unknown_007160D0();

#endif
