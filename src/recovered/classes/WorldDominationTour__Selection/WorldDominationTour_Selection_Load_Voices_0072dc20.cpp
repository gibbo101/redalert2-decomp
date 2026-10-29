// void Selection::Load_Voices(INIClass &ini, Wstring const &section) (0x0072DC20)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Load_Voices(INIClass &ini, Wstring const &section)
{
    TheVoices.Load(ini, section);
    WinningThreshold = ini.Get_Int(section, "WinningThreshold", WinningThreshold);
    MegaWinningThreshold = ini.Get_Int(section, "MegaWinningThreshold", MegaWinningThreshold);
    LosingThreshold = ini.Get_Int(section, "LosingThreshold", LosingThreshold);
    MegaLosingThreshold = ini.Get_Int(section, "MegaLosingThreshold", MegaLosingThreshold);
}
}
// @ref ??_C@_0BA@NBJK@LosingThreshold?$AA@=007fc3c0
// @ref ??_C@_0BB@ONEE@WinningThreshold?$AA@=007fc3e8
// @ref ??_C@_0BE@KDB@MegaLosingThreshold?$AA@=007fc3ac
// @ref ??_C@_0BF@NCJP@MegaWinningThreshold?$AA@=007fc3d0
// @ref ??_E?$rc_ptr@VConflict@WorldDominationTour@@@@UAEPAXI@Z=00726f60
// @ref ??_7?$rc_ptr@VConflict@WorldDominationTour@@@@6B@=007aefec
// @ref ??_E?$rc_ptr@VTerritory@WorldDominationTour@@@@UAEPAXI@Z=0072b940
// @ref ??_7?$rc_ptr@VTerritory@WorldDominationTour@@@@6B@=007af27c
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c
// @ref ??_EWstring@@QAEPAXI@Z=0040af40
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
