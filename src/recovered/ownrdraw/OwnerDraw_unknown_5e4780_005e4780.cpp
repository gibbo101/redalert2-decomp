// @ref __imp__GetParent@4=0079a500
// @ref __imp__GetDlgCtrlID@4=0079a3f4
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref ?Is_Listed_Kind_5e0da0@OwnerDraw@@YI_NH@Z=005e0da0
// @ref ?FUN_005df660@seed_005df660@@YIEH@Z=005df660
// @ref ?OwnerDraw_Control_Test_005e6860@@YI_NIPAUHWND__@@@Z=005e6860
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace seed_005df660 {
unsigned char __fastcall FUN_005df660(int param_1);
}
namespace OwnerDraw {

bool __fastcall Is_Listed_Kind_5e0da0(int kind);
BOOL __fastcall Is_Listed_Kind_5e8590(int kind);
void __fastcall unknown_5e46c0(HWND control, bool value);

inline bool Is_Option_Kind(int kind)
{
    return kind == 0xbc || kind == 0xbd || kind == 0x102 || kind == 0xc2 || kind == 0xc9;
}
inline bool Is_Kind_103(int kind)
{
    return kind == 0x103 || kind == 0xbc7;
}
inline bool Is_Kind_108(int kind)
{
    return kind == 0x108 || kind == 0xbc6;
}
inline bool Is_Rail_ID(int id)
{
    return id == 0x6ec || id == 0x5a8;
}
// BS_OWNERDRAW style.
inline bool Is_Owner_Button(HWND window)
{
    return (GetWindowLongA(window, GWL_STYLE) & 0xb) == 0xb;
}
inline bool Is_Free_Record(HWND window)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)window);
    return record != 0 && record->unknown_68 == 0;
}
inline int Kind_Of(unsigned int key)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find(key);
    return record != 0 ? record->unknown_6c : 0;
}
// EnumChildWindows callback (0x005E4780): stores lparam in the control's record +0xBC for the listed
// kind and control ID pairs and for free owner-draw buttons accepted by 0x005E6860 or 0x005E72C0.
BOOL __stdcall unknown_5e4780(HWND window, LPARAM lparam)
{
    HWND parent = GetParent(window);
    int kind = Kind_Of((unsigned int)parent);
    int id = GetDlgCtrlID(window);
    bool value = lparam != 0;
    if (!(((kind == 0x10c || kind == 0x94 || kind == 0xa3 || kind == 0x73 || kind == 0xd8 || kind == 0xbbb || kind == 0xf5 || kind == 0x105 || kind == 0xe2 || kind == 0xd5 || kind == 0x2b5 || kind == 0xb7 || kind == 0x2b4 || kind == 0xbc7 || kind == 0x101 || kind == 0x129 || kind == 0xbc6 || kind == 0xd7 || kind == 0x108 || kind == 0xbc || kind == 0xbd || kind == 0xbb || kind == 0xb5 || kind == 0xbba || kind == 0xff || kind == 0x6b || kind == 0x100 || kind == 0x102 || kind == 0xb8 || kind == 0xd6 || kind == 0x103 || Is_Listed_Kind_5e0da0(kind)) && id == 0x694)
        || (seed_005df660::FUN_005df660(kind) && id == 0x695)
        || (Is_Listed_Kind_5e8590(kind) && id == 0x71c)
        || ((Is_Option_Kind(kind) || kind == 0x105 || kind == 0x6b || kind == 0x113) && id == 0x468)
        || ((Is_Option_Kind(kind)) && Is_Rail_ID(id))
        || (Is_Kind_103(kind) && (id == 0x6f3 || id == 0x6f4 || id == 0x72b || id == 0x6ef || id == 0x6f1 || id == 0x6f0 || id == 0x6f2 || id == 0x69f || id == 0x6f6 || id == 0x733 || id == 0x735 || id == 0x732 || id == 0x3ea || id == 0x736 || id == 0x737 || id == 0x73c || id == 0x73d || id == 0x73e || id == 0x73f || id == 0x740 || id == 0x411 || id == 0x412 || id == 0x419 || id == 0x41a || id == 0x6a3 || id == 0x6a4 || id == 0x6a5 || id == 0x6a7 || id == 0x6a6 || id == 0x6a8 || id == 0x73a || id == 0x739 || id == 0x73b || id == 0x738))
        || (Is_Kind_108(kind) && (id == 0x6d2 || id == 0x3ea || id == 0x69d || id == 0x69f || id == 0x69e || id == 0x6a0 || id == 0x6a1 || id == 0x5c8 || id == 0x411 || id == 0x412 || id == 0x413 || id == 0x414 || id == 0x415 || id == 0x416 || id == 0x417 || id == 0x418 || id == 0x419 || id == 0x41a || id == 0x41b || id == 0x41c || id == 0x41d || id == 0x41e || id == 0x41f || id == 0x420 || id == 0x6a3 || id == 0x6a4 || id == 0x6a9 || id == 0x6ac || id == 0x6af || id == 0x6b2 || id == 0x6b5 || id == 0x6b8 || id == 0x6a5 || id == 0x6a7 || id == 0x6aa || id == 0x6ad || id == 0x6b0 || id == 0x6b3 || id == 0x6b6 || id == 0x6b9 || id == 0x6a6 || id == 0x6a8 || id == 0x6ab || id == 0x6ae || id == 0x6b1 || id == 0x6b4 || id == 0x6b7 || id == 0x6ba || id == 0x70a || id == 0x70b || id == 0x70c || id == 0x70d || id == 0x70e || id == 0x70f || id == 0x710 || id == 0x711 || id == 0x733 || id == 0x732 || id == 0x71b || id == 0x735))
        || (Is_Owner_Button(window) && Is_Free_Record(window) && ::OwnerDraw_Control_Test_005e6860((unsigned int)parent, window))
        || (Is_Owner_Button(window) && Is_Free_Record(window) && unknown_5e72c0((unsigned int)parent, window)))) {
        return TRUE;
    }
    unknown_5e46c0(window, value);
    return TRUE;
}

}
