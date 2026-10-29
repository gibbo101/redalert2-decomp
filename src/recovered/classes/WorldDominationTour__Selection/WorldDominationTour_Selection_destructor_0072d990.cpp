// Selection::~Selection() (0x0072D990)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
#include "shared/text_print.hpp"
namespace WorldDominationTour {
Selection::~Selection()
{
    Clear_Screen();
    unknown_464.Set(0);
    Remove_Territory_Anims();
    Remove_Territory_Anims_2();
    for (SfxCursor cursor(Sounds); cursor; ++cursor) {
        delete *cursor;
    }
    delete TargetPalette;
    delete ZoomingTarget;
    delete Target;
    delete unknown_484;
    BitFont->Set_Color(OldFontColor);
}
}
// @ref ??0?$VectorCursor@V?$rc_ptr@VTerritory@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@@@QAE@AAV?$DynamicVectorClass@V?$rc_ptr@VTerritory@WorldDominationTour@@@@@@I@Z=00730370
// @ref ??C?$rc_ptr@VTerritory@WorldDominationTour@@@@QBEPAVTerritory@WorldDominationTour@@XZ=00730320
// @ref ?Take_unknown_2c@Territory@WorldDominationTour@@QAEHXZ=007311a0
// @ref ?Remove_Anim@MSEngine@@QAEXPAVMSAnim@@@Z=005b2ec0
// @ref ??1Voices@WorldDominationTour@@QAE@XZ=00731680
// @ref ??1MSSfxEntry@@QAE@XZ=005b16c0
// @ref ?Clear@?$VectorClass@PAVMSSfxEntry@@@@UAEXXZ=005b2690
// @ref ??_7?$VectorClass@PAVMSSfxEntry@@@@6B@=007a6f48
// @ref ??_7Selection@WorldDominationTour@@6B@=007af36c
// @ref ??_7?$rc_ptr@VCampaign@WorldDominationTour@@@@6B@=007aefdc
// @ref ??_7?$rc_ptr@VMap@WorldDominationTour@@@@6B@=007af1e4
// @ref ?Queue_Song@ThemeClass@@QAEXH@Z=006e7e20
// @ref ?Theme@@3VThemeClass@@A=00a35d78
// @ref ?unknown_surface_839954@@3PAVDSurface@@A=00839954
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8
// @ref ?Set_Color@BitFontClass@@QAEGG@Z=00431430
// @ref ??_ESelection@WorldDominationTour@@UAEPAXI@Z=00730290
// @ref ?Unknown_Slot1@MSEngine@@UAEXPAVSurface@@@Z=0058fd90
// @ref ?Unknown_Slot2@MSEngine@@UAEXXZ=005b3830
// @ref ??_GSelection@WorldDominationTour@@UAEPAXI@Z=00730290
// @ref ??_E?$rc_ptr@VCampaign@WorldDominationTour@@@@UAEPAXI@Z=00726b40
// @ref ??_G?$rc_ptr@VCampaign@WorldDominationTour@@@@UAEPAXI@Z=00726b40
// @ref ??_E?$rc_ptr@VMap@WorldDominationTour@@@@UAEPAXI@Z=0072b0c0
// @ref ??_G?$rc_ptr@VMap@WorldDominationTour@@@@UAEPAXI@Z=0072b0c0
// @ref ??_E?$VectorClass@PAVMSSfxEntry@@@@UAEPAXI@Z=005b2b20
// @ref ??_G?$VectorClass@PAVMSSfxEntry@@@@UAEPAXI@Z=005b2b20
// @ref ??8?$VectorClass@PAVMSSfxEntry@@@@UBE_NABV0@@Z=005b25a0
// @ref ?Resize@?$VectorClass@PAVMSSfxEntry@@@@UAE_NHPBQAVMSSfxEntry@@@Z=005b25e0
// @ref ?ID@?$VectorClass@PAVMSSfxEntry@@@@UAEHABQAVMSSfxEntry@@@Z=005b26c0
// @ref ?ID@?$VectorClass@PAVMSSfxEntry@@@@UAEHPBQAVMSSfxEntry@@@Z=005b2700
// @ref ?Fetch@?$VectorClass@PAVMSSfxEntry@@@@UBEPAVMSSfxEntry@@H@Z=005b1920
