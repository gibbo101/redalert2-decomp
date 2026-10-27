// RawFileClass::RawFileClass(char const *) (0x00638B40)
// Creates a closed, unbiased file object. The name is referenced, not copied
// (Allocated stays false), unlike Set_Name().
#include "shared/raw_file_class.hpp"

RawFileClass::RawFileClass(char const *filename) :
    Rights(0),
    BiasStart(0),
    BiasLength(-1),
    Handle(INVALID_HANDLE_VALUE),
    Filename(filename),
    Date(0),
    Time(0),
    Allocated(false)
{
}
