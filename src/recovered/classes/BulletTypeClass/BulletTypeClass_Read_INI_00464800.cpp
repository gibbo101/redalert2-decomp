// bool BulletTypeClass::Read_INI(CCINIClass &ini) (0x00464800)
// The rules keys, then (when the type names an image) the art keys of the
// image section in ArtINI.
#include "shared/weapon_type.hpp"

static inline AnimTypeClass *Get_AnimType(CCINIClass &ini, char const *section, char const *entry, AnimTypeClass *defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) {
        return Find_Or_Make_AnimType_004264a0(buffer);
    }
    return defvalue;
}

static inline WeaponTypeClass *Get_WeaponType(CCINIClass &ini, char const *section, char const *entry, WeaponTypeClass *defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) {
        return WeaponTypeClass::Find_Or_Make(buffer);
    }
    return defvalue;
}

bool BulletTypeClass::Read_INI(CCINIClass &ini)
{
    if (ObjectTypeClass::Read_INI(ini)) {
        char const *section = ID;
        Arm = ini.Get_Int(section, "Arm", Arm);
        ROT = ini.Get_Int(section, "ROT", ROT);
        CourseLockDuration = ini.Get_Int(section, "CourseLockDuration", CourseLockDuration);
        Elasticity = ini.Get_Double(section, "Elasticity", Elasticity);
        Acceleration = ini.Get_Int(section, "Acceleration", Acceleration);
        Color = ini.Get_ColorScheme(section, "Color", Color);
        Arcing = ini.Get_Bool(section, "Arcing", Arcing);
        Floater = ini.Get_Bool(section, "Floater", Floater);
        SubjectToCliffs = ini.Get_Bool(section, "SubjectToCliffs", SubjectToCliffs);
        SubjectToElevation = ini.Get_Bool(section, "SubjectToElevation", SubjectToElevation);
        SubjectToWalls = ini.Get_Bool(section, "SubjectToWalls", SubjectToWalls);
        VeryHigh = ini.Get_Bool(section, "VeryHigh", VeryHigh);
        Shadow = ini.Get_Bool(section, "Shadow", Shadow);
        Dropping = ini.Get_Bool(section, "Dropping", Dropping);
        Level = ini.Get_Bool(section, "Level", Level);
        Inviso = ini.Get_Bool(section, "Inviso", Inviso);
        Proximity = ini.Get_Bool(section, "Proximity", Proximity);
        Ranged = ini.Get_Bool(section, "Ranged", Ranged);
        Inaccurate = ini.Get_Bool(section, "Inaccurate", Inaccurate);
        FlakScatter = ini.Get_Bool(section, "FlakScatter", FlakScatter);
        AA = ini.Get_Bool(section, "AA", AA);
        AG = ini.Get_Bool(section, "AG", AG);
        Degenerates = ini.Get_Bool(section, "Degenerates", Degenerates);
        Bouncy = ini.Get_Bool(section, "Bouncy", Bouncy);
        Airburst = ini.Get_Bool(section, "Airburst", Airburst);
        Cluster = ini.Get_Int(section, "Cluster", Cluster);
        Scalable = ini.Get_Bool(section, "Scalable", Scalable);

        char *graphic = unknown_1c8.Buffer;
        if (ini.Get_String(section, "Image", unknown_string_83c55c, graphic, sizeof(unknown_1c8.Buffer)) > 0) {
            Trailer = Get_AnimType(ArtINI, graphic, "Trailer", Trailer);
            SpawnDelay = ArtINI.Get_Int(graphic, "SpawnDelay", SpawnDelay);
            Rotates = !ArtINI.Get_Bool(graphic, "Rotates", !Rotates);
            Flat = ArtINI.Get_Bool(graphic, "Flat", Flat);
        }
        AirburstWeapon = Get_WeaponType(ini, section, "AirburstWeapon", AirburstWeapon);
        ShrapnelWeapon = Get_WeaponType(ini, section, "ShrapnelWeapon", ShrapnelWeapon);
        ShrapnelCount = ini.Get_Int(section, "ShrapnelCount", ShrapnelCount);
        DetonationAltitude = ini.Get_Int(section, "DetonationAltitude", DetonationAltitude);
        Vertical = ini.Get_Bool(section, "Vertical", Vertical);
        FirersPalette = ini.Get_Bool(section, "FirersPalette", FirersPalette);
        AnimLow = ArtINI.Get_Int(graphic, "AnimLow", AnimLow);
        AnimHigh = ArtINI.Get_Int(graphic, "AnimHigh", AnimHigh);
        AnimRate = ArtINI.Get_Int(graphic, "AnimRate", AnimRate);
        AnimPalette = ArtINI.Get_Bool(graphic, "AnimPalette", AnimPalette);
        if (!Inviso) {
            unknown_func_5d7630();
        }
        if (unknown_206) {
            unknown_func_5d6730();
        }
        return true;
    }
    return false;
}
