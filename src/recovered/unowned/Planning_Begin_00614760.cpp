#define RA2_COORD_EQUAL_MEMBER
// void Planning_Begin() (0x00614760)
// Starts planning mode: sets the flag, plays the start sound and notifies the sink.
#include "shared/planning.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_flag_a767a4@@3_NA=00a767a4
// @ref ?unknown_sink_a76680@@3PAUUnknownPlanningSink@@A=00a76680

void Planning_Begin()
{
    if (!unknown_flag_a767a4) {
        unknown_flag_a767a4 = true;
        Voc_Play(Rules->unknown_1cc, 1.0f, 0x2000, 0);
        if (unknown_sink_a76680) {
            unknown_sink_a76680->Unknown_Slot0(0x11C7, 0);
        }
    }
}
