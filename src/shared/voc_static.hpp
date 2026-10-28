// The static sounds: sound effects kept playing at a coordinate (the VocClass
// unit, 0x00714290-0x0071453B: the list at 0x00AD07D0, nodes from the pool at
// 0x00AD0844, counted by Audio_Static_Sound_Count; names are hypotheses).
#ifndef RA2_SHARED_VOC_STATIC_HPP
#define RA2_SHARED_VOC_STATIC_HPP

#include "shared/audio.hpp"
#include "shared/coord.hpp"
#include "shared/voc_class.hpp"

struct VocStaticSound : AudioListNode {
    void Pause();                   // 0x00714460 (counts a pause, pauses the event)
    void Resume();                  // 0x00714480 (counts it down, resumes the event)

    UnknownAudioController Handle;  // +0x0C (the 0x14-byte game-side handle)
    CoordStruct Coord;              // +0x20
    unsigned int Flags;             // +0x2C
    volatile int PauseCount;        // +0x30
    int unknown_34;                 // +0x34
    int unknown_38;                 // +0x38 (0x3C bytes: Process 0x00714540 sizes the pool)
};
extern AudioListNode unknown_voc_static_list_ad07d0;
extern AudioPool *unknown_voc_static_pool_ad0844;

// Updates every static sound and drops the finished ones (0x00714330); lets
// the ones at a coordinate with any of the flags end (0x007143B0). Stopping and
// dropping them all is Unknown_00714410 (shared/vox_class.hpp).
void Voc_Static_Update();
void __fastcall Voc_Static_Finish_At(CoordStruct const &coord, unsigned int flags);
// Pauses (0x007144B0) and resumes (0x007144F0) every static sound.
void Voc_Static_Pause();
void Voc_Static_Resume();

#endif
