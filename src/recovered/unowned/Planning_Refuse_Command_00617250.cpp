#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Refuse_Command(int kind) (0x00617250)
// Drops the pending command and shows the refusal: terminating command
// (kind 0), continual command (1) or node maximum (2).
#include "shared/planning.hpp"
// @ref ??_C@_0BA@BPML@MSG?3NodeMaximum?$AA@=007ebd04
// @ref ??_C@_0BJ@DFJC@MSG?3PostContinualCommand?$AA@=007ebd14
// @ref ??_C@_0BL@ONIM@MSG?3PostTerminatingCommand?$AA@=007ebd30
// @ref ?Unknown_006AAD40@Tactical@@QAEXXZ=006aad40

void __fastcall Planning_Refuse_Command(int kind)
{
    unknown_tactical_83996c->Unknown_006AAD40();
    if (kind == 0) {
        Planning_Refuse("MSG:PostTerminatingCommand");
    } else if (kind == 1) {
        Planning_Refuse("MSG:PostContinualCommand");
    } else if (kind == 2) {
        Planning_Refuse("MSG:NodeMaximum");
    }
}
