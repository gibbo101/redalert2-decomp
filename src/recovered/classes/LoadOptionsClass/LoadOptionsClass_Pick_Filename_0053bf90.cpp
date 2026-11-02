// Picks a save file name that does not exist yet (0x0053BF90).
#include "shared/map_seed.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
// @ref ??_C@_0O@BGCN@SAVE?$CF04lX?4?$CF3s?$AA@=007dfa30

void LoadOptionsClass::Pick_Filename(char *name)
{
    CCFileClass file;
    do {
        sprintf(name, "SAVE%04lX.%3s", rand(), Extension);
        file.Set_Name(name);
    } while (file.Is_Available() == true);
}
