// 0x007354d0: function not yet identified
//
// Body: 317 bytes (frozen inventory bound).
// Referenced from 4 sites (unconditional call).
// Ghidra prototype: void __thiscall FUN_007354d0(int param_1,uint param_2,byte param_3)
// Callees with accepted source:
//   FUN_004068f0 -> src/recovered/004068f0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_007354d0 {

extern void  FUN_004068f0(int);
extern "C" char s_Comm_status___Character_waiting_f_007fcdd0[];
extern "C" char s_Comm_status___EOF_character_sent_007fcdf8[];
extern "C" char s_Comm_status___Tx_waiting__XOFF_c_007fce1c[];
extern "C" char s_Comm_status___Tx_waiting__XOFF_c_007fce48[];
extern "C" char s_Comm_status___Tx_waiting_for_CTS_007fced0[];
extern "C" char s_Comm_status___Tx_waiting_for_DSR_007fcea4[];
extern "C" char s_Comm_status___Tx_waiting_for_RLS_007fce78[];
extern "C" char s_Communications__Break__detected__007fcff8[];
extern "C" char s_Communications__Framing__error_d_007fd01c[];
extern "C" char s_Communications__IO__error_detect_007fcfd0[];
extern "C" char s_Communications__Parity__error_de_007fcf34[];
extern "C" char s_Communications__Receive_Overrun__007fcf9c[];
extern "C" char s_Communications__Receive_Queue_Ov_007fcf60[];
extern "C" char s_Communications__Transmit_Queue_F_007fcefc[];

struct Owner_007354d0 { void FUN_007354d0(uint param_2, byte param_3, int unused_2, int unused_3); };

void Owner_007354d0::FUN_007354d0(uint param_2, byte param_3, int unused_2, int unused_3)
{
    int param_1 = (int)this;
    if (param_2 != 0) {
        if ((param_2 & 8) != 0) {
            FUN_004068f0((int)(s_Communications__Framing__error_d_007fd01c));
            *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
        }
        if ((param_2 & 0x10) != 0) {
            FUN_004068f0((int)(s_Communications__Break__detected__007fcff8));
        }
        if ((param_2 & 0x400) != 0) {
            FUN_004068f0((int)(s_Communications__IO__error_detect_007fcfd0));
            *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
        }
        if ((param_2 & 2) != 0) {
            FUN_004068f0((int)(s_Communications__Receive_Overrun__007fcf9c));
            *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
        }
        if ((param_2 & 1) != 0) {
            FUN_004068f0((int)(s_Communications__Receive_Queue_Ov_007fcf60));
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
        }
        if ((param_2 & 4) != 0) {
            FUN_004068f0((int)(s_Communications__Parity__error_de_007fcf34));
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
        }
        if ((param_2 & 0x100) != 0) {
            FUN_004068f0((int)(s_Communications__Transmit_Queue_F_007fcefc));
            *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
        }
    }
    if ((param_3 & 1) != 0) {
        FUN_004068f0((int)(s_Comm_status___Tx_waiting_for_CTS_007fced0));
    }
    if ((param_3 & 2) != 0) {
        FUN_004068f0((int)(s_Comm_status___Tx_waiting_for_DSR_007fcea4));
    }
    if ((param_3 & 4) != 0) {
        FUN_004068f0((int)(s_Comm_status___Tx_waiting_for_RLS_007fce78));
    }
    if ((param_3 & 8) != 0) {
        FUN_004068f0((int)(s_Comm_status___Tx_waiting__XOFF_c_007fce48));
    }
    if ((param_3 & 0x10) != 0) {
        FUN_004068f0((int)(s_Comm_status___Tx_waiting__XOFF_c_007fce1c));
    }
    if ((param_3 & 0x20) != 0) {
        FUN_004068f0((int)(s_Comm_status___EOF_character_sent_007fcdf8));
    }
    if ((param_3 & 0x40) != 0) {
        FUN_004068f0((int)(s_Comm_status___Character_waiting_f_007fcdd0));
    }
    return;
}

}  // namespace seed_007354d0
