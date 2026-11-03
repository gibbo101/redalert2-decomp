// HRESULT __stdcall TechnoTypeClass::Load(IStream *stream) (0x006DE260)
// Empties the lists, loads the object type, fixes up the type pointers,
// rebuilds every list from its saved count and elements and fixes up the
// pointer lists and weapons, then reloads the image, the cameos (XXICON when
// none) and the palette from the art INI.
#include "shared/techno_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?Load@ObjectTypeClass@@UAGJPAUIStream@@@Z=005d7c30
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ??0?$TypeList@PAVBuildingTypeClass@@@@QAE@XZ=0058dc70
// @ref ??0?$TypeList@PAVVoxelAnimTypeClass@@@@QAE@XZ=00652a70
// @ref ??0?$TypeList@PAVAnimTypeClass@@@@QAE@XZ=00652b50
// @ref ??0?$TypeList@H@@QAE@XZ=00652bd0
// @ref ??0?$TypeList@PAVParticleSystemTypeClass@@@@QAE@XZ=006df7c0
// @ref ?Add@?$DynamicVectorClass@PAVBuildingTypeClass@@@@QAE_NABQAVBuildingTypeClass@@@Z=0058eff0
// @ref ?Add@?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@QAE_NABQAVVoxelAnimTypeClass@@@Z=00653450
// @ref ?Add@?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE_NABQAVAnimTypeClass@@@Z=0050b590
// @ref ?Add@?$DynamicVectorClass@H@@QAE_NABH@Z=0046d300
// @ref ?Add@?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@QAE_NABQAVParticleSystemTypeClass@@@Z=006df990
// @ref __makepath=007831f0
// @ref __stricmp=00781f20
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ?Get_String@INIClass@@QBEHPBD00PADH@Z=0050e9a0
// @ref ?unknown_art_ini_8397f0@@3VCCINIClass@@A=008397f0
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?Load@PaletteName@@QAEPAXXZ=00603380
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref ??_C@_05LKKC@Cameo?$AA@=007f732c
// @ref ??_C@_06MNFJ@XXICON?$AA@=007f80e4
// @ref ??_C@_08JAIB@AltCameo?$AA@=007f7320
// @ref ??_C@_07HNHN@Palette?$AA@=007d9e2c
// @ref ??_C@_0L@XXICON?4SHP?$AA@=007d61bc

extern CCINIClass unknown_art_ini_8397f0;
extern "C" void __cdecl _makepath(char *path, char const *drive, char const *dir, char const *fname, char const *ext);
extern "C" int __cdecl _stricmp(char const *string1, char const *string2);

// Rebuilds a list in place from its saved count and elements.
template <class T>
static inline void Load_List(IStream *stream, TypeList<T> &list)
{
    new (&list) TypeList<T>;
    int count;
    stream->Read(&count, sizeof(count), 0);
    for (int index = 0; index < count; index++) {
        T value;
        stream->Read(&value, sizeof(value), 0);
        list.Add(value);
    }
}

HRESULT __stdcall TechnoTypeClass::Load(IStream *stream)
{
    Dock.Clear();
    DebrisTypes.Clear();
    DebrisAnims.Clear();
    VoiceSelect.Clear();
    VoiceMove.Clear();
    VoiceAttack.Clear();
    VoiceSpecialAttack.Clear();
    VoiceDie.Clear();
    VoiceFeedback.Clear();
    MoveSound.Clear();
    DieSound.Clear();
    Explosion.Clear();
    DestroyAnim.Clear();
    Prerequisite.Clear();
    PrerequisiteOverride.Clear();
    DebrisMaximums.Clear();

    HRESULT result = ObjectTypeClass::Load(stream);
    if (SUCCEEDED(result)) {

    Swizzle_Pointer(DeploysInto);
    Swizzle_Pointer(UndeploysInto);
    Swizzle_Pointer(NaturalParticleSystem);
    Swizzle_Pointer(Spawns);
    Swizzle_Pointer(DeathWeapon);
    Swizzle_Pointer(UnloadingClass);

    Load_List(stream, Dock);
    Load_List(stream, DebrisTypes);
    Load_List(stream, DebrisAnims);
    Load_List(stream, VoiceSelect);
    Load_List(stream, VoiceMove);
    Load_List(stream, VoiceAttack);
    Load_List(stream, VoiceSpecialAttack);
    Load_List(stream, VoiceDie);
    Load_List(stream, VoiceFeedback);
    Load_List(stream, MoveSound);
    Load_List(stream, DieSound);
    Load_List(stream, Explosion);
    Load_List(stream, DestroyAnim);
    Load_List(stream, DebrisMaximums);
    Load_List(stream, Prerequisite);
    Load_List(stream, PrerequisiteOverride);
    Load_List(stream, DamageParticleSystems);
    Load_List(stream, DestroyParticleSystems);

    int index;
    for (index = 0; index < Dock.Count(); index++) {
        Swizzle_Pointer(Dock[index]);
    }
    for (index = 0; index < Explosion.Count(); index++) {
        Swizzle_Pointer(Explosion[index]);
    }
    for (index = 0; index < DestroyAnim.Count(); index++) {
        Swizzle_Pointer(DestroyAnim[index]);
    }
    for (index = 0; index < DebrisTypes.Count(); index++) {
        Swizzle_Pointer(DebrisTypes[index]);
    }
    for (index = 0; index < DebrisAnims.Count(); index++) {
        Swizzle_Pointer(DebrisAnims[index]);
    }
    for (index = 0; index < 15; index++) {
        Swizzle_Pointer(Weapon[index].WeaponType);
    }
    for (index = 0; index < 15; index++) {
        Swizzle_Pointer(EliteWeapon[index].WeaponType);
    }
    for (index = 0; index < DamageParticleSystems.Count(); index++) {
        Swizzle_Pointer(DamageParticleSystems[index]);
    }
    for (index = 0; index < DestroyParticleSystems.Count(); index++) {
        Swizzle_Pointer(DestroyParticleSystems[index]);
    }

    char name[256];
    char filename[260];
    _makepath(filename, 0, 0, unknown_1c8, ".SHP");
    unknown_a4 = (void *)MixFileClass::Retrieve(filename);

    unknown_art_ini_8397f0.Get_String(unknown_1c8, "Cameo", "XXICON", name, sizeof(name));
    if (_stricmp(name, "XXICON") == 0) {
        unknown_art_ini_8397f0.Get_String(ID, "Cameo", "XXICON", name, sizeof(name));
    }
    _makepath(filename, 0, 0, name, ".SHP");
    CameoData = 0;
    CameoData = (void *)MixFileClass::Retrieve(filename);
    if (CameoData == 0) {
        CameoData = (void *)MixFileClass::Retrieve("XXICON.SHP");
    }

    unknown_art_ini_8397f0.Get_String(unknown_1c8, "AltCameo", unknown_string_83c55c, name, sizeof(name));
    _makepath(filename, 0, 0, name, ".SHP");
    AltCameoData = 0;
    AltCameoData = (void *)MixFileClass::Retrieve(filename);
    PaletteName *palette = &PaletteFile;

    unknown_art_ini_8397f0.Get_String(unknown_1c8, "Palette", unknown_string_83c55c, palette->Buffer, sizeof(palette->Buffer));
    if (palette->Buffer[0] != 0) {
        Palette = palette->Load();
    }
    result = S_OK;
    }
    return result;
}
