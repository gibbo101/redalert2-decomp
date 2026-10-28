// UnknownIDSource's variable setters (0x006612C0, 0x00661560).
#include "shared/id_source.hpp"
#include "shared/tag.hpp"

// Sets one of the 50 variables at +0x1210 (the global ones; TagClass
// 0x006B4220 is told of a change) and returns its old value; false for an
// index out of range.
bool UnknownIDSource::unknown_6612c0(unsigned index, bool value)
{
    if (index < 50) {
        bool old = Variables[index].Value;
        if (old != value) {
            Variables[index].Value = value;
            unknown_222e = true;
            TagClass::unknown_func_6b4220(index);
        }
        return old;
    }
    return false;
}
