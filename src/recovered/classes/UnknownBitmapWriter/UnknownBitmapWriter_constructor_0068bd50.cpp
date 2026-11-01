// UnknownBitmapWriter::UnknownBitmapWriter() (0x0068BD50): an empty image dictionary hashed by name.
#include "shared/pcx_cache.hpp"
// @ref ?Hash_Image_Name_0068bde0@@YIIABVWstring@@@Z=0068bde0

static unsigned int __fastcall Hash_Image_Name_0068bde0(Wstring const &name);

UnknownBitmapWriter::UnknownBitmapWriter() : Images(Hash_Image_Name_0068bde0)
{
}
