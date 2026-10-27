// Cell const *ParticleClass::unknown_slot64(int arg1) (0x0060A550)
// No cell: a function-local static (0x7FFF, 0x7FFF).
#include "shared/particle.hpp"
// @ref _atexit=0078298a
// (the guard's number follows the unit's header contents: 42 with the
// proposed abstract.hpp, 40 with the current one)
// @ref _?$S42@?1??unknown_slot64@ParticleClass@@UAEPBVCell@@H@Z@4EA=00a76520
// @ref _?$S40@?1??unknown_slot64@ParticleClass@@UAEPBVCell@@H@Z@4EA=00a76520
// @ref _?unknown_none@?1??unknown_slot64@ParticleClass@@UAEPBVCell@@H@Z@4UUnknownStaticCell@@B=00a764e0

Cell const *ParticleClass::unknown_slot64(int arg1)
{
    static UnknownStaticCell const unknown_none(Cell(0x7FFF, 0x7FFF));
    return &unknown_none.Cell;
}
