#include "shared/map_generation_path.hpp"
UnknownMapGenerationPath::UnknownMapGenerationPath(UnknownMapGenerationPoint const &a,UnknownMapGenerationPoint const &b)
    : unknown_08(0)
{
    Count=2;
    Points=new UnknownMapGenerationPoint[2];
    Points[0]=a;
    Points[1]=b;
}
