// void SpawnManagerClass::AI() (0x00689C90)
// The spawner's frame update (YR's SpawnManagerClass::AI, name hypothesis): every
// 10 frames walks the records. Docked (0): launches one toward the destination
// when the launch timer allows (9 frames for MissileSpawn owners, else 20), the
// owner is not jammed (0x0051FC80) and a missile launcher is not moving; missiles
// alternate the owner's burst index and fly at the destination, others leave
// for the cell north of the owner. Launching (1): unlinked when its timer runs
// out. Flying (2) and attacking (3): attack the destination while armed, else
// return to the owner (4). Returning (4): docks when it is over the owner's cell
// and less than 20 leptons above it, reloading for ReloadRate frames (6), which
// refills ammo and strength. Dead (7): a new unit is made when the timer runs out.
// Then the spawner's own state: idle (0) takes a target in range, launching (1)
// sends every flying record at the destination once all are out (MissileSpawn
// units go to the kamikaze tracker), and attacking (2) goes idle when no record
// is attacking or returning.
#include "shared/spawn_manager.hpp"
#include "shared/aircraft.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/kamikaze_tracker.hpp"
#include "shared/rules.hpp"
#include "shared/house.hpp"
#include "shared/foot.hpp"
#include "shared/facing.hpp"
#include "shared/map_view.hpp"
#include "shared/weapon_type.hpp"

