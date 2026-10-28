#include "shared/unknown_map_generator.hpp"
// @ref ?unknown_0057ecf0@UnknownMapGenerator@@=0057ecf0
// @ref ?unknown_0057e100@UnknownMapGenerator@@=0057e100
void UnknownMapGenerator::Run_Region_Attempts_0057dd60()
{
    ++unknown_308;
    if((SeedOptions.MapType==3 || SeedOptions.MapType==4) && SeedOptions.WaterAmount>20) {
        int attempts=0;
        bool success=false;
        while(!success) {
            if(attempts>=10)break;
            success=unknown_0057ecf0(Cell(0,0),0.0,false);
            ++attempts;
        }
        if(success)++unknown_308;
    }
    int attempts=0;
    bool success=false;
    while(!success) {
            if(attempts>=10)break;
        success=unknown_0057e100(Cell(0,0));
        ++attempts;
    }
    if(success)++unknown_308;
}
