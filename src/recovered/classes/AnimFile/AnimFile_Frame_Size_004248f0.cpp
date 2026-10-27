// int AnimFile::Frame_Size(int frame) (0x004248F0)
// The size of a frame's record data (its size table entry less the
// 2-byte header); 0 when the frame is not in the file.
#include "shared/anim_file.hpp"

int AnimFile::Frame_Size(int frame)
{
    unsigned size = 0;
    int page = Find_Page(frame);
    if (page != -1) {
        Load_Page(page);
        unsigned short *sizes = (unsigned short *)(PageData + 8);
        frame -= Pages[page].FirstRecord;
        if (frame >= 0) {
            int remaining = frame + 1;
            do {
                size = *sizes++;
                if (size >= 2) {
                    size -= 2;
                }
                remaining--;
            } while (remaining != 0);
        }
    }
    return size;
}
