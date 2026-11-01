// The router's messages (0x00AB68E4).
static unsigned char RouterBuffer[1024];

// 0x0063F840: reads the router's messages; a change of address (type 5: id, IP) becomes an ADDRESSCHANGE event.
void OwnerTalkClass::Unknown_0063F840()
{
    unsigned short product;
    int length;
    IPXAddressClass address;
    if (Frame > 0) {
        while (unknown_ipx_manager_a40978.unknown_525bc0(RouterBuffer, &length, &address, &product)) {
            if (RouterBuffer[0] != 5) {
                Debug_Printf("Got spurious message %d from the router\n", RouterBuffer[0]);
            } else {
                Debug_Printf("Received change of address notification.\n");
                int id = (char)RouterBuffer[1];
                NetNumType net;
                NetNodeType node;
                memset(node, 0, sizeof(node));
                *(unsigned long *)node = *(unsigned long *)&RouterBuffer[2];
                IPXAddressClass newaddress;
                newaddress.Set_Address(net, node, 0);
                OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, &newaddress, id));
            }
        }
    }
}
// @ref ??0EventClass@@QAE@HPAVIPXAddressClass@@E@Z=004b6560
// @ref ??_C@_0CJ@FEPD@Got?5spurious?5message?5?$CFd?5from?5the@=007eea3c
// @ref ??_C@_0CK@FLJL@Received?5change?5of?5address?5notif@=007eea10
// @ref ?Frame@@3HA=00a40d2c
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338
// @ref ?Set_Address@IPXAddressClass@@QAEXQAE0G@Z=00523480
// @ref ?unknown_525bc0@IPXManagerClass@@QAEHPAXPAHPAVIPXAddressClass@@PAG@Z=00525bc0
// @ref _RouterBuffer=00ab68e4
// @ref __imp__timeGetTime@0=0079a524
