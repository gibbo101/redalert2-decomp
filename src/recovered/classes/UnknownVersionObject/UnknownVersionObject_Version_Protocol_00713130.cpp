struct VersionProtocolType {
    unsigned int Version;
    int Protocol;
};

// The version at which each communications protocol starts (0x007F9700).
static VersionProtocolType VersionProtocol[] = {
    {0x00001000, 0},
    {0x00002000, 1},
    {0x00010000, 2},
};
// @ref _VersionProtocol=007f9700

// The protocol of a version: the last table entry not newer than it, else the newest
// protocol (0x00713130).
int UnknownVersionObject::Version_Protocol_00713130(int version)
{
    int i, j;

    j = (sizeof(VersionProtocol) / sizeof(VersionProtocolType)) - 1;
    for (i = j; i >= 0; i--) {
        if ((unsigned int)version >= VersionProtocol[i].Version) {
            return VersionProtocol[i].Protocol;
        }
    }

    return VersionProtocol[j].Protocol;
}
