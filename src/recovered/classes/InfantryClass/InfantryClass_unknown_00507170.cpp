// Thief capture and pursuit of an enemy vehicle; +0xC13 is the shared Thief flag.
#include "shared/infantry.hpp"
#include "shared/tag.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?Spring@TagClass@@=006b3df0
// @ref ?unknown_func_6b41f0@TagClass@@=006b41f0
// @ref ?Attach_Tag@ObjectClass@@=005d4430

bool InfantryClass::unknown_507170()
{
    if (!Type->Thief || !unknown_494 || unknown_494->Kind_Of()!=1) return false;
    TechnoClass *vehicle=static_cast<TechnoClass *>(unknown_494);
    if (House->Is_Ally(vehicle)) return false;
    // The destination query receives the requesting infantry.
    CoordStruct coord=vehicle->unknown_slot19(this);
    int vehicle_z=coord.Z;
    coord=Center_Coord();
    if (abs(vehicle_z-coord.Z)<unknown_geometry_g) {
        if ((reinterpret_cast<UnknownVector3 const &>(Center_Coord())-reinterpret_cast<UnknownVector3 const &>(vehicle->Center_Coord())).Length()<128) {
            if (vehicle->unknown_34) vehicle->unknown_34->Spring(1,this,unknown_geometry_k,false,0);
            vehicle->unknown_slot149(3);
            vehicle->unknown_slot54(false);
            if (unknown_34 && unknown_34->unknown_func_6b41f0()) vehicle->Attach_Tag(unknown_34);
            vehicle->unknown_slot222(House,1);
            vehicle->unknown_290=Type->ArrayIndex;
            unknown_slot60();
            return true;
        }
    }
    if ((reinterpret_cast<UnknownVector3 const &>(Center_Coord())-reinterpret_cast<UnknownVector3 const &>(vehicle->Center_Coord())).Length()<512) {
        if (UnknownCoord434820(Locomotor.Checked()->Destination())!=unknown_geometry_l) {
            if (reinterpret_cast<UnknownVector3 const &>(vehicle->Center_Coord()).Distance_To(reinterpret_cast<UnknownVector3 const &>(UnknownCoord434820(Locomotor.Checked()->Destination())))<=128) return false;
        }
        unknown_slot260(unknown_494,1);
    } else {
        if (UnknownCoord434820(Locomotor.Checked()->Destination())!=unknown_geometry_l) {
            if (Coord_Cell(vehicle->unknown_slot19(this))==Coord_Cell(UnknownCoord434820(Locomotor.Checked()->Destination()))) return false;
        }
    }
    // The original calls this again after the near-target branch.
    unknown_slot260(unknown_494,1);
    return false;
}
