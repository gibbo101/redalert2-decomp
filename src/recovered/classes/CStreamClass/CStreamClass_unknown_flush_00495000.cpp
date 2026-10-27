#include "shared/cstream.hpp"
#include "shared/lzo.hpp"
// @ref ?lzo1x_1_compress@@YIHPBEIPAEPAIPAX@Z=0053e420
HRESULT CStreamClass::unknown_flush_495000(void *buffer, int size)
{
    unsigned int compressed_size = size;
    lzo1x_1_compress((unsigned char const *)buffer, size, (unsigned char *)unknown_1c, &compressed_size, unknown_20);
    unknown_28 = 65536;
    unknown_24 = compressed_size;
    unsigned long written = 0;
    HRESULT result = Stream->Write(&unknown_24, 8, &written);
    if (FAILED(result)) return result;
    if (written != 8) return E_FAIL;
    result = Stream->Write(unknown_1c, compressed_size, &written);
    if (FAILED(result)) return result;
    return written == compressed_size ? S_OK : E_FAIL;
}
