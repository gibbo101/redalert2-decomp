// Aircraft placement (00414020,slot53); preserve ordered type/map/weapon reads.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_0055A7F0@MapClass@@QAE_NABUCoordStruct@@@Z=0055a7f0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?unknown_slot53@FootClass@@UAE_NPBUCoordStruct@@H@Z=004c5e40
// @ref ?Set_Current@FacingClass@@QAEXABUUnknownFacingDir@@@Z=004b8b10
// @ref ?Frame@@3HA=00a40d2c
bool AircraftClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    CoordStruct placed = *coord;
    if (!Type->MissileSpawn) {
        if (!unknown_32c && Map.Unknown_0055A7F0(*coord)) {
            placed.Z = Map.Unknown_0055A280(*coord);
        } else {
            AircraftTypeClass *type = Type;
            placed.Z = Map.Unknown_0055A280(*coord) + type->Flight_Level();
        }
    }
    if (FootClass::unknown_slot53(&placed, dir)) {
        if (!(Type->unknown_200 && Type->Landable) ||
            (unknown_slot231(0)->WeaponType && unknown_slot231(0)->WeaponType->unknown_11f))
            unknown_32c = true;
        if (Cargo.Object) unknown_5b1 = true;
        unknown_2f8.Set_Current(UnknownFacingDir((unsigned short)((unsigned char)dir << 8)));
        AnimationStage.Set_Rate(1);
        AnimationStage.Value = 0;
        int altitude = Type->Flight_Level();
        if (unknown_slot108() == altitude) unknown_slot306(1.0);
        else unknown_slot306(0.0);
        return true;
    }
    return false;
}
