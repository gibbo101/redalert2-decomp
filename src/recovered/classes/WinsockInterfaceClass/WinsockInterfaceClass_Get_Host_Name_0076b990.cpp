// bool WinsockInterfaceClass::Get_Host_Name(char *name, int length) (0x0076B990, slot 17)
#include "shared/winsock_interface.hpp"
// @ref _gethostname@8=00781bd2
// @ref _WSAGetLastError@0=00781b7e
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0CC@CKAA@WinsockInterface?5Host?5name?5is?5?$CFs@=00800e30
// @ref ??_C@_0EB@GDGN@Error?5?9?5WinsockInterface?5Unable?5@=00800e54

bool WinsockInterfaceClass::Get_Host_Name(char *name, int length)
{
    if (gethostname(name, length) == SOCKET_ERROR) {
        Debug_Printf("Error - WinsockInterface Unable to get host name. Error code %d\n", WSAGetLastError());
        return false;
    }
    Debug_Printf("WinsockInterface Host name is %s\n", name);
    return true;
}
