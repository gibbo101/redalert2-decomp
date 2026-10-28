// HRESULT KamikazeTrackerClass::Load(IStream *stream) (0x00531AA0)
#include "shared/kamikaze_tracker.hpp"
#include "shared/swizzle.hpp"

HRESULT KamikazeTrackerClass::Load(IStream *stream)
{
    int count;
    HRESULT result = stream->Read(&count, sizeof(count), 0);
    if (SUCCEEDED(result)) {
        for (int index = 0; index < count; index++) {
            KamikazeControl *node = new KamikazeControl;
            result = stream->Read(node, sizeof(KamikazeControl), 0);
            if (FAILED(result)) {
                return result;
            }
            SwizzleManager.Swizzle((void **)&node->Unit);
            SwizzleManager.Swizzle((void **)&node->Cell);
            Nodes.Add(node);
        }
    }
    return result;
}
