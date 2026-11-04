// BuildingClass::AI 0043C930: production state, damage effects and mission processing.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/anim.hpp"
#include "shared/infantry.hpp"
#include "shared/options.hpp"
#include "shared/tactical.hpp"
#include "shared/tileset_index.hpp"
#include "shared/sound_play.hpp"
inline CoordStruct Projected_Coord_0043bbd0(Point2D const &point);
inline void Accumulate_Coord_004395f0(CoordStruct &destination, CoordStruct const &offset);
void __fastcall Building_Refresh_House_Buildings_0044fa40(HouseClass *house);
// @ref ?Unknown_00556520@MapClass@@=00556520
// @ref ?Unknown_00557090@MapClass@@=00557090
// @ref ?Unknown_00405FE0@UnknownAudioController@@=00405fe0
// @ref ?Normalize_Delay@OptionsClass@@=005d9760
// @ref ?Options@@=00a40b18
// @ref ?unknown_tileset_a6cb68@@=00a6cb68
// @ref ?Voc_Update_At@@=007141b0
// @ref ?Voc_Play_At@@=00713e60
inline CoordStruct::CoordStruct(Point2D const &point,int z)
{
    int point_y=point.Y; int point_x=point.X;
    X=point_x; Y=point_y; Z=z;
}

void BuildingClass::AI()
{
    bool working = unknown_slot195() && unknown_slot91() != 18 && unknown_slot91() != 19;
    if (working != unknown_598) {
        if (Type->WorkingSound != -1 || Type->NotWorkingSound != -1) {
            unknown_584.Unknown_00405FE0();
            if (working) {
                Voc_Play_At(Type->WorkingSound, Position_Coord_004f3f40(), &unknown_584);
            } else {
                Voc_Play_At(Type->NotWorkingSound, Position_Coord_004f3f40(), &unknown_584);
            }
        }
        unknown_44f8e0();
        unknown_598 = working;
    } else {
        if (Type->WorkingSound != -1 || Type->NotWorkingSound != -1) {
            Voc_Update_At(Position_Coord_004f3f40(), &unknown_584);
        }
    }
    bool damaged;
    if (Type->CanBeOccupied) {
        damaged = Health_Ratio() <= Rules->unknown_1370;
    } else {
        damaged = Health_Ratio() <= Rules->unknown_1368;
    }
    if (damaged != unknown_4bc) {
        if (damaged) {
            Create_Damage_Fires_004395f0();
        } else {
            unknown_4397c0();
        }
        unknown_4bc = damaged;
    }
    if (Type->Turret) {
        unknown_3f0 = unknown_2e0.Is_Rotating();
    } else {
        unknown_3f0 = 0;
    }
    if (unknown_20c) {
        unknown_20c->AI();
    }
    if (unknown_slot111() || unknown_slot112()) {
        if (Type->MaxNumberOccupants == 0 || Rules->unknown_2a8 == 0) {
            if (Frame % 24 == 0 && Rules->unknown_2a8) {
                new AnimClass(Rules->unknown_2a8, Position_Coord_004f3f40(), 0, 1, 0x600, 0);
            }
        } else {
            for (int index = 0; index < Type->MaxNumberOccupants; ++index) {
                if ((Frame + index) % 24 == 0 && Rules->unknown_2a8) {
                    CoordStruct location(unknown_tactical_83996c->Unknown_006A2900(Type->MuzzleFlash[index]), 0);
                    location = unknown_slot42() + location;
                    AnimClass *effect = new AnimClass(Rules->unknown_2a8, location, 0, 1, 0x600, 0);
                    effect->ZAdjust = -200;
                }
            }
        }
        if (unknown_228) {
            unknown_slot220(0);
        }
        return;
    }
    if (unknown_5a0 == 1) {
        unknown_5a0 = 0;
        unknown_5a0 = Type->ProduceCashDelay;
        if (!House->Type->MultiplayPassive && unknown_slot195()) {
            int amount = Type->ProduceCashAmount;
            if (amount > 0) {
                House->Refund_Money(amount);
            } else {
                House->Spend_Money_004e5280(-amount);
            }
        }
    }
    if (Type->SAM && unknown_228 && !unknown_228->unknown_slot21()) {
        unknown_slot220(0);
    }
    Update_Animations_0044BD40();
    if (unknown_slot122() && unknown_42c != 0 && unknown_slot117()) {
        unknown_5ad = false;
    }
    TechnoClass::AI();
    if (!unknown_7d) return;
    if (unknown_254 == 0 && !Type->Hospital && !Type->Armory) {
        unknown_254 = Type->Ammo;
    }
    if (unknown_slot122() && unknown_slot117()) {
        unknown_5ad = false;
    }
    if (unknown_430 != -1) {
        if (unknown_42c != unknown_430) {
            unknown_42c = unknown_430;
            BuildingTriple const *control = &Type->AnimFrames[unknown_430];
            if (unknown_42c == 0 || unknown_42c == 1) {
                Set_Rate(Options.Normalize_Delay(control->unknown_08));
            } else {
                Set_Rate(control->unknown_08);
            }
            Set_Stage(control->unknown_00);
        }
        unknown_430 = -1;
    }
    if (Strength != unknown_43c) {
        House->unknown_5668 = true;
        House->unknown_5669 = true;
        unknown_43c = Strength;
        Building_Refresh_House_Buildings_0044fa40(House);
    }
    if (Strength == 0) {
        unknown_4397c0();
        if (unknown_420 == 0) {
            unknown_slot52();
            Spawn_Survivors_0043f8e0((ObjectClass *)unknown_438);
            unknown_slot60();
            Leave_Rubble_0043eba0();
        }
        return;
    }
    unknown_44b770();
    if (Type->Overpowerable) {
        for (int index = unknown_53c.Count() - 1; index >= 0; --index) {
            if (unknown_53c[index]->unknown_228 != this) {
                unknown_53c.Delete(index);
            }
        }
        int count = unknown_53c.Count();
        if (count >= 3 || (House->Power_Fraction() == 1.0 && unknown_530 && count >= 1)) {
            unknown_531 = true;
        } else {
            unknown_531 = false;
        }
    }
    if (Type->CanBeOccupied) {
        unknown_453300();
    }
    Repair_AI_0044b9b0();
    if (Type->Factory != 0) {
        Factory_AI_0044b480();
    }
    if (unknown_5af && unknown_420 == 0) {
        int damage = Strength;
        if (Type->BridgeRepairHut) {
            bool bridge_overlay = false;
            for (int y = -2; y < 3; ++y) {
                for (int x = -2; x < 3; ++x) {
                    int tile = Map[Cell(unknown_slot104() + Cell(x,y))].IsoTileIndex;
                    int overlay = Map[Cell(unknown_slot104() + Cell(x,y))].OverlayIndex;
                    if ((tile >= unknown_tileset_a6cb68 && tile < unknown_tileset_a6cb68 + 16) ||
                        (overlay >= 0x4a && overlay <= 0x65)) {
                        bridge_overlay = true;
                    }
                }
            }
            if (bridge_overlay) {
                Map.Unknown_00557090(unknown_slot104());
            } else {
                Map.Unknown_00556520(unknown_slot104());
            }
            unknown_5af = false;
            unknown_438 = 0;
        } else {
            unknown_slot86(&damage, 0, Rules->unknown_c74, (TechnoClass *)unknown_438, true, 0);
        }
        if (!unknown_7d) return;
        unknown_slot71(2);
    }
    if (Type->FirestormWall && (Frame & 7) == 0) {
        int frame = unknown_4f0 & 15;
        if (House->unknown_142) {
            if (frame != 10 && frame != 5 && unknown_454[11] == 0 && (unknown_id_source_a3d290->Random()() & 15) == 0) {
                unknown_454[11] = new AnimClass(Rules->FirestormIdleAnim, Position_Coord_004f3f40() + CoordStruct(-740,-740,0), 0, 1, 0x604, -10);
            }
        }
    }
    if (unknown_228 && !unknown_slot213(unknown_228)) {
        if (unknown_228->Kind_Of() != 2) {
            unknown_slot220(0);
        } else if (unknown_228->unknown_slot20()) {
            unknown_slot220(0);
        }
    }
}
