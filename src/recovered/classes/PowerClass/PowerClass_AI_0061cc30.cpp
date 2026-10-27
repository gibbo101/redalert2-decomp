// void PowerClass::AI(int &input, Point2D const &xy) (0x0061CC30, slot 10)
// While the power bar is shown: counts the first counter down once per
// expiry of the first timer (redrawing the bar), restarts it when the
// player's power output or drain changed, then once per expiry of the
// second timer moves one of the three counters a step toward its target
// and restarts that timer for the share of the bar they fill. Ends with
// the radar's AI.
#include "shared/power.hpp"
#include "shared/tool_tip.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_flag_8373c1@@3_NA=008373c1
// @ref ?unknown_flag_8373c2@@3_NA=008373c2
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?AI@RadarClass@@UAEXAAHABUPoint2D@@@Z=0062fcc0
// @ref ?Unknown_0061C700@PowerClass@@QAEHAAH00@Z=0061c700
// @ref ?Unknown_0061C5F0@PowerClass@@QAEHXZ=0061c5f0
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref __real@8@4001a000000000000000=0079c278
// @ref __ftol=0077f110

void PowerClass::AI(int &input, Point2D const &xy)
{
    if (unknown_flag_8373c1) {
        if (!unknown_1534 && unknown_1518 > 0 && unknown_150c.Value() == 0) {
            unknown_1508 = true;
            unknown_1518--;
            unknown_flag_8373c2 = true;
            Map.Flag_To_Redraw(false);
            unknown_150c = 3;
        }
        if (unknown_player_a35db4->Power_Drain() != unknown_1538 || unknown_player_a35db4->Power_Output() != unknown_153c || unknown_1534) {
            unknown_1508 = true;
            unknown_flag_8373c2 = true;
            Map.Flag_To_Redraw(false);
            if (unknown_player_a35db4->Power_Drain() != unknown_1538 || unknown_player_a35db4->Power_Output() != unknown_153c) {
                unknown_1534 = true;
                unknown_1518 = 10;
                unknown_150c = 3;
            }
            unknown_1538 = unknown_player_a35db4->Power_Drain();
            unknown_153c = unknown_player_a35db4->Power_Output();
            int target_1528;
            int target_152c;
            int target_1530;
            Unknown_0061C700(target_1528, target_152c, target_1530);
            if (unknown_151c.Value() == 0) {
                unknown_1534 = false;
                if (unknown_1530 != target_1530) {
                    unknown_1534 = true;
                    if (unknown_1530 > target_1530) {
                        unknown_1530--;
                        Unknown_0061CBC0();
                    } else {
                        unknown_1530++;
                        Unknown_0061CB50();
                    }
                } else if (unknown_1528 != target_1528) {
                    unknown_1534 = true;
                    if (unknown_1528 > target_1528) {
                        unknown_1528--;
                        Unknown_0061CBC0();
                    } else {
                        unknown_1528++;
                        Unknown_0061CB50();
                    }
                } else if (unknown_152c != target_152c) {
                    unknown_1534 = true;
                    if (unknown_152c > target_152c) {
                        unknown_152c--;
                        Unknown_0061CBC0();
                    } else {
                        unknown_152c++;
                        Unknown_0061CB50();
                    }
                }
                if (unknown_1534) {
                    int segments = Unknown_0061C5F0();
                    int total = unknown_152c + unknown_1528 + unknown_1530;
                    if (total > segments) {
                        total = segments;
                    }
                    unknown_151c = (int)((double)total / segments * 5.0);
                }
            }
        }
    }
    RadarClass::AI(input, xy);
}
