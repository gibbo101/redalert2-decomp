// UnknownNamedValue_0072a5e0::UnknownNamedValue_0072a5e0(Wstring const &name, int value) -- 0x0072A5E0
// Purpose: copy-constructs the Wstring name (+0x00) and stores the value
// (+0x04). In the world-domination map area after MSFrameAnim; the owning
// type is not identified.
#include "shared/wstring.hpp"
// @ref ??0Wstring@@QAE@ABV0@@Z=0076d980

struct UnknownNamedValue_0072a5e0 {
    UnknownNamedValue_0072a5e0(Wstring const &name, int value);

    Wstring Name;    // +0x00
    int Value;       // +0x04
};

UnknownNamedValue_0072a5e0::UnknownNamedValue_0072a5e0(Wstring const &name, int value) : Name(name), Value(value)
{
}
