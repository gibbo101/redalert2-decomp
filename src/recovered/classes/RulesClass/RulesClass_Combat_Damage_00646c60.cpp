// bool RulesClass::Combat_Damage(CCINIClass &ini) (0x00646C60)
// Reads [CombatDamage]: damages, the scorch and splash lists, the special
// warheads (the elite V3/DMisl warheads default to the normal ones), the
// default particle systems and the combat rules. Integer and lepton values go
// through named locals, as in RulesClass::AI.
// @ref ??0?$DynamicVectorClass@PAVSmudgeTypeClass@@@@QAE@IPBQAVSmudgeTypeClass@@@Z=00653730
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_05HJBJ@Crush?$AA@=007efb38
// @ref ??_C@_07HPPO@C4Delay?$AA@=007efb40
// @ref ??_C@_08JGDI@Incoming?$AA@=007efa94
// @ref ??_C@_08NHDF@Scorches?$AA@=007efe18
// @ref ??_C@_09CDDM@MinDamage?$AA@=007efaf8
// @ref ??_C@_09CFGJ@Scorches2?$AA@=007efe00
// @ref ??_C@_09GMGP@MaxDamage?$AA@=007efb04
// @ref ??_C@_09IBBP@ExpSpread?$AA@=007efb2c
// @ref ??_C@_09IPPO@Scorches3?$AA@=007efdf4
// @ref ??_C@_09MNIB@C4Warhead?$AA@=007efdb4
// @ref ??_C@_09NKBL@Scorches4?$AA@=007efde8
// @ref ??_C@_09NKKC@V3Warhead?$AA@=007efda8
// @ref ??_C@_09NKNA@Scorches1?$AA@=007efe0c
// @ref ??_C@_0BA@DNAB@VeinholeWarhead?$AA@=007efca4
// @ref ??_C@_0BA@GGA@IonCannonDamage?$AA@=007efe64
// @ref ??_C@_0BA@KMI@PlayerAutoCrush?$AA@=007efad4
// @ref ??_C@_0BA@LNEF@AmmoCrateDamage?$AA@=007efe74
// @ref ??_C@_0BB@FPLP@TiberiumStrength?$AA@=007efe24
// @ref ??_C@_0BB@GMFO@IonCannonWarhead?$AA@=007efcc8
// @ref ??_C@_0BB@JMFO@PlayerReturnFire?$AA@=007efac0
// @ref ??_C@_0BB@MCDE@FirestormWarhead?$AA@=007efcb4
// @ref ??_C@_0BB@MGDL@BallisticScatter?$AA@=007efb58
// @ref ??_C@_0BC@BDIP@DMislEliteWarhead?$AA@=007efd74
// @ref ??_C@_0BC@HFBP@TiberiumExplosive?$AA@=007efae4
// @ref ??_C@_0BD@HBPN@DefaultSparkSystem?$AA@=007efc38
// @ref ??_C@_0BE@JBBL@IvanIconFlickerRate?$AA@=007efcf0
// @ref ??_C@_0BE@JJDB@CanDetonateTimeBomb?$AA@=007efd54
// @ref ??_C@_0BE@KOEF@IronCurtainDuration?$AA@=007efcdc
// @ref ??_C@_0BE@PKCF@RailgunDamageRadius?$AA@=007efe50
// @ref ??_C@_0BF@FGKM@CanDetonateDeathBomb?$AA@=007efd3c
// @ref ??_C@_0BI@LGLP@DefaultFireStreamSystem?$AA@=007efbcc
// @ref ??_C@_0BI@ODMD@TiberiumExplosionDamage?$AA@=007efe38
// @ref ??_C@_0BJ@LAN@DefaultDebrisSmokeSystem?$AA@=007efbe4
// @ref ??_C@_0BK@KNH@DefaultTestParticleSystem?$AA@=007efbb0
// @ref ??_C@_0BL@BJFD@DefaultSmallRedSmokeSystem?$AA@=007efc00
// @ref ??_C@_0BL@OPDF@DefaultLargeRedSmokeSystem?$AA@=007efc1c
// @ref ??_C@_0BM@EPMI@DefaultLargeGreySmokeSystem?$AA@=007efc68
// @ref ??_C@_0BM@FPDO@DefaultSmallGreySmokeSystem?$AA@=007efc4c
// @ref ??_C@_0BM@PNDC@DefaultRepairParticleSystem?$AA@=007efb94
// @ref ??_C@_0CA@LPH@DefaultFirestormExplosionSystem?$AA@=007efc84
// @ref ??_C@_0L@CCLL@AtomDamage?$AA@=007efb6c
// @ref ??_C@_0L@FFJL@SplashList?$AA@=007efddc
// @ref ??_C@_0L@FKBE@IvanDamage?$AA@=007efd24
// @ref ??_C@_0L@PMPC@TurboBoost?$AA@=007efb78
// @ref ??_C@_0M@DKHF@DeathWeapon?$AA@=007efd30
// @ref ??_C@_0M@JBAC@IvanWarhead?$AA@=007efd68
// @ref ??_C@_0M@MDOB@FlameDamage?$AA@=007efdd0
// @ref ??_C@_0M@POBF@FireSupress?$AA@=007efb20
// @ref ??_C@_0N@LMHN@FlameDamage2?$AA@=007efdc0
// @ref ??_C@_0N@MAB@BOMBCURS?4SHP?$AA@=007efd04
// @ref ??_C@_0N@OLAC@DMislWarhead?$AA@=007efd98
// @ref ??_C@_0O@BLHH@PlayerScatter?$AA@=007efab0
// @ref ??_C@_0O@IMHI@HomingScatter?$AA@=007efb10
// @ref ??_C@_0O@MHKB@TreeTargeting?$AA@=007efaa0
// @ref ??_C@_0P@CFKJ@IvanTimedDelay?$AA@=007efd14
// @ref ??_C@_0P@EDKE@BerzerkAllowed?$AA@=007efb84
// @ref ??_C@_0P@GDEC@V3EliteWarhead?$AA@=007efd88
// @ref ??_C@_0P@GKNF@CollapseChance?$AA@=007efa84
// @ref ??_C@_0P@NHJF@BridgeStrength?$AA@=007efb48
// @ref ?Find_Or_Make@SmudgeTypeClass@@SIPAV1@PBD@Z=006883d0
// @ref _RulesSection_CombatDamage=007a9044
// @ref ?Add@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@QAE_NABQAVSmudgeTypeClass@@@Z=00653840
// @ref ?Clear@?$VectorClass@PAVAnimTypeClass@@@@UAEXXZ=0050b3f0
// @ref ?Clear@?$VectorClass@PAVSmudgeTypeClass@@@@UAEXXZ=006536a0
// @ref ??_C@_0N@IPGP@CombatDamage?$AA@=007eecd4
// @ref ??4?$DynamicVectorClass@PAVSmudgeTypeClass@@@@QAEAAV0@ABV0@@Z=00652d20
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/warhead_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/particle_system.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"

