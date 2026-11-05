// Create each active house's starting objects from a common per-house unit budget.
#include "shared/multiplayer_game_mode.hpp"
#include "shared/session_state.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/lobby.hpp"
#include "shared/debug_printf.hpp"
extern "C" char const multiplayer_seed_log_7e60bc[];
// @ref _multiplayer_seed_log_7e60bc=007e60bc
bool MultiplayerGameMode::Create_Starting_Objects_005b7ce0()
{
    int starting_money = 0;
    if (unknown_session_a3d298.UnitCount > 0) {
        unsigned int owners = 0;
        for (int house_index = 0; house_index < Houses.Count(); ++house_index) {
            HouseClass *house = Houses[house_index];
            if (!house->Type->MultiplayPassive)
                owners |= 1u << Houses[house_index]->Type->ArrayIndex;
        }
        int total_cost = 0;
        int type_count = 0;
        for (int unit_index = 0; unit_index < UnitTypes.Count(); ++unit_index) {
            UnitTypeClass *type = UnitTypes[unit_index];
            if (type->AllowedToStartInMultiplayer && (owners & type->Owner) && type->TechLevel <= unknown_house_setting_7d88d8) {
                if (!Rules->BaseUnit.Is_Present(type)) {
                    ++type_count;
                    total_cost += type->Raw_Cost();
                }
            }
        }
        for (int infantry_index = 0; infantry_index < InfantryTypes.Count(); ++infantry_index) {
            InfantryTypeClass *type = InfantryTypes[infantry_index];
            if (type->AllowedToStartInMultiplayer && (owners & type->Owner) && type->TechLevel <= unknown_house_setting_7d88d8) {
                ++type_count;
                total_cost += type->Raw_Cost();
            }
        }
        if (type_count == 0) type_count = 1;
        starting_money = ((type_count / 2 + total_cost) / type_count) * unknown_session_a3d298.UnitCount;
    }
    for (int house_index = 0; house_index < Houses.Count(); ++house_index) {
        HouseClass *house = Houses[house_index];
        if (!house->Type->MultiplayPassive) {
            if (house != 0) {
                for (int player_index = 0; player_index < unknown_session_a3d298.Players.Count(); ++player_index) {
                    if (house->unknown_func_4f52f0() && Compare_Wide_007837d3(house->UIName, unknown_session_a3d298.Players[player_index]->Name) == 0) {
                        bool const &observer = unknown_session_a3d298.Players[player_index]->Team == -1;
                        if (observer) goto next_house;
                        break;
                    }
                }
            }
            int money = starting_money;
            if (!unknown_slot43(house, &money) || !unknown_slot44(house, &money)) return false;
            if (money > 0) house->Refund_Money(money);
            // These four 16-byte fields contain CounterClass objects, whose public base is VectorClass<int>.
            reinterpret_cast<VectorClass<int> *>(&house->unknown_54a0)->Clear();
            reinterpret_cast<VectorClass<int> *>(&house->unknown_54d0)->Clear();
            reinterpret_cast<VectorClass<int> *>(&house->unknown_54c0)->Clear();
            reinterpret_cast<VectorClass<int> *>(&house->unknown_54b0)->Clear();
        }
next_house:
        ;
    }
    int seed = Random_Pick(0, 0xffff);
    Debug_Printf(multiplayer_seed_log_7e60bc, seed);
    return true;
}
