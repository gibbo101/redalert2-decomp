// long __fastcall VQA_Configure_Buffer(VQAHandleP *vqap) -- 0x007776B0
// Purpose: chooses the image size (the configured one, else the movie's
// plus its offset with DrawFlags bit 3), allocates and clears a private
// image buffer when buffering is on and none was given, then installs the
// buffer with VQA_Set_DrawBuffer. -9 without a buffer, -8 when out of memory.
#include "shared/vqa_player.hpp"
#include "shared/crt_memory.hpp"
// @ref ?VQA_Unknown_0077C480@@YIHPAUVQAHandle@@HHHHH@Z=0077c480

long __fastcall VQA_Configure_Buffer(VQAHandleP *vqap)
{
    unsigned char *buffer;
    int width;
    int height;
    VQAConfig *config = &vqap->Config;
    VQAHeader *header = &vqap->Header;

    if (config->ImageWidth == -1 || config->ImageHeight == -1) {
        width = header->ImageWidth;
        height = header->ImageHeight;
        if (config->DrawFlags & 8) {
            width += header->Xpos;
            height += header->Ypos;
        }
    } else {
        width = config->ImageWidth;
        height = config->ImageHeight;
    }
    if (config->DrawFlags & 1) {
        if (config->ImageBuf == 0) {
            int size = width * height;
            if (header->ColorMode == 1 || header->ColorMode == 4) {
                size *= 2;
            }
            buffer = (unsigned char *)config->MemoryHandler((VQAHandle *)vqap, VQAMEM_ALLOC, 0, size);
            if (buffer == 0) {
                return -8;
            }
            vqap->MemUsed += size;
            config->MemoryHandler((VQAHandle *)vqap, VQAMEM_LOCK, (int)buffer, size);
            memset(buffer, 0, size);
            vqap->AltImageBuf = buffer;
            vqap->AltImageWidth = width;
            vqap->AltImageHeight = height;
            vqap->Flags |= 0x20;
        } else {
            buffer = (unsigned char *)config->ImageBuf;
        }
    } else {
        if (config->ImageBuf != 0) {
            buffer = (unsigned char *)config->ImageBuf;
        } else {
            return -9;
        }
    }
    VQA_Unknown_0077C480((VQAHandle *)vqap, (int)buffer, width, height, config->X1, config->Y1);
    vqap->Flags |= 0x10;
    return -1;
}
