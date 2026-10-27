// void BuildingTypeClass::unknown_func_4584d0(int index, int value0, int value1, int value2) (0x004584D0)
// Sets one of the six value triples.
#include "shared/building_type.hpp"

void BuildingTypeClass::unknown_func_4584d0(int index, int value0, int value1, int value2)
{
    AnimFrames[index].unknown_00 = value0;
    AnimFrames[index].unknown_04 = value1;
    AnimFrames[index].unknown_08 = value2;
}
