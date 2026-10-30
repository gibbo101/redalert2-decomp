// Base64Pipe::Flush (0x0042B800): codes the partial group still held, then
// flushes the chain.
#include "shared/base64_pipe.hpp"
#include "shared/base64.hpp"

int Base64Pipe::Flush()
{
    int len = 0;

    if (Counter) {
        if (Control == ENCODE) {
            int chars = Base64_Encode(PBuffer, Counter, CBuffer, sizeof(CBuffer));
            len += Pipe::Put(CBuffer, chars);
        } else {
            int chars = Base64_Decode(CBuffer, Counter, PBuffer, sizeof(PBuffer));
            len += Pipe::Put(PBuffer, chars);
        }
        Counter = 0;
    }
    len += Pipe::Flush();
    return len;
}
