// void *AnimFile::Frame_Data(int frame) (0x004247F0)
// The compressed data of a frame inside its large page (loaded first): past
// the page header and size table, after the sizes of the earlier records.
#include "shared/anim_file.hpp"

void *AnimFile::Frame_Data(int frame)
{
    int page = Find_Page(frame);
    if (page != -1) {
        Load_Page(page);
        int first = Pages[page].FirstRecord;
        int offset = Pages[page].RecordCount * 2 + 8;
        unsigned short *sizes = (unsigned short *)(PageData + 8);
        frame -= first;
        while (frame > 0) {
            offset += *sizes++;
            frame--;
        }
        return PageData + offset + 2;
    }
    return 0;
}
