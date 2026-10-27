// char const *__fastcall TriggerTypeClass::Name_From_Persistence(int persistence) (0x006EE400)
#include "shared/trigger_type.hpp"
// @ref ?PersistenceNames@@3PAPBDA=007f85c0

char const *__fastcall TriggerTypeClass::Name_From_Persistence(int persistence)
{
    return PersistenceNames[persistence];
}
