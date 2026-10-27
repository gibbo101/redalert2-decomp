// void MapSelect::Clear() (0x005B0730)
// Deletes the sound effects, animations and stages; resets the text
// rectangle to 640x400.
#include "shared/ms_choice.hpp"
// @ref ??1MapStage@@QAE@XZ=005b11b0

void MapSelect::Clear()
{
    int index;
    for (index = 0; index < Sounds.Count(); index++) {
        if (Sounds[index] != 0) {
            delete Sounds[index];
        }
    }
    Sounds.Clear();
    TextRect.X = 0;
    TextRect.Y = 0;
    TextRect.Width = 640;
    TextRect.Height = 400;
    for (index = 0; index < Anims.Count(); index++) {
        if (Anims[index] != 0) {
            delete Anims[index];
        }
    }
    Anims.Clear();
    for (index = 0; index < Stages.Count(); index++) {
        if (Stages[index] != 0) {
            delete Stages[index];
        }
    }
    Stages.Clear();
}
