// int VQAClass::Unknown_0071D4B0(int request, int unknown2, int unknown3) (0x0071D4B0)
// Stream callback on a movie inside a mixfile: opening seeks the mixfile
// to the movie; otherwise as 0x0071D340.
#include "shared/movie.hpp"
#include "shared/mix_file_class.hpp"

int VQAClass::Unknown_0071D4B0(int request, int unknown2, int unknown3)
{
    int error = 1;
    char byte;
    switch (request) {
    case 3: {
        long offset = 0;
        MixFileClass *mixfile = 0;
        if (MixFileClass::Offset(Filename, 0, &mixfile, &offset, 0)) {
            FileOpen = File.Open(mixfile->Filename, 1) != 0;
            return File.Seek(offset, 1) == 0;
        }
        return 1;
    }
    case 5:
        error = File.Read((void *)unknown2, unknown3) != unknown3;
        break;
    case 6:
        return 1;
    case 7:
        error = File.Seek(unknown3, unknown2) == 0;
        break;
    case 8: {
        if (unknown3 > 0) {
            error = File.Seek(unknown3 - 1, unknown2) == 0;
            if (error) {
                break;
            }
            error = File.Read(&byte, 1) != 1;
        } else {
            error = File.Seek(unknown3, unknown2) == 0;
            if (error) {
                break;
            }
            error = File.Read(&byte, 1) != 1;
            if (error) {
                break;
            }
            error = File.Seek(-1, 1) == 0;
        }
        break;
    }
    case 9:
        *(long *)unknown2 = File.Size();
        return 0;
    case 4:
        File.Close();
        FileOpen = false;
        error = 0;
        break;
    case 1:
    case 2:
        error = 0;
        break;
    }
    return error;
}
