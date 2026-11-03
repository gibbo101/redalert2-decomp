#define RA2_AIRCRAFT_OWNER_FIRE
#define RA2_LOCOMOTION_COM_VALUE_TYPES
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
// Append the selected bin's current objects to the query's working list.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
#include "shared/foot.hpp"
void UnknownTracker839EA0::Append_Bin_00412720(int index)
{
    int count=Bins[index].Count();
    for (int i=0;i<count;++i) Working.Add(Bins[index].Fetch(i));
}
