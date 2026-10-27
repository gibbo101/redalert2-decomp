#include "shared/video_mode_size.hpp"
int __cdecl Compare_Video_Mode_Size_00496260(void const *left,void const *right)
{
    VideoModeSize a=*(VideoModeSize const *)left;
    VideoModeSize b=*(VideoModeSize const *)right;
    if (b.Width>a.Width) return -1;
    if (b.Width<a.Width) return 1;
    if (a.Height<b.Height) return -1;
    return b.Height<a.Height;
}
