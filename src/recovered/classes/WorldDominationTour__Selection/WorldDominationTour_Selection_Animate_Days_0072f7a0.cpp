// bool Selection::Animate_Days(int from, int to) (0x0072F7A0)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
WideString __fastcall unknown_number_text_width_771130(int number, int width);
namespace WorldDominationTour {
bool Selection::Animate_Days(int from, int to)
{
    bool first = true;
    bool first_state = true;
    unsigned length = 0;
    for (int day = from; day <= to; day++) {
        Check_Escape();
        if (Escaped) {
            break;
        }
        WideString text(StringTable::Load_String("WDT:ReviewingHistory", 0, "D:\\Ra2\\WDTSel.cpp", 995));
        text += L"\n";
        if (first) {
            length = text.Length();
        }
        text += WideString(StringTable::Load_String("WDT:ReviewingHistoryDay", 0, "D:\\Ra2\\WDTSel.cpp", 1003)) + WideString(L" ") + unknown_number_text_width_771130(day + 1, 2);
        Set_Description(text, first ? 0 : length);
        Show_State(TheCampaign->TheHistory->Get_State(day), false, first_state);
        first = false;
        first_state = false;
        Wait_For(Description, 300000);
        int count = 5;
        while (!Escaped && count--) {
            Run(5);
            Check_Escape();
        }
        if (Escaped) {
            break;
        }
    }
    return first;
}
}
// @ref ??_C@_0BF@ONEC@WDT?3ReviewingHistory?$AA@=007fc620
// @ref ??_C@_0BI@GJDA@WDT?3ReviewingHistoryDay?$AA@=007fc608
// @ref ??_C@_0BC@PBP@D?3?2Ra2?2WDTSel?4cpp?$AA@=007fc31c
// @ref ??_C@_13DEJI@?$AA?6?$AA?$AA@=007e58ec
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ?unknown_number_text_width_771130@@YI?AVWideString@@HH@Z=00771130
// @ref ??_7?$rc_ptr@VState@WorldDominationTour@@@@6B@=007aefe4
// @ref ??_G?$rc_ptr@VState@WorldDominationTour@@@@UAEPAXI@Z=00726b70
// @ref ?Run@MSEngine@@QAEXH@Z=005b3550
// @ref ?Show_State@Selection@WorldDominationTour@@QAEXABV?$rc_ptr@VState@WorldDominationTour@@@@_N1@Z=0072e780
