// 0x0063FC90: tells the router to stop (type 3) and waits up to 900 ticks for the send queue to empty.
void OwnerTalkClass::Unknown_0063FC90()
{
    TalkPacketStruct packet = {0};
    CDTimerClass<SystemTimerClass> timer;
    if (unknown_18 && RouterProcess != 0) {
        packet.Type = 3;
        unknown_ipx_manager_a40978.unknown_525b50(&packet, sizeof(packet), true);
        timer = 900;
        while (unknown_ipx_manager_a40978.unknown_slot20() > 0 && timer) {
            Service_Game_IO_00481fb0();
        }
    }
}
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?Service_Game_IO_00481fb0@@YIXXZ=00481fb0
// @ref ?unknown_slot20@IPXManagerClass@@UAEHXZ=00526a80
