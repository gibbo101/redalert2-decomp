// 0x0060E4C0
bool PhoneEntryEdit::Dialog(PhoneEntryClass *phone)
{
    if (phone == 0) {
        return false;
    }
    _Dialog = unknown_create_dialog_5ff610(0xEF, Edit_Phone_Dialog_Proc, 0);
    if (_Dialog) {
        Phone = phone;
        RC = -1;
        SetWindowLongA(_Dialog, DWL_USER, (LONG)this);
        Init();
        unknown_dialog_5ff7c0(_Dialog);
        while (RC < 0) {
            if (unknown_6000d0() == true) {
                break;
            }
            unknown_517370(false);
        }
        unknown_dialog_5ff6e0(_Dialog);
    }
    if (RC != 1) {
        return false;
    }
    return true;
}
// @ref ?Edit_Phone_Dialog_Proc@@YGHPAUHWND__@@IIJ@Z=0060e540
// @ref ?Init@PhoneEntryEdit@@QAEXXZ=0060e900
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref __imp__SetWindowLongA@12=0079a488
