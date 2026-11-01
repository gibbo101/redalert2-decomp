// Clear each airborne bin and its working list, preserving capacities.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/foot.hpp"
void UnknownTracker839EA0::Clear_00413540()
{
    for (int i=0;i<400;++i) {
        int capacity=Bins[i].Length();
        Bins[i].Clear();
        Bins[i].Resize(capacity,0);
    }
    int capacity=Working.Length();
    Working.Clear();
    Working.Resize(capacity,0);
}
