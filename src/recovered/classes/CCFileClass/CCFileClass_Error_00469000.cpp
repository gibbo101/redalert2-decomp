// void CCFileClass::Error(int error, int can_retry, char const *filename) (0x00469000, slot 16)
// A file could not be opened: asks a temporary CD object to make the
// required disk available. The answer is ignored.
// Assumes: CD slot 0 is Force_Available (see shared/cd.hpp); the parameters
// are unused, as in Westwood's earlier ccfile.cpp.
#include "shared/cc_file_class.hpp"
#include "shared/cd.hpp"
// @ref ??_7CD@@6B@=0079d868
// @ref ?RequiredCD@CD@@2HA=007d20e0

void CCFileClass::Error(int, int, char const *)
{
    CD().Force_Available(CD::RequiredCD);
}
