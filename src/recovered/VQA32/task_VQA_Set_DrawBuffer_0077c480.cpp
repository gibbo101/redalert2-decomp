// int __fastcall VQA_Unknown_0077C480(VQAHandle *vqa, int buffer, int width, int height, int xpos, int ypos) -- 0x0077C480
// Purpose: VQA_Set_DrawBuffer (TS): sets the image buffer and its size
// (0 keeps the movie's) and places the movie in it: centered (or at the
// movie's offset with DrawFlags bit 3) without a position, else at the
// position relative to the configured origin corner, halved for half-size
// playback. -24 when the origin falls outside the buffer.
#include "shared/vqa_player.hpp"

int __fastcall VQA_Unknown_0077C480(VQAHandle *vqa, int buffer, int width, int height, int xpos, int ypos)
{
    long origin;
    VQAHeader *header;
    VQADrawer *drawer;
    VQAConfig *config;

    header = &((VQAHandleP *)vqa)->Header;
    drawer = &((VQAHandleP *)vqa)->Drawer;
    config = &((VQAHandleP *)vqa)->Config;

    origin = (config->DrawFlags & VQACFGF_ORIGIN);

    if (width == 0) {
        width = header->ImageWidth;
    }
    if (height == 0) {
        height = header->ImageHeight;
    }

    if (xpos < 0 && ypos < 0) {
        if (config->DrawFlags & VQACFGF_OFFSET) {
            if (config->DrawFlags & VQACFGF_HALFSIZE) {
                drawer->X1 = (header->Xpos / 2);
                drawer->Y1 = (header->Ypos / 2);
            } else {
                drawer->X1 = header->Xpos;
                drawer->Y1 = header->Ypos;
            }
        } else {
            if (config->DrawFlags & VQACFGF_HALFSIZE) {
                drawer->X1 = ((unsigned)width - (header->ImageWidth / 2)) / 2;
                drawer->Y1 = ((unsigned)height - (header->ImageHeight / 2)) / 2;
            } else {
                drawer->X1 = ((unsigned)width - header->ImageWidth) / 2;
                drawer->Y1 = ((unsigned)height - header->ImageHeight) / 2;
            }
        }
    } else {
        if (config->DrawFlags & VQACFGF_HALFSIZE) {
            xpos /= 2;
            ypos /= 2;
        }
        switch (origin) {
        default:
        case VQACFGF_TOPLEFT:
            drawer->X1 = xpos;
            drawer->Y1 = ypos;
            break;

        case VQACFGF_BOTLEFT:
            drawer->X1 = xpos;
            drawer->Y1 = (height - ypos);
            break;

        case VQACFGF_BOTRIGHT:
            drawer->X1 = (width - xpos);
            drawer->Y1 = (height - ypos);
            break;
        }
    }

    if (drawer->X1 >= 0 && drawer->Y1 >= 0 && (unsigned)drawer->X1 < (unsigned)width
        && (unsigned)drawer->Y1 < (unsigned)height) {
        long x = drawer->X1;
        long y = drawer->Y1;
        if (header->ColorMode == 1 || header->ColorMode == 4) {
            x *= 2;
            y *= 2;
        }
        drawer->ImageWidth = width;
        drawer->ImageHeight = height;
        drawer->ScreenOffset = ((width * y) + x);
        if (buffer != 0) {
            drawer->ImageBuf = (unsigned char *)buffer;
            ((VQAHandleP *)vqa)->ImageBuf = (void *)buffer;
        }
        ((VQAHandleP *)vqa)->Flags |= VQADATF_BUFCONFIG;
        return -1;
    }
    return -24;
}
