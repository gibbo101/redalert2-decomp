// Resume queued orders, finish piggybacking and settle an otherwise idle foot.
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
#include "shared/waypoint_path.hpp"
#include "shared/unknown_geometry.hpp"
extern "C" GUID const unknown_uuid_IPiggyback_7cfc30;
// @ref _unknown_uuid_IPiggyback_7cfc30=007cfc30
// @ref ?Query@?$UnknownComPtr@UIPiggyback@@$1?unknown_uuid_IPiggyback_7cfc30@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454c70
// @ref ?unknown_slot261@TechnoClass@@UAE_N_N0@Z=006d48f0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Get_Waypoint@WaypointPathClass@@QAEPAUWaypointClass@@H@Z=00724d60
// @ref ?Next_Waypoint@WaypointPathClass@@QAEPAUWaypointClass@@PBUWaypointClass@@@Z=00724f80
bool FootClass::unknown_slot261(bool initial,bool resume_waypoint)
{
    if (!unknown_59d) {
        unknown_59d=true;
        TechnoClass::unknown_slot261(initial,resume_waypoint);
        if (unknown_577) {
            unknown_577=false;
            unknown_slot87(unknown_geometry_l,true,false);
        }
        bool was_piggybacking=false;
        UnknownComPtr<IPiggyback,&unknown_uuid_IPiggyback_7cfc30> piggyback(Locomotor);
        if (piggyback && piggyback.Checked()->Is_Ok_To_End()) {
            Locomotor.Attach(0);
            piggyback.Checked()->End_Piggyback(&Locomotor.Pointer);
            was_piggybacking=true;
        }
        if (unknown_478.Count()>0) {
            unknown_slot260(unknown_478[0],0);
            unknown_478.Delete(0);
            return true;
        }
        if (Mission!=25 || unknown_a8==0) {
            if (unknown_418!=-1 && resume_waypoint) {
                WaypointClass *waypoint=unknown_player_a35db4->WaypointPaths[unknown_418]->Get_Waypoint(unknown_576);
                WaypointClass *next_waypoint=unknown_player_a35db4->WaypointPaths[unknown_418]->Next_Waypoint(waypoint);
                unknown_4cb110(next_waypoint);
            }
        }
        if (was_piggybacking) return true;
        if (Kind_Of()==15 && unknown_1b0) {
            if (Coord_Cell(unknown_1b0->Center_Coord())!=Coord_Cell(Center_Coord())) {
                AbstractClass *target=unknown_1b0;
                if (Mission!=11) {
                    unknown_slot116(2,false);
                    unknown_6d6e50(0);
                }
                unknown_slot260(target,1);
            }
        }
        unknown_slot306(0.0);
    }
    return false;
}
