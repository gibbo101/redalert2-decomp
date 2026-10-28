#include "shared/map_generation_path.hpp"
UnknownMapGenerationPath::UnknownMapGenerationPath(UnknownMapGenerationPoint const &a)
    : unknown_08(0)
{
    Count=1;
    Points=new UnknownMapGenerationPoint[1];
    Points[0]=a;
}
