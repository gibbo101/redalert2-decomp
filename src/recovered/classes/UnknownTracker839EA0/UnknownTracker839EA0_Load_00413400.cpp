// Restore each spatial bin, then register its loaded pointers for swizzling.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
#include "shared/foot.hpp"
#include "shared/swizzle.hpp"
long UnknownTracker839EA0::Load_00413400(IStream *stream)
{
    for (int i=0;i<400;++i) {
        int count;
        long result=stream->Read(&count,4,0);
        if (result<0) return result;
        for (int j=0;j<count;++j) {
            TechnoClass *object;
            result=stream->Read(&object,4,0);
            if (result<0) return result;
            Bins[i].Add(object);
        }
        for (j=0;j<count;++j) SwizzleManager.Swizzle(reinterpret_cast<void **>(&Bins[i][j]));
    }
    return 0;
}
