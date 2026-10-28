// HRESULT KamikazeTrackerClass::Save(IStream *stream) (0x00531A40)
#include "shared/kamikaze_tracker.hpp"

HRESULT KamikazeTrackerClass::Save(IStream *stream)
{
    int count = Nodes.Count();
    HRESULT result = stream->Write(&count, sizeof(count), 0);
    if (SUCCEEDED(result)) {
        for (int index = 0; index < count; index++) {
            result = stream->Write(Nodes[index], sizeof(KamikazeControl), 0);
            if (FAILED(result)) {
                break;
            }
        }
    }
    return result;
}
