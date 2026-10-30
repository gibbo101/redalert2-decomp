// bool VQAClass::Unknown_0071CB30() (0x0071CB30)
// Opens the movie file and records its frame count and size.
#include "shared/movie.hpp"
// @ref ?VQA_Unknown_0077B7A0@@YIHPBDPAUVQAConfig@@PAPAUVQAHandle@@@Z=0077b7a0

bool VQAClass::Unknown_0071CB30()
{
    if (VQA_Unknown_0077B7A0(Filename, &Config, &Handle) != -1) {
        Opened = false;
        return false;
    }
    FrameCount = Handle->Frames;
    unknown_504 = Handle->unknown_0C;
    Width = Handle->Width;
    Height = Handle->Height;
    Opened = true;
    return true;
}
