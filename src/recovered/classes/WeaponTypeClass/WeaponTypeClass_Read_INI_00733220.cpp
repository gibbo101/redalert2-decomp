// WeaponTypeClass::Read_INI (0x00733220)
// Reads the weapon's rules.ini section; the section must exist.
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_03CEPL@ROF?$AA@=007dae30
// @ref ??_C@_04LFDA@Anim?$AA@=007cdea0
// @ref ??_C@_05MCCK@Range?$AA@=007f9afc
// @ref ??_C@_05MKHH@Burst?$AA@=007fc920
// @ref ??_C@_05PDDA@Speed?$AA@=007d381c
// @ref ??_C@_06BABO@Lobber?$AA@=007fc87c
// @ref ??_C@_06ILDP@Damage?$AA@=007cef54
// @ref ??_C@_06KHPA@Camera?$AA@=007fc8fc
// @ref ??_C@_06LKBM@Bright?$AA@=007fb34c
// @ref ??_C@_06LKEP@Report?$AA@=007cedb8
// @ref ??_C@_07ED@Charges?$AA@=007fc8dc
// @ref ??_C@_07GNBF@IsSonic?$AA@=007fc9d8
// @ref ??_C@_07JAAJ@Suicide?$AA@=007f706c
// @ref ??_C@_07LMGG@IsLaser?$AA@=007fc8f4
// @ref ??_C@_07LOND@Warhead?$AA@=007ced5c
// @ref ??_C@_07MGDB@Supress?$AA@=007fc928
// @ref ??_C@_07MGDE@Spawner?$AA@=007fc9d0
// @ref ??_C@_08DMLC@RadLevel?$AA@=007fc7b4
// @ref ??_C@_08EJCM@NeverUse?$AA@=007fc988
// @ref ??_C@_08HDIF@AreaFire?$AA@=007fc810
// @ref ??_C@_08JKFC@FireOnce?$AA@=007fc994
// @ref ??_C@_08MEMC@OmniFire?$AA@=007fc8a8
// @ref ??_C@_09MKCM@IsRadBeam?$AA@=007fc7d0
// @ref ??_C@_09NPBP@IsRailgun?$AA@=007fc884
// @ref ??_C@_0BA@IEIF@LaserInnerColor?$AA@=007fc86c
// @ref ??_C@_0BA@IHND@LaserOuterColor?$AA@=007fc85c
// @ref ??_C@_0BA@MNNL@DrawBoltAsLaser?$AA@=007fc7f0
// @ref ??_C@_0BB@FLA@DisguiseFireOnly?$AA@=007fc948
// @ref ??_C@_0BB@GCOP@LaserOuterSpread?$AA@=007fc848
// @ref ??_C@_0BB@HEDD@IsAlternateColor?$AA@=007fc7dc
// @ref ??_C@_0BB@HJMO@UseFireParticles?$AA@=007fc8c8
// @ref ??_C@_0BB@JLD@CellRangefinding?$AA@=007fc9a0
// @ref ??_C@_0BC@GNAD@UseSparkParticles?$AA@=007fc8b4
// @ref ??_C@_0BG@MDCK@DisguiseFakeBlinkTime?$AA@=007fc930
// @ref ??_C@_0BG@PPEK@DistributedWeaponFire?$AA@=007fc890
// @ref ??_C@_0BH@NGKJ@AttachedParticleSystem?$AA@=007fc79c
// @ref ??_C@_0L@DABG@Projectile?$AA@=007fc790
// @ref ??_C@_0L@EBLO@IsBigLaser?$AA@=007fc82c
// @ref ??_C@_0L@PMPC@TurboBoost?$AA@=007efb78
// @ref ??_C@_0M@EOEH@TerrainFire?$AA@=007fc96c
// @ref ??_C@_0M@ILKM@LimboLaunch?$AA@=007fc9c4
// @ref ??_C@_0M@MFAM@AssaultAnim?$AA@=007fc904
// @ref ??_C@_0N@FFBI@IonSensitive?$AA@=007fc81c
// @ref ??_C@_0N@FGDK@RevealOnFire?$AA@=007fc978
// @ref ??_C@_0N@HLJL@IsHouseColor?$AA@=007fc8e4
// @ref ??_C@_0N@IDNJ@MinimumRange?$AA@=007fc910
// @ref ??_C@_0O@HEHC@LaserDuration?$AA@=007fc838
// @ref ??_C@_0O@HOPG@DecloakToFire?$AA@=007fc9b4
// @ref ??_C@_0O@IDEP@IsRadEruption?$AA@=007fc7c0
// @ref ??_C@_0O@OGIA@AmbientDamage?$AA@=007fc9e0
// @ref ??_C@_0P@FJHJ@IsElectricBolt?$AA@=007fc800
// @ref ??_C@_0P@JGON@SabotageCursor?$AA@=007fc95c
// @ref ??B?$FixedString@$0BJ@@@QBEPBDXZ=0050b0e0
#include "shared/weapon_type.hpp"
#include "shared/particle_system.hpp"
#include "shared/anim_type.hpp"

