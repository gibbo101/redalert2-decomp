// RawFileClass::Seek (0x00638FB0, virtual slot 10)
// Moves the file position. Without a bias window this is a plain Win32 seek.
// With one, positions are relative to the window: a start-relative position
// is clamped to the window length, end-relative seeks become start-relative,
// and a result outside the window is pulled back to its nearest edge.
// Returns the new position relative to the window start.
#include "shared/raw_file_class.hpp"

long RawFileClass::Seek(long position, int origin)
{
    if (BiasLength != -1) {
        switch (origin) {
        case FILE_SEEK_START:
            if (position > BiasLength) {
                position = BiasLength;
            }
            position += BiasStart;
            break;
        case FILE_SEEK_CURRENT:
            break;
        case FILE_SEEK_END:
            origin = FILE_SEEK_START;
            position += BiasStart + BiasLength;
            break;
        }
        long result = Raw_Seek(position, origin) - BiasStart;
        if (result < 0) {
            result = Raw_Seek(BiasStart, FILE_SEEK_START) - BiasStart;
        }
        if (result > BiasLength) {
            result = Raw_Seek(BiasStart + BiasLength, FILE_SEEK_START) - BiasStart;
        }
        return result;
    }
    return Raw_Seek(position, origin);
}
