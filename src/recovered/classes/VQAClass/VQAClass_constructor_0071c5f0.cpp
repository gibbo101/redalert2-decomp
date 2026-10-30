// VQAClass::VQAClass(char const *filename, int flags, int (*callback538)(), void (*callback53c)(),
// void (*callback540)(), int unknown6, int unknown7) (0x0071C5F0): the library's default configuration, then
// the callbacks and options from the VQA option bits and flags (1: drawer 0x0071D640, 2 and 4: option bits).
#include "shared/movie.hpp"
#include "shared/crt_string.hpp"
// @ref ??0CCFileClass@@QAE@XZ=00468fd0
// @ref ?VQA_Unknown_00777850@@YIXPAUVQAConfig@@@Z=00777850
// @ref ?VQA_Unknown_0071DBA0@@YI_NH@Z=0071dba0
// @ref ?unknown_int_a40b54@@3HA=00a40b54
// @ref ?Unknown_004122C0@@YAXXZ=004122c0
// @ref ?Unknown_00411420@@YAXXZ=00411420
// @ref ?Unknown_004115A0@@YAXXZ=004115a0

void Unknown_004122C0();
void Unknown_00411420();
void Unknown_004115A0();

VQAClass::VQAClass(char const *filename, int flags, int (*callback538)(), void (*callback53c)(),
                   void (*callback540)(), int unknown6, int unknown7)
{
    char unknown;
    VQA_Unknown_00777850(&Config);
    Flags = flags;
    Owner = this;
    Config.unknown_1c = &unknown;
    Config.DrawFlags = 0;
    if (!VQA_Unknown_0071DBA0(15)) {
        Config.DrawFlags |= 1;
    }
    if (!VQA_Unknown_0071DBA0(1)) {
        Config.DrawFlags |= 4;
    }
    if (VQA_Unknown_0071DBA0(10) == true) {
        Config.DrawFlags |= 0x40;
    }
    if (VQA_Unknown_0071DBA0(12) == true) {
        Config.DrawFlags |= 0x80;
    }
    Config.OptionFlags |= 8;
    if (Flags & 2) {
        Config.OptionFlags |= 0x20;
        if (Flags & 4) {
            Config.OptionFlags |= 0x100;
        }
    } else {
        Config.OptionFlags &= ~0x20;
    }
    if (VQA_Unknown_0071DBA0(17) == true) {
        Config.OptionFlags |= 4;
    } else {
        Config.OptionFlags &= ~4;
    }
    if (VQA_Unknown_0071DBA0(3) == true) {
        Config.OptionFlags &= ~1;
    } else {
        Config.OptionFlags |= 1;
    }
    Config.unknown_20 = -1;
    Config.unknown_24 = -1;
    Config.unknown_28 = 0;
    Config.unknown_2c = 0;
    Config.NotifyFlags = 0;
    Config.unknown_30 = unknown6;
    Config.unknown_34 = unknown7;
    if (VQA_Unknown_0071DBA0(3) == true) {
        Config.unknown_48 = 1;
    } else {
        Config.unknown_48 = 14;
    }
    Config.unknown_4c = -1;
    if (Flags & 1) {
        Config.DrawerCallback = VQA_Unknown_0071D640;
    } else {
        Config.DrawerCallback = VQA_Unknown_0071D490;
    }
    Config.EventHandler = VQA_Unknown_0071D680;
    Config.unknown_08 = VQA_Unknown_0071D6E0;
    if (VQA_Unknown_0071DBA0(4) == true) {
        Config.unknown_10 = Unknown_004122C0;
        Config.FrameRate = 60;
    } else {
        Config.unknown_10 = Unknown_00411420;
        Config.FrameRate = 60;
        unknown_1f4 = unknown_int_a40b54 & 0xFFFF;
    }
    Config.unknown_18 = Unknown_004115A0;
    Config.unknown_5c = 0x2000;
    CurrentFrame = 0;
    unknown_544 = 0;
    FrameCount = 0;
    strcpy(Filename, filename);
    Width = 0;
    Height = 0;
    unknown_518 = 0;
    unknown_51c = 0;
    unknown_508 = -1;
    PaletteChanged = false;
    Callback538 = callback538;
    Callback53C = callback53c;
    Callback540 = callback540;
    FileOpen = false;
    Opened = false;
    unknown_548 = false;
    unknown_549 = false;
    Companion = 0;
}
