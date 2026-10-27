// RawFileClass::Bias (0x00639360)
// Restricts all positioning and sizes to a window of the disk file. The new
// start is relative to the current window; the length is clamped to the
// file size and to zero. An open file is repositioned to the window start.
#include "shared/raw_file_class.hpp"

void RawFileClass::Bias(int start, int length)
{
    if (start == 0) {
        BiasStart = 0;
        BiasLength = -1;
        return;
    }
    BiasLength = RawFileClass::Size();
    BiasStart += start;
    if (length != -1) {
        BiasLength = (BiasLength < length) ? BiasLength : length;
    }
    BiasLength = (BiasLength <= 0) ? 0 : BiasLength;
    if (Is_Open()) {
        RawFileClass::Seek(0, FILE_SEEK_START);
    }
}
