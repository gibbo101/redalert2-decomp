// 0x0063F430: the mask of the connection at this address (0xFF: none or broadcast).
unsigned char OwnerTalkClass::Unknown_0063F430(IPXAddressClass *address)
{
    if (address == 0) {
        return 0xFF;
    }
    if (address->Is_Broadcast()) {
        return 0xFF;
    }
    unsigned char mask = 0;
    NetNumType net;
    NetNodeType node;
    address->Get_Address(net, node);
    for (int index = 0; index < Connections.Count(); index++) {
        if (*(unsigned long *)node == Connections[index]->Address) {
            mask = Connections[index]->Mask;
            break;
        }
    }
    return mask;
}
// @ref ?Get_Address@IPXAddressClass@@QAEXQAE0@Z=00523500
// @ref ?Is_Broadcast@IPXAddressClass@@QAEHXZ=00523560
