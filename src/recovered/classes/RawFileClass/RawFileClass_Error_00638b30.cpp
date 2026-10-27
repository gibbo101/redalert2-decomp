// RawFileClass::Error (0x00638B30, virtual slot 16)
// RawFileClass ignores errors; derived classes (CCFileClass) override this to
// report them.
#include "shared/raw_file_class.hpp"

void RawFileClass::Error(int, int, char const *)
{
}
