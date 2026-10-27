// bool ParticleTypeClass::Read_INI(CCINIClass &ini) (0x00621490)
// The object keys, then the particle keys: the colour list (empty when
// absent), damage and warhead, animation and state timing, velocities and
// colours, the next particle type (made when missing) and BehavesLike= by
// name (Gas, Smoke, Fire, Spark, Railgun; -1 when unknown).
#include "shared/particle_system.hpp"
#include "shared/ccini_class.hpp"
#include "shared/warhead_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_7?$VectorClass@VRGBClass@@@@6B@=0079da54
// @ref ??_7?$TypeList@VRGBClass@@@@6B@=0079da74
// @ref ??_7?$DynamicVectorClass@VRGBClass@@@@6B@=007a8604
// @ref ??_G?$VectorClass@VRGBClass@@@@UAEPAXI@Z=0046db10
// @ref ??_G?$TypeList@VRGBClass@@@@UAEPAXI@Z=0046cf00
// @ref ??_G?$DynamicVectorClass@VRGBClass@@@@UAEPAXI@Z=00622040
// @ref ??4?$VectorClass@VRGBClass@@@@QAEAAV0@ABV0@@Z=0046dd20
// @ref ??8?$VectorClass@VRGBClass@@@@UBE_NABV0@@Z=0046d720
// @ref ?ID@?$VectorClass@VRGBClass@@@@UAEHABVRGBClass@@@Z=0046d8b0
// @ref ?ID@?$VectorClass@VRGBClass@@@@UAEHPBVRGBClass@@@Z=0046d900
// @ref ?Fetch@?$VectorClass@VRGBClass@@@@UBE?AVRGBClass@@H@Z=0046cda0
// @ref ?Resize@?$VectorClass@VRGBClass@@@@UAE_NHPBVRGBClass@@@Z=0046d780
// @ref ?Clear@?$VectorClass@VRGBClass@@@@UAEXXZ=0046d880
// @ref ?Clear@?$DynamicVectorClass@VRGBClass@@@@UAEXXZ=0046cd40
// @ref ?ID@?$DynamicVectorClass@VRGBClass@@@@UAEHABVRGBClass@@@Z=0046da30
// @ref ?ID@?$DynamicVectorClass@VRGBClass@@@@UAEHPBVRGBClass@@@Z=0046cd70
// @ref ?Resize@?$DynamicVectorClass@VRGBClass@@@@UAE_NHPBVRGBClass@@@Z=0046d930
// @ref ?Clear@?$VectorClass@VRGBClass@@@@UAEXXZ=0046d880
// @ref ??0?$DynamicVectorClass@VRGBClass@@@@QAE@IPBVRGBClass@@@Z=00621fa0
// @ref ?Read_INI@ObjectTypeClass@@UAE_NAAVCCINIClass@@@Z=005d7810
// @ref ?unknown_particle_behaves_like_names_7ec1b4@@3PAPBDA=007ec1b4
// @ref ??B?$FixedString@$0BJ@@@QBEPBDXZ=0050b0e0
// @ref __stricmp=00781f20
// @ref ??_C@_05BOOE@Deacc?$AA@=007ec2ec
// @ref ??_C@_05CPIN@MaxDC?$AA@=007ec330
// @ref ??_C@_05DJCH@MaxEC?$AA@=007ec328
// @ref ??_C@_06CCHE@Radius?$AA@=007ec2e4
// @ref ??_C@_06ILDP@Damage?$AA@=007cef54
// @ref ??_C@_07LOND@Warhead?$AA@=007ced5c
// @ref ??_C@_08OKHA@Velocity?$AA@=007ec2f4
// @ref ??_C@_09DIJP@ColorList?$AA@=007ec338
// @ref ??_C@_09EOLI@XVelocity?$AA@=007ec264
// @ref ??_C@_09IMPA@YVelocity?$AA@=007ec258
// @ref ??_C@_0BB@OJCA@FinalDamageState?$AA@=007ec1f8
// @ref ??_C@_0BD@EJHD@DeleteOnStateLimit?$AA@=007ec2d0
// @ref ??_C@_0BD@HKEJ@NextParticleOffset?$AA@=007ec224
// @ref ??_C@_0BD@PCPO@Translucent25State?$AA@=007ec27c
// @ref ??_C@_0BD@PIDG@Translucent50State?$AA@=007ec290
// @ref ??_C@_0L@BNDM@ColorSpeed?$AA@=007ec270
// @ref ??_C@_0L@CLCE@Normalized?$AA@=007cefc8
// @ref ??_C@_0L@GMMO@EndStateAI?$AA@=007ec2c4
// @ref ??_C@_0L@LAIE@WindEffect?$AA@=007ec300
// @ref ??_C@_0L@PDMP@StartFrame?$AA@=007ec31c
// @ref ??_C@_0M@CAMN@BehavesLike?$AA@=007ec13c
// @ref ??_C@_0M@FKPJ@StartColor2?$AA@=007ec20c
// @ref ??_C@_0M@KFEA@StartColor1?$AA@=007ec218
// @ref ??_C@_0N@BPCC@MinZVelocity?$AA@=007ec248
// @ref ??_C@_0N@LMP@Translucency?$AA@=007ceedc
// @ref ??_C@_0N@OCKG@NextParticle?$AA@=007ec1e8
// @ref ??_C@_0N@PEHL@StartStateAI?$AA@=007ec2b4
// @ref ??_C@_0O@FCPC@NumLoopFrames?$AA@=007ec30c
// @ref ??_C@_0P@HJKA@StateAIAdvance?$AA@=007ec2a4
// @ref ??_C@_0P@PDHO@ZVelocityRange?$AA@=007ec238

