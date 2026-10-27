// MSVQAnim::~MSVQAnim() (0x005ADF90)
#include "shared/ms_anim.hpp"
// @ref ?VQA_Movie_Close@@YIXPAVVQAMovie@@@Z=005a1470
// @ref ??1VQAMovie@@QAE@XZ=005a1760

MSVQAnim::~MSVQAnim()
{
    delete Image;
    if (Movie != 0) {
        VQA_Movie_Close(Movie);
        delete Movie;
    }
}
