// AnimFile::~AnimFile() (0x00423FF0)
// Closes the player (the file when this object opened it, the frame surface
// and the page buffer).
#include "shared/anim_file.hpp"
// @ref ??_7AnimFile@@6B@=0079c294
// @ref ??_7Animate@@6B@=0079c2b8
// @ref ??3@YAXPAX@Z=00781d3b

AnimFile::~AnimFile()
{
    AnimFile::Close();
}
