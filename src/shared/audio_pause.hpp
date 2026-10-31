// The game sound pause around movies (0x005A09E0-0x005A0B4F, beside the radar's movie queue): the
// flag 0x00A7101C, the pause and resume pair and the queue's clear and count. Names are hypotheses.
#ifndef RA2_SHARED_AUDIO_PAUSE_HPP
#define RA2_SHARED_AUDIO_PAUSE_HPP

// The game sound is paused (0x00A7101C).
extern bool unknown_audio_paused_a7101c;
// Runs the sound object 0x00AD095C and counts 0x00AD08C8 down (0x007169F0; accepted elsewhere).
void unknown_tick_sound();
// Deletes every queued movie, empties the queue and resumes the sound (0x005A09E0).
void Unknown_Clear_Movies_005a09e0();
// Whether a movie is queued (0x005A0AB0).
bool Unknown_Movies_Queued_005a0ab0();
// Resumes the paused sound: releases and resumes the streams, fades them in, sets the global levels 7 and 5
// back to full volume (0x005A0AC0).
void Unknown_Audio_Resume_005a0ac0();
// Pauses the sound: holds the speech and the streams, halves the global levels 7 and 5 (0x005A0B10).
void Unknown_Audio_Pause_005a0b10();

#endif
