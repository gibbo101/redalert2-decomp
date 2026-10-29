// char const *Description_From_Category(CategoryType category) -- 0x00468EA0
// The category's description ("Armored Fighting Vehicle"), "<none>" out of range.
// @ref ?CategoryNames@@3PAUCategoryNameStruct@@A=007d17e0
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
#include "shared/ini_enums.hpp"
#include "shared/crt_string.hpp"

char const *__fastcall Description_From_Category(CategoryType category)
{
    if ((unsigned)category < CATEGORY_COUNT) {
        return CategoryNames[category].Description;
    }
    return "<none>";
}
