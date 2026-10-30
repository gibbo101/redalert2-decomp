#include "shared/mono_class.hpp"
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90
void MonoClass::Clear()
{
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            Characters[x][y] = ' ';
            Attributes[x][y] = 0;
        }
    }
    Changed = true;
    Refresh(0, 0, 80, 25);
}
