// FixedString<32> assignment returns the copied value, original006B3230 complete41+7/RET8.
#include "shared/crt_memory.hpp"
#include "shared/fixed_string.hpp"
template<> FixedString<32> FixedString<32>::operator=(FixedString<32> const &other)
{
    if (&other != this) memcpy(Buffer, other.Buffer, 32);
    return *this;
}
