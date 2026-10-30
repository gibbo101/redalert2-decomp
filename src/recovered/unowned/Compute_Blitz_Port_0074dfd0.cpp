#include "shared/debug_printf.hpp"
extern char blitz_port_debug_007fee9c[];
// @ref ?blitz_port_debug_007fee9c@@3PADA=007fee9c
unsigned short __fastcall Compute_Blitz_Port_0074dfd0(int sender,int base,int unknown,int step)
{
    int port=sender+base;
    if(step!=1) {
      if(step==2) {
        port=base+sender*2;
    } else if(step>1) {
        port=sender%2+base+(sender/2)*step;
    } else if(step<0) {
        if(step==-100) port=base+sender*100;
        else port=sender%2-(sender/2)*step+base;
    }
    }
    Debug_Printf(blitz_port_debug_007fee9c,sender,base,step,port);
    if((unsigned short)port<1024) port=1024;
    return (unsigned short)port;
}
