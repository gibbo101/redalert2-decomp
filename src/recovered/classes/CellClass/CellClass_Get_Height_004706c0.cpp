// int CellClass::unknown_4706c0(Point2D const &point) const (0x004706C0): TibSun Get_Height.
#include "shared/cell.hpp"
// @ref _?$S40@?1??unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z@4EA=00850bb8
// @ref _?_level_height@?1??unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z@4NA=00850ba8
// @ref _?_level_slope@?1??unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z@4NA=00850bd0
// @ref _?_ramp_control@?1??unknown_4706c0@CellClass@@QBEHABUPoint2D@@@Z@4PAU__unnamed@2@A=007d27e8
// @ref __real@8@bffe8000000000000000=0079c9b0

int CellClass::unknown_4706c0(Point2D const &point) const
{
    static double _level_height = unknown_geometry_g;
    static double _level_slope = _level_height / 256.0;

    static struct {
        double XChange;
        double YChange;
        double Base;
        double Max;
        double Extra;
    } _ramp_control[20] = {
        {  1.0,  0.0,  0.0,                           _level_height,                  0.0 },
        {  0.0,  1.0,  0.0,                           _level_height,                  0.0 },
        { -1.0,  0.0,  _level_height,                 _level_height,                  0.0 },
        {  0.0, -1.0,  _level_height,                 _level_height,                  0.0 },
        {  1.0,  1.0, -_level_height,                 _level_height,                  0.0 },
        { -1.0,  1.0,  0.0,                           _level_height,                  0.0 },
        { -1.0, -1.0,  _level_height,                 _level_height,                  0.0 },
        {  1.0, -1.0,  0.0,                           _level_height,                  0.0 },
        {  1.0,  1.0,  0.0,                           _level_height,                  0.0 },
        { -1.0,  1.0,  _level_height,                 _level_height,                  0.0 },
        { -1.0, -1.0,  _level_height + _level_height, _level_height,                  0.0 },
        {  1.0, -1.0,  _level_height,                 _level_height,                  0.0 },
        {  1.0,  1.0,  0.0,                           _level_height + _level_height,  0.0 },
        { -1.0,  1.0,  _level_height,                 _level_height + _level_height,  0.0 },
        { -1.0, -1.0,  _level_height + _level_height, _level_height + _level_height,  0.0 },
        {  1.0, -1.0,  _level_height,                 _level_height + _level_height,  0.0 },
        {  0.0,  0.0,  0.0,                           _level_height * 0.5,            _level_height * 0.5 },
        {  0.0,  0.0,  _level_height,                 _level_height * 0.5,            _level_height * -0.5 },
        {  0.0,  0.0,  0.0,                           _level_height * 0.5,            _level_height * 0.5 },
        {  0.0,  0.0,  _level_height,                 _level_height * 0.5,            _level_height * -0.5 }
    };

    int height = int(unknown_geometry_g * unknown_11b + 0.5);

    if (unknown_11c > 0) {
        int ramp = unknown_11c - 1;
        double rampheight = ((point.X & 255) * _ramp_control[ramp].XChange * _level_slope) +
                            ((point.Y & 255) * _ramp_control[ramp].YChange * _level_slope) +
                            _ramp_control[ramp].Base +
                            _ramp_control[ramp].Extra;

        if (rampheight < 0.0) {
            rampheight = 0.0;
        }
        if (rampheight > _ramp_control[ramp].Max) {
            rampheight = _ramp_control[ramp].Max;
        }

        height += rampheight;
    }

    return height;
}