// The behaviour names in BehavesLike order (0x007EC1B4).
extern char const *unknown_particle_behaves_like_names_7ec1b4[5];

static inline WarheadTypeClass *Get_Warhead(CCINIClass &ini, char const *section, char const *entry, WarheadTypeClass *defvalue)
{
    char name[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, name, sizeof(name))) {
        return WarheadTypeClass::Find_Or_Make(name);
    }
    return defvalue;
}

// The behaviour with this name, or -1.
static inline int Behaves_From_Name(char const *name)
{
    for (int index = 0; index < 5; index++) {
        if (_stricmp(name, unknown_particle_behaves_like_names_7ec1b4[index]) == 0) {
            return index;
        }
    }
    return -1;
}

bool ParticleTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        ColorList = ini.Get_Color_List(ID, "ColorList", TypeList<RGBClass>());
        MaxDC = ini.Get_Int(ID, "MaxDC", MaxDC);
        MaxEC = ini.Get_Int(ID, "MaxEC", MaxEC);
        Damage = ini.Get_Int(ID, "Damage", Damage);
        Warhead = Get_Warhead(ini, ID, "Warhead", Warhead);
        StartFrame = ini.Get_Int(ID, "StartFrame", StartFrame);
        NumLoopFrames = ini.Get_Int(ID, "NumLoopFrames", NumLoopFrames);
        Translucency = ini.Get_Int(ID, "Translucency", Translucency);
        WindEffect = ini.Get_Int(ID, "WindEffect", WindEffect);
        Velocity = ini.Get_Double(ID, "Velocity", Velocity);
        Deacc = ini.Get_Double(ID, "Deacc", Deacc);
        Radius = ini.Get_Int(ID, "Radius", Radius);
        DeleteOnStateLimit = ini.Get_Bool(ID, "DeleteOnStateLimit", DeleteOnStateLimit);
        EndStateAI = ini.Get_Int(ID, "EndStateAI", EndStateAI);
        StartStateAI = ini.Get_Int(ID, "StartStateAI", StartStateAI);
        StateAIAdvance = ini.Get_Int(ID, "StateAIAdvance", StateAIAdvance);
        Translucent50State = ini.Get_Int(ID, "Translucent50State", Translucent50State);
        Translucent25State = ini.Get_Int(ID, "Translucent25State", Translucent25State);
        Normalized = ini.Get_Bool(ID, "Normalized", Normalized);
        ColorSpeed = ini.Get_Double(ID, "ColorSpeed", ColorSpeed);
        XVelocity = ini.Get_Int(ID, "XVelocity", XVelocity);
        YVelocity = ini.Get_Int(ID, "YVelocity", YVelocity);
        MinZVelocity = ini.Get_Int(ID, "MinZVelocity", MinZVelocity);
        ZVelocityRange = ini.Get_Int(ID, "ZVelocityRange", ZVelocityRange);
        (INIPoint3D &)NextParticleOffset = ini.Get_Integer_Triple(ID, "NextParticleOffset", (INIPoint3D &)NextParticleOffset);
        StartColor1 = ini.Get_RGB(ID, "StartColor1", StartColor1);
        StartColor2 = ini.Get_RGB(ID, "StartColor2", StartColor2);
        FinalDamageState = ini.Get_Int(ID, "FinalDamageState", EndStateAI);
        char buffer[32];
        if (ini.Get_String(ID, "NextParticle", 0, buffer, sizeof(buffer))) {
            NextParticle = Index_Or_Make(buffer);
        }
        buffer[0] = '\0';
        ini.Get_String(ID, "BehavesLike", 0, buffer, sizeof(buffer));
        BehavesLike = Behaves_From_Name(buffer);
        return true;
    }
    return false;
}
