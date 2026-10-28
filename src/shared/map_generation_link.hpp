// Nonpolymorphic 0x14-byte map-generation record, original nominal class name unknown.
// Layout hypothesis: constructor0058B190, copy0058B1D0, 1024-element stack array
// at0058A1C4/1CF with stride0x14. Two packed signed16 Cell members at+4/+C.
#ifndef RA2_SHARED_MAP_GENERATION_LINK_HPP
#define RA2_SHARED_MAP_GENERATION_LINK_HPP
#include "shared/coord.hpp"
class UnknownMapGenerationLink {
public:
    UnknownMapGenerationLink(); //0058B190
    UnknownMapGenerationLink(unsigned int value,Cell const &a,unsigned int next,Cell const &b,int index); //0058B160
    UnknownMapGenerationLink(UnknownMapGenerationLink const &other); //0058B1D0
    unsigned int unknown_00;
    Cell unknown_04;
    unsigned int unknown_08;
    Cell unknown_0c;
    int unknown_10;
};
typedef char UnknownMapGenerationLink_size[(sizeof(UnknownMapGenerationLink)==0x14)?1:-1];
#endif
