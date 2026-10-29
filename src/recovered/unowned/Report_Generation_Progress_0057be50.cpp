// Original entry0057BE50: incoming ECX unused, one signed32 argument, RET4.
// Operation/free-stdcall/void intent hypotheses; no caller/runtime root established.
#include "shared/id_source.hpp"
#include "shared/session_state.hpp"
#include "shared/progress_screen.hpp"

void __stdcall Report_Generation_Progress_0057be50(int progress)
{
    if (unknown_id_source_a3d290->unknown_22fc) {
        unknown_session_a3d298.Loading_Progress_00672160((int)((unsigned int)progress + 99u));
    } else {
        ProgressScreen.Set_Progress_006201c0(0, (double)progress, Point2D(-1, -1));
    }
}
