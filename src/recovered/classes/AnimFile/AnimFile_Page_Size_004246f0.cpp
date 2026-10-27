// int AnimFile::Page_Size(int page) const (0x004246F0)
// The bytes of a large page: its data, the record size table and the header.
#include "shared/anim_file.hpp"

int AnimFile::Page_Size(int page) const
{
    return Pages[page].ByteCount + Pages[page].RecordCount * 2 + 8;
}
