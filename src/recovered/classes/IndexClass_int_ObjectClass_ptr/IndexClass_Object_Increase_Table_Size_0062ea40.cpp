// The object-distance index used by Queue.CPP's group destination assignment.
#include "shared/ini_class.hpp"
#include "shared/object.hpp"
template<> bool IndexClass<int,ObjectClass *>::Increase_Table_Size(int amount)
{
    if (amount>=0) {
        NodeElement *table=new NodeElement[IndexSize+amount];
        if (table) {
            for (int index=0;index<IndexCount;++index) table[index]=IndexTable[index];
            delete[] IndexTable;
            IndexTable=table;
            IndexSize+=amount;
            Invalidate_Archive();
            return true;
        }
    }
    return false;
}
