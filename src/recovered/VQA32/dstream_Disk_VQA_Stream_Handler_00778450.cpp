// int __cdecl Disk_VQA_Stream_Handler(VQAHandle *vqa, int action, int buffer, int nbytes) -- 0x00778450
// Purpose: the default stream handler: serves the player's VQACMD_* requests
// from the file handle kept in Config.StreamFileHandle with the CRT's
// low-level file calls. Nonzero means the request failed.
#include "shared/vqa_player.hpp"
#include "shared/crt_io.hpp"
// @ref __open=0078d841
// @ref __read=00788a6f
// @ref __lseek=0078fd48
// @ref __filelength=00797198
// @ref __close=0078ad04

int __cdecl Disk_VQA_Stream_Handler(VQAHandle *vqa, int action, int buffer, int nbytes)
{
    int fh;
    int error = 0;
    int temp;

    fh = ((VQAHandleP *)vqa)->Config.StreamFileHandle;

    switch (action) {
    case VQACMD_OPEN:
        error = _open((char *)buffer, _O_RDONLY | _O_BINARY);
        if (error != -1) {
            ((VQAHandleP *)vqa)->Config.StreamFileHandle = error;
            error = 0;
        }
        break;

    case VQACMD_READ:
        error = (_read(fh, (void *)buffer, nbytes) != nbytes);
        break;

    case VQACMD_WRITE:
        error = 1;
        break;

    case VQACMD_SEEK:
        error = (_lseek(fh, nbytes, buffer) == -1);
        break;

    case VQACMD_SEEKPEEK:
        if (nbytes > 0) {
            error = _lseek(fh, nbytes - 1, buffer) == -1;
            if (error == 0) {
                error = _read(fh, &temp, 1) != 1;
            }
        } else {
            error = _lseek(fh, nbytes, buffer) == -1;
            if (error == 0) {
                error = _read(fh, &temp, 1) != 1;
            }
            if (error == 0) {
                error = _lseek(fh, -1, 1) == -1;
            }
        }
        break;

    case VQACMD_SIZE:
        *((unsigned int *)buffer) = _filelength(fh);
        error = 0;
        break;

    case VQACMD_CLOSE:
        _close(fh);
        error = 0;
        break;

    case VQACMD_INIT:
        error = 0;
        break;

    case VQACMD_CLEANUP:
        error = 0;
        break;
    }

    return error;
}
