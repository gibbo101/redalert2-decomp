// void UDPInterfaceClass::unknown_slot28() (0x0076CCC0, slot 28)
// Closes the spare sockets and forgets them.
#include "shared/udp_interface.hpp"
// @ref ??_7?$DynamicVectorClass@PAE@@6B@=007afbac
// @ref ??_7?$VectorClass@PAE@@6B@=007afbcc
// @ref ??_G?$DynamicVectorClass@PAE@@UAEPAXI@Z=0076d8c0
// @ref ??_G?$VectorClass@PAE@@UAEPAXI@Z=0076d870
// @ref ??8?$VectorClass@PAE@@UBE_NABV0@@Z=0076d610
// @ref ?Clear@?$DynamicVectorClass@PAE@@UAEXXZ=0076d5b0
// @ref ?Clear@?$VectorClass@PAE@@UAEXXZ=0076d700
// @ref ?Fetch@?$VectorClass@PAE@@UBEPAEH@Z=0076d600
// @ref ?ID@?$DynamicVectorClass@PAE@@UAEHABQAE@Z=0076d840
// @ref ?ID@?$DynamicVectorClass@PAE@@UAEHPBQAE@Z=0076d5e0
// @ref ?ID@?$VectorClass@PAE@@UAEHABQAE@Z=0076d730
// @ref ?ID@?$VectorClass@PAE@@UAEHPBQAE@Z=0076d770
// @ref ?Resize@?$DynamicVectorClass@PAE@@UAE_NHPBQAE@Z=0076d790
// @ref ?Resize@?$VectorClass@PAE@@UAE_NHPBQAE@Z=0076d650
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?WSAAsyncSelect@@YGHIPAXIJ@Z=00781bc0
// @ref ?closesocket@@YGHI@Z=00781b96
// @ref ??_C@_0BJ@LEI@Closing?5spare?5socket?5?$CFd?6?$AA@=00801014

extern HWND MainWindow;                     // 0x00B263D8

void UDPInterfaceClass::unknown_slot28()
{
    for (int index = 0; index < NumSockets; index++) {
        Debug_Printf("Closing spare socket %d\n", Sockets[index]);
        WSAAsyncSelect(Sockets[index], MainWindow, 0, 0);
        closesocket(Sockets[index]);
    }
    NumSockets = 0;
    unknown_3f334 = -1;
}
