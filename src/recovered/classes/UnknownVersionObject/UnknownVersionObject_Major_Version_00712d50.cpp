// The major version number, 1 (0x00712D50).
unsigned short UnknownVersionObject::Major_Version()
{
    if (!TextInit) {
        Read_Text_String();
        TextInit = 1;
    }

    if (MajorInit) {
        return MajorVer;
    }

    MajorVer = 1;
    MajorInit = 1;
    return MajorVer;
}
