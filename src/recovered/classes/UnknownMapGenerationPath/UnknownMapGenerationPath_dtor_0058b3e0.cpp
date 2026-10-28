#include "shared/map_generation_path.hpp"
UnknownMapGenerationPath::~UnknownMapGenerationPath()
{
    delete[] Points;
    Points=0;
}
