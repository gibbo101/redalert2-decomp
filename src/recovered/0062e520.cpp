// 0x0062e520: function not yet identified
//
// Body: 129 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void __fastcall FUN_0062e520(byte *param_1)
// Callees with accepted source:
//   FUN_004068f0 -> src/recovered/004068f0.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0062e520 {

extern void  FUN_004068f0(int);
extern void  FUN_004068f0(int, int);
extern "C" undefined4 DAT_00a3d560;
extern "C" undefined4 DAT_00a3d564;
extern "C" undefined4 DAT_00a40d2c;
extern "C" void* PTR_s_EMPTY_007d65cc;
extern "C" char s_FrameSendRate__d_007ecf8c[];
extern "C" char s_Frame___d_007ecfcc[];
extern "C" char s_Frame__d_007ecfa0[];
extern "C" char s_ID___d_007ecfbc[];
extern "C" char s_MaxAhead__d_007ecfac[];
extern "C" char s_Packet_received_too_late__007ed018[];
extern "C" char s_Type___s_007ecfdc[];
extern "C" char s___________Event_data_____________007ecfec[];

void __fastcall FUN_0062e520(byte *param_1)
{
    FUN_004068f0((int)(s_Packet_received_too_late__007ed018));
    FUN_004068f0((int)(s___________Event_data_____________007ecfec));
    FUN_004068f0((int)(s_Type___s_007ecfdc), (int)((&PTR_s_EMPTY_007d65cc)[*param_1]));
    FUN_004068f0((int)(s_Frame___d_007ecfcc), (int)(*(undefined4 *)(param_1 + 3)));
    FUN_004068f0((int)(s_ID___d_007ecfbc), (int)((int)(char)param_1[2]));
    FUN_004068f0((int)(s_MaxAhead__d_007ecfac), (int)(DAT_00a3d560));
    FUN_004068f0((int)(s_Frame__d_007ecfa0), (int)(DAT_00a40d2c));
    FUN_004068f0((int)(s_FrameSendRate__d_007ecf8c), (int)(DAT_00a3d564));
    return;
}

}  // namespace seed_0062e520
