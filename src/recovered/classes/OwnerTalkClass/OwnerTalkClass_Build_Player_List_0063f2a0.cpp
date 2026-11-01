// 0x0063F2A0: rebuilds the connection list from the human houses still playing (packet-router games).
void OwnerTalkClass::Unknown_0063F2A0()
{
    while (Connections.Count()) {
        delete Connections[0];
        Connections.Delete(0);
    }
    for (int house = 0; house < Houses.Count(); house++) {
        HouseClass *hptr = Houses[house];
        if (hptr->Unknown_004F52F0() && !hptr->unknown_13e) {
            ConnectionListStruct *connection = new ConnectionListStruct;
            connection->ID = house;
            strncpy(connection->Name, Unknown_006FA120(hptr->UIName), 20);
            for (int index = 0; index < unknown_session_a3d298.Players.Count(); index++) {
                if (unknown_session_a3d298.Players[index]->ID == house) {
                    NetNumType net;
                    NetNodeType node;
                    unknown_session_a3d298.Players[index]->Address.Get_Address(net, node);
                    connection->Address = *(unsigned long *)node;
                    connection->Port = unknown_node_ids_a402ba[index];
                    break;
                }
            }
            connection->IsActive = true;
            connection->IsHost = (unknown_session_a3d298.MasterPlayerID == hptr->ArrayIndex);
            connection->Mask = 1 << house;
            Connections.Add(connection);
        }
    }
}
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref ?unknown_node_ids_a402ba@@3PAGA=00a402ba
// @ref _strncpy=007823d0
