#include "shared/cstream.hpp"
// @ref ??_7CStreamClass@@6BIStream@@@=0079e704
// @ref ??_7CStreamClass@@6BILinkStream@@@=0079e6ec
// @ref ?unknown_flush_495000@CStreamClass@@QAEJPAXH@Z=00495000
CStreamClass::CStreamClass() : RefCount(0), unknown_10(false), unknown_11(false), unknown_14(0), unknown_18(new char[65536]), unknown_1c(new char[65536]), unknown_20(new char[65536])
{
    unknown_24 = 65535;
}
