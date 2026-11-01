// @ref ?Get_Char@WideString@@QBEGI@Z=00770470
#include "shared/ms_anim.hpp"
int MSPrintAnim::Line_Width(WideString const &line)
{
    int i = 0;
    int width = 0;
    while (line.Get_Char(i) != 0 && line.Get_Char(i) != '\n') {
        width += Font->Char_Width(line.Get_Char(i));
        i++;
    }
    return width;
}

