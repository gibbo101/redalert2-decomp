#include "shared/cstream.hpp"
#include "shared/lzo.hpp"
// @ref _memmove=00783290
// @ref ?lzo1x_decompress@@YIHPBEIPAEPAIPAX@Z=0053e970
HRESULT __stdcall CStreamClass::Read(void *buffer, unsigned long size, unsigned long *read)
{
    int remaining = size;
    if (!buffer) return E_POINTER;
    if ((long)size < 0) return (HRESULT)0x80070057L;
    if (!Stream) return E_FAIL;
    if (unknown_11) return E_FAIL;
    unknown_10 = true;
    if (read) *read = 0;
    while (remaining > 0) {
        if (unknown_14 > 0) {
            int count = remaining < unknown_14 ? remaining : unknown_14;
            memmove(buffer, (char *)unknown_18 + unknown_28 - unknown_14, count);
            buffer = (char *)buffer + count;
            remaining -= count;
            unknown_14 -= count;
        }
        if (!remaining) break;
        unsigned long received = 0;
        HRESULT result = Stream->Read(&unknown_24, 8, &received);
        if (FAILED(result)) return result;
        if (received != 8) return E_FAIL;
        result = Stream->Read(unknown_1c, unknown_24, &received);
        if (FAILED(result)) return result;
        if (received != unknown_24) return E_FAIL;
        unsigned int decompressed_size = 65536;
        lzo1x_decompress((unsigned char const *)unknown_1c, unknown_24, (unsigned char *)unknown_18, &decompressed_size, 0);
        unknown_14 = unknown_28;
    }
    if (read) *read = size;
    return S_OK;
}
