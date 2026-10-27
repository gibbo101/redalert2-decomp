// CCINIClass::Get_Unique_ID (0x0046C1C0).
// Layout and behaviour: shared/ccini_class.hpp (Calculate_Message_Digest,
// defined later in the unit, is expanded here).
#include "shared/sha_pipe.hpp"

int CCINIClass::Get_Unique_ID() const
{
    if (!IsDigestValid) {
        ((CCINIClass *)this)->Calculate_Message_Digest();
    }
    return CRCEngine()(&Digest[0], sizeof(Digest));
}
