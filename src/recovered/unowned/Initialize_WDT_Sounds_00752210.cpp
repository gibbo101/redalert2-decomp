// WDT sound table initializer; complete1268B+12NOP, mapped before source.
#include "shared/wol_sink.hpp"
extern bool unknown_wdt_sounds_initialized_b2ac28;
// @ref ?unknown_wdt_sounds_initialized_b2ac28@@3_NA=00b2ac28
void __fastcall Initialize_WDT_Sounds_00752210()
{
    if(!unknown_wdt_sounds_initialized_b2ac28) {
        static Wstring sounds[16];
        sounds[0].Set("01-W024.V01");
        sounds[1].Set("01-W026.V01");
        sounds[2].Set("01-W028.V01");
        sounds[3].Set("01-W018.V01");
        sounds[4].Set("01-W020.V01");
        sounds[5].Set("01-W022.V01");
        sounds[6].Set("00-W022.V00");
        sounds[7].Set("00-W024.V00");
        sounds[8].Set("00-W026.V00");
        sounds[9].Set("00-W017.V00");
        sounds[10].Set("00-W018.V00");
        sounds[11].Set("00-W020.V00");
        sounds[12].Set("01-W032.V01");
        sounds[13].Set("01-W030.V01");
        sounds[14].Set("00-W031.V00");
        sounds[15].Set("00-W029.V00");
        unknown_strings_b26a50.Clear();
        unknown_strings_b26570.Clear();
        unknown_strings_b299b0.Clear();
        unknown_strings_b29380.Clear();
        unknown_strings_b26960.Clear();
        unknown_strings_b2a6c8.Clear();
        unknown_strings_b26580.Clear();
        unknown_strings_b29000.Clear();
        unknown_strings_b26a50.Add_Head(sounds[0]);
        unknown_strings_b26a50.Add_Head(sounds[1]);
        unknown_strings_b26a50.Add_Head(sounds[2]);
        unknown_strings_b299b0.Add_Head(sounds[3]);
        unknown_strings_b299b0.Add_Head(sounds[4]);
        unknown_strings_b299b0.Add_Head(sounds[5]);
        unknown_strings_b26570.Add_Head(sounds[6]);
        unknown_strings_b26570.Add_Head(sounds[7]);
        unknown_strings_b26570.Add_Head(sounds[8]);
        unknown_strings_b29380.Add_Head(sounds[9]);
        unknown_strings_b29380.Add_Head(sounds[10]);
        unknown_strings_b29380.Add_Head(sounds[11]);
        unknown_strings_b26960.Add_Head(sounds[12]);
        unknown_strings_b26580.Add_Head(sounds[13]);
        unknown_strings_b2a6c8.Add_Head(sounds[14]);
        unknown_strings_b29000.Add_Head(sounds[15]);
        unknown_wdt_sounds_initialized_b2ac28=true;
    }
}
// @ref ?Grow@?$WolArrayList@VWstring@@@@QAE_NXZ=00768320
// @ref ??_C@_0M@BGHK@00?9W029?4V00?$AA@=007ff9e4
// @ref ??_C@_0M@ICPA@00?9W031?4V00?$AA@=007ff9f0
// @ref ??_C@_0M@HIA@01?9W030?4V01?$AA@=007ff9fc
// @ref ??_C@_0M@EHMK@01?9W032?4V01?$AA@=007ffa08
// @ref ??_C@_0M@LHHF@00?9W020?4V00?$AA@=007ffa14
// @ref ??_C@_0M@ILP@00?9W018?4V00?$AA@=007ffa20
// @ref ??_C@_0M@GJGP@00?9W017?4V00?$AA@=007ffa2c
// @ref ??_C@_0M@HHKK@00?9W026?4V00?$AA@=007ffa38
// @ref ??_C@_0M@DHOA@00?9W024?4V00?$AA@=007ffa44
// @ref ??_C@_0M@PHDP@00?9W022?4V00?$AA@=007ffa50
// @ref ??_C@_0M@NCGK@01?9W022?4V01?$AA@=007ffa5c
// @ref ??_C@_0M@JCCA@01?9W020?4V01?$AA@=007ffa68
// @ref ??_C@_0M@CNOK@01?9W018?4V01?$AA@=007ffa74
// @ref ??_C@_0M@JDAK@01?9W028?4V01?$AA@=007ffa80
// @ref ??_C@_0M@FCPP@01?9W026?4V01?$AA@=007ffa8c
// @ref ??_C@_0M@BCLF@01?9W024?4V01?$AA@=007ffa98
// @ref _?sounds@?4??Initialize_WDT_Sounds_00752210@@YIXXZ@4PAVWstring@@A=00b297d0
// @ref _?$S209@?4??Initialize_WDT_Sounds_00752210@@YIXXZ@4EA=00b29734
// @ref ?Add_At@?$WolArrayList@VWstring@@@@QAEDAAVWstring@@H@Z=007679c0
