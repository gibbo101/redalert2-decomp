// bool WarheadTypeClass::Read_INI(CCINIClass &ini) (0x007204E0)
// The warhead's keys when its section exists. Verses= lists eleven armor
// modifiers, each a percentage ("50%") or a plain factor; a warhead that
// does nothing against armor types 4 and 6 is flagged (unknown_148).
#include "shared/warhead_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/anim_type.hpp"
// @ref ?Find_Section@INIClass@@QBEPAUINISection@1@PBD@Z=0050c9b0
// @ref ??0?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE@IPBQAVAnimTypeClass@@@Z=0050b480
// @ref ?Add@?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE_NABQAVAnimTypeClass@@@Z=0050b590
// @ref ??4?$VectorClass@PAVAnimTypeClass@@@@QAEAAV0@ABV0@@Z=006534d0
// @ref ?Find_Or_Make_ParticleSystemType_00620df0@@YIPAVParticleSystemTypeClass@@PBD@Z=00620df0
// @ref ?Clear@?$VectorClass@PAVAnimTypeClass@@@@UAEXXZ=0050b3f0
// @ref _strtok=00782ec2
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref _strchr=00784130
// @ref _atoi=00782dfd
// @ref _atof=00782f66
// @ref ??_7?$DynamicVectorClass@PAVAnimTypeClass@@@@6B@=007a3b7c
// @ref ??_G?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ??0?$TypeList@PAVAnimTypeClass@@@@QAE@ABV0@@Z=0050b7d0
// @ref ??_C@_04EBFF@Fire?$AA@=007ebffc
// @ref ??_C@_04OEDL@Wood?$AA@=007fb36c
// @ref ??_C@_04PHLO@Wall?$AA@=007d0fa8
// @ref ??_C@_05KKKK@Sonic?$AA@=007fb35c
// @ref ??_C@_06BPH@Verses?$AA@=007fb1d8
// @ref ??_C@_06EABP@Deform?$AA@=007fb2fc
// @ref ??_C@_06ELMO@Sparky?$AA@=007fb364
// @ref ??_C@_06HNCM@Rocker?$AA@=007fb354
// @ref ??_C@_06LKBM@Bright?$AA@=007fb34c
// @ref ??_C@_07EDBM@Bullets?$AA@=007fb260
// @ref ??_C@_07EEOC@Culling?$AA@=007fb2a0
// @ref ??_C@_08BMEK@ShakeYhi?$AA@=007fb224
// @ref ??_C@_08CNIF@IvanBomb?$AA@=007d1c74
// @ref ??_C@_08EAIC@Tiberium?$AA@=007cdcd0
// @ref ??_C@_08EOFM@ShakeXhi?$AA@=007fb23c
// @ref ??_C@_08FFNH@Particle?$AA@=007cdddc
// @ref ??_C@_08FLGD@AnimList?$AA@=007fb310
// @ref ??_C@_08KIAN@Veinhole?$AA@=007fb254
// @ref ??_C@_08KJEC@Parasite?$AA@=007cdbd4
// @ref ??_C@_08LJJC@ShakeYlo?$AA@=007fb230
// @ref ??_C@_08MCD@EMEffect?$AA@=007fb2dc
// @ref ??_C@_08OLIE@ShakeXlo?$AA@=007fb248
// @ref ??_C@_08PJCH@InfDeath?$AA@=007fb304
// @ref ??_C@_08PLCG@Temporal?$AA@=007cdbc0
// @ref ??_C@_09BCCG@Paralyzes?$AA@=007fb2a8
// @ref ??_C@_09DMND@Radiation?$AA@=007eecc8
// @ref ??_C@_09FIKO@CellInset?$AA@=007fb3ec
// @ref ??_C@_09OMDB@NukeMaker?$AA@=007fb284
// @ref ??_C@_0BA@DHPB@ElectricAssault?$AA@=007fb2c0
// @ref ??_C@_0BA@GLOA@CombatLightSize?$AA@=007fb39c
// @ref ??_C@_0BA@HCGA@CausesDelayKill?$AA@=007fb3cc
// @ref ??_C@_0BA@PGIP@DelayKillFrames?$AA@=007fb3bc
// @ref ??_C@_0BB@LCHC@DeformThreshhold?$AA@=007fb2e8
// @ref ??_C@_0BG@MHHK@WallAbsoluteDestroyer?$AA@=007fb374
// @ref ??_C@_0EC@FCPK@100?$CF?$CF?0100?$CF?$CF?0100?$CF?$CF?0100?$CF?$CF?0100?$CF?$CF?010@=007fb1e0
// @ref ??_C@_0L@CNDM@CellSpread?$AA@=007fb3f8
// @ref ??_C@_0L@DMJI@BombDisarm?$AA@=007fb2b4
// @ref ??_C@_0M@HJBC@MindControl?$AA@=007fb2d0
// @ref ??_C@_0M@PBAE@ProneDamage?$AA@=007fb278
// @ref ??_C@_0N@DKC@CLDisableRed?$AA@=007fb33c
// @ref ??_C@_0N@MJEH@PercentAtMax?$AA@=007fb3dc
// @ref ??_C@_0N@NAGB@Conventional?$AA@=007fb38c
// @ref ??_C@_0O@GCAP@MakesDisguise?$AA@=007fb290
// @ref ??_C@_0O@IKGJ@CLDisableBlue?$AA@=007fb31c
// @ref ??_C@_0O@NPGG@PsychicDamage?$AA@=007fb268
// @ref ??_C@_0P@FBIK@DelayKillAtMax?$AA@=007fb3ac
// @ref ??_C@_0P@JPOH@CLDisableGreen?$AA@=007fb32c

