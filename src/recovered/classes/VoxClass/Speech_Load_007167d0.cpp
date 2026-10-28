// long Speech_Load(IStream *stream) (0x007167D0): stops the speech, then
// queues the speeches a saved game lists between 'SxoV' and 'ExoV' (each an
// 'IxoV' marker and the VoxClass index, type and priority); E_FAIL for an
// unknown marker (name hypothesis).
#include "shared/vox_speech.hpp"
#include "shared/com_persist.hpp"
// @ref ?Speech_Queue@@YIXPAVVoxClass@@HH@Z=007159d0

long __fastcall Speech_Load(IStream *stream)
{
    Speech_Stop(true);
    int marker;
    HRESULT result = stream->Read(&marker, sizeof(marker), 0);
    if (FAILED(result) || marker != 0x566F7853) {
        return result;
    }
    for (result = stream->Read(&marker, sizeof(marker), 0); SUCCEEDED(result);
            result = stream->Read(&marker, sizeof(marker), 0)) {
        if (marker == 0x566F7845) {
            break;
        }
        if (marker != 0x566F7849) {
            return (HRESULT)0x80004005L;
        }
        struct {
            int Index;
            int Type;
            int Priority;
        } entry;
        result = stream->Read(&entry, sizeof(entry), 0);
        if (FAILED(result)) {
            break;
        }
        if (unknown_vox_stream_ad095c != 0 && entry.Index >= 0 && entry.Index < unknown_VoxClass_list_00ad0930.Count()) {
            Speech_Queue(unknown_VoxClass_list_00ad0930[entry.Index], entry.Type, entry.Priority);
        }
    }
    return result;
}
