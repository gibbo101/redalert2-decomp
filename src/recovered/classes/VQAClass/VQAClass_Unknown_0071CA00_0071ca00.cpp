// VQAClass stream callback over the movie file held in memory (Buffer,
// FileSize bytes, read position unknown_530); 0 on success, 1 on failure.
// The read clips at FileSize; seek origin 0 = set, 1 = current, 2 = end.
#include "shared/crt_memory.hpp"

int VQAClass::Unknown_0071CA00(int request, int unknown2, int unknown3)
{
    int rc = 1;
    switch (request) {
    case 1:
    case 2:
    case 3:
    case 4:
        rc = 0;
        break;
    case 5:
        if (unknown_530 + unknown3 > FileSize) {
            rc = 1;
            return rc;
        } else {
            memcpy((void *)unknown2, Buffer + unknown_530, unknown3);
            unknown_530 += unknown3;
            rc = 0;
        }
        break;
    case 7:
        switch (unknown2) {
        case 1:
            unknown_530 += unknown3;
            rc = 0;
            break;
        case 0:
            unknown_530 = unknown3;
            rc = 0;
            break;
        case 2:
            unknown_530 = FileSize - unknown3 - 1;
            rc = 0;
            break;
        default:
            rc = 1;
            break;
        }
        break;
    default:
        rc = 1;
        break;
    }
    return rc;
}
