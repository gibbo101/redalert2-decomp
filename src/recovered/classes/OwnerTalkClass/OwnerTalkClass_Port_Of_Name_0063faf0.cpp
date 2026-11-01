// 0x0063FAF0: the port of the named connection (0: none).
unsigned short OwnerTalkClass::Unknown_0063FAF0(char *name)
{
    for (int index = 0; index < Connections.Count(); index++) {
        if (_stricmp(Connections[index]->Name, name) == 0) {
            return Connections[index]->Port;
        }
    }
    return 0;
}
// @ref __stricmp=00781f20
