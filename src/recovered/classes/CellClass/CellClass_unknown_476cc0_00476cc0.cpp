// bool CellClass::unknown_476cc0(ObjectClass *object) (0x00476CC0): Westwood's Goodie_Check. Picks up
// the crate overlay in this cell for the foot object entering it: the powerup comes from the overlay
// data or the crate shares, is replaced by money when it would have no effect, and then takes effect.
#include "shared/cell.hpp"
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/overlay_type.hpp"
#include "shared/tag.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/debug_printf.hpp"
#include "shared/warhead_type.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/bullet.hpp"
#include "shared/sound_play.hpp"
#include "shared/vox_class.hpp"
#include "shared/fast_math.hpp"
#include "shared/coord_distance.hpp"
#include "shared/layer.hpp"
#include "shared/unknown_list_832470.hpp"
#include "shared/tiberium.hpp"
#include "shared/super.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/ini_enums.hpp"

// @ref ??_C@_03HEMN@GAS?$AA@=007d2edc
// @ref ??_C@_0BG@KIO@EVA_UnitSpeedUpgraded?$AA@=007d2ce0
// @ref ??_C@_0BG@PJIE@EVA_UnitArmorUpgraded?$AA@=007d2d18
// @ref ??_C@_0BK@MCM@EVA_UnitFirePowerUpgraded?$AA@=007d2ca0
// @ref ??_C@_0BO@MNB@Crate?5at?5?$CFd?0?$CFd?5contains?5ICBM?6?$AA@=007d2d50
// @ref ??_C@_0BP@BGNL@Crate?5at?5?$CFd?0?$CFd?5contains?5armor?6?$AA@=007d2d30
// @ref ??_C@_0BP@BLFA@Crate?5at?5?$CFd?0?$CFd?5contains?5money?6?$AA@=007d2e30
// @ref ??_C@_0BP@CEIN@Crate?5at?5?$CFd?0?$CFd?5contains?5speed?6?$AA@=007d2cf8
// @ref ??_C@_0CA@CNJO@Crate?5at?5?$CFd?0?$CFd?5contains?5napalm?6?$AA@=007d2dec
// @ref ??_C@_0CA@EOPH@Crate?5at?5?$CFd?0?$CFd?5contains?5a?5unit?6?$AA@=007d2e50
// @ref ??_C@_0CC@FICC@Crate?5at?5?$CFd?0?$CFd?5contains?5tiberium@=007d2eb8
// @ref ??_C@_0CC@HMF@Crate?5at?5?$CFd?0?$CFd?5contains?5?8reveal?8@=007d2e70
// @ref ??_C@_0CC@OILJ@Crate?5at?5?$CFd?0?$CFd?5contains?5?8shroud?8@=007d2e94
// @ref ??_C@_0CD@ICAD@Crate?5at?5?$CFd?0?$CFd?5contains?5firepowe@=007d2cbc
// @ref ??_C@_0CE@GEB@Crate?5at?5?$CFd?0?$CFd?5contains?5poison?5g@=007d2ee0
// @ref ??_C@_0CE@NGOI@Crate?5at?5?$CFd?0?$CFd?5contains?5explosiv@=007d2e0c
// @ref ??_C@_0CF@KBPC@Springing?5trigger?5on?5crate?5at?5?$CFd@=007d2f04
// @ref ??_C@_0CG@HBNI@Crate?5at?5?$CFd?0?$CFd?5contains?5base?5hea@=007d2d70
// @ref ??_C@_0CH@HHGF@Crate?5at?5?$CFd?0?$CFd?5contains?5veteranc@=007d2d98
// @ref ??_C@_0CJ@JEKO@Crate?5at?5?$CFd?0?$CFd?5contains?5cloaking@=007d2dc0
// @ref ?Remove_Crate@MapClass@@QAE_NABVCell@@@Z=0054e6e0
// @ref ?unknown_7133d0@UnknownTechnoPair@@QBE_NXZ=007133d0
// @ref ?unknown_713510@UnknownTechnoPair@@QAEX_N@Z=00713510
// @ref ?unknown_cell_850bd8@@3VCell@@A=00850bd8

extern Cell unknown_cell_850bd8;

inline int Length3_YZX(CoordStruct const &c)
{
    double y = c.Y;
    double z = c.Z;
    double x = c.X;
    return (int)Fast_Sqrt(y * y + (z * z + x * x));
}

inline int Length3(CoordStruct const &c)
{
    double x = c.X;
    double y = c.Y;
    double z = c.Z;
    return (int)Fast_Sqrt(x * x + y * y + z * z);
}


