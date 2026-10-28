// The audio stream file layer (0x00522B20-0x00522E00, unit before the isometric tile code): one stdio file
// feeding a ring queue, guarded by a critical section. Placeholders named by address until recovered.
#ifndef RA2_SHARED_AUDIO_FILE_HPP
#define RA2_SHARED_AUDIO_FILE_HPP

#include "shared/audio.hpp"

extern CRITICAL_SECTION unknown_audio_file_lock_a52280;     // 0x00A52280
extern "C" int DAT_00a522ac;                    // 0x00A522AC the file's mode (1: read at close, 2: opened to read)
extern "C" int DAT_00a522b0;                    // 0x00A522B0 the layer is set up
extern "C" int DAT_00a522c4;                    // 0x00A522C4
extern "C" AudioQueue *DAT_00a522c8;            // 0x00A522C8 the queue the opened file feeds
extern "C" AudioQueue *DAT_00a522cc;            // 0x00A522CC the queue the open file is flushed into
extern "C" void *DAT_00a522d0;                  // 0x00A522D0 the open stdio file
extern "C" int DAT_00a522d4;                    // 0x00A522D4 set when the first fill failed

#endif
