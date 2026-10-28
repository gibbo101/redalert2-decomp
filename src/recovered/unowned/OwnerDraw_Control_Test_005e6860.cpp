// bool __fastcall OwnerDraw_Control_Test_005e6860(unsigned int key, HWND window) (0x005E6860)
// A test of an owner-drawn dialog control (name not recovered): true for the listed control
// kinds (record +0x6C of the registered control) with control ID 0x694, the second kind list
// with ID 0x71C and the third with ID 0x468; otherwise a per-kind ID list. Every list return
// (`return id == a || ...`) shares one `mov eax, 1` block; single compares return a sete.
// @ref __imp__GetDlgCtrlID@4=0079a3f4
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

bool __fastcall OwnerDraw_Control_Test_005e6860(unsigned int key, HWND window)
{
    OwnerDraw::UnknownControlRecord *record = OwnerDraw::unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    if (((((((((kind == 0x10c) || (kind == 0x94)) || (kind == 0xa3)) ||
                    (((kind == 0x73 || (kind == 0xd8)) ||
                      ((kind == 0xbbb || ((kind == 0xf5 || (kind == 0x105)))))))) ||
                  ((kind == 0xe2 || (((kind == 0xd5 || (kind == 0x2b5)) || (kind == 0xb7)))))) ||
                (((kind == 0x2b4 || (kind == 0xbc7)) ||
                  (((kind == 0x101 || ((kind == 0x129 || (kind == 0xbc6)))) || (kind == 0xd7)))))) ||
              ((((((((kind == 0x108 || (kind == 0xbc)) || (kind == 0xbd)) ||
                        ((kind == 0xbb || (kind == 0xb5)))) ||
                      ((kind == 0xbba || ((kind == 0xff || (kind == 0x6b)))))) || (kind == 0x100)) ||
                  ((((kind == 0x102 || (kind == 0xb8)) || (kind == 0xd6)) ||
                    (((kind == 0x103 || (kind == 0x125)) ||
                      ((kind == 0xe7 || ((kind == 0x116 || (kind == 0xc2)))))))))) || (kind == 0xc9)))) ||
            (((((kind == 0x11d || (kind == 0x11c)) || (kind == 0x114)) ||
                ((kind == 700 || (kind == 0x113)))) ||
              (((kind == 0x109 || ((kind == 0x10f || (kind == 0x117)))) ||
                ((kind == 0xe6 || (((kind == 0xf3 || (kind == 0xf4)) || (kind == 0x10e)))))))))) &&
          (id == 0x694)) {
        return true;
    }
    if ((((((kind == 0x94) || (kind == 0xd8)) ||
                ((kind == 0xf5 || ((kind == 0xe2 || (kind == 0xd5)))))) ||
              ((kind == 0x101 ||
                (((((kind == 0x129 || (kind == 0xd7)) || (kind == 0xbb)) ||
                    ((kind == 0x100 || (kind == 0xd6)))) || (kind == 0x125)))))) ||
            (((((kind == 0x122 || (kind == 0x112)) ||
                  ((kind == 0xe7 || (((kind == 0x116 || (kind == 0x11d)) || (kind == 0x11c)))))) ||
                (((kind == 0xfe || (kind == 0x10f)) || (kind == 0x117)))) ||
              (((kind == 0x114 || (kind == 0xe6)) ||
                (((kind == 0xf3 || (((kind == 0xf4 || (kind == 700)) || (kind == 0x10e)))) ||
                  ((kind == 0xbc6 || (kind == 0xbc7)))))))))) && (id == 0x71c)) {
        return true;
    }
    if ((((kind == 0xbc) || (kind == 0xbd)) ||
            ((kind == 0x102 ||
              ((((kind == 0xc2 || (kind == 0xc9)) || (kind == 0x105)) ||
                ((kind == 0x6b || (kind == 0x113)))))))) && (id == 0x468)) {
        return true;
    }
    if (kind == 0xe2) {
        return id == 0x686 || id == 0x578 || id == 0x55c || id == 0x683 || id == 0x684;
    }
    if (kind == 0x101) {
        return id == 0x68e || id == 0x68d || id == 0x68f;
    }
    if (kind == 0x129) {
        return id == 0x745;
    }
    if (kind == 0x100) {
        return id == 0x689 || id == 0x688 || id == 0x579;
    }
    if (kind == 0x94) {
        return id == 0x40e;
    }
    if (kind == 0xb7) {
        return id == 0x40f;
    }
    if (kind == 0x2b4) {
        return id == 0x6c7;
    }
    if (kind == 0x2b5) {
        return id == 0x6c8;
    }
    if (kind == 0x105) {
        return id == 0x6c4 || id == 0x6c2 || id == 0x6c3 || id == 0x6c5;
    }
    if (kind == 0x102) {
        return id == 0x6ec || id == 0x5aa || id == 0x5a8 || id == 0x617;
    }
    if (kind == 0xb5) {
        return id == 0x522 || id == 0x521 || id == 0x51e || id == 0x51f || id == 0x520;
    }
    if (kind == 0xbba) {
        return id == 0x522 || id == 0x521;
    }
    if (kind == 0xbbb) {
        return id == 0x52c || id == 0x52d;
    }
    if (kind == 0xd5) {
        return id == 0x5ce || id == 0x5cd;
    }
    if (kind == 0xfb) {
        return id == 6 || id == 1;
    }
    if (kind == 0xd8) {
        return id == 0x6cb;
    }
    if (kind == 0xd7) {
        return id == 1;
    }
    if (kind == 0xbc || kind == 0xc2) {
        return id == 0x6ec || id == 0x588 || id == 0x5aa || id == 0x5a8;
    }
    if (kind == 0xbd || kind == 0xc9) {
        return id == 0x59f || id == 0x6ec || id == 0x5a8;
    }
    if (kind == 0xbb) {
        return id == 0x6cd || id == 0x6cc || id == 0x6ce;
    }
    if (kind == 0xb6) {
        return id == 0x6c9 || id == 0x712 || id == 0x524;
    }
    if (kind == 0x6b) {
        return id == 0x583 || id == 0x6c5;
    }
    if (kind == 0xbc6) {
        return id == 0x6d1;
    }
    if (kind == 0xbc7) {
        return id == 0x6d1;
    }
    if (kind == 0x10f || kind == 0x11d) {
        return id == 0x539 || id == 0x6ea || id == 0x6ec || id == 0x6eb;
    }
    if (kind == 0x109) {
        return id == 1 || id == 0x625 || id == 0x53b;
    }
    if (kind == 0x10e || kind == 0x11c) {
        return id == 0x6e0 || id == 0x6e1 || id == 0x6e2 || id == 0x6e4 || id == 0x6e3;
    }
    if (kind == 0x114) {
        return id == 0x687 || id == 0x6ea || id == 0x6ec || id == 0x6eb || id == 0x688;
    }
    if (kind == 0x113) {
        return id == 0x61f || id == 0x558 || id == 0x689 || id == 0x62d || id == 0x62b || id == 0x53d;
    }
    if (kind == 700) {
        return id == 1 || id == 0x63a;
    }
    if (kind == 0x116) {
        return id == 0x62b || id == 0x62d || id == 0x5c2 || id == 0x702 || id == 0x703;
    }
    if (kind == 0xff) {
        return id == 0x521 || id == 0x522;
    }
    if (kind == 0x122) {
        return id == 1 || id == 2;
    }
    if (kind == 0x112) {
        return id == 1;
    }
    if (kind == 0xe7) {
        return id == 1 || id == 0x576;
    }
    if (kind == 0xfe) {
        return id == 1;
    }
    if (kind == 0xe6 || kind == 0xf3 || kind == 0xf4) {
        return id == 1;
    }
    return false;
}
