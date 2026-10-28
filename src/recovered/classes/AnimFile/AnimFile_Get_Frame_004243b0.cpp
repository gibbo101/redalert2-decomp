// void *AnimFile::Get_Frame(int frame) (0x004243B0, slot 3)
// Decodes frames into the frame surface until it shows the wanted one:
// going back restarts from a cleared surface unless the file loops through
// its last delta back to frame 0; past the last record it wraps to 0.
#include "shared/anim_file.hpp"
// @ref ?Decode_Frame@AnimFile@@QAEXPAEH0I@Z=004249f0

void *AnimFile::Get_Frame(int frame)
{
    if (!Loaded) {
        return 0;
    }
    if (CurrentFrame > frame) {
        if (Header.HasLastDelta && Header.LastDeltaValid) {
            if (CurrentFrame != (int)Header.RecordCount || frame != 0) {
                Frame->Fill(0);
                CurrentFrame = -1;
            }
        } else {
            Frame->Fill(0);
            CurrentFrame = -1;
        }
    }
    if (CurrentFrame != frame) {
        void *buffer = Frame->Lock();
        int size = Frame->Get_Height() * Frame->Get_Width() * Frame->Bytes_Per_Pixel();
        while (CurrentFrame != frame) {
            CurrentFrame++;
            void *data = Frame_Data(CurrentFrame);
            if (data != 0) {
                Decode_Frame((unsigned char *)data, Frame_Size(CurrentFrame), (unsigned char *)buffer, size);
            }
            if (CurrentFrame > Header.FrameCount) {
                CurrentFrame = 0;
            }
        }
        Frame->Unlock();
    }
    return Frame;
}
