// Infantry object action selection (0x00505390, virtual slot 28).
// Action numbers are retained until their complete mapping is evidenced.
#include "shared/building.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/house_type.hpp"
#include "shared/infantry.hpp"
#include "shared/keyboard.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
// Original RTTI-kind checked conversion: kinds 1, 2, 6 and 15, all TechnoClass descendants.
TechnoClass *__fastcall As_Techno_0040dbd0(AbstractClass *object);
unsigned char __fastcall Infantry_Action_Allowed_00614b50(int action);
// @ref ?Unknown_00569320@MapClass@@QAE_NABVCell@@@Z=00569320
// @ref ?As_Techno_0040dbd0@@YIPAVTechnoClass@@PAVAbstractClass@@@Z=0040dbd0
// @ref ?Infantry_Action_Allowed_00614b50@@YIEH@Z=00614b50
// @ref ?KeyForceFire1@@3HA=00a40bac
// @ref ?KeyForceFire2@@3HA=00a40bb0
// @ref ?KeyForceMove1@@3HA=00a40bb4
// @ref ?KeyForceMove2@@3HA=00a40bb8
// @ref ?unknown_adjacent_851a70@@3QBVCell@@B=00851a70

inline Cell Infantry_Add_Cells(Cell const & a, Cell const & b)
{
    Cell sum;
    sum.X = a.X + b.X;
    sum.Y = a.Y + b.Y;
    return sum;
}

