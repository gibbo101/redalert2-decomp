// DynamicVectorClass<CampaignClass *>::ID_pointer (0x004D5160; DynamicVectorClass<CampaignClass *> vtable 0x007a2524 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class CampaignClass;

template class DynamicVectorClass<CampaignClass *>;
