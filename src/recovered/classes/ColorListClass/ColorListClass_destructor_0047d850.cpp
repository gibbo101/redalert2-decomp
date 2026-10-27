// ColorListClass::~ColorListClass() (0x0047D850)
#include "shared/color_list.hpp"
// @ref ??1ListClass@@UAE@XZ=00539fc0
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??3@YAXPAX@Z=00781d3b

ColorListClass::~ColorListClass()
{
    Colors.Clear();
    SelectColor = 0;
}
