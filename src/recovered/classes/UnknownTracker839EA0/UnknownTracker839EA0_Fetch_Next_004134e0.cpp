// Return and remove the first airborne object selected by the tracker.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
#include "shared/foot.hpp"
TechnoClass *UnknownTracker839EA0::Fetch_Next_004134e0()
{
    if (Working.Count()==0) return 0;
    TechnoClass *object=Working[0];
    Working.Delete(object);
    return object;
}
