// CCFileClass::Close (0x004691F0, virtual slot 13)
// Forgets resident data and closes the disk file.
#include "shared/cc_file_class.hpp"
#include "shared/crt_new.hpp"

void CCFileClass::Close()
{
    new (&Data) ::Buffer;
    Position = 0;
    CDFileClass::Close();
}
