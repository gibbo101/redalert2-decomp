// Grant building-provided super weapons; original004F4DB0.
#include "shared/building_class.hpp"
#include "shared/map_view.hpp"
void HouseClass::Enable_Available_Super_Weapons_004f4db0()
{
    if (unknown_13d) return;
    for (int super_index=0;super_index<Supers.Count();++super_index) {
        if (!Supers[super_index]->Is_Present() || Supers[super_index]->Is_One_Time()) {
            bool from_upgrade=false;
            int building_index=Buildings.Count()-1;
            if (building_index>=0) while (true) {
                BuildingClass *building=Buildings[building_index];
                if (building->unknown_7d && !building->unknown_76) {
                    for (int upgrade_index=0;upgrade_index<3;++upgrade_index) {
                        BuildingTypeClass *upgrade=(BuildingTypeClass *)building->unknown_4c0[upgrade_index];
                        if (upgrade && (upgrade->SuperWeapon==super_index || upgrade->SuperWeapon2==super_index)) {
                            from_upgrade=true;
                            break;
                        }
                    }
                    if (building->unknown_452800()==super_index || building->unknown_452860()==super_index || from_upgrade) {
                        Supers[super_index]->Grant(false,this==unknown_player_a35db4,Power_Fraction()<1.0);
                        if (this==unknown_player_a35db4) {
                            Map.Unknown_0067C530(31,super_index);
                            int type_index=Supers[super_index]->Type->unknown_slot16();
                            Map.Unknown_0067C2D0(Unknown_006818D0(57,type_index,0));
                        }
                        break;
                    }
                }
                --building_index;
                if (building_index<0) break;
            }
        }
    }
}
