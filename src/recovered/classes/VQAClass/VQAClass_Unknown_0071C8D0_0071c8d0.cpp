// int VQAClass::Unknown_0071C8D0(unsigned size) (0x0071C8D0)
// Loads the movie file into Buffer in pieces of `size` bytes (0: the rest);
// returns -1 while more remains, -2 when complete, -3/-4/-5 on errors.
#include "shared/movie.hpp"
// @ref _malloc=00782630

extern "C" void *__cdecl malloc(unsigned size);

int VQAClass::Unknown_0071C8D0(unsigned size)
{
    if (!FileOpen) {
        FileOpen = File.Open(Filename, 1) != 0;
        if (!FileOpen) {
            return -4;
        }
        FileSize = File.Size();
        unknown_530 = 0;
        Position = 0;
        Buffer = (unsigned char *)malloc(FileSize);
        if (Buffer == 0) {
            File.Close();
            FileOpen = false;
            return -3;
        }
    }
    if (size == 0) {
        size = FileSize - Position;
    } else if (Position + size > FileSize) {
        size = FileSize - Position;
    }
    if ((unsigned)File.Read(Buffer + Position, size) != size) {
        File.Close();
        FileOpen = false;
        unknown_530 = 0;
        Position = 0;
        return -5;
    }
    Position += size;
    if (Position >= FileSize) {
        File.Close();
        FileOpen = false;
        return -2;
    }
    return -1;
}
