// bool UnknownBitmapWriter::Draw_0068ce80(Rect const &, Surface *, Surface *, int) (0x0068CE80):
// copies image into rect of destination, skipping the transparent pixel.
#include "shared/pcx_cache.hpp"
#include "shared/surface.hpp"

bool UnknownBitmapWriter::Draw_0068ce80(Rect const &rect, Surface *destination, Surface *image, int transparent)
{
    unsigned short *target = (unsigned short *)destination->Lock();
    if (target == 0) {
        return false;
    }
    unsigned short *source = (unsigned short *)image->Lock();
    if (source == 0) {
        destination->Unlock();
        return false;
    }
    Rect area = rect;
    area.Width = image->Get_Width();
    area.Height = image->Get_Height();
    int pitch = destination->Stride() / 2;
    int index = 0;
    for (int y = 0; y < area.Height; y++) {
        int offset = (y + area.Y) * pitch + area.X;
        for (int x = 0; x < area.Width; x++) {
            unsigned short value = source[index];
            if (value != (unsigned short)transparent) {
                target[offset + x] = value;
            }
            index++;
        }
    }
    destination->Unlock();
    image->Unlock();
    return true;
}
