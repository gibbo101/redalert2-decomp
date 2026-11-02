// The version as text, "major.minor" with the minor's trailing zero digits trimmed
// (0x00712ED0; Tiberian Sun's VersionClass::Version_Name).
// @ref ??_C@_08JHOJ@?$CFd?4?$CF3?43d?$AA@=007f9928
char const *UnknownVersionObject::Internal_Version_Name_00712ed0()
{
    unsigned short adjusted_minor;
    int i;

    adjusted_minor = Minor_Version();
    for (i = 0; i < 4; i++) {
        if ((adjusted_minor & 0x000F) != 0) {
            break;
        }
        adjusted_minor >>= 4;
    }

    sprintf(VersionName, "%d.%3.3d", version_object_00a40c88.Major_Version(), adjusted_minor);
    return VersionName;
}
