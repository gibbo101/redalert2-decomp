// @ref __imp__GetParent@4=0079a500
// @ref __imp__GetDlgCtrlID@4=0079a3f4
// @ref __imp__GetWindowRect@8=0079a398
// @ref __imp__MoveWindow@24=0079a3e0
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ?OwnerDraw_Control_Test_005e6860@@YI_NIPAUHWND__@@@Z=005e6860
// @ref ?unknown_5e72c0@OwnerDraw@@YI_NIPAUHWND__@@@Z=005e72c0
// @ref ?unknown_dialog_a763cc@OwnerDraw@@3PAUHWND__@@A=00a763cc
// @ref ?Bucket_Index@UnknownControlIndex@OwnerDraw@@QBEIABI@Z=00602020
// @ref ?unknown_5e8ba0@OwnerDraw@@YIXPAUHWND__@@ABVRect@@@Z=005e8ba0
// @ref ?unknown_5e8c50@OwnerDraw@@YIXPAUHWND__@@ABUPoint2D@@@Z=005e8c50
// @ref ?unknown_5e8e20@OwnerDraw@@YIXPAUHWND__@@ABUPoint2D@@@Z=005e8e20
// @ref ?unknown_5e8fa0@OwnerDraw@@YIXPAUHWND__@@@Z=005e8fa0
// @ref ?unknown_5e9070@OwnerDraw@@YIXPAUHWND__@@@Z=005e9070
// @ref ?unknown_5e91a0@OwnerDraw@@YIXPAUHWND__@@@Z=005e91a0
// @ref ?unknown_5e9260@OwnerDraw@@YIXPAUHWND__@@@Z=005e9260
// @ref ?unknown_5e9410@OwnerDraw@@YIXPAUHWND__@@@Z=005e9410
// @ref ?Select_Control_Rect_005e6450@OwnerDraw@@YI_NPAUHWND__@@0PAVRect@@@Z=005e6450
// @ref ?Get@UnknownControlIndex@OwnerDraw@@QBE_NABIAAPAUUnknownControlRecord@2@@Z=00601710
// @ref ?FUN_005df660@seed_005df660@@YIEH@Z=005df660
#include "shared/owner_draw_sidebar.hpp"
namespace OwnerDraw {
bool __fastcall Select_Control_Rect_005e6450(HWND dialog, HWND control, Rect *bounds);
void __fastcall unknown_5e8ba0(HWND window, Rect const &rect);
void __fastcall unknown_5e8c50(HWND window, Point2D const &size);
void __fastcall unknown_5e8e20(HWND window, Point2D const &size);
void __fastcall unknown_5e8fa0(HWND window);
void __fastcall unknown_5e9070(HWND window);
void __fastcall unknown_5e91a0(HWND window);
void __fastcall unknown_5e9260(HWND window);
void __fastcall unknown_5e9410(HWND window);

inline bool Is_Placed_Control(unsigned int key, HWND window)
{
    return ::OwnerDraw_Control_Test_005e6860(key, window);
}
inline void Adjust_Control(HWND window)
{
    unknown_5e9410(window);
}
inline bool Is_Lobby_Control(unsigned int key, HWND window)
{
    UnknownControlRecord *record = 0;
    unknown_registry_a73640.Get(key, record);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (kind == 0xe2) {
        return id == 0x71d;
    }
    return false;
}
BOOL __stdcall unknown_5e9bb0(HWND window, LPARAM lparam)
{
    HWND parent = GetParent(window);
    if (unknown_dialog_a763cc == parent) {
        Rect rect(0, 0, 0, 0);
        Point2D const &size = *(Point2D const *)lparam;
        if (Select_Control_Rect_005e6450(parent, window, &rect)) {
            unknown_5e8ba0(window, rect);
        } else if (unknown_5e7230((unsigned int)parent, window)) {
            unknown_5e8c50(window, size);
        } else if (Is_Placed_Control((unsigned int)parent, window)) {
            unknown_5e8e20(window, size);
        } else if (unknown_5e7620((unsigned int)parent, window)) {
            unknown_5e8fa0(window);
        } else if (unknown_5e72c0((unsigned int)parent, window)) {
            unknown_5e9070(window);
        } else if (unknown_5e76b0((unsigned int)parent, window)) {
            unknown_5e91a0(window);
        } else if (Is_Lobby_Control((unsigned int)parent, window)) {
            unknown_5e9260(window);
        } else {
            unknown_5e9390(window, size);
        }
        Adjust_Control(window);
    }
    return TRUE;
}

}
