#include "shared/map_generation_path.hpp"
UnknownMapGenerationPath::UnknownMapGenerationPath(UnknownMapGenerationPoint const &a,UnknownMapGenerationPoint const &b,UnknownMapGenerationPoint const &c)
    : unknown_08(0)
{
    Count=3;
    Points=new UnknownMapGenerationPoint[3];
    Points[0]=a;
    Points[1]=b;
    Points[2]=c;
}
