// MapStage::~MapStage() (0x005B11B0)
// Deletes the stage's text lines and selections.
#include "shared/ms_choice.hpp"
// @ref ??_7?$VectorClass@UPoint2D@@@@6B@=007a6fc8
// @ref ??_7?$VectorClass@PAVMSTextEntry@@@@6B@=007a6fe8
// @ref ??_7?$VectorClass@PAVMapSelection@@@@6B@=007a7008
// @ref ??1WideString@@QAE@XZ=0076fa50

MapStage::~MapStage()
{
    int index;
    for (index = 0; index < Texts.Count(); index++) {
        if (Texts[index] != 0) {
            delete Texts[index];
        }
    }
    for (index = 0; index < Selections.Count(); index++) {
        if (Selections[index] != 0) {
            delete Selections[index];
        }
    }
}
