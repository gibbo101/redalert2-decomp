// void RadarEventClass_unknown_all_63b910() -- 0x0063B910
// Purpose: runs 0x0063B940 on every radar event of the list at 0x00AB67E8.
// Assumptions: 0x0063B940 is a RadarEventClass member taking no arguments
// (its meaning is unidentified); names are hypotheses.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
// @ref ?unknown_radar_events_ab67e8@@3V?$DynamicVectorClass@PAVRadarEventClass@@@@A=00ab67e8
// @ref ?Unknown_0063B940@RadarEventClass@@QAEXXZ=0063b940

class RadarEventClass {
public:
    void Unknown_0063B940();
};
extern DynamicVectorClass<RadarEventClass *> unknown_radar_events_ab67e8;

void RadarEventClass_unknown_all_63b910()
{
    for (int index = 0; index < unknown_radar_events_ab67e8.Count(); index++) {
        unknown_radar_events_ab67e8[index]->Unknown_0063B940();
    }
}
