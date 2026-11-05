// void ScoreClass::Show_Credits() (0x00666B60)
// Types the player's money, right-aligned at 590 (12 pixels a digit).
#include "shared/score.hpp"
// @ref ?ScoreDelay@ScoreClass@@QAEXH@Z=00667420
#include "shared/house.hpp"
#include "shared/crt_string.hpp"

void ScoreClass::Show_Credits()
{
    char buffer[20];
    sprintf(buffer, "%d", unknown_player_a35db4->Available_Money());
    int x = 590 - strlen(buffer) * 12;
    ScorePrintClass *anim = new ScorePrintClass(buffer, XOffset + x, YOffset + 214, Font, false);
    Anims.Add(anim);
    while (!Is_Anim_Done(anim)) {
        ScoreDelay(1);
    }
}
