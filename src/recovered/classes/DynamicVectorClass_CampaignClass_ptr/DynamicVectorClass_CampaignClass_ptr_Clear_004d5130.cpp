// DynamicVectorClass<CampaignClass *>::Clear (0x004D5130; DynamicVectorClass<CampaignClass *> vtable 0x007a2524 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class CampaignClass;

template class DynamicVectorClass<CampaignClass *>;
