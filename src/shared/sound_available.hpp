// The sound-available check at 0x00406F30 (nonzero when the sound system can
// play; callers test EAX, and the font and movie code ignore it).
#ifndef RA2_SHARED_SOUND_AVAILABLE_HPP
#define RA2_SHARED_SOUND_AVAILABLE_HPP

int unknown_check_406f30();                     // 0x00406F30 sound available

#endif
