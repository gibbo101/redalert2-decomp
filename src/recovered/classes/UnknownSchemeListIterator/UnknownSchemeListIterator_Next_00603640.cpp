// DynamicVectorClass<ColorScheme *> *UnknownSchemeListIterator::Next() (0x00603640; Set_Scheme_Lighting
// 0x00520A80 and Set_Lighting 0x00520B00 walk the table with it): the scheme list of the table's next non-empty
// key, null at the end. The table's Next and Find expand inline; Find goes through the global again.
#define RA2_HASH_STRING_UNIT
#include "shared/scheme_table.hpp"
// @ref ?unknown_scheme_table_a76414@@3PAVSchemeTable@@A=00a76414

DynamicVectorClass<ColorScheme *> *UnknownSchemeListIterator::Next()
{
    HashTableClass<HashString, SchemeNode *> *table = unknown_scheme_table_a76414->Table;
    HashString *key = table->Next(*this);
    if (key == 0) {
        return 0;
    }
    SchemeNode **node = unknown_scheme_table_a76414->Table->Find(*key);
    if (node == 0) {
        return 0;
    }
    return (*node)->Schemes;
}
