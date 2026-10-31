#include "shared/wol_sink.hpp"
// RA2 retains destruction of the by-value sound category, with no playback work.
// Original callers construct a 12-byte independent list before calling 0x752890;
// the complete callee destroys Count Wstrings forwards and frees Items.
// __fastcall is an ABI hypothesis: the class argument is stack-passed and RET 12.
void __fastcall Discard_WDT_Sound_List_00752890(WolStringArray sounds)
{
}
