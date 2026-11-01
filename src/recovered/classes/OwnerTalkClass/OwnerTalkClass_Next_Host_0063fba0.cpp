// 0x0063FBA0: the next game host (the session's choice, else the first active non-host);
// when the local player becomes the host of a game of three or more, it restarts the router.
int OwnerTalkClass::Unknown_0063FBA0()
{
    int host = unknown_session_a3d298.unknown_303c;
    int index;
    if (host == -1) {
        for (index = 0; index < Connections.Count(); index++) {
            ConnectionListStruct *connection = Connections[index];
            if (connection->IsActive && !connection->IsHost) {
                host = connection->ID;
                connection->IsHost = true;
            }
        }
    } else {
        for (index = 0; index < Connections.Count(); index++) {
            ConnectionListStruct *connection = Connections[index];
            if (connection->ID == host) {
                connection->IsHost = true;
            } else {
                connection->IsHost = false;
            }
        }
    }
    if (!unknown_session_a3d298.Am_I_Master(0) && host != -1 && host == unknown_player_a35db4->ArrayIndex
        && unknown_session_a3d298.Players.Count() > 2) {
        IPXAddressClass *address = 0;
        for (index = 0; index < unknown_session_a3d298.Players.Count(); index++) {
            if (unknown_session_a3d298.Players[index]->ID == host) {
                address = &unknown_session_a3d298.Players[index]->Address;
                break;
            }
        }
        NetNumType net;
        NetNodeType node;
        address->Get_Address(net, node);
        Unknown_0063F510(node);
    }
    return host;
}
// @ref ?Am_I_Master@UnknownSessionState@@QAE_NPAVHouseClass@@@Z=0066f150
// @ref ?Unknown_0063F510@OwnerTalkClass@@QAE_NH@Z=0063f510
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?Unknown_0063F510@OwnerTalkClass@@QAE_NPAE@Z=0063f510