inline bool Infantry_Key_Down(int key)
{
    return WWKeyboard->Down(key);
}
int InfantryClass::unknown_slot28(ObjectClass *object, bool ignore_modifiers)
{
    bool force_move;
    bool force_fire;
    if (!(unsigned char)ignore_modifiers && (Infantry_Key_Down(KeyForceMove1) || Infantry_Key_Down(KeyForceMove2))) {
        force_move = true;
read_force_fire:
        if (!Infantry_Key_Down(KeyForceFire1) && !Infantry_Key_Down(KeyForceFire2)) goto clear_force_fire;
        force_fire = true;
    } else {
        force_move = false;
        if (!(unsigned char)ignore_modifiers) goto read_force_fire;
clear_force_fire:
        force_fire = false;
    }
    if (force_move && force_fire) force_fire = false;
    int action = FootClass::unknown_slot28(object, ignore_modifiers);
    if (action == 8) return 8;
    TechnoClass *target = static_cast<TechnoClass *>(object);
    BuildingClass *building = static_cast<BuildingClass *>(object);
    {
        if (Type->Engineer && House->Unknown_004F52B0() && object->unknown_38 && object->unknown_68) return 0x39;
        if (Type->Engineer && object->Kind_Of() == 6 && House->Unknown_004F52B0() &&
            !object->unknown_slot31() && building->Type->Repairable) {
            if (building->Type->BridgeRepairHut) {
                Cell cell = Coord_Cell(object->Center_Coord());
                return Map.Unknown_00569320(cell) ? 0x1d : 0x20;
            }
            if (House->Is_Ally(target) || (building->House->Type->MultiplayPassive && building->Type->CanBeOccupied)) {
                if (building->Type->Hospital && Health_Ratio() < Rules->unknown_1360) return 3;
                if (object->Health_Ratio() == Rules->unknown_1360) return 0x20;
                return 0x1d;
            }
            if (building->Type->Capturable) {
                if (object->Health_Ratio() <= Rules->unknown_143c) goto return_capture_action;
                return 0x1c;
            }
        }
        if (object->Kind_Of() == 6 && House->Unknown_004F52B0() && building->Unknown_00452EB0(this) && !force_fire) {
return_capture_action:
            return 9;
        }
        if (Type->Engineer && action == 5) return 2;
        if (unknown_6c16f0(-1) < 0 && House->Unknown_004F52B0()) {
            if (House->Is_Ally(target)) {
                if (object->Kind_Of() == 15) {
                    if (object != this) {
                        if (object->Health_Ratio() < Rules->unknown_1360) return 0x1b;
                    } else return 0x1a;
                }
                TechnoClass *transport = As_Techno_0040dbd0(object);
                if (!transport || transport->unknown_slot32()->Passengers == 0) {
                    if (action == 0x1a || action == 1) goto return_selected_action;
                    return 7;
                }
            } else return 0x3b;
        }
        if (House->Unknown_004F52B0() && Type->VehicleThief && object->unknown_slot31()) {
            if (target->unknown_slot32()->IsTrain) return 7;
            if (target->House != House) {
                if ((unknown_id_source_a3d290->unknown_000 & 0x800) != 0) {
                    for (int i = 0; i < Rules->unknown_9ec.Count(); ++i) {
                        if (Rules->unknown_9ec[i] == (UnitTypeClass *)object) return 7;
                    }
                }
                return 9;
            }
        }
        if (object->Kind_Of() == 6 && House->Is_Ally(target) && House->Unknown_004F52B0() && building->Type->Hospital && !force_fire) {
            if (Strength < Type->MaxStrength) {
                if (!Type->Deployer || (Sequence != 27 && Sequence != 28 && Sequence != 29 && Sequence != 30)) {
                    switch (unknown_slot150(15,target)) {
                    case 1: action = 3; break;
                    case 10: action = 0x1f; break;
                    }
                }
            } else action = 0x1f;
        }
        if (object->Kind_Of() == 6 && House->Is_Ally(target) && House->Unknown_004F52B0() && building->Type->Armory) {
            if (!unknown_118.unknown_713420()) {
                if (!Type->Deployer || (Sequence != 27 && Sequence != 28 && Sequence != 29 && Sequence != 30)) {
                    switch (unknown_slot150(15,target)) {
                    case 1: action = 3; break;
                    case 10: action = 0x1f; break;
                    }
                }
            } else action = 0x1f;
        }
        if (House->Unknown_004F52B0() && (Type->C4 || unknown_6d7910(14)) && action == 5 && object->Kind_Of() == 6 && !object->unknown_slot31()) {
            if (building->Type->CanC4 && !building->Type->InvisibleInGame) return 0x10;
            return 5;
        }
        WeaponTypeClass *weapon = unknown_slot231(unknown_slot174(object))->WeaponType;
        if (action == 5 && weapon && weapon->unknown_115) return 0x40;
        if (House->Unknown_004F52B0() && action == 5 && Type->Ivan) {
            if (object->Class_Of()->unknown_1fe && !object->unknown_38) return 0x35;
            return 0x36;
        }
        if (House->Unknown_004F52B0() && Type->Deployer && (Sequence == 27 || Sequence == 28 || Sequence == 29 || Sequence == 30)) {
            if (action == 1) return 2;
            if (action == 5) {
                if (!Type->DeployFire) goto stop_deployed_fire;
                {
                    int weapon_index = unknown_slot174(0);
                    if (!unknown_slot212(object,weapon_index)) goto stop_deployed_fire;
                }
                goto deployed_fire_allowed;
stop_deployed_fire:
                return 2;
deployed_fire_allowed:;
            } else if (action == 4) {
                if (!Infantry_Action_Allowed_00614b50(4)) return 0x1e;
                if (Type->UndeployDelay > -1) return 0x1e;
            }
        }
        if (House->Unknown_004F52B0()) {
            if (action == 4) {
                if (Type->Deployer && Type->UndeployDelay > -1 && Sequence == 31) return 0x1e;
                goto check_action_four;
            }
            goto check_action_31;
        }
        if (action == 4) {
check_action_four:
            if (Infantry_Action_Allowed_00614b50(4)) {
                if (!House->Unknown_004F52B0()) action = 0;
                else {
                    if (unknown_slot229()->WeaponType && unknown_slot229()->WeaponType->unknown_126) action = 0x34;
                    else if (!Type->Deployer) action = 0;
                }
            } else action = 0x1e;
        } else {
check_action_31:
            if (action == 0x1f) goto infiltration;
        }
        TechnoTypeClass *transport_type;
        if (House->Is_Ally(target) && House->Unknown_004F52B0() && As_Techno_0040dbd0(object) &&
            action != 5 && action != 0x1a && (transport_type = target->unknown_slot32()) != 0 && transport_type->Passengers > 0) {
            if (Type->BalloonHover) action = 0x1f;
            else {
                FootClass *foot = static_cast<FootClass *>(object);
                bool transport_ready;
                if (object) transport_ready = object->AbstractFlags.IsFoot != 0;
                if (object && transport_ready &&
                    ((!foot->Team || foot->Team->Class->Loadable) ? foot->Locomotor.Checked()->Is_Moving() : true)) action = 0x1f;
                else {
                    switch (unknown_slot150(15,target)) {
                    case 1: action = 3; break;
                    case 10: action = 0x1f; break;
                    }
                }
            }
        }
infiltration:
        if (House->Unknown_004F52B0() && Type->Infiltrate) {
            if (action != 5) goto cloning;
            if ((!Type->Agent && !House->Is_Ally(target) && object->Kind_Of() == 6 && building->Type->Capturable) ||
                (Type->Agent && !House->Is_Ally(target) && object->Kind_Of() == 6 && building->Type->Spyable)) {
                action = 9;
                if (object->Kind_Of() == 6) {
                    Cell base = Coord_Cell(object->Center_Coord());
                    int zone = Map.Zone(unknown_slot106(),Type->MovementZone,unknown_79);
                    Cell const *offset = building->Type->unknown_slot36(0);
                    bool found = false;
                    while (!(offset->X == 0x7fff && offset->Y == 0x7fff) && !found) {
                        Cell foundation = Infantry_Add_Cells(base, *offset++);
                        for (int facing = 0; facing < 8; ++facing) {
                            if (Map.Zone(Infantry_Add_Cells(foundation,unknown_adjacent_851a70[facing & 7]),Type->MovementZone,false) == zone) {
                                found = true;
                                break;
                            }
                        }
                    }
                }
                goto finish;
            }
            if (!unknown_slot163()) {
                action = 0;
                goto finish;
            }
        } else if (action != 5) goto cloning;
        if (action == 5) {
            if (!unknown_slot163()) action = 0x3b;
        } else {
cloning:
            if (action == 7 && object->Kind_Of() == 6 && House->Unknown_004F52B0() && !object->unknown_slot31() && building->Type->Cloning)
                return object->Owning_House() != unknown_player_a35db4 ? 0x1f : 0xb;
            goto finish;
        }
finish:
        if (House->Unknown_004F52B0() && action == 0) {
            if (unknown_slot111() || unknown_slot112()) goto return_selected_action;
            action = 2;
        }
        if (action == 2) {
            if (object->unknown_slot48() && !object->unknown_slot51(true) && object->unknown_slot50(true)->Kind_Of() == 21) action = 1;
        } else if (action == 5 && object->Class_Of()->unknown_203) action = 2;
        goto return_selected_action;
    }
return_selected_action:
    return action;
}
