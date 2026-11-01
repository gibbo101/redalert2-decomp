// 0x0063FEB0: TALK_PORT_BLITZ.
void OwnerTalkClass::Unknown_0063FEB0(unsigned char flag)
{
    TalkPacketStruct packet = {0};
    if (unknown_18) {
        packet.Type = 6;
        packet.Data = flag;
        Debug_Printf("Sending TALK_PORT_BLITZ to router\n");
        unknown_ipx_manager_a40978.unknown_525b50(&packet, sizeof(packet), true);
    }
}
// @ref ??_C@_0CD@FAPD@Sending?5TALK_PORT_BLITZ?5to?5route@=007eeb40
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_525b50@IPXManagerClass@@QAEHPAXH_N@Z=00525b50
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978
