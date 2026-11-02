#include "shared/score.hpp"
#include "shared/sound_available.hpp"
#include "shared/crt_memory.hpp"
// 0x00668280: 43-byte body and five original padding bytes.
// Only the role name is retained; the second argument is unused in this release.
extern "C" char *__cdecl _strdup(char const *text);
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref __strdup=0078d816
ScoreSoundClass::ScoreSoundClass(char const *name, char const *filename) :
    Name(0), unknown_04(0), unknown_08(false)
{
    if (unknown_check_406f30()) {
        Name = _strdup(name);
    }
}
