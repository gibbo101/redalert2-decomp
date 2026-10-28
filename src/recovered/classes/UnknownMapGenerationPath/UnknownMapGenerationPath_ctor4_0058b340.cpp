#include "shared/map_generation_path.hpp"
UnknownMapGenerationPath::UnknownMapGenerationPath(UnknownMapGenerationPoint const &a,UnknownMapGenerationPoint const &b,UnknownMapGenerationPoint const &c,UnknownMapGenerationPoint const &d)
    : unknown_08(0)
{
    Count=4;
    Points=new UnknownMapGenerationPoint[4];
    Points[0]=a;
    Points[1]=b;
    Points[2]=c;
    Points[3]=d;
}
