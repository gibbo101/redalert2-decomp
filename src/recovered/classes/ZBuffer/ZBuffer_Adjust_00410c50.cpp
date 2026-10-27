// Scroll the ring by dx columns and dy rows (the view moved): move the ring
// origin and clear the newly exposed columns and rows to value. A move
// larger than the buffer clears all of it and resets MaxValue.
#include "shared/blit.hpp"
void ZBuffer::Adjust(int dx, int dy, unsigned short value)
{
    int x = (BufferOffset / 2) % Width;
    if (abs(dx) > Width || abs(dy) > Height) {
        Clear(value);
        MaxValue = 0x8000;
        return;
    }
    int right = x + dx;
    if (dx) {
        BufferOffset += dx * 2;
        char *pointer = BufferHead + BufferOffset;
        if (pointer < BufferHead) pointer += BufferSize;
        pointer = (char *)Wrap_Pointer((unsigned short *)pointer);
        BufferOffset = pointer - BufferHead;
        if (dx < 0) {
            if (right < 0) {
                Clear_Region_00411090(value, Rect(0, 0, x, Height));
                right += Width;
                Clear_Region_00411090(value, Rect(right, 0, Width - right, Height));
            } else {
                Clear_Region_00411090(value, Rect(right, 0, -dx, Height));
            }
        } else {
            if (right >= Width) {
                Clear_Region_00411090(value, Rect(x, 0, Width - x, Height));
                right -= Width;
                Clear_Region_00411090(value, Rect(0, 0, right, Height));
            } else {
                Clear_Region_00411090(value, Rect(x, 0, dx, Height));
            }
        }
    }
    if (dy) {
        int row = (BufferOffset / 2) / Width;
        int old_offset = BufferOffset;
        MaxValue -= dy;
        BufferOffset += Width * dy * 2;
        row += dy;
        char *pointer = BufferHead + BufferOffset;
        if (pointer < BufferHead) pointer += BufferSize;
        pointer = (char *)Wrap_Pointer((unsigned short *)pointer);
        BufferOffset = pointer - BufferHead;
        if (dy < 0) {
            if (row < 0) {
                Fill_Words((unsigned short *)BufferHead, old_offset / 2, value);
                Fill_Words((unsigned short *)(BufferHead + BufferOffset), (Height * Width * 2 - BufferOffset) / 2, value);
            } else {
                Fill_Words((unsigned short *)(BufferHead + BufferOffset), (old_offset - BufferOffset) / 2, value);
            }
        } else {
            if (row >= Height) {
                Fill_Words((unsigned short *)(BufferHead + old_offset), (Height * Width * 2 - old_offset) / 2, value);
                Fill_Words((unsigned short *)BufferHead, BufferOffset / 2, value);
            } else {
                Fill_Words((unsigned short *)(BufferHead + old_offset), (BufferOffset - old_offset) / 2, value);
            }
        }
    }
}
