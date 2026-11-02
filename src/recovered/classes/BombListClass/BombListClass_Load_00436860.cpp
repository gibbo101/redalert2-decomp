#include "shared/object.hpp"

HRESULT BombListClass::Load(IStream *stream)
{
    BombClass *bomb;
    TechnoClass *techno;
    int count;
    HRESULT result=stream->Read(&count,sizeof(count),0);
    if(FAILED(result)) return result;
    for(int index=0;index<count;++index) {
        result=stream->Read(&bomb,sizeof(bomb),0);
        if(FAILED(result)) return result;
        Bombs.Add(bomb);
    }
    for(index=0;index<count;++index) Swizzle_Pointer(Bombs[index]);
    result=stream->Read(&count,sizeof(count),0);
    if(FAILED(result)) return result;
    for(index=0;index<count;++index) {
        result=stream->Read(&techno,sizeof(techno),0);
        if(FAILED(result)) return result;
        unknown_18.Add(techno);
    }
    for(index=0;index<count;++index) Swizzle_Pointer(unknown_18[index]);
    return result;
}

// External references checked against complete original body operands.
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
