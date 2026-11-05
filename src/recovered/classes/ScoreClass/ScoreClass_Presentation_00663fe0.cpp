// void ScoreClass::Presentation() (0x00663FE0, Score.CPP): the campaign score screen.
#include "shared/score.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/dsurface.hpp"
#include "shared/convert.hpp"
#include "shared/hicolor.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/id_source.hpp"
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"
#include "shared/ms_engine.hpp"
#include "shared/palette.hpp"
#include "shared/play_movie.hpp"
#include "shared/rgb_class.hpp"
#include "shared/sound_available.hpp"
#include "shared/string_table.hpp"
#include "shared/theme.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"

void *__fastcall Load_Alloc_Data(class FileClass &file);
void __fastcall Load_Title_Screen_00738190(char const *name, Surface *surface, PaletteClass *palette);
void unknown_481fb0();

extern "C" char *__cdecl _strdup(char const *text);
inline ScoreSoundClass::ScoreSoundClass(char const *name, char const *filename) :
    Name(0), unknown_04(0), unknown_08(false)
{
    if (unknown_check_406f30()) {
        Name = _strdup(name);
    }
}

inline ScoreSoundClass::~ScoreSoundClass()
{
    if (Name) {
        free(Name);
    }
}

// The file classes' open by name: names the file, then opens it (virtual calls).
static inline int Open_Named(FileClass &file, char const *name, int rights = FILE_RIGHTS_READ)
{
    file.Set_Name(name);
    return file.Open(rights);
}

// The string table entry for a label, typed as the score fonts take it.
static inline unsigned short const *Fetch_Text(char const *label, char const *file, int line)
{
    return (unsigned short const *)StringTable::Load_String(label, 0, file, line);
}
#define FETCH(label, line) Fetch_Text(label, "D:\\Ra2\\Score.CPP", line)

struct Fame {
    char name[0x68];
    int score;
    int level;
    int side;
};

#define PRINT(string, xp, yp, font) \
    Add_Anim(obj = new ScorePrintClass(string, xp, yp, font, false))
#define WAIT() Wait_For_Print(obj)

