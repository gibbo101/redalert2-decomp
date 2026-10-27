// HRESULT RadarClass::unknown_slot31(IStream *stream) (0x00632E10, slot 31)
// Saves the radar after the display: the queued points (+0x1258) and cells
// (+0x1220), each with its count, then the mode values at +0x14AC, +0x14A8,
// +0x14B0 and +0x14B4.
#include "shared/radar.hpp"
// @ref ?unknown_slot31@DisplayClass@@UAEJPAUIStream@@@Z=0049e840

HRESULT RadarClass::unknown_slot31(IStream *stream)
{
    HRESULT result = DisplayClass::unknown_slot31(stream);
    if (FAILED(result)) {
        return result;
    }
    int count = unknown_1258.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        result = stream->Write(&unknown_1258[index], sizeof(Point2D), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    count = unknown_1220.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (index = 0; index < count; index++) {
        result = stream->Write(&unknown_1220[index], sizeof(Cell), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    result = stream->Write(&unknown_14ac, sizeof(unknown_14ac), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&unknown_14a8, sizeof(unknown_14a8), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&unknown_14b0, sizeof(unknown_14b0), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&unknown_14b4, sizeof(unknown_14b4), 0);
    return FAILED(result) ? result : S_OK;
}
