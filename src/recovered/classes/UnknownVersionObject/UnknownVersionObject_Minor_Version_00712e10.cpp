// The minor version number, 6 (0x00712E10).
unsigned short UnknownVersionObject::Minor_Version()
{
    if (!TextInit) {
        Read_Text_String();
        TextInit = 1;
    }

    if (MinorInit) {
        return MinorVer;
    }

    MinorVer = 6;
    MinorInit = 1;
    return MinorVer;
}
