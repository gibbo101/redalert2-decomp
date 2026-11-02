// The version number: the major version in the high word, the minor in the low (0x00712B50).
unsigned long UnknownVersionObject::Version_Number()
{
    if (!TextInit) {
        Read_Text_String();
        TextInit = 1;
    }

    if (VersionInit) {
        return Version;
    }

    Version = (Major_Version() << 16) | Minor_Version();
    VersionInit = 1;
    return Version;
}
