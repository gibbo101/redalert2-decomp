// INIClass::Put_UUBlock (0x0050CFC0)
// Replaces the section with a binary block, Base64 encoded in lines of up
// to 70 characters stored as entries "1", "2", ... False for a null section
// or block or an empty length.
#include "shared/ini_class.hpp"
#include "shared/buffer_straw.hpp"
#include "shared/base64_straw.hpp"
// @ref ??_7Base64Straw@@6B@=007a3bcc
// @ref ?Get@Base64Straw@@UAEHPAXH@Z=0042b850

bool INIClass::Put_UUBlock(char const *section, void const *block, int length)
{
    if (section == 0 || block == 0 || length < 1) return false;

    Clear(section);

    BufferStraw straw((void *)block, length);
    Base64Straw bstraw(Base64Straw::ENCODE);
    bstraw.Get_From(straw);

    int counter = 1;

    for (;;) {
        char buffer[71];
        char sbuffer[32];

        int count = bstraw.Get(buffer, sizeof(buffer) - 1);
        buffer[count] = '\0';
        if (count == 0) break;

        sprintf(sbuffer, "%d", counter);
        Put_String(section, sbuffer, buffer);
        counter++;
    }
    return true;
}
