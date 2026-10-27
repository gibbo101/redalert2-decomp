// AnimTypeClass::Read_INI (0x00425690, slot 25)
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_03HPMG@End?$AA@=007cef48
// @ref ??_C@_04CIMM@Next?$AA@=007cef20
// @ref ??_C@_04GGHG@Rate?$AA@=007cef5c
// @ref ??_C@_04JKI@Flat?$AA@=007cefdc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??_C@_05EPEB@Layer?$AA@=007ceff0
// @ref ??_C@_05IMKO@Start?$AA@=007cef4c
// @ref ??_C@_05LIK@Tiled?$AA@=007ced4c
// @ref ??_C@_06BMBE@Spawns?$AA@=007cee70
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_06DHBC@Flamer?$AA@=007cefd4
// @ref ??_C@_06HEMM@Shadow?$AA@=007cf00c
// @ref ??_C@_06ILDP@Damage?$AA@=007cef54
// @ref ??_C@_06JCLH@Sticky?$AA@=007cd8d4
// @ref ??_C@_06LKEP@Report?$AA@=007cedb8
// @ref ??_C@_06NEFL@Crater?$AA@=007cefac
// @ref ??_C@_06OKDL@Scorch?$AA@=007cefb4
// @ref ??_C@_07BEOP@Reverse?$AA@=007cef88
// @ref ??_C@_07EKPB@LoopEnd?$AA@=007cef34
// @ref ??_C@_07EMEC@Bouncer?$AA@=007ced54
// @ref ??_C@_07FLNF@IsVeins?$AA@=007cee50
// @ref ??_C@_07HOLF@MinZVel?$AA@=007cee78
// @ref ??_C@_07KNHB@ZAdjust?$AA@=007cedcc
// @ref ??_C@_07LOND@Warhead?$AA@=007ced5c
// @ref ??_C@_07OHHF@Theater?$AA@=007cf004
// @ref ??_C@_08CGML@MaxXYVel?$AA@=007cee80
// @ref ??_C@_08DCPG@PingPong?$AA@=007cef90
// @ref ??_C@_08IHLE@IsMeteor?$AA@=007cee58
// @ref ??_C@_09MJBN@StopSound?$AA@=007cedac
// @ref ??_C@_09ON@LoopCount?$AA@=007cef28
// @ref ??_C@_09POJI@LoopStart?$AA@=007cef3c
// @ref ??_C@_0BA@EFKJ@RandomLoopDelay?$AA@=007ceeec
// @ref ??_C@_0BA@FAMI@ShouldFogRemove?$AA@=007cee00
// @ref ??_C@_0BA@OFLL@ForceBigCraters?$AA@=007cef9c
// @ref ??_C@_0BB@JPDF@FreeAfterPlaying?$AA@=007cee98
// @ref ??_C@_0BC@KAB@TrailerSeperation?$AA@=007ced74
// @ref ??_C@_0BC@LFDJ@TiberiumSpawnType?$AA@=007cee24
// @ref ??_C@_0BD@HGN@IsAnimatedTiberium?$AA@=007cee10
// @ref ??_C@_0BE@ENKN@ShouldUseCellDrawer?$AA@=007ced38
// @ref ??_C@_0BF@DDPM@TiberiumSpreadRadius?$AA@=007cee38
// @ref ??_C@_0BG@OGGM@TiberiumChainReaction?$AA@=007cef64
// @ref ??_C@_0BI@OEKI@TranslucencyDetailLevel?$AA@=007ceefc
// @ref ??_C@_0L@BGFD@DemandLoad?$AA@=007ceeac
// @ref ??_C@_0L@CAKH@PsiWarning?$AA@=007cef7c
// @ref ??_C@_0L@CLCE@Normalized?$AA@=007cefc8
// @ref ??_C@_0L@CMEP@Elasticity?$AA@=007cee8c
// @ref ??_C@_0L@CNEJ@NewTheater?$AA@=007ceff8
// @ref ??_C@_0L@DJNP@ExpireAnim?$AA@=007ced94
// @ref ??_C@_0L@JDDE@BounceAnim?$AA@=007ceda0
// @ref ??_C@_0L@MCEI@AltPalette?$AA@=007cefe4
// @ref ??_C@_0L@MFM@SpawnCount?$AA@=007cee64
// @ref ??_C@_0L@OGNJ@StartSound?$AA@=007cedc0
// @ref ??_C@_0L@OLGE@RandomRate?$AA@=007ced1c
// @ref ??_C@_0L@PIJE@IsTiberium?$AA@=007ceed0
// @ref ??_C@_0M@EMBH@Translucent?$AA@=007cefbc
// @ref ??_C@_0M@FPGM@YSortAdjust?$AA@=007ceeb8
// @ref ??_C@_0M@GGAD@HideIfNoOre?$AA@=007ceec4
// @ref ??_C@_0M@GPK@YDrawOffset?$AA@=007cedd4
// @ref ??_C@_0M@IPI@TrailerAnim?$AA@=007ced88
// @ref ??_C@_0M@PNCF@DetailLevel?$AA@=007cef14
// @ref ??_C@_0N@DCNG@IsFlamingGuy?$AA@=007cedf0
// @ref ??_C@_0N@DNBP@DamageRadius?$AA@=007ced64
// @ref ??_C@_0N@LMP@Translucency?$AA@=007ceedc
// @ref ??_C@_0O@LHIF@RunningFrames?$AA@=007cede0
// @ref ??_C@_0P@PDHN@UseNormalLight?$AA@=007ced28
// The object type keys, then the animation keys from the type's own section;
// "Theater"/"NewTheater" come from the art INI when the type has an image
// name and no image yet.
#include "shared/anim_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/overlay_type.hpp"
#include "shared/warhead_type.hpp"

