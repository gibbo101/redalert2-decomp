// int VQAClass::Unknown_0071CCD0(int frame, bool unknown) (0x0071CCD0): plays the movie until it ends (to
// frame; out of range: the last), pumping window messages and sleeping while the application is inactive;
// returns 1 when stopped by Escape (keys are not read when unknown is set).
#include "shared/movie.hpp"
#include "shared/palette.hpp"
#include "shared/debug_printf.hpp"
#include "shared/keyboard.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Set@PaletteClass@@QAEXXZ=00496120
// @ref ??_C@_0BA@ODBD@Movie?5is?5awake?6?$AA@=007fb110
// @ref ??_C@_0BD@PAIN@Movie?5is?5sleeping?6?$AA@=007fb0fc
// @ref ?Unknown_0069B420@VQAMovieCompanion@@QAE_NH@Z=0069b420
// @ref ?VQA_Unknown_0070B690@@YIXH@Z=0070b690
// @ref ?VQA_Unknown_0070B820@@YAXXZ=0070b820
// @ref ?VQA_Unknown_0077C440@@YIHPAUVQAHandle@@P6AXXZ1@Z=0077c440
// @ref ?VQA_Unknown_0077C8A0@@YIHPAUVQAHandle@@H@Z=0077c8a0
// @ref ?VQA_Unknown_0077C920@@YIHPAUVQAHandle@@PAH11@Z=0077c920
// @ref ?VQA_Unknown_0077CBA0@@YIHPAUVQAHandle@@@Z=0077cba0
// @ref ?VQA_Unknown_0077FD80@@YAXXZ=0077fd80
// @ref ?VQA_Unknown_0077FE89@@YAXXZ=0077fe89
// @ref ?VQA_Unknown_0070BBC0@@YAXXZ=0070bbc0
// @ref ?VQA_Unknown_0070BF60@@YAXXZ=0070bf60
// @ref ?VQA_Unknown_0070C0A0@@YAXXZ=0070c0a0
// @ref ?VQA_Unknown_0071DBA0@@YI_NH@Z=0071dba0

int VQAClass::Unknown_0071CCD0(int frame, bool unknown)
{
    bool done = false;
    bool sleeping = false;
    if (frame < 0 || frame >= FrameCount) {
        frame = FrameCount - 1;
    }
    VQA_Unknown_0077C8A0(Handle, frame);
    if (unknown_508 != -1) {
        int unknown2;
        int unknown3;
        int state;
        VQA_Unknown_0077C920(Handle, &unknown3, &unknown2, &state);
        if (state == 1) {
            VQA_Unknown_0070B690(unknown_508);
            if (VQA_Unknown_0071DBA0(11)) {
                VQA_Unknown_0077C440(Handle, VQA_Unknown_0077FE89, VQA_Unknown_0070BBC0);
            } else {
                VQA_Unknown_0077C440(Handle, VQA_Unknown_0077FD80, VQA_Unknown_0070B820);
            }
        } else if (state == 4) {
            VQA_Unknown_0070B690(unknown_508);
            if (VQA_Unknown_0071DBA0(11)) {
                VQA_Unknown_0077C440(Handle, VQA_Unknown_0070BF60, VQA_Unknown_0070C0A0);
            }
        }
    }
    int result = 0;
    while ((result >= 0 || result == -10 || result == -9 || result == -11 || result == -1) && !done) {
        VQA_Unknown_0071C590();
        if (sleeping == true) {
            if (unknown_flag_a40d28 == false) {
                Sleep(33);
                continue;
            }
            sleeping = false;
            unknown_548 = false;
            Debug_Printf("Movie is awake\n");
        }
        if (unknown_flag_a40d28 == true && !unknown_548) {
            result = VQA_Unknown_0077BF10(Handle, 1, 0);
            if (result >= 0) {
                if (PaletteChanged) {
                    Unknown_0071CB20();
                    PaletteChanged = false;
                }
                if (Companion) {
                    Companion->Unknown_0069B420(VQA_Unknown_0077CBA0(Handle));
                }
                if (Callback540) {
                    Callback540();
                }
                CurrentFrame = result + 1;
            }
        } else if (!sleeping) {
            sleeping = true;
            if (Opened && !unknown_548) {
                VQA_Unknown_0077BF10(Handle, 2, 0);
            }
            unknown_548 = true;
            Debug_Printf("Movie is sleeping\n");
        }
        if (!unknown && WWKeyboard->Check() && WWKeyboard->Get() == 0x81B) {
            done = true;
        }
    }
    if (done) {
        return 1;
    }
    return 0;
}