extern "C" char *__cdecl strtok(char *string, char const *delimiters);
extern "C" char *__cdecl strchr(char const *string, int character);
extern "C" double __cdecl atof(char const *string);

static inline bool Is_Zero(double value)
{
    return value == 0.0;
}

static inline ParticleSystemTypeClass *Get_Particle_System(CCINIClass &ini, char const *section, char const *entry, ParticleSystemTypeClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return Find_Or_Make_ParticleSystemType_00620df0(name);
    }
    return defvalue;
}

static inline TypeList<AnimTypeClass *> Get_Anim_List(CCINIClass &ini, char const *section, char const *entry,
                                                      TypeList<AnimTypeClass *> const &defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) {
        TypeList<AnimTypeClass *> list;
        for (char *name = strtok(buffer, ","); name != 0 && *name != 0; name = strtok(0, ",")) {
            AnimTypeClass *anim = AnimTypeClass::Find_Or_Make(name);
            if (anim != 0) {
                list.Add(anim);
            }
        }
        return list;
    }
    return defvalue;
}

bool WarheadTypeClass::Read_INI(CCINIClass &ini)
{
    if (ini.Is_Present(ID)) {
        CellSpread = ini.Get_Double(ID, "CellSpread", CellSpread);
        CellInset = ini.Get_Double(ID, "CellInset", CellInset);
        PercentAtMax = ini.Get_Double(ID, "PercentAtMax", PercentAtMax);
        CausesDelayKill = ini.Get_Bool(ID, "CausesDelayKill", CausesDelayKill);
        DelayKillFrames = ini.Get_Int(ID, "DelayKillFrames", DelayKillFrames);
        DelayKillAtMax = ini.Get_Double(ID, "DelayKillAtMax", DelayKillAtMax);
        CombatLightSize = ini.Get_Double(ID, "CombatLightSize", CombatLightSize);
        Particle = Get_Particle_System(ini, ID, "Particle", Particle);
        Conventional = ini.Get_Bool(ID, "Conventional", Conventional);
        Wall = ini.Get_Bool(ID, "Wall", Wall);
        WallAbsoluteDestroyer = ini.Get_Bool(ID, "WallAbsoluteDestroyer", WallAbsoluteDestroyer);
        Wood = ini.Get_Bool(ID, "Wood", Wood);
        Tiberium = ini.Get_Bool(ID, "Tiberium", Tiberium);
        Sparky = ini.Get_Bool(ID, "Sparky", Sparky);
        Sonic = ini.Get_Bool(ID, "Sonic", Sonic);
        Rocker = ini.Get_Bool(ID, "Rocker", Rocker);
        Fire = ini.Get_Bool(ID, "Fire", Fire);
        Bright = ini.Get_Bool(ID, "Bright", Bright);
        CLDisableRed = ini.Get_Bool(ID, "CLDisableRed", CLDisableRed);
        CLDisableGreen = ini.Get_Bool(ID, "CLDisableGreen", CLDisableGreen);
        CLDisableBlue = ini.Get_Bool(ID, "CLDisableBlue", CLDisableBlue);
        AnimList = Get_Anim_List(ini, ID, "AnimList", AnimList);
        InfDeath = ini.Get_Int(ID, "InfDeath", InfDeath);
        Deform = ini.Get_Double(ID, "Deform", Deform);
        DeformThreshhold = ini.Get_Int(ID, "DeformThreshhold", DeformThreshhold);
        EMEffect = ini.Get_Bool(ID, "EMEffect", EMEffect);
        MindControl = ini.Get_Bool(ID, "MindControl", MindControl);
        IvanBomb = ini.Get_Bool(ID, "IvanBomb", IvanBomb);
        ElectricAssault = ini.Get_Bool(ID, "ElectricAssault", ElectricAssault);
        Parasite = ini.Get_Bool(ID, "Parasite", Parasite);
        Temporal = ini.Get_Bool(ID, "Temporal", Temporal);
        BombDisarm = ini.Get_Bool(ID, "BombDisarm", BombDisarm);
        Paralyzes = ini.Get_Int(ID, "Paralyzes", Paralyzes);
        Culling = ini.Get_Bool(ID, "Culling", Culling);
        MakesDisguise = ini.Get_Bool(ID, "MakesDisguise", MakesDisguise);
        NukeMaker = ini.Get_Bool(ID, "NukeMaker", NukeMaker);
        ProneDamage = ini.Get_Double(ID, "ProneDamage", ProneDamage);
        Radiation = ini.Get_Bool(ID, "Radiation", Radiation);
        PsychicDamage = ini.Get_Bool(ID, "PsychicDamage", PsychicDamage);
        Bullets = ini.Get_Bool(ID, "Bullets", Bullets);
        Veinhole = ini.Get_Bool(ID, "Veinhole", Veinhole);
        ShakeXlo = ini.Get_Int(ID, "ShakeXlo", ShakeXlo);
        ShakeXhi = ini.Get_Int(ID, "ShakeXhi", ShakeXhi);
        ShakeYlo = ini.Get_Int(ID, "ShakeYlo", ShakeYlo);
        ShakeYhi = ini.Get_Int(ID, "ShakeYhi", ShakeYhi);
        char buffer[128];
        if (ini.Get_String(ID, "Verses", "100%%,100%%,100%%,100%%,100%%,100%%,100%%,100%%,100%%,100%%,100%%", buffer, sizeof(buffer))) {
            char *token = strtok(buffer, ",");
            for (int index = 0; index < 11; index++) {
                double percent = Percent_Value(token);
                Verses[index] = percent;
                token = strtok(0, ",");
            }
        }
        unknown_148 = Is_Zero(Verses[4]) && Is_Zero(Verses[6]);
        return true;
    }
    return false;
}
