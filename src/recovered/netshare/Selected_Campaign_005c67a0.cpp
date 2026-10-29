// int Selected_Campaign_005c67a0() (0x005C67A0)
// The selected row of the lobby campaign list (0x553 in the lobby dialog; LB_GETCURSEL).
#include "shared/lobby.hpp"

int Selected_Campaign_005c67a0()
{
    return SendDlgItemMessageA(unknown_lobby_dialog_a728e0, 0x553, 0x188, 0, 0);
}
