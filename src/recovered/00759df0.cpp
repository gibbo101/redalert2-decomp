// WOL matchmaking state transition, 0x00759DF0 (39 bytes plus nine frozen NOPs).
// State/result and timeout are separate 32-bit words; entering a state refreshes its timestamp.
#include "shared/crt_time.hpp"
extern int unknown_b2ac2c;
extern int unknown_b26898;
extern int unknown_b2ab88;
extern long unknown_b2a8a4;
// @ref ?unknown_b2ac2c@@3HA=00b2ac2c
// @ref ?unknown_b26898@@3HA=00b26898
// @ref ?unknown_b2ab88@@3HA=00b2ab88
// @ref ?unknown_b2a8a4@@3JA=00b2a8a4
// @ref _time=0078387f
void __fastcall Set_Matchmaking_State_00759df0(int state,int timeout,int result)
{
    unknown_b2ac2c=result;
    unknown_b26898=state;
    unknown_b2ab88=timeout;
    unknown_b2a8a4=time(0);
    return;
}
