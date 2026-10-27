// The event layer of the audio library is plain C that the compiler did not
// expand functions in: where the binary has a step inline the source writes it
// out (these macros), where the binary calls Audio_Event_Detach or
// Audio_Event_Release_Samples the source calls them. The event code is built with
// /Ob1, which expands only functions marked inline, so ordinary calls stay calls.
// Include this instead of audio.hpp from the event code (0x00403EB0-0x00406880).
#ifndef RA2_SHARED_AUDIO_EVENT_HPP
#define RA2_SHARED_AUDIO_EVENT_HPP

#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

#define AUDIO_EVENT_DETACH_INLINE(event) \
    { \
        if ((event)->Channel != 0 && (event) == (event)->Channel->Owner) { \
            if ((event)->Flags & 2) { \
                Audio_Channel_Stop((event)->Channel); \
            } \
            Audio_Channel_Clear_Flag_10((event)->Channel); \
            (event)->Channel->Owner = 0; \
            (event)->Channel->unknown_end_callback_bc = 0; \
            (event)->Channel->unknown_loop_b4 = 0; \
            (event)->Channel->unknown_done_b8 = 0; \
            (event)->Channel->unknown_levels_90 = 0; \
            (event)->Channel->unknown_levels_98 = 0; \
            (event)->Channel->unknown_levels_9c = 0; \
            (event)->Channel = 0; \
        } \
    }

#define AUDIO_EVENT_RELEASE_SAMPLES_INLINE(event) \
    { \
        for (int i = 0; i < (event)->SampleCount; i++) { \
            ((AudioCountedList *)(event)->Samples[i])->Leave(); \
            (event)->Samples[i] = 0; \
        } \
        (event)->SampleCount = 0; \
    }

#define AUDIO_EVENT_MARK_STOPPED(event) \
    { \
        (event)->State = 4; \
        (event)->unknown_138 = 0; \
        (event)->unknown_278 = 0; \
        (event)->Flags |= AUDIO_EVENT_STOPPED; \
    }

#define AUDIO_EVENT_FREE_INLINE(event) \
    { \
        Audio_List_Remove(event); \
        (event)->unknown_138 = 0; \
        if ((event)->Flags & AUDIO_EVENT_ALLOCATED) { \
            operator delete(event); \
        } else { \
            Audio_Pool_Free(Audio_Event_Pool, event); \
        } \
        Audio_Event_Count--; \
    }


#endif