void SpawnManagerClass::AI()
{
    if (unknown_50.Value()) {
        return;
    }
    unknown_50 = 10;

    for (int i = 0; i < SpawnedNodes.Count(); i++) {
        bool burst = false;
        AircraftClass *unit = SpawnedNodes[i]->Unit;
        switch (SpawnedNodes[i]->Status) {
        case 0:
            if (Destination == 0 || unknown_5c.Value() || Status == 2 || Owner->House->Unknown_0051FC80()) {
                break;
            }
            if (SpawnedNodes[i]->IsMissile == 1) {
                if (((FootClass *)Owner)->Locomotor.Checked()->Is_Moving()) {
                    break;
                }
                if (((FootClass *)Owner)->Locomotor.Checked()->Is_Moving_Now()) {
                    break;
                }
            }
            if (Owner->unknown_slot32()->MissileSpawn) {
                unknown_5c = 9;
            } else {
                unknown_5c = 20;
            }
            if (SpawnedNodes[i]->IsMissile == 1) {
                WeaponTypeClass *weapon = Owner->unknown_slot231(0)->WeaponType;
                if (weapon != 0 && weapon->Burst > 1) {
                    burst = true;
                    Owner->unknown_310 = i & 1;
                }
            }
            SpawnedNodes[i]->Status = 2;
            {
                CoordStruct coord = Owner->unknown_slot43(0);
                coord.Z += 10;
                unit->unknown_slot53(&coord, Dir_To_256(Owner->unknown_2e0.Current()));
            }
            if (burst) {
                Owner->unknown_310 = 0;
            }
            if (SpawnedNodes[i]->IsMissile == 1) {
                if (Target != 0) {
                    Destination = Target;
                    Target = 0;
                }
                unit->unknown_slot260(Destination, 1);
            } else {
                CellClass &cell = Map[Owner->unknown_slot104()];
                unit->unknown_slot260(&cell.Adjacent_Cell(0), 1);
            }
            unit->unknown_slot116(2, false);
            break;

        case 1:
            if (!SpawnedNodes[i]->Timer.Value()) {
                Unlink(unit);
            }
            break;

        case 2:
            if (SpawnedNodes[i]->IsMissile == 1) {
                break;
            }
            if (Target != 0) {
                Destination = Target;
                Target = 0;
            }
            if (Destination == 0) {
                unit->unknown_slot260(Owner, 1);
                unit->unknown_slot220(0);
                unit->unknown_slot116(2, false);
                SpawnedNodes[i]->Status = 4;
            } else {
                CellClass &cell = Map[Owner->unknown_slot104()];
                unit->unknown_slot260(&cell.Adjacent_Cell(4), 1);
                unit->unknown_slot116(2, false);
            }
            break;

        case 3:
            if (Target != 0) {
                Destination = Target;
                Target = 0;
            }
            if (unit->unknown_254 == 0 || Destination == 0) {
                unit->unknown_slot260(Owner, 1);
                unit->unknown_slot220(0);
                unit->unknown_slot116(2, false);
                SpawnedNodes[i]->Status = 4;
            } else {
                SpawnedNodes[i]->Unit->unknown_slot220(Destination);
                SpawnedNodes[i]->Unit->unknown_slot116(1, false);
            }
            break;

        case 4:
            if (Target != 0) {
                Destination = Target;
                Target = 0;
            }
            if (unit->unknown_254 > 0 && Destination != 0) {
                SpawnedNodes[i]->Status = 3;
                SpawnedNodes[i]->Unit->unknown_slot220(Destination);
                SpawnedNodes[i]->Unit->unknown_slot116(1, false);
            } else if (unit->unknown_slot104() == Owner->unknown_slot104() && CoordStruct(unit->Coord).Z - CoordStruct(Owner->Coord).Z < 20) {
                unit->unknown_slot52();
                SpawnedNodes[i]->Status = 6;
                SpawnedNodes[i]->Timer = ReloadRate;
            } else {
                unit->unknown_slot260(Owner, 1);
                unit->unknown_slot220(0);
                unit->unknown_slot116(2, false);
            }
            break;

        case 6:
            if (!SpawnedNodes[i]->Timer.Value()) {
                SpawnedNodes[i]->Status = 0;
                unit->unknown_254 = unit->Type->Ammo;
                unit->unknown_70 = unit->Strength = unit->Type->MaxStrength;
            }
            break;

        case 7:
            if (!SpawnedNodes[i]->Timer.Value()) {
                SpawnedNodes[i]->Unit = (AircraftClass *)SpawnType->unknown_slot35(Owner->Owning_House());
                if (SpawnType == Rules->V3Rocket.Type || SpawnType == Rules->DMisl.Type) {
                    SpawnedNodes[i]->IsMissile = 1;
                } else {
                    SpawnedNodes[i]->IsMissile = 0;
                }
                SpawnedNodes[i]->Unit->unknown_slot52();
                SpawnedNodes[i]->Unit->unknown_23c = Owner;
                SpawnedNodes[i]->Status = 0;
            }
            break;
        }
    }

    bool flag = false;
    switch (Status) {
    case 0:
        if (Target != 0) {
            Destination = Target;
            Target = 0;
        }
        if (Destination != 0) {
            if (!Owner->unknown_slot213(Destination)) {
                Abandon_Target();
                return;
            }
            Status = 1;
        }
        break;

    case 1: {
        if (Destination == 0) {
            Abandon_Target();
            return;
        }
        int index;
        for (index = 0; index < SpawnedNodes.Count(); index++) {
            int status = SpawnedNodes[index]->Status;
            if (status != 2 && status != 7) {
                return;
            }
        }
        for (index = 0; index < SpawnedNodes.Count(); index++) {
            if (SpawnedNodes[index]->Status == 2) {
                if (SpawnedNodes[index]->Unit->Type->MissileSpawn) {
                    flag = true;
                    KamikazeTracker.Add(SpawnedNodes[index]->Unit, Destination);
                    KamikazeTracker.Timer = 2;
                    if (SpawnedNodes[index]->IsMissile == 1) {
                        SpawnedNodes[index]->Status = 1;
                        if (SpawnType == Rules->V3Rocket.Type) {
                            SpawnedNodes[index]->Timer = Rules->V3Rocket.PauseFrames + Rules->V3Rocket.TiltFrames;
                        } else {
                            SpawnedNodes[index]->Timer = Rules->DMisl.PauseFrames + Rules->DMisl.TiltFrames;
                        }
                    } else {
                        Unlink(SpawnedNodes[index]->Unit);
                    }
                } else {
                    SpawnedNodes[index]->Status = 3;
                    SpawnedNodes[index]->Unit->unknown_slot220(Destination);
                    SpawnedNodes[index]->Unit->unknown_slot116(1, false);
                }
            }
        }
        if (flag) {
            Abandon_Target();
        }
        Status = 2;
        break;
    }

    case 2: {
        flag = true;
        for (int index = 0; index < SpawnedNodes.Count(); index++) {
            int status = SpawnedNodes[index]->Status;
            if (status == 3 || status == 4) {
                flag = false;
            }
        }
        if (flag) {
            Status = 0;
        }
        break;
    }
    }
}
