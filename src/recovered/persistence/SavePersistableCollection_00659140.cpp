#include "shared/com_collection.hpp"

// Serialize the saved count, then each element's IPersistStream through the
// PE-bound OleSaveToStream import. Original target e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f,
// VA 0x00659140, 127 body bytes plus 1 separately frozen padding byte(s).
// The concrete element/collection classes and original source prototype remain
// unknown. The outer two-register ABI is fastcall-compatible, not a class claim.
extern "C" int __fastcall SavePersistableCollection_00659140(
    ComInterface32* stream, ComCollection32* collection)
{
    // Write the saved local, not the live collection count. Its address escapes:
    // subsequent loop tests must reread this local after external calls.
    int count = collection->count;
    int status = ((ComWriteCountCall)stream->slots[4])(
        stream, &count, 4, 0);
    if (status < 0) {
        return status;
    }

    for (int index = 0; index < count; ++index) {
        // Preserve this order: reload items, clear the output local, load element.
        ComInterface32** items = collection->items;
        ComInterface32* persist_stream = 0;
        ComInterface32* element = items[index];
        status = ((ComQueryInterfaceCall)element->slots[0])(
            element, ra2_iid_ipersist_stream, &persist_stream);
        if (status < 0) {
            return status;
        }

        status = ra2_ole_save_to_stream(persist_stream, stream);
        if (status < 0) {
            // The original skips Release on this failure path. Do not add RAII.
            return status;
        }

        // Reload the queried local after the import; preserve the signed test
        // even though conventional COM Release returns an unsigned reference count.
        status = ((ComReleaseStatusCall)persist_stream->slots[2])(persist_stream);
        if (status < 0) {
            return status;
        }
    }

    return 0;
}
