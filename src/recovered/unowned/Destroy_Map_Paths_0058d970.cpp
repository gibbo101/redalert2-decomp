#include "shared/map_generation_path.hpp"
// Original reverse destruction of109 twelve-byte records, each Points member freed then cleared.
// Complete array extent follows the loop count and field offsets; nominal global name is unknown.
extern UnknownMapGenerationPath unknown_map_paths_a700a0[109];
// @ref ?unknown_map_paths_a700a0@@=00a700a0
void Destroy_Map_Paths_0058d970()
{
    UnknownMapGenerationPath *current=unknown_map_paths_a700a0+109;
    for(int count=109;count>0;--count) {
        (--current)->~UnknownMapGenerationPath();
    }
}
