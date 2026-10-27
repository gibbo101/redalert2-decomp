// int AnimFile::Find_Page(int frame) const (0x004247A0)
// The large page holding a frame; -1 when there is none.
#include "shared/anim_file.hpp"

int AnimFile::Find_Page(int frame) const
{
    if (frame < Header.FrameCount) {
        for (int page = 0; page < Header.PageCount; page++) {
            if (Pages[page].FirstRecord <= frame && Pages[page].RecordCount + Pages[page].FirstRecord > frame) {
                return page;
            }
        }
    }
    return -1;
}
