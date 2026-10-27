// bool AnimFile::Validate() (0x004242B0)
// Whether the header describes a supported animation: "LPF " / "ANIM",
// 256 pages at most, 320x200, a plain bitmap, and every page of at most 256
// records.
#include "shared/anim_file.hpp"

bool AnimFile::Validate()
{
    if (Header.ID == 0x2046504c && Header.ContentType == 0x4d494e41 && Header.MaxPages == 0x100
        && Header.RecordCount <= 0xffff && Header.MaxRecordsPerPage <= 0x100 && Header.TableOffset == 0x500
        && Header.Width == 0x140 && Header.Height == 200 && Header.CompressionType <= 1
        && Header.BitmapType == 1 && Header.OtherRecordsPerFrame == 0 && Header.PixelType == 0) {
        for (int page = 0; page < Header.PageCount; page++) {
            if (Pages[page].RecordCount > 0x100) {
                return false;
            }
        }
        return true;
    }
    return false;
}
