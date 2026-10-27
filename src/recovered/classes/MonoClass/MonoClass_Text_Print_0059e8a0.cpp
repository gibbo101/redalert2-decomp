// void MonoClass::Text_Print(char const *text, int x, int y, int attribute) (0x0059E8A0)
// Puts the cursor at a place, picks the attribute and prints.
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?Print@MonoClass@@QAEXPBD@Z=0059e6d0

void MonoClass::Text_Print(char const *text, int x, int y, int attribute)
{
    if (unknown_mono_enabled_a70f0a) {
        Set_Cursor(x, y);
        Set_Attribute(attribute);
        Print(text);
    }
}
