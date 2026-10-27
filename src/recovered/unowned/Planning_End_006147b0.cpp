#define RA2_COORD_EQUAL_MEMBER
// void Planning_End() (0x006147B0)
// Ends planning mode: sends the release event, forgets the remembered nodes,
// plays the end sound and notifies the sink.
#include "shared/planning.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_flag_a767a4@@3_NA=00a767a4
// @ref ?unknown_sink_a76680@@3PAUUnknownPlanningSink@@A=00a76680
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ??0EventClass@@QAE@HH@Z=004b5fd0
// @ref ?Unknown_0062E670@@YGXVEventClass@@@Z=0062e670

void Planning_End()
{
    if (unknown_flag_a767a4) {
        EventClass event(unknown_player_a35db4->ArrayIndex, 0x2B);
        Unknown_0062E670(event);
        unknown_node_a7678c = 0;
        unknown_node_a766f8 = 0;
        unknown_node_a766b0 = 0;
        unknown_flag_a767a4 = false;
        Unknown_00713DB0(Rules->unknown_1d8, 1.0f, 0x2000, 0);
        if (unknown_sink_a76680) {
            unknown_sink_a76680->Unknown_Slot0(0x11C8, 0);
        }
    }
}
