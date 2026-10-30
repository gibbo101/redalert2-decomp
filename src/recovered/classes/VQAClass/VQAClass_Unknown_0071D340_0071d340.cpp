// int VQAClass::Unknown_0071D340(int request, int unknown2, int unknown3) (0x0071D340)
// Stream callback on the movie file (File); nonzero results are errors.
#include "shared/movie.hpp"

int VQAClass::Unknown_0071D340(int request, int unknown2, int unknown3)
{
    int error = 1;
    char byte;
    switch (request) {
    case 3:
        FileOpen = File.Open((char const *)unknown2, 1) != 0;
        error = !FileOpen;
        break;
    case 5:
        error = File.Read((void *)unknown2, unknown3) != unknown3;
        break;
    case 6:
        error = 1;
        break;
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
        error = 0;
        break;
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
