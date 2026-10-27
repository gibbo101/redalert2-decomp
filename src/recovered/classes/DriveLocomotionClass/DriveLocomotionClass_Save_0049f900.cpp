// HRESULT __stdcall DriveLocomotionClass::Save(IStream *stream, BOOL clear_dirty) (0x0049F900)
// LocomotionClass::Save, then whether a locomotor is carried and, if so,
// that locomotor (OleSaveToStream through its IPersistStream).
#include "shared/drive_locomotion.hpp"
// @ref ?Save@LocomotionClass@@UAGJPAUIStream@@H@Z=0053d360
// @ref __imp__OleSaveToStream@8=0079a5e8
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref _unknown_uuid_IPersistStream_7d5f38=007d5f38

HRESULT __stdcall DriveLocomotionClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = LocomotionClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    bool piggybacking;
    if (Piggybacker != 0) {
        piggybacking = true;
        stream->Write(&piggybacking, sizeof(piggybacking), 0);
        UnknownComPtr<IPersistStream, &unknown_uuid_IPersistStream_7d5f38> persist(static_cast<ILocomotion *>(Piggybacker));
        return OleSaveToStream(persist, stream);
    }
    piggybacking = false;
    stream->Write(&piggybacking, sizeof(piggybacking), 0);
    return result;
}
// @ref ?Release_Held@?$UnknownComPtr@UIPersistStream@@$1?unknown_uuid_IPersistStream_7d5f38@@3UGUID@@B@@QAEXXZ=004a4d10