bool CellClass::unknown_476cc0(ObjectClass *crate_object)
{
    FootClass *object = (FootClass *)crate_object;
    if (object != 0 && OverlayIndex != -1 && OverlayTypes[OverlayIndex]->Crate) {
        bool force_mcv = false;
        int force_money = 0;
        int damage;
        CoordStruct coord;


        if (unknown_game_mode_a3d298 != 0 && object->House->Type->MultiplayPassive) {
            return true;
        }

        if (OverlayTypes[OverlayIndex]->CrateTrigger) {
            if (object->unknown_34 != 0) {
                Debug_Printf("Springing trigger on crate at %d,%d\n", MapCoords.X, MapCoords.Y);
                object->unknown_34->Spring(0x31, object, unknown_cell_850bd8, false, 0);
                if (!object->unknown_7d) {
                    return false;
                }
            }
            unknown_id_source_a3d290->unknown_223c = true;
        }

        CrateType powerup;
        int index;
        if (OverlayData >= CRATE_COUNT) {
            int total_shares = 0;
            for (index = CRATE_FIRST; index < CRATE_COUNT; index++) {
                total_shares += CrateShares[index];
            }
            int pick = Random_Pick(1, total_shares);
            int share_count = 0;
            for (index = CRATE_FIRST; index < CRATE_COUNT; index++) {
                share_count += CrateShares[index];
                if (pick <= share_count) break;
            }
            powerup = (CrateType)index;
        } else {
            powerup = (CrateType)OverlayData;
        }

        if (unknown_game_mode_a3d298 == 0) {
            if (OverlayData == 0) {
                force_money = Rules->SoloCrateMoney;
                if (OverlayTypes[OverlayIndex] == Rules->unknown_f4) {
                    powerup = Rules->SilverCrate;
                }
                if (OverlayTypes[OverlayIndex] == Rules->unknown_f0) {
                    powerup = Rules->WoodCrate;
                }
                if (OverlayTypes[OverlayIndex] == Rules->unknown_f8) {
                    powerup = Rules->WaterCrate;
                }
            }
        } else {
            HouseClass *house = object->House;
            UnitTypeClass *mcv = house->Unknown_004EF6F0(Rules->BaseUnit);
            if (house->CurBuildings == 0 && house->Available_Money() > 1500 &&
                    house->unknown_5430.unknown_func_491d10(mcv->ArrayIndex) == 0 && unknown_flag_a3d2b8) {
                powerup = CRATE_UNIT;
                force_mcv = true;
            }

            switch (powerup) {
                case CRATE_UNIT:
                    if (object->House->unknown_228 > 50) powerup = CRATE_MONEY;
                    if (unknown_ec == 2 || unknown_ec == 6) powerup = CRATE_MONEY;
                    break;

                case CRATE_SQUAD:
                    if (object->House->unknown_234 > 100) powerup = CRATE_MONEY;
                    if (unknown_ec == 2 || unknown_ec == 6) powerup = CRATE_MONEY;
                    break;

                case CRATE_ARMOR:
                    if (object->unknown_120 != 1) powerup = CRATE_MONEY;
                    break;

                case CRATE_VETERAN:
                    if (object->AbstractFlags.IsTechno) {
                        if (!object->unknown_slot32()->Trainable) {
                            powerup = CRATE_MONEY;
                        } else if (object->AbstractFlags.IsTechno && object->unknown_118.unknown_713420()) {
                            powerup = CRATE_MONEY;
                        }
                    }
                    break;

                case CRATE_SPEED:
                    if (object->unknown_470 != 1 || object->Kind_Of() == 2) powerup = CRATE_MONEY;
                    break;

                case CRATE_FIREPOWER:
                    if (object->unknown_128 != 1 || !object->unknown_slot163()) powerup = CRATE_MONEY;
                    break;

                case CRATE_CLOAK:
                    if (object->unknown_32a) powerup = CRATE_MONEY;
                    break;

            }

            if (unknown_ec == 2 && !CrateWater[powerup]) {
                powerup = CRATE_MONEY;
            }

            if (unknown_game_mode_a3d298 == 4) {
                object->House->unknown_4ab0.Unknown_0070C490(powerup);
            }
        }

        Map.Remove_Crate(Fetch_CellID());

        if (unknown_game_mode_a3d298 != 0 && unknown_flag_a3d2c1) {
            Map.Unknown_0054E410();
        }

        if (powerup == CRATE_SQUAD) {
            powerup = CRATE_MONEY;
        }

        double data = CrateData[powerup];
        bool tospeak = false;
        switch (powerup) {

            case CRATE_MONEY:
crate_money:
                Debug_Printf("Crate at %d,%d contains money\n", MapCoords.X, MapCoords.Y);
                if (!force_money) {
                    force_money = Random_Pick((int)data, (int)data + 900);
                }
                if (!object->House->Unknown_004F52B0() || unknown_game_mode_a3d298 != 0) {
                    object->House->Refund_Money(force_money);
                } else {
                    unknown_player_a35db4->Refund_Money(force_money);
                }
                if (object->House->Unknown_004F52B0()) {
                    Voc_Play_At(Rules->CrateMoneySound, Ground_Coord(), 0);
                }
                break;

            case CRATE_GAS: {
                Debug_Printf("Crate at %d,%d contains poison gas\n", MapCoords.X, MapCoords.Y);
                WarheadTypeClass *gas = WarheadTypeClass::From_Name("GAS");
                damage = data;
                Unknown_0047E2C0(Center_Coord(), damage, (TechnoClass *)0, gas, false);
                for (FacingType facing = FACING_N; facing < FACING_COUNT; facing++) {
                    Unknown_0047E2C0(Adjacent_Cell(facing).Center_Coord(), damage, (TechnoClass *)0, gas, false);
                }
                break;
            }

            case CRATE_TIBERIUM: {
                Debug_Printf("Crate at %d,%d contains tiberium\n", MapCoords.X, MapCoords.Y);
                int tibtype = Random_Pick(0, unknown_TiberiumClass_list_00ac0b30.Count() - 1);
                if (tibtype == 1) {
                    tibtype = 0;
                }
                unknown_47c3a0(tibtype, true);
                int count = Random_Pick(10, 20);
                while (count--) {
                    CoordStruct scatter = Coord_Scatter(Center_Coord(), Random_Pick(0, 3 * 256), true);
                    Map[scatter].unknown_47c3a0(tibtype, true);
                }
                break;
            }

            case CRATE_DARKNESS:
                Debug_Printf("Crate at %d,%d contains 'shroud'\n", MapCoords.X, MapCoords.Y);
                if (object->House->Unknown_004F52B0()) {
                    Map.Unknown_00559F10();
                }
                break;

            case CRATE_REVEAL:
                Debug_Printf("Crate at %d,%d contains 'reveal'\n", MapCoords.X, MapCoords.Y);
                if (object->House->Unknown_004F52B0()) {
                    Map.Unknown_0055A120();
                    Voc_Play_At(Rules->CrateRevealSound, Ground_Coord(), 0);
                }
                break;

            case CRATE_UNIT: {
                Debug_Printf("Crate at %d,%d contains a unit\n", MapCoords.X, MapCoords.Y);
                UnitTypeClass *utp = 0;
                if (force_mcv) {
                    utp = object->House->Unknown_004EF6F0(Rules->BaseUnit);
                }
                if (utp == 0 &&
                        (object->House->unknown_5420.unknown_func_491d10(Rules->BuildRefinery[0]->ArrayIndex) > 0 ||
                         object->House->unknown_5420.unknown_func_491d10(Rules->BuildRefinery[1]->ArrayIndex) > 0) &&
                        object->House->unknown_5430.unknown_func_491d10(Rules->unknown_9ec[0]->ArrayIndex) == 0 &&
                        object->House->unknown_5430.unknown_func_491d10(Rules->unknown_9ec[1]->ArrayIndex) == 0) {
                    utp = object->House->Unknown_004EF6F0(Rules->unknown_9ec);
                }
                if (Rules->UnitCrateType != 0) {
                    utp = Rules->UnitCrateType;
                }
                while (utp == 0) {
                    utp = UnitTypes[Random_Pick(0, UnitTypes.Count() - 1)];
                    bool isbase = Rules->BaseUnit.Is_Present(utp);
                    bool human = object->House->Unknown_004F52F0();
                    if (utp->CrateGoodie) {
                        if (!unknown_flag_a3d2b8) {
                            if (!isbase) break;
                        } else if (!isbase || human || force_mcv) {
                            break;
                        }
                    }
                    utp = 0;
                }

                if (utp != 0) {
                    UnitClass *goodie_unit = (UnitClass *)utp->unknown_slot35(object->House);
                    if (goodie_unit != 0) {
                        if (goodie_unit->unknown_slot53(&Ground_Coord(), 0)) {
                            if (object->House->Unknown_004F52B0()) {
                                Voc_Play_At(Rules->CrateUnitSound, Ground_Coord(), 0);
                            }
                            return false;
                        }
                        Cell cell = Map.Unknown_005502E0(Fetch_CellID(), goodie_unit->Type->SpeedType, -1, 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
                        if (cell != unknown_cell_850bd8 && goodie_unit->unknown_slot53(&UnknownCellCoord(cell), 0)) {
                            if (object->House->Unknown_004F52B0()) {
                                Voc_Play_At(Rules->CrateUnitSound, Ground_Coord(), 0);
                            }
                            return false;
                        }
                        delete goodie_unit;
                        powerup = CRATE_MONEY;
                        goto crate_money;
                    }
                }
                break;
            }

            case CRATE_EXPLOSION:
                Debug_Printf("Crate at %d,%d contains explosives\n", MapCoords.X, MapCoords.Y);
                damage = data;
                {
                    int d = damage;
                    object->unknown_slot86(&d, 0, Rules->unknown_c74, 0, true, 0);
                }
                {
                for (int i = 0; i < 5; i++) {
                    CoordStruct frag_coord = Coord_Scatter(Ground_Coord(), Random_Pick(0, 2 * 256), false);
                    Unknown_0047E2C0(frag_coord, damage, (TechnoClass *)0, Rules->unknown_c74, true);
                    AnimTypeClass *anim = Select_Damage_Anim(damage, Rules->unknown_c74, 0, &frag_coord);
                    new AnimClass(anim, frag_coord, 0, 1, 0x2600, Unknown_0047FCC0(frag_coord));
                    Unknown_0047F600(frag_coord, damage, Rules->unknown_c74, 0, 0);
                }
                }
                break;

            case CRATE_NAPALM: {
                Debug_Printf("Crate at %d,%d contains napalm\n", MapCoords.X, MapCoords.Y);
                coord = (object->Center_Coord() + Ground_Coord()) / 2;
                new AnimClass(AnimTypes[0], coord, 0, 1, 0x600, 0);
                damage = data;
                {
                    int d = damage;
                    object->unknown_slot86(&d, 0, Rules->FlameDamage, 0, true, 0);
                }
                Unknown_0047E2C0(coord, damage, (TechnoClass *)0, Rules->FlameDamage, true);
                break;
            }

            case CRATE_CLOAK:
                Debug_Printf("Crate at %d,%d contains cloaking device\n", MapCoords.X, MapCoords.Y);
                {
                for (int i = 0; i < DisplayClass::Layer[2].Count(); i++) {
                    ObjectClass *obj = DisplayClass::Layer[2][i];
                    if (obj != 0 && obj->unknown_74 && obj->Is_Techno() && Length3(Ground_Coord() - obj->Center_Coord()) < Rules->CrateRadius) {
                        ((TechnoClass *)obj)->unknown_32a = true;
                    }
                }
                }
                break;

            case CRATE_VETERAN:
                Debug_Printf("Crate at %d,%d contains veterancy(TM)\n", MapCoords.X, MapCoords.Y);
                {
                for (int i = 0; i < DisplayClass::Layer[2].Count(); i++) {
                    ObjectClass *obj = DisplayClass::Layer[2][i];
                    if (obj != 0 && obj->unknown_74 && obj->Is_Techno() && Length3(Ground_Coord() - obj->Center_Coord()) < Rules->CrateRadius &&
                            ((TechnoClass *)obj)->unknown_slot32()->Trainable) {
                        for (int count = 0; count < data; count++) {
                            UnknownTechnoPair *vet = &((TechnoClass *)obj)->unknown_118;
                            if (vet->unknown_7133a0()) vet->Unknown_00713550(true);
                            if (vet->unknown_7133d0()) vet->unknown_713520(true);
                            if (vet->unknown_713400()) vet->unknown_713510(true);
                        }
                    }
                }
                }
                if (object->House->Unknown_004F52B0()) {
                    Voc_Play_At(Rules->CratePromoteSound, Ground_Coord(), 0);
                }
                break;

            case CRATE_HEAL_BASE:
                Debug_Printf("Crate at %d,%d contains base healing\n", MapCoords.X, MapCoords.Y);
                if (object->House->Unknown_004F52B0()) {
                    Voc_Play_At(Rules->HealCrateSound, Ground_Coord(), 0);
                }
                {
                for (int i = 0; i < unknown_list_832470.Count(); i++) {
                    ObjectClass *obj = unknown_list_832470[i];
                    if (obj != 0 && object->Is_Techno() && object->House == obj->Owning_House()) {
                        int damage = obj->Strength - obj->Class_Of()->MaxStrength;
                        obj->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 1);
                    }
                }
                }
                break;

            case CRATE_ICBM: {
                Debug_Printf("Crate at %d,%d contains ICBM\n", MapCoords.X, MapCoords.Y);
                SuperWeaponTypeClass *super = SuperWeaponTypeClass::From_Action(0x14);
                int sindex = -1;
                {
                for (int i = 0; i < object->House->Supers.Count(); i++) {
                    if (object->House->Supers[i]->Type->Type == 0) {
                        sindex = i;
                        break;
                    }
                }
                }
                if (sindex != -1 && object->House->Supers[super->ArrayIndex]->Grant(true, false, false) && object->unknown_372) {
                    Map.Unknown_0067C530(0x1F, super->ArrayIndex);
                }
                break;
            }

            case CRATE_ARMOR:
                Debug_Printf("Crate at %d,%d contains armor\n", MapCoords.X, MapCoords.Y);
                {
                for (int i = 0; i < DisplayClass::Layer[2].Count(); i++) {
                    ObjectClass *obj = DisplayClass::Layer[2][i];
                    if (obj != 0 && obj->Is_Techno() && Length3(Ground_Coord() - obj->Center_Coord()) < Rules->CrateRadius &&
                            ((TechnoClass *)obj)->unknown_120 == 1) {
                        ((TechnoClass *)obj)->unknown_120 = data * ((TechnoClass *)obj)->unknown_120;
                        if (obj->Owning_House()->Unknown_004F52B0()) tospeak = true;
                    }
                }
                }
                if (tospeak) Speech_Play_Name("EVA_UnitArmorUpgraded", -1, -1);
                if (object->House->Unknown_004F52B0()) {
                    Voc_Play_At(Rules->CrateArmourSound, Ground_Coord(), 0);
                }
                break;

            case CRATE_SPEED:
                Debug_Printf("Crate at %d,%d contains speed\n", MapCoords.X, MapCoords.Y);
                {
                for (int i = 0; i < DisplayClass::Layer[2].Count(); i++) {
                    ObjectClass *obj = DisplayClass::Layer[2][i];
                    if (obj != 0 && obj->Is_Foot() && Length3(Ground_Coord() - obj->Center_Coord()) < Rules->CrateRadius &&
                            ((FootClass *)obj)->unknown_470 == 1 && obj->Kind_Of() != 2) {
                        ((FootClass *)obj)->unknown_470 = data * ((FootClass *)obj)->unknown_470;
                        if (((FootClass *)obj)->House->unknown_135) tospeak = true;
                    }
                }
                }
                if (tospeak) Speech_Play_Name("EVA_UnitSpeedUpgraded", -1, -1);
                if (object->House->Unknown_004F52B0()) {
                    Voc_Play_At(Rules->CrateSpeedSound, Ground_Coord(), 0);
                }
                break;

            case CRATE_FIREPOWER:
                Debug_Printf("Crate at %d,%d contains firepower\n", MapCoords.X, MapCoords.Y);
                {
                for (int i = 0; i < DisplayClass::Layer[2].Count(); i++) {
                    ObjectClass *obj = DisplayClass::Layer[2][i];
                    if (obj != 0 && obj->Is_Techno() && Length3_YZX(Ground_Coord() - obj->Center_Coord()) < Rules->CrateRadius &&
                            ((TechnoClass *)obj)->unknown_128 == 1) {
                        ((TechnoClass *)obj)->unknown_128 = data * ((TechnoClass *)obj)->unknown_128;
                        if (obj->Owning_House()->Unknown_004F52B0()) tospeak = true;
                    }
                }
                }
                if (tospeak) Speech_Play_Name("EVA_UnitFirePowerUpgraded", -1, -1);
                if (object->House->Unknown_004F52B0()) {
                    Voc_Play_At(Rules->CrateFireSound, Ground_Coord(), 0);
                }
                break;

            case CRATE_INVULN:
                break;

            case CRATE_ION_STORM:
                break;

            default:
                break;
        }

        if (CrateAnims[powerup] != -1) {
            CoordStruct coord = Ground_Coord() + CoordStruct(0, 0, 200);
            new AnimClass(AnimTypes[CrateAnims[powerup]], coord, 0, 1, 0x600, 0);
        }
    }

    return true;
}
