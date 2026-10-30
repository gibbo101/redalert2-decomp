// bool VQAClass::Unknown_0071CFC0(bool *unknown) (0x0071CFC0): VQAClass::Advance_Frame (debug strings);
// true when a frame was drawn; otherwise *unknown is set when the movie ended with an error.
#include "shared/movie.hpp"
#include "shared/palette.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?Set@PaletteClass@@QAEXXZ=00496120
// @ref ??_C@_0CD@BELF@VQAClass?3?3Advance_Frame?$CI?$CJ?5?9?5Read@=007fb16c
// @ref ??_C@_0CD@GFFF@VQAClass?3?3Advance_Frame?$CI?$CJ?5?9?5Paus@=007fb120
// @ref ??_C@_0CF@NHAK@VQAClass?3?3Advance_Frame?$CI?$CJ?5?9?5Unpa@=007fb144
// @ref ?Unknown_0069B420@VQAMovieCompanion@@QAE_NH@Z=0069b420
// @ref ?VQA_Unknown_0070B690@@YIXH@Z=0070b690
// @ref ?VQA_Unknown_0070B820@@YAXXZ=0070b820
// @ref ?VQA_Unknown_0077C440@@YIHPAUVQAHandle@@P6AXXZ1@Z=0077c440
// @ref ?VQA_Unknown_0077C8A0@@YIHPAUVQAHandle@@H@Z=0077c8a0
// @ref ?VQA_Unknown_0077C920@@YIHPAUVQAHandle@@PAH11@Z=0077c920
// @ref ?VQA_Unknown_0077CBA0@@YIHPAUVQAHandle@@@Z=0077cba0
// @ref ?VQA_Unknown_0077FD80@@YAXXZ=0077fd80
// @ref ?unknown_vqa_paused_af901c@@3_NA=00af901c

bool VQAClass::Unknown_0071CFC0(bool *unknown)
{
    *unknown = false;
    if (!unknown_549) {
        VQA_Unknown_0077C8A0(Handle, FrameCount);
        if (unknown_508 != -1) {
            int unknown2;
            int unknown3;
            int state;
            VQA_Unknown_0077C920(Handle, &unknown3, &unknown2, &state);
            if (state == 1 || state == 4) {
                VQA_Unknown_0070B690(unknown_508);
                if (state == 1) {
                    VQA_Unknown_0077C440(Handle, VQA_Unknown_0077FD80, VQA_Unknown_0070B820);
                }
            }
        }
        Debug_Printf("VQAClass::Advance_Frame() - Ready\n");
        unknown_549 = true;
    }
    if (unknown_548 == true && !(unknown_flags_a3f600 & 2) && unknown_int_a40d48 == 0) {
        if (unknown_flag_a40d28 != true) {
            goto pause;
        }
        unknown_548 = false;
        Debug_Printf("VQAClass::Advance_Frame() - Unpause\n");
    }
    if (unknown_flag_a40d28 == true && !unknown_548) {
        int result = VQA_Unknown_0077BF10(Handle, 1, 0);
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
            return true;
        }
        switch (result) {
        case -11:
        case -10:
        case -1:
            *unknown = false;
            return false;
        default:
            *unknown = true;
            return false;
        }
    }
pause:
    if (!unknown_vqa_paused_af901c) {
        if (Opened && !unknown_548) {
            VQA_Unknown_0077BF10(Handle, 2, 0);
        }
        unknown_548 = true;
        unknown_vqa_paused_af901c = true;
        Debug_Printf("VQAClass::Advance_Frame() - Pause\n");
    }
    return false;
}
