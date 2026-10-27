// AnimFile::AnimFile() (0x00423F90)
// An empty player: no file, a cleared palette, no frame surface or page
// buffer, no current frame or page.
#include "shared/anim_file.hpp"
// @ref ??_7AnimFile@@6B@=0079c294
// @ref ??_7Animate@@6B@=0079c2b8

AnimFile::AnimFile() :
    File(0),
    Loaded(false),
    OpenedFile(false),
    Frame(0),
    PageData(0),
    CurrentFrame(-1),
    CurrentPage(-1)
{
}
