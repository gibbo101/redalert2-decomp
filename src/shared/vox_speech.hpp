// The EVA speech queue of the VoxClass unit (0x007156D0-0x00715EF0): the
// stream that plays the speeches, a node for each waiting speech and the lists
// it waits in (names are hypotheses; Speech_Stop, Speech_Clear, Speech_Play
// and Speech_Shutdown are in shared/vox_class.hpp).
#ifndef RA2_SHARED_VOX_SPEECH_HPP
#define RA2_SHARED_VOX_SPEECH_HPP

#include "shared/audio.hpp"
#include "shared/vox_class.hpp"

// A waiting speech (0x20 bytes, operator new).
struct VoxSpeech : AudioListNode {
    VoxClass *Vox;                  // +0x0C
    int unknown_10;
    int Priority;                   // +0x14
    int Type;                       // +0x18
    int Serial;                     // +0x1C the queue serial modulo 100

    // The speech's type and priority, each when asked for (inline).
    void Get(int *type, int *priority) const
    {
        if (type != 0) {
            *type = Type;
        }
        if (priority != 0) {
            *priority = Priority;
        }
    }
};

extern int unknown_vox_type_ad0858;                 // the type of the speech playing
extern AudioListNode unknown_vox_list_ad0868;       // type 3 speeches
extern int unknown_vox_ad0878;                      // nonzero: no speech is queued
extern int unknown_vox_priority_ad0880;             // the priority of the speech playing
extern AudioListNode unknown_vox_list_ad0890;       // priority 3 speeches
extern int volatile unknown_countdown_ad08c8;       // nonzero: no speech starts
extern AudioListNode unknown_vox_lists_ad08e0[4];   // type 1 speeches by priority
extern VoxSpeech *unknown_vox_pending_ad0948;       // the one other speech waiting
extern int unknown_vox_enabled_ad094c;
extern int unknown_vox_serial_ad0950;
extern VoxClass *unknown_vox_playing_ad0954;
extern int unknown_flag_ad0958;                     // nonzero: the Russian speech files
extern AudioStreamPlayer *unknown_vox_stream_ad095c;
extern unsigned __int64 unknown_vox_delay_ad0960;   // the gap after the last speech

// Empties the lists and makes the stream (0 without one; 0x007156D0).
int Speech_Init();
// Queues a speech of a VoxClass (0x007159D0).
void __fastcall Speech_Queue(VoxClass *vox, int type, int priority);
// The waiting speech of a VoxClass, 0 for none (0x00715AC0).
VoxSpeech *__fastcall Speech_Find(VoxClass *vox);
// Starts the next waiting speech once the stream is free (0x00715BA0).
void Speech_Update();

#endif
