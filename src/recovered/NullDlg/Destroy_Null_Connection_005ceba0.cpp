// void __fastcall Destroy_Null_Connection(int id, int error) (0x005CEBA0)
// A serial player has gone: shows "left the game" (error 0) or "connection
// lost" (error 1), or drops the modem connection (error -1); removes the
// player from the session list, hands the house to the computer and, when
// only one player is left, says so.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/queue.hpp"
#include "shared/null_dlg.hpp"
#include "shared/serial_progress.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/gadget.hpp"
#include "shared/vector_class.hpp"
#include "shared/session_state.hpp"
// @ref ?serial_manager_00a40a28@@3VNullModemClass@@A=00a40a28
// @ref ?Delete_Connection@NullModemClass@@QAEHXZ=005d0360
// @ref ?unknown_session_a3d55c@@3HA=00a3d55c
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?Add_Message@MessageListClass@@QAEPAVUnknownMessageNode@@PBGH0HIH_N@Z=005b4da0
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?unknown_func_4f4070@HouseClass@@QAEXXZ=004f4070
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_0BD@MKPO@D?3?2Ra2?2NullDlg?4CPP?$AA@=007e74bc
// @ref ??_C@_0BE@DDAG@TXT_CONNECTION_LOST?$AA@=007e6954
// @ref ??_C@_0BE@MJJO@TXT_JUST_YOU_AND_ME?$AA@=007e74d0
// @ref ??_C@_0O@JGPN@TXT_LEFT_GAME?$AA@=007e6930
// @ref ??_C@_15DEDE@?$AA?$CF?$AAs?$AA?$AA@=007d9c94
// @ref _swprintf=00783764
// @ref _wcslen=00783605
// @ref __wcsicmp=00796318
// @ref ??3@YAXPAX@Z=00781d3b
// @ref __ftol=0077f110
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __real@8@4008e100000000000000=0079b608

void __fastcall Destroy_Null_Connection(int id, int error)
{
    int i;
    HouseClass *housep;
    wchar_t txt[80];

    if (unknown_session_a3d55c == 1) {
        return;
    }
    housep = Houses[id];
    if (!housep || !housep->unknown_134) {
        return;
    }

    txt[0] = 0;
    switch (error) {
        case 1:
            swprintf(txt, StringTable::Load_String("TXT_CONNECTION_LOST", 0, "D:\\Ra2\\NullDlg.CPP", 0x190C), housep->UIName);
            break;
        case 0:
            swprintf(txt, StringTable::Load_String("TXT_LEFT_GAME", 0, "D:\\Ra2\\NullDlg.CPP", 0x1910), housep->UIName);
            break;
        case -1:
            serial_manager_00a40a28.Delete_Connection();
            break;
    }

    if (wcslen(txt)) {
        unknown_session_a3d298.Messages.Add_Message(0, 0, txt, housep->Type->Color, 0x4046, Rules->MessageDelay * 900, false);
        Map.Flag_To_Redraw(false);
    }

    for (i = 0; i < unknown_session_a3d298.Players.Count(); i++) {
        if (!_wcsicmp(unknown_session_a3d298.Players[i]->Name, housep->UIName)) {
            delete unknown_session_a3d298.Players[i];
            unknown_session_a3d298.Players.Delete(unknown_session_a3d298.Players[i]);
            break;
        }
    }

    housep->unknown_func_4f4070();
    unknown_session_a3d55c--;
    if (unknown_session_a3d55c == 1) {
        swprintf(txt, L"%s", StringTable::Load_String("TXT_JUST_YOU_AND_ME", 0, "D:\\Ra2\\NullDlg.CPP", 0x1935));
        unknown_session_a3d298.Messages.Add_Message(0, 0, txt, housep->Type->Color, 0x4046, Rules->MessageDelay * 900, false);
        Map.Flag_To_Redraw(false);
    }
}
