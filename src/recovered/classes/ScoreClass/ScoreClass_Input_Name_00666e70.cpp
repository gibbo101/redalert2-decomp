// void ScoreClass::Input_Name(char *name, int x, int y) (0x00666E70)
// Reads the player's name from the keyboard: typed characters are drawn by
// a ScorePrintClass, backspace restores the background, return ends it.
#include "shared/score.hpp"
#include "shared/keyboard.hpp"
#include "shared/ms_engine.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?Check@WWKeyboardClass@@QAEGXZ=005322d0
// @ref ?Get@WWKeyboardClass@@QAEGXZ=00532320
// @ref ?To_Char@WWKeyboardClass@@QAEDG@Z=00532800
// @ref ?unknown_481fb0@@YAXXZ=00481fb0
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?Draw_Cursor@ScoreClass@@QAEXHH@Z=006672a0
// @ref ?ScoreDelay@ScoreClass@@QAEXH@Z=00667420
// @ref ??_C@_04JDGB@Back?$AA@=007f2884
// @ref ??_C@_04FCOP@Type?$AA@=007d9eec

void ScoreClass::Input_Name(char *name, int x, int y)
{
    int key = 0;
    int index = 0;
    int xpos = x;
    do {
        Wait_While_Inactive();
        if (WWKeyboard->Check()) {
            key = WWKeyboard->To_Char(WWKeyboard->Get()) & 0xFF;
            unknown_481fb0();
            if (xpos >= x + 90) {
                while (WWKeyboard->Check()) {
                    WWKeyboard->Get();
                }
            }
            if (key == 8 && xpos >= x + 84) {
                if (name[index] && name[index] != ' ') {
                    Rect rect(xpos, y + 1, Font->Char_Pixel_Width(name[index]) + 1, 16);
                    unknown_surface_839954->Copy_From(rect, *(Surface *)SurfacePtr, rect, false, true);
                    unknown_surface_839958->Copy_From(rect, *(Surface *)SurfacePtr, rect, false, true);
                    key = ' ';
                }
            }
            if (key == 8) {
                if (index) {
                    char letter = name[--index];
                    int width = Font->Char_Pixel_Width(letter) + 1;
                    xpos -= width;
                    Rect rect(xpos, y + 1, width, 16);
                    unknown_surface_839954->Copy_From(rect, *(Surface *)SurfacePtr, rect, false, true);
                    unknown_surface_839958->Copy_From(rect, *(Surface *)SurfacePtr, rect, false, true);
                    name[index] = 0;
                    Play_Sound("Back", 192);
                }
            } else if (key != 13 && key >= ' ') {
                int width = Font->Char_Pixel_Width(key) + 1;
                if (xpos + Font->Width <= x + 90) {
                    if (xpos + width >= x + 84) {
                        Rect rect(xpos, y + 1, Font->Char_Pixel_Width(name[index]) + 1, 16);
                        unknown_surface_839954->Copy_From(rect, *(Surface *)SurfacePtr, rect, false, true);
                        unknown_surface_839958->Copy_From(rect, *(Surface *)SurfacePtr, rect, false, true);
                    }
                    name[index] = key;
                    name[index + 1] = 0;
                    ScorePrintClass *anim = new ScorePrintClass(&name[index], xpos, y, Font, false);
                    Anims.Add(anim);
                    Play_Sound("Type", 128);
                    if (xpos < x + 87) {
                        index++;
                        xpos += Font->Char_Pixel_Width(key) + 1;
                    }
                }
            }
        }
        Draw_Cursor(xpos, y);
        ScoreDelay(1);
    } while (key != 13);
}