bool WeaponTypeClass::Read_INI(CCINIClass &ini)
{
    if (ini.Is_Present(ID)) {
        unknown_98 = ini.Get_Int(ID, "AmbientDamage", unknown_98);
        unknown_10c = ini.Get_Bool(ID, "IsSonic", unknown_10c);
        unknown_10d = ini.Get_Bool(ID, "Spawner", unknown_10d);
        unknown_10e = ini.Get_Bool(ID, "LimboLaunch", unknown_10e);
        unknown_10f = ini.Get_Bool(ID, "DecloakToFire", unknown_10f);
        unknown_110 = ini.Get_Bool(ID, "CellRangefinding", unknown_110);
        unknown_111 = ini.Get_Bool(ID, "FireOnce", unknown_111);
        unknown_112 = ini.Get_Bool(ID, "NeverUse", unknown_112);
        unknown_113 = ini.Get_Bool(ID, "RevealOnFire", unknown_113);
        unknown_114 = ini.Get_Bool(ID, "TerrainFire", unknown_114);
        unknown_115 = ini.Get_Bool(ID, "SabotageCursor", unknown_115);
        unknown_116 = ini.Get_Bool(ID, "DisguiseFireOnly", unknown_116);
        unknown_118 = ini.Get_Int(ID, "DisguiseFakeBlinkTime", unknown_118);
        unknown_11c = ini.Get_Bool(ID, "Suicide", unknown_11c);
        unknown_11e = ini.Get_Bool(ID, "Supress", unknown_11e);
        Burst = ini.Get_Int(ID, "Burst", Burst);
        unknown_a4 = ini.Get_Int(ID, "Damage", unknown_a4);
        unknown_a8 = ini.Get_Percent(ID, "Speed", unknown_a8);
        unknown_b0 = ini.Get_Int(ID, "ROF", unknown_b0);
        unknown_b4 = ini.Get_Lepton(ID, "Range", unknown_b4);
        unknown_b8 = ini.Get_Lepton(ID, "MinimumRange", unknown_b8);
        unknown_bc = Get_Voc_List(ini, ID, "Report", unknown_bc);
        Anim = TypeListReader<AnimTypeClass>::Get(ini, ID, "Anim", Anim);
        unknown_f4 = Get_Type(ini, ID, "AssaultAnim", unknown_f4);
        unknown_11f = ini.Get_Bool(ID, "Camera", unknown_11f);
        unknown_121 = ini.Get_Bool(ID, "IsLaser", unknown_121);
        unknown_123 = ini.Get_Bool(ID, "IsHouseColor", unknown_123);
        unknown_120 = ini.Get_Bool(ID, "Charges", unknown_120);
        unknown_11d = ini.Get_Bool(ID, "TurboBoost", unknown_11d);
        unknown_105 = ini.Get_Bool(ID, "UseFireParticles", unknown_105);
        unknown_106 = ini.Get_Bool(ID, "UseSparkParticles", unknown_106);
        unknown_107 = ini.Get_Bool(ID, "OmniFire", unknown_107);
        unknown_108 = ini.Get_Bool(ID, "DistributedWeaponFire", unknown_108);
        unknown_109 = ini.Get_Bool(ID, "IsRailgun", unknown_109);
        unknown_10a = ini.Get_Bool(ID, "Lobber", unknown_10a);
        unknown_fc = ini.Get_RGB(ID, "LaserInnerColor", unknown_fc);
        unknown_ff = ini.Get_RGB(ID, "LaserOuterColor", unknown_ff);
        unknown_102 = ini.Get_RGB(ID, "LaserOuterSpread", unknown_102);
        unknown_124 = ini.Get_Int(ID, "LaserDuration", unknown_124);
        unknown_122 = ini.Get_Bool(ID, "IsBigLaser", unknown_122);
        unknown_10b = ini.Get_Bool(ID, "Bright", unknown_10b);
        unknown_125 = ini.Get_Bool(ID, "IonSensitive", unknown_125);
        unknown_126 = ini.Get_Bool(ID, "AreaFire", unknown_126);
        unknown_127 = ini.Get_Bool(ID, "IsElectricBolt", unknown_127);
        unknown_128 = ini.Get_Bool(ID, "DrawBoltAsLaser", unknown_128);
        unknown_129 = ini.Get_Bool(ID, "IsAlternateColor", unknown_129);
        unknown_12a = ini.Get_Bool(ID, "IsRadBeam", unknown_12a);
        unknown_12b = ini.Get_Bool(ID, "IsRadEruption", unknown_12b);
        unknown_12c = ini.Get_Int(ID, "RadLevel", unknown_12c);
        char system[20];
        system[0] = 0;
        ini.Get_String(ID, "AttachedParticleSystem", system, system, sizeof(system));
        int index = ParticleSystemTypeClass::Index_Or_Make(system);
        if (index != -1) {
            unknown_f8 = ParticleSystemTypes[index];
        }
        Warhead = Get_Type(ini, ID, "Warhead", Warhead);
        Projectile = Get_Type(ini, ID, "Projectile", Projectile);
        return true;
    }
    return false;
}
