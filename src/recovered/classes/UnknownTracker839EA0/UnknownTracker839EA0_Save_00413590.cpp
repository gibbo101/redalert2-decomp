// Serialize the airborne spatial bins; the temporary query list is not stored.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/foot.hpp"
long UnknownTracker839EA0::Save_00413590(IStream *stream)
{
    for (int i=0;i<400;++i) {
        int count=Bins[i].Count();
        long result=stream->Write(&count,4,0);
        if (result<0) return result;
        for (int j=0;j<count;++j) {
            result=stream->Write(&Bins[i][j],4,0);
            if (result<0) return result;
        }
    }
    return 0;
}
