// bool MultiplayerSiege::unknown_slot43(HouseClass *house, int *money) -- 0x005ABA80
// The defenders (session team 1) get a construction yard (the first type of Rules +0x7C8
// the house may build) at their BaseCenter, or near it; every other player gets the
// base behaviour. A house without a session player gets the base behaviour and false.
// @ref ?unknown_slot43@MultiplayerGameMode@@UAE_NPAVHouseClass@@PAH@Z=005b7f90
// @ref ?Unknown_00660b60@@YIHPAVObjectClass@@AAVCell@@H@Z=00660b60
#include "shared/building_class.hpp"
#include "shared/id_source.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/multiplayer_game_mode.hpp"

bool MultiplayerSiege::unknown_slot43(HouseClass *house, int *money)
{
    int index;
    for (index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        if (unknown_players_a3fa7c[index]->ID == house->ArrayIndex) {
            break;
        }
    }
    if (index >= unknown_players_a3fa7c.Count()) {
        MultiplayerGameMode::unknown_slot43(house, money);
    } else {
        if (unknown_players_a3fa7c[index]->Team != 1) {
            return MultiplayerGameMode::unknown_slot43(house, money);
        }
        BuildingTypeClass *type = house->unknown_func_4ef600(Rules->unknown_7c8);
        if (type != 0) {
            TechnoClass *building = (TechnoClass *)new BuildingClass(type, house);
            if (building != 0) {
                CoordStruct &center = house->BaseCenter;
                if (!building->unknown_slot53(&center, 0)) {
                    Cell cell = Cell(center.X / 256, center.Y / 256);
                    if (!Unknown_00660b60(building, cell, 1)) {
                        delete building;
                        return false;
                    }
                }
                return true;
            }
        }
    }
    return false;
}
