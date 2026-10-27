// CRCEngine memory append, original 00493FC0: full 457-byte body plus 7 frozen padding bytes.
#include "shared/ini_class.hpp"
inline void Consume_Partial_CRC_Input(CRCEngine &engine,void const *&cursor,int &remaining)
{
    engine.Append_Partial_Byte(*(char const *)cursor);
    cursor=(char const *)cursor+1;
    --remaining;
}
long CRCEngine::operator()(void const *buffer, int length)
{
    if (buffer && length>0) {
        int remaining=length;
        while(remaining>0 && Index && (unsigned int)Index<4) {
            Consume_Partial_CRC_Input(*this,buffer,remaining);
        }
        unsigned int words = (unsigned int)remaining / 4;
        buffer=Consume_Whole_Words(buffer,words,remaining);
        while (remaining > 0) {
            (*this)(*(char const *)buffer);
            buffer = (char const *)buffer + 1;
            --remaining;
        }
    }
    return Value();
}
