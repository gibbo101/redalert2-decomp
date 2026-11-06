// bool TActionClass::Execute(...) (0x006ADAE0)
// Performs the action: a switch over its type, most types handled by their own member (an inactive object is passed as none); types without a handler succeed.
#include "shared/taction.hpp"
#include "shared/object.hpp"
// @ref ?unknown_damage_006afd80@TActionClass@@QAE_NPAVHouseClass@@PAVObjectClass@@PAVTriggerClass@@PAVCell@@@Z=006afd80
// @ref ?unknown_iron_curtain_at_waypoint@TActionClass@@QAE_NPAVHouseClass@@PAVObjectClass@@PAVTriggerClass@@PAVCell@@@Z=006b26d0
// @ref ?Set_Type_Tech_Level_006b27e0@TActionClass@@QAE_NPAVHouseClass@@PAVObjectClass@@PAVTriggerClass@@PAVCell@@@Z=006b27e0
// @ref ??0?$CDTimerClass@VFrameTimerClass@@@@QAE@J@Z=00463f80
bool TActionClass::Execute(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool success = true;
    if (object != 0 && !object->unknown_7d) object = 0;
    switch (Type) {
    case 97: success = unknown_toggle_session_flag_2229(house, object, trigger, cell); break;
    case 94: success = unknown_ion_blast_at_waypoint(house, object, trigger, cell); break;
    case 95: success = unknown_nuke_at_waypoint(house, object, trigger, cell); break;
    case 102: success = unknown_func_6b25e0(house, object, trigger, cell); break;
    case 96: success = unknown_chem_missile_at_waypoint(house, object, trigger, cell); break;
    case 91: success = unknown_infantry_with_tag_slot294(house, object, trigger, cell); break;
    case 81: success = unknown_hunt_technos_with_tag(house, object, trigger, cell); break;
    case 85: success = unknown_set_session_flag_222b(house, object, trigger, cell); break;
    case 86: success = unknown_set_session_flag_222a(house, object, trigger, cell); break;
    case 87: success = unknown_set_session_flag_222c(house, object, trigger, cell); break;
    case 82: success = unknown_hunt_idle_feet_not_of_house(house, object, trigger, cell); break;
    case 83: success = unknown_hunt_feet_mission_23_of_house(house, object, trigger, cell); break;
    case 84: success = unknown_hunt_technos_of_house_type(house, object, trigger, cell); break;
    case 67: success = unknown_player_4e7ee0(house, object, trigger, cell); break;
    case 68: success = unknown_player_4e80d0(house, object, trigger, cell); break;
    case 69: success = unknown_player_4e82c0(house, object, trigger, cell); break;
    case 63: success = unknown_damage_006afd80(house, object, trigger, cell); break;
    case 64: success = unknown_explosion_50_at_waypoint(house, object, trigger, cell); break;
    case 65: success = unknown_explosion_100_at_waypoint(house, object, trigger, cell); break;
    case 66: success = unknown_explosion_300_at_waypoint(house, object, trigger, cell); break;
    case 60: success = unknown_buildings_with_tag_slot98(house, object, trigger, cell); break;
    case 61: success = unknown_buildings_with_tag_power_down(house, object, trigger, cell); break;
    case 62: success = unknown_buildings_with_tag_power_up(house, object, trigger, cell); break;
    case 14: success = unknown_technos_with_tag_to_house(house, object, trigger, cell); break;
    case 36: success = unknown_give_technos_to_house(house, object, trigger, cell); break;
    case 11: success = unknown_show_text(house, object, trigger, cell); break;
    case 37: success = unknown_make_ally(house, object, trigger, cell); break;
    case 38: success = unknown_make_enemy(house, object, trigger, cell); break;
    case 35: success = unknown_action_006b0540(house, object, trigger, cell); break;
    case 30: success = unknown_base_building(house, object, trigger, cell); break;
    case 31: success = unknown_map_49cc20(house, object, trigger, cell); break;
    case 28: success = unknown_set_local_variable(house, object, trigger, cell); break;
    case 29: success = unknown_clear_local_variable(house, object, trigger, cell); break;
    case 59: success = unknown_map_55d990_at_waypoint(house, object, trigger, cell); break;
    case 17: success = unknown_reveal_around_waypoint(house, object, trigger, cell); break;
    case 18: success = unknown_reveal_zone_of_waypoint(house, object, trigger, cell); break;
    case 16: success = unknown_reveal_whole_map(house, object, trigger, cell); break;
    case 23: success = unknown_start_mission_timer(house, object, trigger, cell); break;
    case 24: success = unknown_stop_mission_timer(house, object, trigger, cell); break;
    case 25: success = unknown_func_6b0ac0(house, object, trigger, cell); break;
    case 26: success = unknown_func_6b0b20(house, object, trigger, cell); break;
    case 27: success = unknown_func_6b0ba0(house, object, trigger, cell); break;
    case 103: success = unknown_set_mission_timer_text(house, object, trigger, cell); break;
    case 10: success = unknown_func_6b0d30(house, object, trigger, cell); break;
    case 19: success = unknown_func_6b0d70(house, object, trigger, cell); break;
    case 98: success = unknown_sound_at_random_waypoint(house, object, trigger, cell); break;
    case 99: success = unknown_waypoint_sound_6b0ec0(house, object, trigger, cell); break;
    case 101: success = unknown_reveal_6b1050(house, object, trigger, cell); break;
    case 20: success = unknown_queue_theme(house, object, trigger, cell); break;
    case 21: success = unknown_play_voice(house, object, trigger, cell); break;
    case 33: success = unknown_grant_super_6b11a0(house, object, trigger, cell); break;
    case 34: success = unknown_grant_super_6b1200(house, object, trigger, cell); break;
    case 8: success = unknown_func_6b1270(house, object, trigger, cell); break;
    case 1: success = unknown_win_or_lose_6b1360(house, object, trigger, cell); break;
    case 2: success = unknown_lose_or_win_6b1390(house, object, trigger, cell); break;
    case 3: success = unknown_set_house_136(house, object, trigger, cell); break;
    case 9: success = unknown_set_house_198(house, object, trigger, cell); break;
    case 13: success = unknown_set_house_137(house, object, trigger, cell); break;
    case 4: success = unknown_create_team(house, object, trigger, cell); break;
    case 5: success = unknown_destroy_teams(house, object, trigger, cell); break;
    case 7: success = unknown_func_6b1470(house, object, trigger, cell); break;
    case 80: success = unknown_func_6b1490(house, object, trigger, cell); break;
    case 6: success = unknown_func_6b14b0(house, object, trigger, cell); break;
    case 32: success = unknown_func_6b14d0(house, object, trigger, cell); break;
    case 39: success = unknown_action_006b1640(house, object, trigger, cell); break;
    case 40: success = unknown_func_6b1650(house, object, trigger, cell); break;
    case 41: success = unknown_func_6b1710(house, object, trigger, cell); break;
    case 42: success = unknown_weapon_explosion_at_waypoint(house, object, trigger, cell); break;
    case 43: success = unknown_func_6b19a0(house, object, trigger, cell); break;
    case 44: success = unknown_func_6b1a80(house, object, trigger, cell); break;
    case 45: success = unknown_action_006b1ac0(house, object, trigger, cell); break;
    case 46: success = unknown_action_006b1ae0(house, object, trigger, cell); break;
    case 47: success = unknown_action_006b1af0(house, object, trigger, cell); break;
    case 48: success = unknown_look_at_waypoint(house, object, trigger, cell); break;
    case 49: success = unknown_func_6b1c80(house, object, trigger, cell); break;
    case 50: success = unknown_func_6b1d00(house, object, trigger, cell); break;
    case 51: success = unknown_map_559fd0(house, object, trigger, cell); break;
    case 52: success = unknown_spotlight_behavior_6b1d80(house, object, trigger, cell); break;
    case 12: success = unknown_func_6b1e20(house, object, trigger, cell); break;
    case 70: success = unknown_func_6b1e70(house, object, trigger, cell); break;
    case 22: success = unknown_func_6b1ec0(house, object, trigger, cell); break;
    case 53: success = unknown_func_6b1f10(house, object, trigger, cell); break;
    case 54: success = unknown_func_6b1f90(house, object, trigger, cell); break;
    case 55: success = unknown_63b5b0_at_waypoint(house, object, trigger, cell); break;
    case 56: success = unknown_set_global_variable(house, object, trigger, cell); break;
    case 57: success = unknown_clear_global_variable(house, object, trigger, cell); break;
    case 58: success = unknown_meteor_shower_at_waypoint(house, object, trigger, cell); break;
    case 71: success = unknown_func_6b2220(house, object, trigger, cell); break;
    case 72: success = unknown_func_6b2240(house, object, trigger, cell); break;
    case 73: success = unknown_set_session_22a8(house, object, trigger, cell); break;
    case 74: success = unknown_func_6b2290(house, object, trigger, cell); break;
    case 75: success = unknown_func_6b22b0(house, object, trigger, cell); break;
    case 76: success = unknown_action_006b22f0(house, object, trigger, cell); break;
    case 77: success = unknown_action_006b2310(house, object, trigger, cell); break;
    case 78: success = unknown_action_006b2330(house, object, trigger, cell); break;
    case 79: success = unknown_action_006b2350(house, object, trigger, cell); break;
    case 88: success = unknown_particle_system_at_waypoint(house, object, trigger, cell); break;
    case 89: success = unknown_func_6af980(house, object, trigger, cell); break;
    case 90: success = unknown_func_6af950(house, object, trigger, cell); break;
    case 100: success = unknown_func_6b0d50(house, object, trigger, cell); break;
    case 92: success = unknown_action_006af930(house, object, trigger, cell); break;
    case 93: success = unknown_action_006af940(house, object, trigger, cell); break;
    case 104: success = unknown_func_6b2f30(house, object, trigger, cell); break;
    case 105: success = unknown_func_6b2f50(house, object, trigger, cell); break;
    case 106: success = Set_Type_Tech_Level_006b27e0(house, object, trigger, cell); break;
    case 107: success = unknown_func_6b2810(house, object, trigger, cell); break;
    case 108: success = unknown_map_54e580_at_waypoint(house, object, trigger, cell); break;
    case 109: success = unknown_iron_curtain_at_waypoint(house, object, trigger, cell); break;
    case 110: success = unknown_func_6b2f90(house, object, trigger, cell); break;
    case 111: success = unknown_func_6b2fa0(house, object, trigger, cell); break;
    case 112: success = unknown_center_on_waypoint(house, object, trigger, cell); break;
    case 113: success = unknown_func_6b22d0(house, object, trigger, cell); break;
    case 114: success = unknown_select_sidebar_tab(house, object, trigger, cell); break;
    case 115: success = unknown_sidebar_6822b0(house, object, trigger, cell); break;
    case 116: success = unknown_waypoint_sound_6b0f90(house, object, trigger, cell); break;
    case 117: success = unknown_func_6b0d60(house, object, trigger, cell); break;
    default: break;
    }
    return success;
}


