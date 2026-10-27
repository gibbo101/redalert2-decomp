// HRESULT __stdcall InfantryTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x0050AD80)
// The techno part, the three lists and the sequences.
#include "shared/infantry_type.hpp"
// @ref ?Save@TechnoTypeClass@@UAGJPAUIStream@@H@Z=006dec10

HRESULT __stdcall InfantryTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = TechnoTypeClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        VoiceComment.Save(stream);
        DeadBodies.Save(stream);
        DeathAnims.Save(stream);
        stream->Write(DoControls, 38 * sizeof(DoInfoStruct), 0);
    }
    return result;
}
