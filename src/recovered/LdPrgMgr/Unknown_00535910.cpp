// Unknown535910 *Unknown_00535910() -- 0x00535910
// Makes the loading progress object once and returns it.
#include "shared/unknown_globals.hpp"
// @ref ?unknown_load_progress_a6e7c4@@3PAUUnknown535910@@A=00a6e7c4
// @ref ??_7Unknown535910@@6B@=007a549c

Unknown535910 *Unknown_00535910()
{
    if (unknown_load_progress_a6e7c4 == 0) {
        unknown_load_progress_a6e7c4 = new Unknown535910;
    }
    return unknown_load_progress_a6e7c4;
}
