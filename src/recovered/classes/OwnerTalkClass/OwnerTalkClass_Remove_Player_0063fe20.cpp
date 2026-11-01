// 0x0063FE20: a player left: marks its connection inactive and tells the router.
void OwnerTalkClass::Unknown_0063FE20(int id)
{
    TalkPacketStruct packet = {0};
    for (int index = 0; index < Connections.Count(); index++) {
        ConnectionListStruct *connection = Connections[index];
        if (connection->ID == id) {
            connection->IsActive = false;
            connection->IsHost = false;
        }
    }
    if (unknown_18) {
        packet.Type = 2;
        packet.Data = id;
        Debug_Printf("Sending TALK_REMOVE_PLAYER to router\n");
        unknown_ipx_manager_a40978.unknown_525b50(&packet, sizeof(packet), true);
    }
}
// @ref ??_C@_0CG@MPLL@Sending?5TALK_REMOVE_PLAYER?5to?5ro@=007eeb18
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_525b50@IPXManagerClass@@QAEHPAXH_N@Z=00525b50
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