void ScoreClass::Presentation()
{
    int i;
    int index;
    int total;
    int x, y;
    unsigned short const *str;
    ScoreAnimClass *obj;
    CCFileClass file;
    Fame hallfame[9];

    XOffset = (unknown_surface_839954->Get_Width() - 640) / 2;
    YOffset = (unknown_surface_839954->Get_Height() - 400) / 2;
    WWMouse->Hide_Mouse();
    WWKeyboard->Clear();
    Theme.Stop();
    Theme.Play_Song((ThemeType)Theme.From_Name("SCORE"));

    Open_Named(file, "SIDEFNT3.PAL");
    unsigned char *fontpal = (unsigned char *)Load_Alloc_Data(file);
    file.Close();
    for (i = 0; i < 256; i++) {
        unknown_palette_838710[i] = RGBClass(fontpal[i * 3] << 2, fontpal[i * 3 + 1] << 2, fontpal[i * 3 + 2] << 2);
    }
    Color = Build_Hicolor_Pixel(fontpal[204] << 2, fontpal[205] << 2, fontpal[206] << 2);
    delete fontpal;

    ConvertClass *drawer = new ConvertClass(unknown_palette_838710, unknown_palette_838710, unknown_surface_839950, 1, 0);
    SurfacePtr = new DSurface(unknown_surface_839954->Get_Width(), unknown_surface_839954->Get_Height(), false);
    SurfacePtr->Fill(0);
    Load_Title_Screen_00738190("SCORE.PCX", SurfacePtr, &unknown_palette_838710);

#define LOAD(var, name) \
    Open_Named(file, name); \
    ShapeFileStruct const *var = (ShapeFileStruct const *)Load_Alloc_Data(file); \
    file.Close();
    LOAD(best01shape, "BEST01.SHP")
    LOAD(best02shape, "BEST02.SHP")
    unknown_481fb0();
    LOAD(logo01shape, "LOGO01.SHP")
    LOAD(efic01shape, "EFIC01.SHP")
    LOAD(time01shape, "TIME01.SHP")
    LOAD(casu01shape, "CASU01.SHP")
    unknown_481fb0();
    LOAD(casu02shape, "CASU02.SHP")
    LOAD(curr01shape, "CURR01.SHP")

    Sounds.Clear();
    Sounds.Add(new ScoreSoundClass("Wipe", "WIPE.AUD"));
    Sounds.Add(new ScoreSoundClass("Emblem", "EMBLEM.AUD"));
    Sounds.Add(new ScoreSoundClass("BestBox", "BESTBOX.AUD"));
    Sounds.Add(new ScoreSoundClass("Efficiency", "EFFICIEN.AUD"));
    Sounds.Add(new ScoreSoundClass("BarGraph", "BARGRAPH.AUD"));
    Sounds.Add(new ScoreSoundClass("Type", "TYPE.AUD"));
    Sounds.Add(new ScoreSoundClass("Back", "SCOLD8.AUD"));

    Font = new ScoreFullFontClass(drawer);
    unknown_font_10 = new ScoreBigFontClass(drawer);
    unknown_481fb0();
    Anims.Clear();
    WWKeyboard->Clear();
    Play_Sound("Wipe", 256);
    Play_Movie("SCORE.VQA", -1, false, false, true, false);
    unknown_surface_839954->Copy_From(*SurfacePtr, false, true);
    unknown_surface_839958->Copy_From(*SurfacePtr, false, true);

    Drawer = new ConvertClass(unknown_palette_838710, unknown_palette_838710, unknown_surface_839950, 1, 0);
    Add_Anim(new ScoreTimeClass(XOffset + 7, YOffset + 6, logo01shape, 60, 3, Drawer));

    Play_Sound("Efficiency", 128);
#define WIPE(shape, xp, yp) \
    CC_Draw_Shape(unknown_surface_839954, Drawer, shape, i, Point2D(xp, yp), unknown_surface_839954->Get_Rect(), 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0))
    for (i = 0; i < 10; i++) {
        WIPE(efic01shape, XOffset + 480, YOffset + 23);
        ScoreDelay(4);
    }
    Rect rect(XOffset + 480, YOffset + 23, 160, 120);
    SurfacePtr->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    unknown_surface_839958->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    str = FETCH("TXT_MISSION_EFFICIENCY", 506);
    Font->String_Pixel_Width(str);
    x = XOffset - Font->String_Pixel_Width(str) / 2 + 552;
    PRINT(str, x, YOffset + 13, Font);
    WAIT();
    WWKeyboard->Clear();

    total = Efficiency(unknown_player_a35db4);
    unsigned short dest[64];
    swprintf((wchar_t *)dest, L"%3d%%", total);
    PRINT(dest, XOffset + 520, YOffset + 60, unknown_font_10);
    WAIT();

    for (i = 0; i < 10; i++) {
        WIPE(curr01shape, XOffset + 481, YOffset + 148);
        ScoreDelay(4);
    }
    rect.Set(XOffset + 481, YOffset + 148, 144, 86);
    SurfacePtr->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    unknown_surface_839958->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    str = FETCH("TXT_CURRENCY", 543);
    Font->String_Pixel_Width(str);
    x = XOffset - Font->String_Pixel_Width(str) / 2 + 560;
    PRINT(str, x, YOffset + 193, Font);
    WAIT();
    rect.Set(XOffset + 481, YOffset + 148, 150, 120);
    SurfacePtr->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    unknown_surface_839958->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    Show_Credits();

    for (i = 0; i < 10; i++) {
        WIPE(time01shape, XOffset + 444, YOffset + 273);
        ScoreDelay(4);
    }
    rect.Set(XOffset + 444, YOffset + 273, 196, 118);
    SurfacePtr->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    unknown_surface_839958->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    str = FETCH("TXT_MISSION_TIME_LAPSE", 571);
    Font->String_Pixel_Width(str);
    x = XOffset - Font->String_Pixel_Width(str) / 2 + 542;
    PRINT(str, x, YOffset + 366, Font);
    WAIT();
    Print_Time(unknown_id_source_a3d290->ElapsedTime.Time() / 60);

    Play_Sound("Emblem", 256);
    for (i = 0; i < 10; i++) {
        WIPE(casu01shape, XOffset + 186, YOffset + 54);
        WIPE(casu02shape, XOffset + 186, YOffset + 254);
        ScoreDelay(4);
    }
    rect.Set(XOffset + 186, YOffset + 54, 262, 326);
    SurfacePtr->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    unknown_surface_839958->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    str = FETCH("TXT_CASUALTIES", 601);
    Font->String_Pixel_Width(str);
    x = XOffset - Font->String_Pixel_Width(str) / 2 + 316;
    PRINT(str, x, YOffset + 300, Font);
    WAIT();

    str = FETCH("TXT_STRUCTURES", 613);
    x = XOffset + 194;
    PRINT(str, x, YOffset + 247, Font);
    x = XOffset + 328;
    PRINT(str, x, YOffset + 247, Font);
    WAIT();
    str = FETCH("TXT_UNITS", 628);
    x = XOffset - Font->String_Pixel_Width(str) / 2 + 290;
    PRINT(str, x, YOffset + 247, Font);
    x = XOffset - Font->String_Pixel_Width(str) / 2 + 422;
    PRINT(str, x, YOffset + 247, Font);
    WAIT();
    Do_Graphs();
    while (unknown_score_print_ab6f9c) {
        ScoreDelay(1);
    }
    WWKeyboard->Clear();

    Play_Sound("BestBox", 256);
    for (i = 0; i < 10; i++) {
        WIPE(best01shape, XOffset, YOffset + 188);
        WIPE(best02shape, XOffset, YOffset + 388);
        ScoreDelay(4);
    }
    rect.Set(XOffset, YOffset + 188, 182, 212);
    SurfacePtr->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    unknown_surface_839958->Copy_From(rect, *unknown_surface_839954, rect, false, true);
    str = FETCH("TXT_BEST_SCORES", 669);
    Font->String_Pixel_Width(str);
    x = XOffset - Font->String_Pixel_Width(str) / 2 + 84;
    PRINT(str, x, YOffset + 217, Font);

    memset(hallfame, 0, sizeof(hallfame));
    file.Close();
    file.Set_Name("HALLFAME.DAT");
    if (file.Is_Available() == true) {
        file.Read(hallfame, sizeof(hallfame));
        file.Close();
    }
    if (hallfame[8].score >= total) {
        hallfame[8].score = 0;
    }
    for (index = 0; index < 9; index++) {
        // Tests i, not index (as in the original): i is still 10 from the box wipe above.
        if (total > hallfame[i].score) {
            if (index < 8) {
                for (i = 8; i > index; i--) {
                    hallfame[i] = hallfame[i - 1];
                }
            }
            hallfame[index].name[0] = 0;
            hallfame[index].score = total;
            hallfame[index].level = unknown_id_source_a3d290->TechLevel;
            hallfame[index].side = unknown_player_a35db4->Type->Side;
            break;
        }
    }
    char maststr[9 * 32];
    for (i = 0; i < 9; i++) {
        PRINT(hallfame[i].name, XOffset + 7, YOffset + 242 + i * 16, Font);
        if (hallfame[i].score) {
            char *scorestr = maststr + i * 32;
            sprintf(scorestr, "%d%%", hallfame[i].score);
            PRINT(scorestr, XOffset + 109, YOffset + 242 + i * 16, Font);
            char *levelstr = scorestr + 16;
            sprintf(levelstr, "%02d", hallfame[i].level);
            PRINT(levelstr, XOffset + 151, YOffset + 242 + i * 16, Font);
            WAIT();
        }
        ScoreDelay(1);
    }
    while (unknown_score_print_ab6f9c) {
        ScoreDelay(1);
    }
    WWKeyboard->Clear();
    WWMouse->Show_Mouse();
    if (index < 9) {
        Input_Name(hallfame[index].name, XOffset + 7, YOffset + 242 + index * 16);
    } else {
        unsigned short const *str = FETCH("TXT_CLICK_CONTINUE", 749);
        x = XOffset + (640 - Font->String_Pixel_Width(str)) / 2;
        y = YOffset - Font->Height / 2 + 357;
        PRINT(str, x, y, Font);
        Cycle_Wait_Click(true);
    }
    WWKeyboard->Clear();
    if (Open_Named(file, "HALLFAME.DAT", FILE_RIGHTS_WRITE)) {
        file.Write(hallfame, sizeof(hallfame));
        file.Close();
    }
    Theme.Stop(true);

    for (i = 0; i < Sounds.Count(); i++) {
        if (Sounds[i]) {
            delete Sounds[i];
        }
    }
    Sounds.Clear();
    for (i = 0; i < Anims.Count(); i++) {
        if (Anims[i]) {
            delete Anims[i];
        }
    }
    Anims.Clear();
    if (Drawer != 0) {
        delete Drawer;
        Drawer = 0;
    }
    if (Font != 0) {
        delete Font;
        Font = 0;
    }
    if (unknown_font_10 != 0) {
        delete unknown_font_10;
        unknown_font_10 = 0;
    }
    if (SurfacePtr != 0) {
        delete SurfacePtr;
        SurfacePtr = 0;
    }
    delete drawer;
    unknown_surface_839954->Fill(0);
    Blit_Score();
    Theme.Queue_Song((ThemeType)-1);
}
// @ref ??_C@_04BMHD@Wipe?$AA@=007f28b4
// @ref ??_C@_04FOAE@?$CFd?$CF?$CF?$AA@=007f27c4
// @ref ??_C@_06LMBK@Emblem?$AA@=007f28ac
// @ref ??_C@_07LGJN@BestBox?$AA@=007f28a4
// @ref ??_C@_09DJKJ@SCORE?4PCX?$AA@=007f291c
// @ref ??_C@_09FCHB@TXT_UNITS?$AA@=007f27ec
// @ref ??_C@_09MFHN@SCORE?4VQA?$AA@=007f2878
// @ref ??0?$CDTimerClass@VSystemTimerClass@@@@QAE@J@Z=004de1e0
// @ref ??_C@_0BA@DDND@TXT_BEST_SCORES?$AA@=007f27dc
// @ref ??_C@_0BB@CDGD@D?3?2Ra2?2Score?4CPP?$AA@=007f2864
// @ref ??_C@_0BD@KMAM@TXT_CLICK_CONTINUE?$AA@=007f27b0
// @ref ??_C@_0BH@CDOJ@TXT_MISSION_TIME_LAPSE?$AA@=007f2818
// @ref ??_C@_0BH@COKE@TXT_MISSION_EFFICIENCY?$AA@=007f284c
// @ref ??_C@_0L@DEAL@TIME01?4SHP?$AA@=007f28e0
// @ref ??_C@_0L@EDGF@CURR01?4SHP?$AA@=007f28bc
// @ref ??_C@_0L@EHHG@BEST01?4SHP?$AA@=007f2910
// @ref ??_C@_0L@FKJI@Efficiency?$AA@=007f2898
// @ref ??_C@_0L@KHBJ@BEST02?4SHP?$AA@=007f2904
// @ref ??_C@_0L@MDCC@LOGO01?4SHP?$AA@=007f28f8
// @ref ??_C@_0L@NNJD@EFIC01?4SHP?$AA@=007f28ec
// @ref ??_C@_0L@OPAB@CASU01?4SHP?$AA@=007f28d4
// @ref ??_C@_0L@PGO@CASU02?4SHP?$AA@=007f28c8
// @ref ??_C@_0N@LDEJ@TXT_CURRENCY?$AA@=007f2830
// @ref ??_C@_0N@PDDF@HALLFAME?4DAT?$AA@=007f27cc
// @ref ??_C@_0P@IFON@TXT_CASUALTIES?$AA@=007f2808
// @ref ??_C@_0P@JEIE@TXT_STRUCTURES?$AA@=007f27f8
// @ref ??_C@_1M@ILBO@?$AA?$CF?$AA3?$AAd?$AA?$CF?$AA?$CF?$AA?$AA@=007f2840
// @ref ??_C@_04LGDF@?$CF02d?$AA@=007deda8
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_05DDDB@SCORE?$AA@=007e5648
// @ref ??_C@_0N@IKPJ@SIDEFNT3?4PAL?$AA@=007e5d98
