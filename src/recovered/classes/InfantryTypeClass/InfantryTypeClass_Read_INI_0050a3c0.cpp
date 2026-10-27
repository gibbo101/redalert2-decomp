// bool InfantryTypeClass::Read_INI(CCINIClass &ini) (0x0050A3C0)
// The techno keys, then the infantry keys (rules section) and the art
// keys (image section); cyborgs are flagged (unknown_a9b) and C4,
// engineers and agents can infiltrate; finally the sequence table.
#include "shared/infantry_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/anim_type.hpp"
#include "shared/aircraft_type.hpp"
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
// @ref ??_C@_08NIHI@Civilian?$AA@=007ceb30
// @ref ??4?$VectorClass@H@@QAEAAV0@ABV0@@Z=0046db60
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_7?$DynamicVectorClass@PAVAnimTypeClass@@@@6B@=007a3b7c
// @ref ??_G?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_G?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ?Read_INI@TechnoTypeClass@@UAE_NAAVCCINIClass@@@Z=006daf60
// @ref ?Get_PipType@CCINIClass@@QBEHPBD0H@Z=00469d60
// @ref ?Get_Voc_List@@YI?AV?$TypeList@H@@AAVCCINIClass@@PBD1V1@@Z=0050b610
// @ref ??B?$FixedString@$0BJ@@@QBEPBDXZ=0050b0e0
// @ref ??0?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE@IPBQAVAnimTypeClass@@@Z=0050b480
// @ref ?Add@?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE_NABQAVAnimTypeClass@@@Z=0050b590
// @ref ??4?$DynamicVectorClass@PAVAnimTypeClass@@@@QAEAAV0@ABV0@@Z=0050b160
// @ref ?Read_Sequence@InfantryTypeClass@@QAEXXZ=0050a0e0
// @ref ?From_Name@VocClass@@SIHPBD@Z=00714940
// @ref ??_C@_02MAJG@C4?$AA@=007db294
// @ref ??_C@_03CGJJ@Pip?$AA@=007db34c
// @ref ??_C@_04GEJC@Ivan?$AA@=007db2c4
// @ref ??_C@_05DJGL@Agent?$AA@=007db270
// @ref ??_C@_05GBLK@Thief?$AA@=007db268
// @ref ??_C@_06CLAJ@Crawls?$AA@=007db23c
// @ref ??_C@_06ECC@Doggie?$AA@=007db250
// @ref ??_C@_06FHBF@FireUp?$AA@=007db130
// @ref ??_C@_06LPEL@Cyborg?$AA@=007db31c
// @ref ??_C@_08ENHF@Fearless?$AA@=007db2e4
// @ref ??_C@_08GNDP@Occupier?$AA@=007db2b8
// @ref ??_C@_08ILJD@NotHuman?$AA@=007db310
// @ref ??_C@_08PAJI@Deployer?$AA@=007db244
// @ref ??_C@_08PBKA@Engineer?$AA@=007db288
// @ref ??_C@_09DLMH@Fraidycat?$AA@=007db2d8
// @ref ??_C@_09FIPJ@Assaulter?$AA@=007db2ac
// @ref ??_C@_09INEJ@FireProne?$AA@=007db110
// @ref ??_C@_0BA@ILON@EnterWaterSound?$AA@=007db300
// @ref ??_C@_0BA@OJPH@LeaveWaterSound?$AA@=007db2f0
// @ref ??_C@_0BC@ENNL@DetectionDistance?$AA@=007db298
// @ref ??_C@_0L@EMCE@DeathAnims?$AA@=007db324
// @ref ??_C@_0L@IHAE@DeadBodies?$AA@=007db330
// @ref ??_C@_0L@LCEP@Infiltrate?$AA@=007db2cc
// @ref ??_C@_0N@BGLG@VehicleThief?$AA@=007db258
// @ref ??_C@_0N@GKGD@VoiceComment?$AA@=007db33c
// @ref ??_C@_0O@DGEM@TiberiumProof?$AA@=007db278

extern "C" char *__cdecl strtok(char *string, char const *delimiters);

// The voice and sound name lists (0x0050B610; unknown names skipped).
TypeList<int> __fastcall Get_Voc_List(CCINIClass &ini, char const *section, char const *entry, TypeList<int> defvalue);

// Get_Sound: shared/ccini_class.hpp.

// Animation types named by the entry (comma separated), else the default.
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

bool InfantryTypeClass::Read_INI(CCINIClass &ini)
{
    unknown_a9b = false;
    if (TechnoTypeClass::Read_INI(ini)) {
        Pip = ini.Get_PipType(ID, "Pip", Pip);
        VoiceComment = Get_Voc_List(ini, ID, "VoiceComment", VoiceComment);
        DeadBodies = Get_Anim_List(ini, ID, "DeadBodies", DeadBodies);
        DeathAnims = Get_Anim_List(ini, ID, "DeathAnims", DeathAnims);
        Cyborg = ini.Get_Bool(ID, "Cyborg", Cyborg);
        NotHuman = ini.Get_Bool(ID, "NotHuman", NotHuman);
        if (Cyborg) {
            unknown_a9b = true;
        }
        EnterWaterSound = Get_Sound(ini, ID, "EnterWaterSound", EnterWaterSound);
        LeaveWaterSound = Get_Sound(ini, ID, "LeaveWaterSound", LeaveWaterSound);
        Fearless = ini.Get_Bool(ID, "Fearless", Fearless);
        Fraidycat = ini.Get_Bool(ID, "Fraidycat", Fraidycat);
        Infiltrate = ini.Get_Bool(ID, "Infiltrate", Infiltrate);
        Ivan = ini.Get_Bool(ID, "Ivan", Ivan);
        Occupier = ini.Get_Bool(ID, "Occupier", Occupier);
        Assaulter = ini.Get_Bool(ID, "Assaulter", Assaulter);
        DetectionDistance = ini.Get_Int(ID, "DetectionDistance", DetectionDistance);
        C4 = ini.Get_Bool(ID, "C4", C4);
        Civilian = ini.Get_Bool(ID, "Civilian", Civilian);
        Engineer = ini.Get_Bool(ID, "Engineer", Engineer);
        TiberiumProof = ini.Get_Bool(ID, "TiberiumProof", TiberiumProof);
        Agent = ini.Get_Bool(ID, "Agent", Agent);
        Thief = ini.Get_Bool(ID, "Thief", Thief);
        VehicleThief = ini.Get_Bool(ID, "VehicleThief", VehicleThief);
        Doggie = ini.Get_Bool(ID, "Doggie", Doggie);
        Deployer = ini.Get_Bool(ID, "Deployer", Deployer);
        if (C4) {
            Infiltrate = true;
        }
        if (Engineer) {
            Infiltrate = true;
        }
        if (Agent) {
            Infiltrate = true;
        }
        Crawls = ArtINI.Get_Bool(unknown_1c8, "Crawls", Crawls);
        FireUp = ArtINI.Get_Int(unknown_1c8, "FireUp", FireUp);
        FireProne = ArtINI.Get_Int(unknown_1c8, "FireProne", FireProne);
        Read_Sequence();
        return true;
    }
    return false;
}
