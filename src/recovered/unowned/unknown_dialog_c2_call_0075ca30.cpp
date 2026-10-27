// void __fastcall unknown_dialog_c2_call(int arg1, int arg2, int arg3) -- 0x0075CA30
// Purpose: passes the arguments to 0x005CBDB0 for dialog 0xC2 (found by
// 0x00735940).
// Assumptions: what 0x005CBDB0 does with them is unknown.
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?unknown_dialog_call_5cbdb0@@YIXPAXHHH@Z=005cbdb0

void *__fastcall Unknown_00735940(int id);              // 0x00735940 (a dialog by id)
void __fastcall unknown_dialog_call_5cbdb0(void *dialog, int arg1, int arg2, int arg3);   // 0x005CBDB0

void __fastcall unknown_dialog_c2_call(int arg1, int arg2, int arg3)
{
    void *dialog = Unknown_00735940(0xC2);
    unknown_dialog_call_5cbdb0(dialog, arg1, arg2, arg3);
}
