// HRESULT DisplayClass::unknown_slot31(IStream *stream) (0x0049E840, slot 31)
// Saves the five display layers, stopping at the first failure.
#include "shared/display.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?Save@LayerClass@@QAEJPAUIStream@@@Z=00534a10

HRESULT DisplayClass::unknown_slot31(IStream *stream)
{
    HRESULT result;
    for (int index = 0; index < 5; index++) {
        result = Layer[index].Save(stream);
        if (FAILED(result)) {
            break;
        }
    }
    return result;
}
