// bool MSBinkAnim::Unknown_Slot7() (0x005ADA00, slot 7): no movie, or it finished.
#include "shared/ms_anim.hpp"
// @ref ?Unknown_00430420@BinkClass@@QAE_NXZ=00430420

bool MSBinkAnim::Unknown_Slot7()
{
    return Movie == 0 || Movie->Unknown_00430420();
}
