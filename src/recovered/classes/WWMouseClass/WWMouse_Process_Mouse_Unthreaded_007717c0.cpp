// void Process_Mouse_Unthreaded() (0x007717C0)
// Updates the mouse directly when the mouse thread is not running (called
// from 0x00406F00). Name is a hypothesis.
#include "shared/wwmouse.hpp"
// @ref ?MouseThreadActive@@3HA=00b2af64
// @ref ?_Mouse@@3PAVWWMouseClass@@A=00b2af5c
// @ref ?Process_Mouse@WWMouseClass@@QAEXXZ=00773400

void Process_Mouse_Unthreaded()
{
    if (!MouseThreadActive && _Mouse != 0) {
        _Mouse->Process_Mouse();
    }
}
