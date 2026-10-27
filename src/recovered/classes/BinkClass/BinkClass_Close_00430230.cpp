// void BinkClass::Close() (0x00430230)
// Frees the companion, closes the movie and the file handle.
#include "shared/movie.hpp"

void BinkClass::Close()
{
    if (Companion != 0) {
        delete Companion;
        Companion = 0;
    }
    if (Handle != 0) {
        BinkClose(Handle);
        Handle = 0;
    }
    if (File != INVALID_HANDLE_VALUE) {
        CloseHandle(File);
        File = INVALID_HANDLE_VALUE;
    }
}
