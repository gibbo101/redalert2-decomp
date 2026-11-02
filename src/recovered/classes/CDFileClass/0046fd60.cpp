#define CD_FILE_DECLARE_WSTRING_CTOR
#include "shared/cd_file_class.hpp"
#include "shared/wstring.hpp"
CDFileClass::CDFileClass(Wstring const &filename) : IsDisabled(false)
{
    CDFileClass::Set_Name(filename.Peek_Buffer());
}
