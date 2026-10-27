// bool FootClass::unknown_slot189() (0x004C8CA0)
#include "shared/foot.hpp"
// @ref ?Unknown_006BA990@TeamClass@@QAE_NXZ=006ba990

bool FootClass::unknown_slot189()
{
    if (!unknown_32d) {
        return false;
    }
    if (unknown_slot32()->IsTrain || unknown_32c || unknown_slot91() == 4 || (Team != 0 && Team->Unknown_006BA990())) {
        return true;
    }
    return false;
}
