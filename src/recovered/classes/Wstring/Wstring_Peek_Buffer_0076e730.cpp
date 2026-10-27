// char const *Wstring::Peek_Buffer() const (0x0076E730)
// The text, or the empty string when null: a second copy of Get (0x0076E6F0).
// Formerly declared as operator char const *; the original passes string
// literals to INIClass's Wstring overloads, which an implicit conversion to
// char const * would make ambiguous, so the accessor is a named call. The name
// is a hypothesis.
// @ref ??_C@_00A@?$AA@=0083c55c
#include "shared/wstring.hpp"

char const *Wstring::Peek_Buffer() const
{
    return (Buffer == 0) ? "" : Buffer;
}
