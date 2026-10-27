// bool AnimFile::Initialize() (0x00424110)
// Reads the animation file's header, color map (stored as 4-byte entries
// in blue, green, red order) and large page table, rejects a file Validate
// does not accept (the player closes itself), and allocates the frame
// surface and the page buffer. Returns whether the player is loaded.
#include "shared/anim_file.hpp"
#include "shared/crt_memory.hpp"
// @ref ??2@YAPAXI@Z=00782017

bool AnimFile::Initialize()
{
    if (!Loaded && File != 0) {
        Loaded = true;
        memset(&Header, 0, sizeof(Header));
        File->Read(&Header, sizeof(Header));
        memset(Buffer, 0, sizeof(Buffer));
        File->Read(Buffer, sizeof(Buffer));
        File->Seek(0, FILE_SEEK_CURRENT);
        File->Read(ColorMap, sizeof(ColorMap));
        for (int index = 0; index < 256; index++) {
            Palette[index % 256] = RGBClass(ColorMap[index * 4 + 2], ColorMap[index * 4 + 1], ColorMap[index * 4]);
        }
        memset(Pages, 0, sizeof(Pages));
        File->Read(Pages, sizeof(Pages));
        if (!Validate()) {
            Close();
            return false;
        }
        Frame = new BSurface(Header.Width, Header.Height, 1);
        PageData = (unsigned char *)operator new(0x10000);
        memset(PageData, 0, 0x10000);
    }
    return Loaded;
}
