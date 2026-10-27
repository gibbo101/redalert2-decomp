// FilePipe::End (0x007737C0, virtual slot 2)
// Flushes the chain, then closes the file if this pipe opened it.
#include "shared/file_pipe.hpp"

int FilePipe::End()
{
    int total = Pipe::End();
    if (Valid_File() && HasOpened) {
        HasOpened = false;
        File->Close();
    }
    return total;
}
