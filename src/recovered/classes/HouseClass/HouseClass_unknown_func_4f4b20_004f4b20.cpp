// void HouseClass::unknown_func_4f4b20() (0x004F4B20)
// TibSun Update_Present_Super_Weapons: for each super weapon present that needs a building (or
// when the house is defeated), find a building or upgrade that grants it, drop it when power is
// short, suspend or resume it, or remove it when nothing grants it any more. A change clears
// the pending target and redraws the sidebar for the player's house.
// `on` and `alive` are not in TibSun. `on` stops known-value threading of the flag, so the
// second test stays; the second named negation sets the compare order of the Fetch_ID pair.
#include "shared/building_class.hpp"
#include "shared/map_view.hpp"
void HouseClass::unknown_func_4f4b20()
{
    if (!unknown_flag_a40958) return;
    bool is_player = unknown_player_a35db4 == this;
    for (int s = 0; s < Supers.Count(); ++s) {
        if (Supers[s]->Is_Present() && ((Supers[s]->unknown_0x48 && !Supers[s]->Is_One_Time()) || unknown_13d)) {
            bool present = false;
            bool enabled = false;
            bool alive = !unknown_13d;
            if (alive) {
                for (int j = 0; j < unknown_BuildingClass_list_00a40af8.Count(); ++j) {
                    BuildingClass *b = unknown_BuildingClass_list_00a40af8[j];
                    if (!b->unknown_76 && b->unknown_7d && b->House->Fetch_ID() == Fetch_ID()) {
                        for (int k = 0; k < 3; ++k) {
                            BuildingTypeClass *upgrade = (BuildingTypeClass *)b->unknown_4c0[k];
                            if (upgrade && (upgrade->SuperWeapon == s || upgrade->SuperWeapon2 == s)) {
                                present = true;
                                if (!enabled) enabled = b->unknown_530;
                            }
                        }
                        if (b->unknown_452800() == s || b->unknown_452860() == s) {
                            present = true;
                            if (enabled) break;
                            enabled = b->unknown_530;
                        }
                        if (enabled && present) break;
                    }
                }
            }
            int power = Power;
            int drain = Drain;
            if (power < drain && drain != 0) {
                if (power == 0 || (double)power / (double)drain < 1.0) {
                    enabled = false;
                }
            }
            int type_id = Supers[s]->Type->unknown_slot16();
            int type_index = Unknown_006818D0(57, type_id, 0);
            if (present && !unknown_13d) {
                bool const &on = enabled;
                bool off = !on;
                if ((off && Supers[s]->Is_Powered() && Supers[s]->Suspend(true)) || (enabled && Supers[s]->Suspend(false))) {
                    if (is_player) {
                        if (unknown_pending_super_833694 == s) unknown_pending_super_833694 = -1;
                        Map.Unknown_0067C2D0(type_index);
                    }
                    unknown_144 = true;
                }
            } else {
                if (Supers[s]->Remove() && unknown_player_a35db4 != 0) {
                    if (is_player) {
                        if (unknown_pending_super_833694 == s) unknown_pending_super_833694 = -1;
                        Map.Unknown_0067C2D0(type_index);
                    }
                    unknown_144 = true;
                }
            }
        }
    }
}
