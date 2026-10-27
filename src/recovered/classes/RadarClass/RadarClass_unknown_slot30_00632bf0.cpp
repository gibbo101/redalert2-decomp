// HRESULT RadarClass::unknown_slot30(IStream *stream) (0x00632BF0, slot 30)
// Loads the radar after the display: rebuilds its list (+0x14BC) and its
// vectors in place, reads back the queued points and cells, empties the 22
// point vectors, reads the mode values, and resets the list again.
#include "shared/radar.hpp"
// @ref ?unknown_slot30@DisplayClass@@UAEJPAUIStream@@@Z=0049e810
// @ref ?Unknown_00405BF0@UnknownList14BC@@QAEXXZ=00405bf0
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0

HRESULT RadarClass::unknown_slot30(IStream *stream)
{
    HRESULT result = DisplayClass::unknown_slot30(stream);
    if (FAILED(result)) {
        return result;
    }
    int count;
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    unknown_14bc.Unknown_00405BF0();
    new (&unknown_1258) DynamicVectorClass<Point2D>;
    for (int index = 0; index < count; index++) {
        Point2D point;
        result = stream->Read(&point, sizeof(point), 0);
        if (FAILED(result)) {
            return result;
        }
        unknown_1258.Add(point);
    }
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    new (&unknown_1220) DynamicVectorClass<Cell>;
    for (index = 0; index < count; index++) {
        Cell cell;
        result = stream->Read(&cell, sizeof(cell), 0);
        if (FAILED(result)) {
            return result;
        }
        unknown_1220.Add(cell);
    }
    for (index = 0; index < 22; index++) {
        new (&unknown_1274[index]) DynamicVectorClass<Point2D>;
    }
    result = stream->Read(&unknown_14ac, sizeof(unknown_14ac), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&unknown_14a8, sizeof(unknown_14a8), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&unknown_14b0, sizeof(unknown_14b0), 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&unknown_14b4, sizeof(unknown_14b4), 0);
    if (FAILED(result)) {
        return result;
    }
    unknown_14bc.Unknown_00405BF0();
    return S_OK;
}
