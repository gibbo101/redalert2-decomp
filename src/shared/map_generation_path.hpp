// Unknown original nonpolymorphic map-generation path/point records; names are hypotheses.
// Original overloads0058B200/250/2C0/340 allocate1/2/3/4 eight-byte records.
// Count+0, Points+4, unknown_08+8; no RTTI identity or accepted ABI change.
#ifndef RA2_SHARED_MAP_GENERATION_PATH_HPP
#define RA2_SHARED_MAP_GENERATION_PATH_HPP
#include "shared/coord.hpp"
struct UnknownMapGenerationPoint {
    UnknownMapGenerationPoint() : Position(0,0),unknown_04(-1) {}
    UnknownMapGenerationPoint(UnknownMapGenerationPoint const &other); //0058B140, copyctor-versus-assignment intent qualified
    Cell Position;
    int unknown_04;
};
class UnknownMapGenerationPath {
public:
    UnknownMapGenerationPath(); //0058B3D0, deliberately leaves unknown_08 uninitialized
    UnknownMapGenerationPath(UnknownMapGenerationPoint const &a); //0058B200
    UnknownMapGenerationPath(UnknownMapGenerationPoint const &a,UnknownMapGenerationPoint const &b); //0058B250
    UnknownMapGenerationPath(UnknownMapGenerationPoint const &a,UnknownMapGenerationPoint const &b,UnknownMapGenerationPoint const &c); //0058B2C0
    UnknownMapGenerationPath(UnknownMapGenerationPoint const &a,UnknownMapGenerationPoint const &b,UnknownMapGenerationPoint const &c,UnknownMapGenerationPoint const &d); //0058B340
    ~UnknownMapGenerationPath(); //0058B3E0
    int Count;
    UnknownMapGenerationPoint *Points;
    int unknown_08;
};
typedef char UnknownMapGenerationPoint_size[(sizeof(UnknownMapGenerationPoint)==8)?1:-1];
typedef char UnknownMapGenerationPath_size[(sizeof(UnknownMapGenerationPath)==12)?1:-1];
#endif
