// void __fastcall Selection::Show(rc_ptr<Campaign> const &campaign, int faction) (0x0072FF80)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void __fastcall Selection::Show(rc_ptr<Campaign> const &campaign, int faction)
{
    WWKeyboard->Clear();
    Selection selection(campaign, faction);
    selection.Show_Result(faction);
}
}
// @ref ??0Selection@WorldDominationTour@@QAE@ABV?$rc_ptr@VCampaign@WorldDominationTour@@@@H@Z=0072d560
// @ref ??1Selection@WorldDominationTour@@UAE@XZ=0072d990
// @ref ?Show_Result@Selection@WorldDominationTour@@QAEXH@Z=0072fa00