// The animation named by an entry (Find_Or_Make_Type over AnimTypes), else the default.
static inline AnimTypeClass *Get_Anim_Type(CCINIClass &ini, char const *section, char const *entry, AnimTypeClass *defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, "", buffer, sizeof(buffer))) {
        return Find_Or_Make_Type(buffer, AnimTypes);
    }
    return defvalue;
}

bool AnimTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
    char const *section = ID;
    bool shadow = ini.Get_Bool(section, "Shadow", Shadow);
    if (shadow != Shadow) {
        Shadow = shadow;
        if (Shadow) {
            End /= 2;
        } else {
            End *= 2;
        }
        if (LoopEnd > End) {
            LoopEnd = End;
        }
    }

    if (unknown_1c8[0] != '\0') {
        if (unknown_a4 == 0) {
            unknown_1fc = ArtINI.Get_Bool(section, "Theater", unknown_1fc);
            unknown_207 = ArtINI.Get_Bool(section, "NewTheater", unknown_207);
        }
        unknown_slot40(-1);
    }

    Layer = ini.Get_LayerType(section, "Layer", (LayerType)Layer);
    AltPalette = ArtINI.Get_Bool(section, "AltPalette", AltPalette);
    Flat = ini.Get_Bool(section, "Flat", Flat);
    Flamer = ini.Get_Bool(section, "Flamer", Flamer);
    Normalized = ini.Get_Bool(section, "Normalized", Normalized);
    Translucent = ini.Get_Bool(section, "Translucent", Translucent);
    Scorch = ini.Get_Bool(section, "Scorch", Scorch);
    Crater = ini.Get_Bool(section, "Crater", Crater);
    ForceBigCraters = ini.Get_Bool(section, "ForceBigCraters", ForceBigCraters);
    Sticky = ini.Get_Bool(section, "Sticky", Sticky);
    PingPong = ini.Get_Bool(section, "PingPong", PingPong);
    Reverse = ini.Get_Bool(section, "Reverse", Reverse);
    PsiWarning = ini.Get_Bool(section, "PsiWarning", PsiWarning);
    TiberiumChainReaction = ini.Get_Bool(section, "TiberiumChainReaction", TiberiumChainReaction);

    int rate = ini.Get_Int(section, "Rate", -1);
    if (rate != -1) {
        Rate = rate > 0 ? 900 / rate : 0;
    }

    Damage = ini.Get_Double(section, "Damage", Damage);
    Start = ini.Get_Int(section, "Start", Start);
    End = ini.Get_Int(section, "End", End);
    LoopStart = ini.Get_Int(section, "LoopStart", LoopStart);
    LoopEnd = ini.Get_Int(section, "LoopEnd", LoopEnd);
    LoopCount = ini.Get_Int(section, "LoopCount", LoopCount);

    Next = Get_Anim_Type(ini, section, "Next", Next);

    DetailLevel = ini.Get_Int(section, "DetailLevel", DetailLevel);
    TranslucencyDetailLevel = ini.Get_Int(section, "TranslucencyDetailLevel", TranslucencyDetailLevel);
    Point2D delay = ini.Get_Point(section, "RandomLoopDelay", Point2D(RandomLoopDelayMin, RandomLoopDelayMax));
    RandomLoopDelayMin = delay.X;
    RandomLoopDelayMax = delay.Y;
    Translucency = ini.Get_Int(section, "Translucency", Translucency);
    IsTiberium = ini.Get_Bool(section, "IsTiberium", IsTiberium);
    HideIfNoOre = ini.Get_Bool(section, "HideIfNoOre", HideIfNoOre);
    YSortAdjust = ini.Get_Int(section, "YSortAdjust", YSortAdjust);
    DemandLoad = ini.Get_Bool(section, "DemandLoad", DemandLoad);
    FreeAfterPlaying = ini.Get_Bool(section, "FreeAfterPlaying", FreeAfterPlaying);
    Elasticity = ini.Get_Double(section, "Elasticity", Elasticity);
    MaxXYVel = ini.Get_Double(section, "MaxXYVel", MaxXYVel);
    MinZVel = ini.Get_Double(section, "MinZVel", MinZVel);

    Spawns = Get_Anim_Type(ini, section, "Spawns", Spawns);

    SpawnCount = ini.Get_Int(section, "SpawnCount", SpawnCount);
    IsMeteor = ini.Get_Bool(section, "IsMeteor", IsMeteor);
    IsVeins = ini.Get_Bool(section, "IsVeins", IsVeins);
    TiberiumSpreadRadius = ini.Get_Int(section, "TiberiumSpreadRadius", TiberiumSpreadRadius);
    TiberiumSpawnType = Get_Type(ini, section, "TiberiumSpawnType", TiberiumSpawnType);
    IsAnimatedTiberium = ini.Get_Bool(section, "IsAnimatedTiberium", IsAnimatedTiberium);
    ShouldFogRemove = ini.Get_Bool(section, "ShouldFogRemove", ShouldFogRemove);
    IsFlamingGuy = ini.Get_Bool(section, "IsFlamingGuy", IsFlamingGuy);
    RunningFrames = ini.Get_Int(section, "RunningFrames", RunningFrames);
    YDrawOffset = ini.Get_Int(section, "YDrawOffset", YDrawOffset);
    ZAdjust = ini.Get_Int(section, "ZAdjust", ZAdjust);

    StartSound = Get_Sound(ini, section, "StartSound", StartSound);
    if (StartSound == -1) {
        StartSound = Get_Sound(ini, section, "Report", -1);
    }
    StopSound = Get_Sound(ini, section, "StopSound", StopSound);

    BounceAnim = Get_Type(ini, section, "BounceAnim", BounceAnim);
    ExpireAnim = Get_Type(ini, section, "ExpireAnim", ExpireAnim);
    TrailerAnim = Get_Type(ini, section, "TrailerAnim", TrailerAnim);
    TrailerSeperation = ini.Get_Int(section, "TrailerSeperation", TrailerSeperation);
    DamageRadius = ini.Get_Int(section, "DamageRadius", DamageRadius);
    Warhead = Get_Type(ini, section, "Warhead", Warhead);
    Bouncer = ini.Get_Bool(section, "Bouncer", Bouncer);
    Tiled = ini.Get_Bool(section, "Tiled", Tiled);
    ShouldUseCellDrawer = ini.Get_Bool(section, "ShouldUseCellDrawer", ShouldUseCellDrawer);
    UseNormalLight = ini.Get_Bool(section, "UseNormalLight", UseNormalLight);

    Point2D rates = ini.Get_Point(section, "RandomRate", Point2D(-1, -1));
    if (rates.X != -1) {
        RandomRateMin = rates.X > 0 ? 900 / rates.X : 0;
    }
    if (rates.Y != -1) {
        RandomRateMax = rates.Y > 0 ? 900 / rates.Y : 0;
    }
    if (RandomRateMax < 0) {
        RandomRateMax = 0;
    }
    if (RandomRateMin > RandomRateMax) {
        RandomRateMin = RandomRateMax;
    }
    return true;
    }
    return false;
}
