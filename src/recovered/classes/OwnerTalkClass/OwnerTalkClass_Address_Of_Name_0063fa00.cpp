// 0x0063FA00: the address of the named connection (a function-local static; null node if none).
IPXAddressClass *OwnerTalkClass::Unknown_0063FA00(char *name)
{
    static IPXAddressClass address;
    NetNodeType node;
    memset(node, 0, sizeof(node));
    address.Set_Node(node);
    address.unknown_523960(0);
    for (int index = 0; index < Connections.Count(); index++) {
        if (_stricmp(Connections[index]->Name, name) == 0) {
            NetNodeType ip;
            *(unsigned long *)ip = Connections[index]->Address;
            address.Set_Node(ip);
            address.unknown_523960(Connections[index]->Port);
            break;
        }
    }
    return &address;
}
// @ref ??0IPXAddressClass@@QAE@XZ=00523410
// @ref ?Set_Node@IPXAddressClass@@QAEXQAE@Z=00523540
// @ref ?unknown_523960@IPXAddressClass@@QAEXG@Z=00523960
// @ref _?address@?1??Unknown_0063FA00@OwnerTalkClass@@QAEPAVIPXAddressClass@@PAD@Z@4V3@A=00ab6d08
// @ref __stricmp=00781f20
// @ref _$E68=0063fae0
// @ref _?$S67@?1??Unknown_0063FA00@OwnerTalkClass@@QAEPAVIPXAddressClass@@PAD@Z@4EA=00ab6cf0
