// 0x0063F9A0: a player's new address.
void OwnerTalkClass::Unknown_0063F9A0(int id, IPXAddressClass *address)
{
    NetNumType net;
    NetNodeType node;
    address->Get_Address(net, node);
    for (int index = 0; index < Connections.Count(); index++) {
        if (Connections[index]->ID == id) {
            Connections[index]->Address = *(unsigned long *)node;
            break;
        }
    }
}
// @ref ?Get_Address@IPXAddressClass@@QAEXQAE0@Z=00523500