bool RulesClass::Combat_Damage(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_CombatDamage)) {
        int ammo_crate_damage = ini.Get_Int(RulesSection_CombatDamage, "AmmoCrateDamage", AmmoCrateDamage);
        AmmoCrateDamage = ammo_crate_damage;
        int ion_cannon_damage = ini.Get_Int(RulesSection_CombatDamage, "IonCannonDamage", IonCannonDamage);
        IonCannonDamage = ion_cannon_damage;
        int railgun_damage_radius = ini.Get_Int(RulesSection_CombatDamage, "RailgunDamageRadius", RailgunDamageRadius);
        RailgunDamageRadius = railgun_damage_radius;
        int tiberium_explosion_damage = ini.Get_Int(RulesSection_CombatDamage, "TiberiumExplosionDamage", unknown_488);
        unknown_488 = tiberium_explosion_damage;
        int tiberium_strength = ini.Get_Int(RulesSection_CombatDamage, "TiberiumStrength", TiberiumStrength);
        TiberiumStrength = tiberium_strength;
        Scorches = TypeListReader<SmudgeTypeClass>::Get(ini, RulesSection_CombatDamage, "Scorches", Scorches);
        Scorches1 = TypeListReader<SmudgeTypeClass>::Get(ini, RulesSection_CombatDamage, "Scorches1", Scorches1);
        Scorches2 = TypeListReader<SmudgeTypeClass>::Get(ini, RulesSection_CombatDamage, "Scorches2", Scorches2);
        Scorches3 = TypeListReader<SmudgeTypeClass>::Get(ini, RulesSection_CombatDamage, "Scorches3", Scorches3);
        Scorches4 = TypeListReader<SmudgeTypeClass>::Get(ini, RulesSection_CombatDamage, "Scorches4", Scorches4);
        SplashList = TypeListReader<AnimTypeClass>::Get(ini, RulesSection_CombatDamage, "SplashList", SplashList);
        FlameDamage = Get_Type(ini, RulesSection_CombatDamage, "FlameDamage", FlameDamage);
        FlameDamage2 = Get_Type(ini, RulesSection_CombatDamage, "FlameDamage2", FlameDamage2);
        unknown_c74 = Get_Type(ini, RulesSection_CombatDamage, "C4Warhead", unknown_c74);
        V3Warhead = Get_Type(ini, RulesSection_CombatDamage, "V3Warhead", V3Warhead);
        DMislWarhead = Get_Type(ini, RulesSection_CombatDamage, "DMislWarhead", DMislWarhead);
        V3EliteWarhead = Get_Type(ini, RulesSection_CombatDamage, "V3EliteWarhead", V3Warhead);
        DMislEliteWarhead = Get_Type(ini, RulesSection_CombatDamage, "DMislEliteWarhead", DMislWarhead);
        IvanWarhead = Get_Type(ini, RulesSection_CombatDamage, "IvanWarhead", IvanWarhead);
        CanDetonateTimeBomb = ini.Get_Bool(RulesSection_CombatDamage, "CanDetonateTimeBomb", CanDetonateTimeBomb);
        CanDetonateDeathBomb = ini.Get_Bool(RulesSection_CombatDamage, "CanDetonateDeathBomb", CanDetonateDeathBomb);
        DeathWeapon = Get_Type(ini, RulesSection_CombatDamage, "DeathWeapon", DeathWeapon);
        int ivan_damage = ini.Get_Int(RulesSection_CombatDamage, "IvanDamage", IvanDamage);
        IvanDamage = ivan_damage;
        int ivan_timed_delay = ini.Get_Int(RulesSection_CombatDamage, "IvanTimedDelay", IvanTimedDelay);
        IvanTimedDelay = ivan_timed_delay;
        BombCursorShape = MixFileClass::Retrieve("BOMBCURS.SHP");
        int ivan_icon_flicker_rate = ini.Get_Int(RulesSection_CombatDamage, "IvanIconFlickerRate", IvanIconFlickerRate);
        IvanIconFlickerRate = ivan_icon_flicker_rate;
        int iron_curtain_duration = ini.Get_Int(RulesSection_CombatDamage, "IronCurtainDuration", IronCurtainDuration);
        IronCurtainDuration = iron_curtain_duration;
        IonCannonWarhead = Get_Type(ini, RulesSection_CombatDamage, "IonCannonWarhead", IonCannonWarhead);
        unknown_cac = Get_Type(ini, RulesSection_CombatDamage, "FirestormWarhead", unknown_cac);
        unknown_cb0 = Get_Type(ini, RulesSection_CombatDamage, "VeinholeWarhead", unknown_cb0);
        unknown_cf4 = Get_Type(ini, RulesSection_CombatDamage, "DefaultFirestormExplosionSystem", unknown_cf4);
        DefaultLargeGreySmokeSystem = Get_Type(ini, RulesSection_CombatDamage, "DefaultLargeGreySmokeSystem", DefaultLargeGreySmokeSystem);
        DefaultSmallGreySmokeSystem = Get_Type(ini, RulesSection_CombatDamage, "DefaultSmallGreySmokeSystem", DefaultSmallGreySmokeSystem);
        unknown_ce0 = Get_Type(ini, RulesSection_CombatDamage, "DefaultSparkSystem", unknown_ce0);
        DefaultLargeRedSmokeSystem = Get_Type(ini, RulesSection_CombatDamage, "DefaultLargeRedSmokeSystem", DefaultLargeRedSmokeSystem);
        DefaultSmallRedSmokeSystem = Get_Type(ini, RulesSection_CombatDamage, "DefaultSmallRedSmokeSystem", DefaultSmallRedSmokeSystem);
        DefaultDebrisSmokeSystem = Get_Type(ini, RulesSection_CombatDamage, "DefaultDebrisSmokeSystem", DefaultDebrisSmokeSystem);
        DefaultFireStreamSystem = Get_Type(ini, RulesSection_CombatDamage, "DefaultFireStreamSystem", DefaultFireStreamSystem);
        DefaultTestParticleSystem = Get_Type(ini, RulesSection_CombatDamage, "DefaultTestParticleSystem", DefaultTestParticleSystem);
        DefaultRepairParticleSystem = Get_Type(ini, RulesSection_CombatDamage, "DefaultRepairParticleSystem", DefaultRepairParticleSystem);
        BerzerkAllowed = ini.Get_Bool(RulesSection_CombatDamage, "BerzerkAllowed", BerzerkAllowed);
        TurboBoost = ini.Get_Double(RulesSection_CombatDamage, "TurboBoost", TurboBoost);
        int atom_damage = ini.Get_Int(RulesSection_CombatDamage, "AtomDamage", unknown_1190);
        unknown_1190 = atom_damage;
        int ballistic_scatter = ini.Get_Lepton(RulesSection_CombatDamage, "BallisticScatter", unknown_139c);
        unknown_139c = ballistic_scatter;
        int bridge_strength = ini.Get_Int(RulesSection_CombatDamage, "BridgeStrength", unknown_13a8);
        unknown_13a8 = bridge_strength;
        unknown_13b8 = ini.Get_Double(RulesSection_CombatDamage, "C4Delay", unknown_13b8);
        int crush = ini.Get_Lepton(RulesSection_CombatDamage, "Crush", unknown_1390);
        unknown_1390 = crush;
        ExpSpread = ini.Get_Double(RulesSection_CombatDamage, "ExpSpread", ExpSpread);
        int fire_supress = ini.Get_Lepton(RulesSection_CombatDamage, "FireSupress", FireSupress);
        FireSupress = fire_supress;
        int homing_scatter = ini.Get_Lepton(RulesSection_CombatDamage, "HomingScatter", HomingScatter);
        HomingScatter = homing_scatter;
        int max_damage = ini.Get_Int(RulesSection_CombatDamage, "MaxDamage", MaxDamage);
        MaxDamage = max_damage;
        int min_damage = ini.Get_Int(RulesSection_CombatDamage, "MinDamage", MinDamage);
        MinDamage = min_damage;
        unknown_1429 = ini.Get_Bool(RulesSection_CombatDamage, "TiberiumExplosive", unknown_1429);
        unknown_142f = ini.Get_Bool(RulesSection_CombatDamage, "PlayerAutoCrush", unknown_142f);
        PlayerReturnFire = ini.Get_Bool(RulesSection_CombatDamage, "PlayerReturnFire", PlayerReturnFire);
        unknown_1431 = ini.Get_Bool(RulesSection_CombatDamage, "PlayerScatter", unknown_1431);
        unknown_142d = ini.Get_Bool(RulesSection_CombatDamage, "TreeTargeting", unknown_142d);
        unknown_1328 = ini.Get_Percent(RulesSection_CombatDamage, "Incoming", unknown_1328);
        int collapse_chance = ini.Get_Int(RulesSection_CombatDamage, "CollapseChance", unknown_140c);
        unknown_140c = collapse_chance;
        return true;
    }
    return false;
}
