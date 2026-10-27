// void AnimFile::Close() (0x004240B0)
#include "shared/anim_file.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void AnimFile::Close()
{
    if (OpenedFile) {
        File->Close();
        OpenedFile = false;
    }
    File = 0;
    if (Frame != 0) {
        delete Frame;
        Frame = 0;
    }
    if (PageData != 0) {
        delete PageData;
        PageData = 0;
    }
    Loaded = false;
}
