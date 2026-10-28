// bool __fastcall OwnerDraw_Control_Test_005e0760(unsigned int key, HWND window) (0x005E0760)
// A test of an owner-drawn dialog control (name not recovered): true for the listed
// control kinds (record +0x6C of the registered control) with control ID 0x694, the
// 0xBC/0xBD/0x102/0xC2/0xC9 kinds with IDs 0x6EC/0x5A8, and per-kind ID lists; also for
// a 0x005DF660 kind with ID 0x695 while the session byte +0x3080 is clear. Seed 0x005E0DA0
// returns 0 or 1 in eax and the original tests only al (the char conversion).
// @ref __imp__GetDlgCtrlID@4=0079a3f4
// @ref ?Unknown_00672F10@UnknownSessionState@@QAEEXZ=00672f10
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

#include "shared/unknown_globals.hpp"
namespace seed_005df660 {
unsigned char __fastcall FUN_005df660(int param_1);   // 0x005DF660
}
namespace seed_005e0da0 {
unsigned int __fastcall FUN_005e0da0(int param_1);    // 0x005E0DA0 (returns 0 or 1 in eax; callers test only al)
}

bool __fastcall OwnerDraw_Control_Test_005e0760(unsigned int key, HWND window)
{

    OwnerDraw::UnknownControlRecord *record = OwnerDraw::unknown_registry_a73640.Find(key);
    int kind = record != 0 ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(window);
    bool general = ((((((((kind == 0x10c) || (kind == 0x94)) || (kind == 0xa3)) ||
                    ((kind == 0x73 || (kind == 0xd8)))) || (kind == 0xbbb)) ||
                (((kind == 0xf5 || (kind == 0x105)) ||
                  ((kind == 0xe2 || (((kind == 0xd5 || (kind == 0x2b5)) || (kind == 0xb7)))))))) ||
              (((kind == 0x2b4 || (kind == 0xbc7)) ||
                ((kind == 0x101 ||
                  ((((kind == 0x129 || (kind == 0xbc6)) ||
                      ((kind == 0xd7 || (((kind == 0x108 || (kind == 0xbc)) || (kind == 0xbd)))))) ||
                    ((kind == 0xbb || (kind == 0xb5)))))))))) ||
            ((kind == 0xbba ||
              (((kind == 0xff || (kind == 0x6b)) ||
                ((kind == 0x100 ||
                  ((((kind == 0x102 || (kind == 0xb8)) || (kind == 0xd6)) ||
                    ((kind == 0x103 || (char)seed_005e0da0::FUN_005e0da0(kind) != 0))))))))))) && (id == 0x694)
          ;
    if (general) {
        return true;
    }
    bool dual_rail = (((kind == 0xbc) || (kind == 0xbd)) ||
            ((kind == 0x102 || ((kind == 0xc2 || (kind == 0xc9)))))) &&
          ((id == 0x6ec || (id == 0x5a8)));
    if (dual_rail) {
        return true;
    }
    bool special_103 = ((kind == 0x103) || (kind == 0xbc7)) &&
          (((((id == 0x6f3 || (((id == 0x6f4 || (id == 0x69f)) || (id == 0x6f6)))) ||
                (((id == 0x6ef || (id == 0x6f1)) || (id == 0x6f0)))) ||
              (((id == 0x6f2 || (id == 0x733)) ||
                ((id == 0x735 || (((id == 0x732 || (id == 0x3ea)) || (id == 0x736)))))))) ||
            (((id == 0x737 || (id == 0x73c)) ||
              ((((id == 0x73d ||
                    (((id == 0x73e || (id == 0x73f)) ||
                      ((id == 0x740 ||
                        ((((id == 0x411 || (id == 0x412)) || (id == 0x419)) ||
                          ((id == 0x41a || (id == 0x6a3)))))))))) || (id == 0x6a4)) ||
                (((id == 0x6a5 || (id == 0x6a7)) ||
                  (((id == 0x6a6 || (((id == 0x6a8 || (id == 0x73a)) || (id == 0x739)))) ||
                    ((id == 0x73b || (id == 0x738)))))))))))));
    if (special_103) {
        return true;
    }
    bool special_108 = ((kind == 0x108) || (kind == 0xbc6)) &&
          (((((id == 0x6d2 || (((id == 0x3ea || (id == 0x69d)) || (id == 0x69f)))) ||
                ((((id == 0x69e || (id == 0x6a0)) || (id == 0x6a1)) ||
                  ((id == 0x5c8 || (id == 0x411)))))) ||
              ((id == 0x412 ||
                ((((((id == 0x413 || (id == 0x414)) || (id == 0x415)) ||
                      ((id == 0x416 || (id == 0x417)))) || (id == 0x418)) ||
                  ((id == 0x419 || (id == 0x41a)))))))) ||
            (((((id == 0x41b || (((id == 0x41c || (id == 0x41d)) || (id == 0x41e)))) ||
                  ((((id == 0x41f || (id == 0x420)) ||
                      ((((id == 0x6a3 || ((id == 0x6a4 || (id == 0x6a9)))) || (id == 0x6ac)) ||
                        (((id == 0x6af || (id == 0x6b2)) || (id == 0x6b5)))))) ||
                    ((((id == 0x6b8 || (id == 0x6a5)) ||
                        ((id == 0x6a7 || ((id == 0x6aa || (id == 0x6ad)))))) || (id == 0x6b0))))))
                || (((((id == 0x6b3 || (id == 0x6b6)) || (id == 0x6b9)) ||
                          ((id == 0x6a6 || (id == 0x6a8)))) ||
                        (((id == 0x6ab || ((id == 0x6ae || (id == 0x6b1)))) ||
                          ((id == 0x6b4 ||
                            ((((((id == 0x6b7 || (id == 0x6ba)) || (id == 0x70a)) ||
                                  ((id == 0x70b || (id == 0x70c)))) ||
                                ((id == 0x70d || ((id == 0x70e || (id == 0x70f)))))) || (id == 0x710))))
                          )))))) ||
              ((((id == 0x711 || (id == 0x733)) || (id == 0x732)) ||
                ((id == 0x71b || (id == 0x735)))))))));
    if (special_108) {
        return true;
    }
    char special = seed_005df660::FUN_005df660(kind);
    if (((special != 0) && (id == 0x695)) && unknown_session_a3d298.Unknown_00672F10() == 0) {
        return true;
    }
    return false;
}

