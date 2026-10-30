// INIClass::Get_UUBlock (0x0050D0F0)
// Decodes the section's Base64 lines (stored by Put_UUBlock) into block, at
// most length bytes; returns the decoded length.
#include "shared/ini_class.hpp"
#include "shared/buffer_pipe.hpp"
#include "shared/base64_pipe.hpp"
// @ref ??_7Base64Pipe@@6B@=007a3bdc
// @ref ?Put@Base64Pipe@@UAEHPBXH@Z=0042b670
// @ref ?Flush@Base64Pipe@@UAEHXZ=0042b800
// @ref ??_C@_01NEMO@?$DN?$AA@=007ce9b8

int INIClass::Get_UUBlock(char const *section, void *block, int length) const
{
    if (section == 0) return 0;

    Base64Pipe b64pipe(Base64Pipe::DECODE);
    BufferPipe bpipe(block, length);

    b64pipe.Put_To(&bpipe);

    int total = 0;
    int counter = Entry_Count(section);
    for (int index = 0; index < counter; index++) {
        char buffer[128];

        int count = Get_String(section, Get_Entry(section, index), "=", buffer, sizeof(buffer));
        int outcount = b64pipe.Put(buffer, count);
        total += outcount;
    }
    total += b64pipe.End();
    return total;
}
