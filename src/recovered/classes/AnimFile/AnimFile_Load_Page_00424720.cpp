// bool AnimFile::Load_Page(int page) (0x00424720)
// Reads a large page into the page buffer unless it is the current one.
#include "shared/anim_file.hpp"

bool AnimFile::Load_Page(int page)
{
    if (Loaded) {
        if (CurrentPage != page) {
            CurrentPage = page;
            File->Seek(page * 0x10000 + 0xb00, FILE_SEEK_START);
            if (File->Read(PageData, Page_Size(page)) != Page_Size(page)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
