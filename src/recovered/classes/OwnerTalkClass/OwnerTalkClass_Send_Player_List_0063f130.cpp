// 0x0063F130: sends the router the master player list (TALK type 1; players the IPX manager no longer
// knows, other than the local one, are sent inactive) and waits up to 900 ticks for the queue to empty.
bool OwnerTalkClass::Unknown_0063F130()
{
    TalkPacketStruct packet = {0};
    CDTimerClass<SystemTimerClass> timer;
    if (!unknown_18) {
        return false;
    }
    Debug_Printf("About to send master player list to router\n");
    packet.Type = 1;
    packet.Data = Connections.Count();
    for (int index = 0; index < Connections.Count(); index++) {
        packet.Players[index] = *Connections[index];
        if (unknown_ipx_manager_a40978.Connection_Index(Connections[index]->ID) == -1
            && unknown_player_a35db4->ArrayIndex != Connections[index]->ID) {
            Debug_Printf("Marking player %s as inactive\n", Connections[index]->Name);
            packet.Players[index].IsActive = false;
            packet.Players[index].IsHost = false;
        }
    }
    unknown_ipx_manager_a40978.unknown_525b50(&packet, sizeof(packet), true);
    Debug_Printf("Player list sent to router\n");
    timer = 900;
    while (unknown_ipx_manager_a40978.unknown_slot20() > 0 && timer) {
        Service_Game_IO_00481fb0();
    }
    return true;
}
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ??_C@_0BM@HCDL@Player?5list?5sent?5to?5router?6?$AA@=007ee8e4
// @ref ??_C@_0BP@EEBL@Marking?5player?5?$CFs?5as?5inactive?6?$AA@=007ee900
// @ref ??_C@_0CM@JMGI@About?5to?5send?5master?5player?5list@=007ee920
// @ref ?Connection_Index@IPXManagerClass@@UAEHH@Z=00525780
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_slot20@IPXManagerClass@@UAEHXZ=00526a80
