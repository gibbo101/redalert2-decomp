// int PowerClass::Unknown_0061C700(int &target_1528, int &target_152c, int &target_1530) (0x0061C700)
// The three power bar counters' targets: the segments 0x0061C5F0 leaves are
// split by the shares of the player's drain (target_1530), of the surplus
// output up to 100 (target_152c) and of the rest of
// the surplus (target_1528); what the truncations lose goes to
// target_1530. Returns the bar's segment count (0x0061C6E0).
#include "shared/power.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_int_abcd70@@3HA=00abcd70
// @ref ?Unknown_0061C5F0@PowerClass@@QAEHXZ=0061c5f0
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@4005c800000000000000=0079b7f0
// @ref __real@8@3ff8a3d70a3d70a3d800=0079c518
// @ref __ftol=0077f110

int PowerClass::Unknown_0061C700(int &target_1528, int &target_152c, int &target_1530)
{
    int segments = Unknown_0061C6E0();
    int count = Unknown_0061C5F0();
    int surplus = unknown_player_a35db4->Power_Output() - unknown_player_a35db4->Power_Drain();
    double value = surplus;
    double first = 100.0;
    double second;
    if (value < 0.0) {
        first = 0.0;
        second = 0.0;
    } else {
        if (value < 100.0) {
            first = value;
        }
        second = value - first;
    }
    double drain_share = 1.0;
    double second_share = 0.0;
    double first_share = 0.0;
    double total = unknown_player_a35db4->Power_Drain();
    total += first;
    total += second;
    if (total > 0.0) {
        drain_share = unknown_player_a35db4->Power_Drain() / total;
        second_share = second / total;
        first_share = first / total;
    }
    double bar = count;
    double drain_part = bar * drain_share;
    target_1530 = (int)drain_part;
    double first_part = bar * first_share;
    target_152c = (int)first_part;
    double second_part = bar * second_share;
    target_1528 = (int)second_part;
    target_1530 = (int)((first_part - target_152c) + (second_part - target_1528) + (drain_part - target_1530) + target_1530 + 0.01);
    return segments;
}
