// char const *TActionClass::Get_Text() const (0x006B2F20)
#include "shared/object.hpp"

char const *TActionClass::Get_Text() const
{
    return Text[0] ? Text : 0;
}
