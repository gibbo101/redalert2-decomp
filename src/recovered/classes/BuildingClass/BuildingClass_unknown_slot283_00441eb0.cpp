// Building production options available to the local player's sidebar.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/house.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
void BuildingClass::unknown_slot283()
{
    if (House == unknown_player_a35db4 && !unknown_76 && unknown_373 && unknown_530) {
        switch (Type->Factory) {
        case 7: {
            for (int index = 0; index < BuildingTypes.Count(); ++index) {
                if (unknown_player_a35db4->unknown_4e3660(BuildingTypes[index], 0, 1))
                    Map.Unknown_0067C530(7, index);
            }
            break;
        }
        case 40: {
            for (int index = 0; index < UnitTypes.Count(); ++index) {
                if (unknown_player_a35db4->unknown_4e3660(UnitTypes[index], 0, 1))
                    Map.Unknown_0067C530(40, index);
            }
            break;
        }
        case 16: {
            for (int index = 0; index < InfantryTypes.Count(); ++index) {
                if (unknown_player_a35db4->unknown_4e3660(InfantryTypes[index], 0, 1))
                    Map.Unknown_0067C530(16, index);
            }
            break;
        }
        case 3: {
            for (int index = 0; index < AircraftTypes.Count(); ++index) {
                if (unknown_player_a35db4->unknown_4e3660(AircraftTypes[index], 0, 1))
                    Map.Unknown_0067C530(3, index);
            }
            break;
        }
        }
    }
}
