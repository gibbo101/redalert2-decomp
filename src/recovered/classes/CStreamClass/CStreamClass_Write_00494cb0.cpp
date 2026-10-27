#include "shared/cstream.hpp"
// @ref _memmove=00783290
// @ref ?unknown_flush_495000@CStreamClass@@QAEJPAXH@Z=00495000
HRESULT __stdcall CStreamClass::Write(void const *buffer, unsigned long size, unsigned long *written)
{
    char const *input = (char const *)buffer;
    int remaining = size;
    if (!input) return E_POINTER;
    if ((long)size < 0) return (HRESULT)0x80070057L;
    if (!Stream) return E_FAIL;
    if (unknown_10) return E_FAIL;
    unknown_11 = true;
    if (size != 0) {
        if (written) *written = 0;
        if (unknown_14 > 0) {
            int count = (int)size < 65536 - unknown_14 ? size : 65536 - unknown_14;
            memmove((char *)unknown_18 + unknown_14, input, count);
            int buffered = unknown_14 + count;
            input += count;
            remaining = size - count;
            unknown_14 = buffered;
            if (unknown_14 == 65536) {
                HRESULT result = unknown_flush_495000(unknown_18, 65536);
                if (FAILED(result)) return result;
                unknown_14 = 0;
            }
        }
        for (; remaining >= 65536; remaining -= 65536) {
            HRESULT result = unknown_flush_495000((void *)input, 65536);
            if (FAILED(result)) return result;
            input += 65536;
        }
        if (remaining > 0) {
            memmove(unknown_18, input, remaining);
            unknown_14 = remaining;
        }
        if (written) *written = size;
    }
    return S_OK;
}
