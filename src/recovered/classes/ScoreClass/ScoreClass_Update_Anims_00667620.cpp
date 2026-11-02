// void ScoreClass::Update_Anims() (0x00667620)
#include "shared/score.hpp"
#include "shared/ms_engine.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"

void ScoreClass::Update_Anims()
{
    unknown_score_print_ab6f9c = false;
    if (unknown_redraw_8523dc) {
        unknown_redraw_8523dc = false;
        unknown_surface_839954->Fill(0);
        unknown_surface_839954->Copy_From(*unknown_surface_839958, false, true);
    }
    for (int index = 0; index < Anims.Count(); index++) {
        if (Anims[index]->Update(SurfacePtr) == true) {
            delete Anims[index];
            Anims.Delete(index);
        }
    }
}
