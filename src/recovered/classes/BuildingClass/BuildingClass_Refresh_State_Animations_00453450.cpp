// Refresh existing idle and active animation names for damage and garrison state.
#include "shared/building.hpp"
#include "shared/rules.hpp"
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_44ca60@BuildingClass@@QAEXPBDH_N1H@Z=0044ca60
void BuildingClass::Refresh_State_Animations_00453450()
{
    if(unknown_454[17]) {
        unknown_44c920(17,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
    }
    if(unknown_454[3]) {
        unknown_44c920(3,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
    }
    if(unknown_454[4]) {
        unknown_44c920(4,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
    }
    if(unknown_454[5]) {
        unknown_44c920(5,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
    }
    if(unknown_454[6]) {
        unknown_44c920(6,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
    }
}
