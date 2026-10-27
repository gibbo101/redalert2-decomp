// bool VQAClass::Unknown_0071CC90() (0x0071CC90): seeks back to the saved frame.
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077C2E0@@YIHPAUVQAHandle@@HH@Z=0077c2e0

bool VQAClass::Unknown_0071CC90()
{
    if (Opened) {
        if (VQA_Unknown_0077C2E0(Handle, unknown_544, 0) != -6) {
            CurrentFrame = unknown_544;
        } else {
            return false;
        }
    }
    return true;
}
