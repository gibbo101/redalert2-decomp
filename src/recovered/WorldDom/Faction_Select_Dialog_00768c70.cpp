// int __fastcall Faction_Select_Dialog_00768c70() -- 0x00768C70
// Runs the World Domination faction choice dialog 0x125 with a FactionSelectDialogControl (whose inline
// constructor loads the three small faction images; out of line at 0x00769790) and returns its selection.
#include "shared/wdt_faction_select.hpp"
#include "shared/surface.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ms_anim.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Run_Control_Dialog_006011a0@@YIHHP6GHPAUHWND__@@IIJ@ZPAVDialogControl@OwnerDraw@@@Z=006011a0
// @ref ??_C@_0N@HOGN@WDTFSBSm?4pcx?$AA@=0080058c
// @ref ??_C@_0N@LJNH@WDTFSAsm?4pcx?$AA@=0080057c
// @ref ??_C@_0N@NKG@WDTFSSsm?4pcx?$AA@=0080056c

int __fastcall Run_Control_Dialog_006011a0(int id, DLGPROC procedure, OwnerDraw::DialogControl *control);

namespace WorldDominationTour {

// Loads one image file into image (the constructor skips images already set).
static void Load_Image(Surface *&image, char const *filename)
{
    CCFileClass file(filename);
    image = unknown_load_pcx_60d110(&file, 0, 0, 0);
}

inline FactionSelectDialogControl::FactionSelectDialogControl() :
    Selection(0),
    NoneImage(0),
    AlliedImage(0),
    SovietImage(0)
{
    if (NoneImage == 0) {
        Load_Image(NoneImage, "WDTFSBSm.pcx");
    }
    if (AlliedImage == 0) {
        Load_Image(AlliedImage, "WDTFSAsm.pcx");
    }
    if (SovietImage == 0) {
        Load_Image(SovietImage, "WDTFSSsm.pcx");
    }
    Current = NoneImage;
}

}

using namespace WorldDominationTour;

int __stdcall Faction_Select_Dialog_Proc_007689c0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

int __fastcall Faction_Select_Dialog_00768c70()
{
    unknown_5159b0(0, true);
    FactionSelectDialogControl control;
    Run_Control_Dialog_006011a0(0x125, Faction_Select_Dialog_Proc_007689c0, &control);
    return control.Selection;
}
