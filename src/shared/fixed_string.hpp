// FixedString: Westwood's fixed-capacity string (moved out of
// shared/abstract_type.hpp so a class header can hold one as a member without
// the type-class headers). The members are only instantiated where used; the
// user provides strncpy and memcpy (shared/ini_class.hpp, shared/crt_memory.hpp).
#ifndef RA2_SHARED_FIXED_STRING_HPP
#define RA2_SHARED_FIXED_STRING_HPP

class NoInitClass;

// A fixed-capacity, always terminated string (N bytes including the
// terminator); assignment from a C string truncates through a temporary.
template <int N>
class FixedString {
public:
    FixedString() { Buffer[0] = 0; }
    FixedString(NoInitClass const &noinit) {}
    FixedString(char const *string)
    {
        if (string == 0) {
            Buffer[0] = 0;
        } else {
            strncpy(Buffer, string, N - 1);
            Buffer[N - 1] = 0;
        }
    }
#ifdef RA2_FIXEDSTRING_ASSIGN_VALUE
#ifdef RA2_FIXEDSTRING_COPY_ASSIGN_SOURCE
    // The owning unit supplies its original by-value copy-assignment body.
    FixedString operator=(FixedString const &other);
#else
    FixedString operator=(FixedString const &other)
    {
        if (&other != this) {
            memcpy(Buffer, other.Buffer, N);
        }
        return *this;
    }
#endif
    FixedString &operator=(char const *string) { *this = FixedString(string); return *this; }
#else
    FixedString &operator=(FixedString const &other)
    {
        if (&other != this) {
            memcpy(Buffer, other.Buffer, N);
        }
        return *this;
    }
    FixedString &operator=(char const *string) { return *this = FixedString(string); }
#endif
    operator char const *() const { return Buffer; }

    char Buffer[N];
};

#endif
