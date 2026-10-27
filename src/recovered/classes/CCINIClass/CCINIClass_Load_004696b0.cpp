// CCINIClass::Load (0x004696B0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Get_UUBlock@INIClass@@QBEHPBDPAXH@Z=0050d0f0
// @ref ??1FileStraw@@UAE@XZ=00773900
// @ref ??_7FileStraw@@6B@=0079d9ac
// @ref ??_EFileStraw@@UAEPAXI@Z=0046cbb0
// @ref ??_GFileStraw@@UAEPAXI@Z=0046cbb0
// @ref ?Get@FileStraw@@UAEHPAXH@Z=007738a0
// @ref ?Get_From@Straw@@UAEXPAV1@@Z=0069b050
// @ref ??_C@_06JBJP@Digest?$AA@=007d1ef0
#include "shared/ccini_class.hpp"
#include "shared/ccini_extra.hpp"
#include "shared/crt_memory.hpp"

int CCINIClass::Load(FileClass &file, bool withdigest, bool keep_comments)
{
    FileStraw straw(file);
    return Load(straw, withdigest, keep_comments);
}
