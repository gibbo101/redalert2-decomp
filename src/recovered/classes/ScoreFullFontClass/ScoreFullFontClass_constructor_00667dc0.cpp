// ScoreFullFontClass::ScoreFullFontClass(ConvertClass *drawer) (0x00667DC0)
// The FULLFNT3.SHP sheet: from the mixfiles, or else from a loose file (then owned).
#include "shared/score_font.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/palette.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_7ScoreFontClass@@6B@=007a92a0
// @ref ??_7ScoreFullFontClass@@6B@=007a92b8
// @ref ?unknown_score_fonts_ab6fa4@@3HA=00ab6fa4
// @ref ?Load_Sounds@ScoreFontClass@@QAEXXZ=00667900
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
// @ref ?Close@CCFileClass@@UAEXXZ=004691f0
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??1CDFileClass@@UAE@XZ=00438410
// @ref ??1RawFileClass@@UAE@XZ=0042f350
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7RawFileClass@@6B@=0079a658
// @ref ??_C@_0N@HEOG@FULLFNT3?4SHP?$AA@=007e5dcc
// @ref ??_C@_0CC@BKPB@ScoreScreen?3?5Loaded?5FULLFNT3?4SHP@=007f2b14

ScoreFullFontClass::ScoreFullFontClass(ConvertClass *drawer)
{
    IsAllocated = false;
    Image = (ShapeFileStruct const *)MixFileClass::Retrieve("FULLFNT3.SHP");
    if (!Image) {
        CCFileClass file("FULLFNT3.SHP");
        Image = (ShapeFileStruct const *)Load_Alloc_Data(file);
        IsAllocated = true;
        file.Close();
        Debug_Printf("ScoreScreen: Loaded FULLFNT3.SHP\n");
    }
    Width = 11;
    Drawer = drawer;
    Height = 21;
}
