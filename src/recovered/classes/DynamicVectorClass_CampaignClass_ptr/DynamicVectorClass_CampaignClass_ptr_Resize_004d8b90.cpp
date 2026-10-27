// DynamicVectorClass<CampaignClass *>::Resize (0x004D8B90; DynamicVectorClass<CampaignClass *> vtable 0x007a2524 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class CampaignClass;

template class DynamicVectorClass<CampaignClass *>;
