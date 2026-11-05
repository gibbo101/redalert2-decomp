// Unit type rules/art loading, original0x0070AB40.
#include "shared/unit_type.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/crt_string.hpp"
// @ref ?Read_INI@TechnoTypeClass@@UAE_NAAVCCINIClass@@@Z=006daf60
// @ref ?Set_Turret_Weapon@TechnoTypeClass@@QAEXHH@Z=006df690
bool UnitTypeClass::Read_INI(CCINIClass &ini)
{
    if (TechnoTypeClass::Read_INI(ini)) {
        char const *section = ID;
        CrateGoodie = ini.Get_Bool(section, "CrateGoodie", CrateGoodie);
        DeployToFire = ini.Get_Bool(section, "DeployToFire", DeployToFire);
        IsSimpleDeployer = ini.Get_Bool(section, "IsSimpleDeployer", IsSimpleDeployer);
        Harvester = ini.Get_Bool(section, "Harvester", Harvester);
        Weeder = ini.Get_Bool(section, "Weeder", Weeder);
        if (SpeedType == -1) SpeedType = Crusher ? 1 : 2;
        SpeedType = ini.Get_SpeedType(section, "SpeedType", (::SpeedType)SpeedType);
        IsTilter = ini.Get_Bool(section, "IsTilter", IsTilter);
        CarriesCrate = ini.Get_Bool(section, "CarriesCrate", CarriesCrate);
        unknown_ba9 = !Turret;
        TooBigToFitUnderBridge = ini.Get_Bool(section, "TooBigToFitUnderBridge", TooBigToFitUnderBridge);
        (INIPoint3D &)HalfDamageSmokeLocation = ini.Get_Point(section, "HalfDamageSmokeLocation", (INIPoint3D const &)HalfDamageSmokeLocation);
        unknown_368 = 15;
        if (Harvester || Weeder) unknown_368 = 10;
        char const *art_section = unknown_1c8;
        UseTurretShadow = ArtINI.Get_Bool(art_section, "UseTurretShadow", UseTurretShadow);
        WalkFrames = (char)ArtINI.Get_Int(art_section, "WalkFrames", WalkFrames);
        FiringFrames = (char)ArtINI.Get_Int(art_section, "FiringFrames", FiringFrames);
        Passive = ini.Get_Bool(section, "Passive", Passive);
        MovementRestrictedTo = ini.Get_LandType(section, "MovementRestrictedTo", (LandType)MovementRestrictedTo);
        CanBeach = ini.Get_Bool(section, "CanBeach", CanBeach);
        SmallVisceroid = ini.Get_Bool(section, "SmallVisceroid", SmallVisceroid);
        LargeVisceroid = ini.Get_Bool(section, "LargeVisceroid", LargeVisceroid);
        NonVehicle = ini.Get_Bool(section, "NonVehicle", NonVehicle);
        if (FiringFrames > 0) StandingFrames = 1;
        StandingFrames = ArtINI.Get_Int(art_section, "StandingFrames", StandingFrames);
        DeathFrames = ArtINI.Get_Int(art_section, "DeathFrames", DeathFrames);
        DeathFrameRate = ArtINI.Get_Int(art_section, "DeathFrameRate", DeathFrameRate);
        if (DeathFrameRate < 1) DeathFrameRate = 1;
        if (!FiringFrames && !Turret) Facings = 1;
        Facings = ArtINI.Get_Int(art_section, "Facings", Facings);
        if (StartWalkFrame == -1) StartWalkFrame = 0;
        if (StartStandFrame == -1) StartStandFrame = StandingFrames == 0 ? StartWalkFrame : WalkFrames * Facings;
        if (StartFiringFrame == -1) StartFiringFrame = FiringFrames == 0 ? StartStandFrame : (WalkFrames + StandingFrames) * Facings;
        if (StartDeathFrame == -1) {
            StartDeathFrame = DeathFrames == 0 ? -1 : (FiringFrames + 1 + WalkFrames) * Facings;
            MaxDeathCounter = StartDeathFrame + DeathFrames;
        }
        StartStandFrame = ArtINI.Get_Int(art_section, "StartStandFrame", StartStandFrame);
        StartWalkFrame = ArtINI.Get_Int(art_section, "StartWalkFrame", StartWalkFrame);
        StartFiringFrame = ArtINI.Get_Int(art_section, "StartFiringFrame", StartFiringFrame);
        StartDeathFrame = ArtINI.Get_Int(art_section, "StartDeathFrame", StartDeathFrame);
        MaxDeathCounter = ArtINI.Get_Int(art_section, "MaxDeathCounter", MaxDeathCounter);
        for (int sync = 0; sync < 2; ++sync) {
            char key[20];
            sprintf(key, "FiringSyncFrame%d", sync);
            FiringSyncFrame[sync] = ArtINI.Get_Int(art_section, key, FiringSyncFrame[sync]);
        }
        for (int burst = 0; burst < 4; ++burst) {
            char key[20];
            sprintf(key, "BurstDelay%d", burst);
            BurstDelay[burst] = ini.Get_Int(section, key, BurstDelay[burst]);
        }
        char default_image[25];
        strcpy(default_image, AltImageFile);
        ini.Get_String(section, "AltImage", default_image, AltImageFile.Buffer, sizeof(AltImageFile));
        char filename[260];
        _makepath(filename, 0, 0, AltImageFile, ".SHP");
        AltImage = MixFileClass::Retrieve(filename);
        if (*this == "FV") {
            {
                int turret = ini.Get_Int(section, "NormalTurretIndex", 0);
                int weapon = ini.Get_Int(section, "NormalTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "RepairTurretIndex", 1);
                int weapon = ini.Get_Int(section, "RepairTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "MachineGunTurretIndex", 2);
                int weapon = ini.Get_Int(section, "MachineGunTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "FlakTurretIndex", 3);
                int weapon = ini.Get_Int(section, "FlakTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "PistolTurretIndex", 0);
                int weapon = ini.Get_Int(section, "PistolTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "SniperTurretIndex", 0);
                int weapon = ini.Get_Int(section, "SniperTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "ShockTurretIndex", 0);
                int weapon = ini.Get_Int(section, "ShockTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "ExplodeTurretIndex", 0);
                int weapon = ini.Get_Int(section, "ExplodeTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "BrainBlastTurretIndex", 0);
                int weapon = ini.Get_Int(section, "BrainBlastTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "RadCannonTurretIndex", 0);
                int weapon = ini.Get_Int(section, "RadCannonTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "ChronoTurretIndex", 0);
                int weapon = ini.Get_Int(section, "ChronoTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "TerroristExplodeTurretIndex", 0);
                int weapon = ini.Get_Int(section, "TerroristExplodeTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
            {
                int turret = ini.Get_Int(section, "CowTurretIndex", 0);
                int weapon = ini.Get_Int(section, "CowTurretWeapon", -1);
                Set_Turret_Weapon(turret, weapon);
            }
        }
        return true;
    }
    return false;
}

// @ref ??_C@_02COJI@FV?$AA@=007f9254
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref ??_C@_06OFE@Weeder?$AA@=007d0fa0
// @ref ??_C@_07BDNK@Facings?$AA@=007f92dc
// @ref ??_C@_07LONN@Passive?$AA@=007f9340
// @ref ??_C@_08JKBF@AltImage?$AA@=007f9258
// @ref ??_C@_08PAGE@IsTilter?$AA@=007f93b4
// @ref ??_C@_08PDGJ@CanBeach?$AA@=007f931c
// @ref ??_C@_09FPHJ@SpeedType?$AA@=007f80b8
// @ref ??_C@_09IBOJ@Harvester?$AA@=007f1a28
// @ref ??_C@_0BA@CHMM@FlakTurretIndex?$AA@=007f91c4
// @ref ??_C@_0BA@EKKK@StartDeathFrame?$AA@=007f9298
// @ref ??_C@_0BA@HMMD@UseTurretShadow?$AA@=007f9364
// @ref ??_C@_0BA@JMLN@MaxDeathCounter?$AA@=007f9288
// @ref ??_C@_0BA@KCKP@CowTurretWeapon?$AA@=007f902c
// @ref ??_C@_0BA@MEFG@StartStandFrame?$AA@=007f92cc
// @ref ??_C@_0BB@BCND@IsSimpleDeployer?$AA@=007f93c0
// @ref ??_C@_0BB@BIL@FlakTurretWeapon?$AA@=007f91b0
// @ref ??_C@_0BB@EFCJ@StartFiringFrame?$AA@=007f92a8
// @ref ??_C@_0BB@KFOI@ShockTurretIndex?$AA@=007f914c
// @ref ??_C@_0BC@GLIO@ChronoTurretIndex?$AA@=007f909c
// @ref ??_C@_0BC@KCAJ@ShockTurretWeapon?$AA@=007f9138
// @ref ??_C@_0BC@MAJI@NormalTurretIndex?$AA@=007f9240
// @ref ??_C@_0BC@NGKO@PistolTurretIndex?$AA@=007f919c
// @ref ??_C@_0BC@OALE@SniperTurretIndex?$AA@=007f9174
// @ref ??_C@_0BC@OOPP@RepairTurretIndex?$AA@=007f9218
// @ref ??_C@_0BC@PIFC@FiringSyncFrame?$CFd?$AA@=007f9274
// @ref ??_C@_0BD@BACG@ExplodeTurretIndex?$AA@=007f9124
// @ref ??_C@_0BD@DCHK@PistolTurretWeapon?$AA@=007f9188
// @ref ??_C@_0BD@FDEC@RepairTurretWeapon?$AA@=007f9204
// @ref ??_C@_0BD@JJGM@NormalTurretWeapon?$AA@=007f922c
// @ref ??_C@_0BD@KDEM@SniperTurretWeapon?$AA@=007f9160
// @ref ??_C@_0BD@KNMH@ChronoTurretWeapon?$AA@=007f9088
// @ref ??_C@_0BE@LM@ExplodeTurretWeapon?$AA@=007f9110
// @ref ??_C@_0BF@IHBL@RadCannonTurretIndex?$AA@=007f90c8
// @ref ??_C@_0BF@KLGA@MovementRestrictedTo?$AA@=007f9328
// @ref ??_C@_0BG@BGCL@RadCannonTurretWeapon?$AA@=007f90b0
// @ref ??_C@_0BG@CKPF@BrainBlastTurretIndex?$AA@=007f90f8
// @ref ??_C@_0BG@KHJO@MachineGunTurretIndex?$AA@=007f91ec
// @ref ??_C@_0BH@BKAL@MachineGunTurretWeapon?$AA@=007f91d4
// @ref ??_C@_0BH@HBEL@TooBigToFitUnderBridge?$AA@=007f938c
// @ref ??_C@_0BH@JAIG@BrainBlastTurretWeapon?$AA@=007f90e0
// @ref ??_C@_0BI@PINE@HalfDamageSmokeLocation?$AA@=007f9374
// @ref ??_C@_0BM@BKDD@TerroristExplodeTurretIndex?$AA@=007f906c
// @ref ??_C@_0BN@NLG@TerroristExplodeTurretWeapon?$AA@=007f904c
// @ref ??_C@_0L@MIEL@NonVehicle?$AA@=007f9310
// @ref ??_C@_0L@PLOM@WalkFrames?$AA@=007f9358
// @ref ??_C@_0M@EHAP@CrateGoodie?$AA@=007f93e4
// @ref ??_C@_0M@FJOJ@DeathFrames?$AA@=007f92f4
// @ref ??_C@_0N@HBKF@DeployToFire?$AA@=007f93d4
// @ref ??_C@_0N@KFKM@FiringFrames?$AA@=007f9348
// @ref ??_C@_0N@LNKO@CarriesCrate?$AA@=007f93a4
// @ref ??_C@_0N@PCGG@BurstDelay?$CFd?$AA@=007f9264
// @ref ??_C@_0P@DFM@CowTurretIndex?$AA@=007f903c
// @ref ??_C@_0P@DPBO@StartWalkFrame?$AA@=007f92bc
// @ref ??_C@_0P@HIDM@DeathFrameRate?$AA@=007f92e4
// @ref ??_C@_0P@IEHO@StandingFrames?$AA@=007f9300
// @ref ??_C@_0P@LKBE@LargeVisceroid?$AA@=007f14e8
// @ref ??_C@_0P@OAEO@SmallVisceroid?$AA@=007f14d8
