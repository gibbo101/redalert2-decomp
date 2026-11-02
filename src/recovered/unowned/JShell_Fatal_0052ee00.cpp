// Fatal (0x0052EE00): posts the main window's destroy, prints the message to stderr and the
// mono screen, then exits with code 1 (Westwood's JSHELL.CPP Fatal).
// @ref __iob=0082ec90
// @ref _vfprintf=00784502
// @ref ?Unknown_0059DA50@@YIPAVMonoClass@@H@Z=0059da50
#include "shared/jshell.hpp"
#include "shared/crt_stderr.hpp"
#include "shared/exit.hpp"
#include "shared/mono_class.hpp"

MonoClass *__fastcall Unknown_0059DA50(int page);       // 0x0059DA50

void __cdecl Fatal(char const *message, ...)
{
    Unknown_00691320();
    vfprintf(stderr, message, (char *)(&message + 1));
    Unknown_0059DA50(4)->Printf(message);
    Emergency_Exit(1);
}
