// UnknownFrameTiming::UnknownFrameTiming() (0x00623210): an empty frame-sync
// record (frame -1). Out of line; the array initializers 0x00623230 and
// 0x006232D0 expand it.
#include "shared/queue.hpp"

UnknownFrameTiming::UnknownFrameTiming() :
    Frame(-1),
    unknown_04(0),
    unknown_08(0),
    unknown_0c(0),
    unknown_10(0),
    unknown_14(0)
{
}
