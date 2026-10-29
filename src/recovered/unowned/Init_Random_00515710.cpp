// void __fastcall Init_Random() -- 0x00515710
// __fastcall (no parameters): as __cdecl VC6 schedules the object address loads after the argument pushes.
#include "shared/win32_api.hpp"
#include "shared/random_straw.hpp"
#include "shared/random2.hpp"
#include "shared/id_source.hpp"
#include "shared/wwmouse.hpp"
#include "shared/debug_printf.hpp"

// @ref ?CryptRandom@@3VRandomStraw@@A=00a40778
// @ref ?Seed@@3IA=00a40d3c
// @ref ?CustomSeed@@3IA=00a40d40
// @ref ??_C@_0BE@CGBM@Init?5random?5number?6?$AA@=007dbeac
// @ref ??_C@_0O@LIDB@Seed?5is?5?$CF08x?6?$AA@=007dbe9c
// @ref ?unknown_function_522e80@@YAHXZ=00522e80

// Seeds the scenario's generator and the shared one (0x00839218) from Seed; a new
// single-player or skirmish game first picks Seed (Red Alert's Init_Random).
void __fastcall Init_Random()
{
    Debug_Printf("Init random number\n");
    if (unknown_a3d8c8 != 0 || (unknown_flags_a3f600 & 2) != 0 || unknown_function_522e80() != 0) {
        unknown_id_source_a3d290->RandomNumber = Seed;
        unknown_random_839218 = Seed;
        Debug_Printf("Seed is %08x\n", Seed);
        return;
    }
    if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5) {
        SYSTEMTIME t;
        GetSystemTime(&t);
        CryptRandom.Seed_Byte(t.wMilliseconds);
        CryptRandom.Seed_Bit(t.wSecond);
        CryptRandom.Seed_Bit(t.wSecond >> 1);
        CryptRandom.Seed_Bit(t.wSecond >> 2);
        CryptRandom.Seed_Bit(t.wSecond >> 3);
        CryptRandom.Seed_Bit(t.wSecond >> 4);
        CryptRandom.Seed_Bit(t.wMinute);
        CryptRandom.Seed_Bit(t.wMinute >> 1);
        CryptRandom.Seed_Bit(t.wMinute >> 2);
        CryptRandom.Seed_Bit(t.wMinute >> 3);
        CryptRandom.Seed_Bit(t.wMinute >> 4);
        CryptRandom.Seed_Bit(t.wHour);
        CryptRandom.Seed_Bit(t.wDay);
        CryptRandom.Seed_Bit(t.wDayOfWeek);
        CryptRandom.Seed_Bit(t.wMonth);
        CryptRandom.Seed_Bit(t.wYear);
        if (CustomSeed != 0) {
            Seed = CustomSeed;
        } else {
            CryptRandom.Get(&Seed, sizeof(Seed));
            Seed = GetTickCount();
        }
    }
    Debug_Printf("Seed is %08x\n", Seed);
    unknown_id_source_a3d290->RandomNumber = Seed;
    unknown_random_839218 = Seed;
}
