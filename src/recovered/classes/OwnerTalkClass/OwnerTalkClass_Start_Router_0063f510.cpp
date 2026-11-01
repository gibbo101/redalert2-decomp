struct _SECURITY_ATTRIBUTES;
struct _STARTUPINFOA {
    DWORD cb;
    char *lpReserved, *lpDesktop, *lpTitle;
    DWORD dwX, dwY, dwXSize, dwYSize, dwXCountChars, dwYCountChars, dwFillAttribute, dwFlags;
    unsigned short wShowWindow, cbReserved2;
    unsigned char *lpReserved2;
    HANDLE hStdInput, hStdOutput, hStdError;
};
struct _PROCESS_INFORMATION {
    HANDLE hProcess, hThread;
    DWORD dwProcessId, dwThreadId;
};
WIN32_IMPORT void WINAPI GetStartupInfoA(_STARTUPINFOA *info);
WIN32_IMPORT BOOL WINAPI CreateProcessA(char const *, char *, _SECURITY_ATTRIBUTES *, _SECURITY_ATTRIBUTES *, BOOL, DWORD,
                                        void *, char const *, _STARTUPINFOA *, _PROCESS_INFORMATION *);

// 0x0063F510: starts the packet router (mph.exe) for an IP (null: the first player's address, or the
// transport's own when there are no players), sets the forward addresses and waits up to 1800 ticks
// for the router's TALK_HELLO (type 4).
bool OwnerTalkClass::Unknown_0063F510(unsigned char *address)
{
    CDTimerClass<SystemTimerClass> timer;
    IPXAddressClass from;
    _STARTUPINFOA startup;
    _PROCESS_INFORMATION process;
    char command[256];
    char buffer[1024];
    int length;
    unsigned short product;

    Debug_Printf("Starting packet router process\n");
    GetStartupInfoA(&startup);
    if (!PacketTransport->unknown_slot18()) {
        return false;
    }
    if (address == 0) {
        if (unknown_session_a3d298.Players.Count() == 0) {
            unsigned char *ip = (unsigned char *)PacketTransport->unknown_slot19(0);
            sprintf(command, "mph.exe %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
            goto create;
        }
        IPXAddressClass *first = &unknown_session_a3d298.Players[0]->Address;
        if (first == 0) {
            goto create;
        }
        NetNumType net;
        NetNodeType node;
        first->Get_Address(net, node);
        sprintf(command, "mph.exe %d.%d.%d.%d", node[0], node[1], node[2], node[3]);
        unknown_forward_address_a3fbb8 = *first;
        unknown_session_a3d298.unknown_292c = 0;
    } else {
        sprintf(command, "mph.exe %d.%d.%d.%d", address[0], address[1], address[2], address[3]);
        IPXAddressClass *first = &unknown_session_a3d298.Players[0]->Address;
        if (first == 0) {
            goto create;
        }
        NetNumType net;
        NetNodeType node;
        first->Get_Address(net, node);
        node[0] = address[0];
        node[1] = address[1];
        node[2] = address[2];
        node[3] = address[3];
        unknown_forward_address_a3fbb8.Set_Address(net, node, 0);
        unknown_forward_address_a3fbb8.unknown_523960(*(unsigned short *)&unknown_session_a3d298.Players[0]->Address);
        unknown_session_a3d298.unknown_292c = *(unsigned short *)&unknown_session_a3d298.Players[0]->Address;
        unknown_forward_address_a3fbac = unknown_session_a3d298.Players[0]->Address;
    }
    Debug_Printf("Session.PacketRouterAddressTranslate = %s\n", unknown_forward_address_a3fbb8.As_String_00523840());

create:
    BOOL result = CreateProcessA("mph.exe", command, 0, 0, false, 0x200, 0, 0, &startup, &process);
    if (!result) {
        Debug_Printf("CreateProcess failed with error %d, %s\n", GetLastError(), result);
    } else {
        RouterProcess = process.hProcess;
        Debug_Printf("hRouterProcess = %d\n", process.hProcess);
        SetFocus(MainWindow);
        timer = 1800;
        result = false;
        while (timer) {
            Service_Game_IO_00481fb0();
            if (unknown_ipx_manager_a40978.unknown_525bc0(buffer, &length, &from, &product) && buffer[0] == 4) {
                result = true;
                Debug_Printf("Received TALK_HELLO from router\n");
                unknown_18 = true;
                break;
            }
        }
    }
    return result;
}
// @ref ??_C@_07MIIF@mph?4exe?$AA@=007ee844
// @ref ??_C@_0BE@IBDL@mph?4exe?5?$CFd?4?$CFd?4?$CFd?4?$CFd?$AA@=007ee9dc
// @ref ??_C@_0BF@JMCB@hRouterProcess?5?$DN?5?$CFd?6?$AA@=007ee970
// @ref ??_C@_0CA@NNHN@Starting?5packet?5router?5process?6?$AA@=007ee9f0
// @ref ??_C@_0CB@DHAE@Received?5TALK_HELLO?5from?5router?6@=007ee94c
// @ref ??_C@_0CI@MNDF@CreateProcess?5failed?5with?5error?5@=007ee988
// @ref ??_C@_0CL@PLML@Session?4PacketRouterAddressTrans@=007ee9b0
// @ref ?As_String_00523840@IPXAddressClass@@QAEPADPBV1@@Z=00523840
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?PacketTransport@@3PAVWinsockInterfaceClass@@A=00839c50
// @ref ?Set_Address@IPXAddressClass@@QAEXQAE0G@Z=00523480
// @ref ?unknown_525bc0@IPXManagerClass@@QAEHPAXPAHPAVIPXAddressClass@@PAG@Z=00525bc0
// @ref ?unknown_forward_address_a3fbac@@3VIPXAddressClass@@A=00a3fbac
// @ref ?unknown_forward_address_a3fbb8@@3VIPXAddressClass@@A=00a3fbb8
// @ref __imp__CreateProcessA@40=0079a1a4
// @ref __imp__GetLastError@0=0079a1f4
// @ref __imp__GetStartupInfoA@4=0079a254
// @ref __imp__SetFocus@4=0079a38c
// @ref _sprintf=007820f4
