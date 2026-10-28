// Existing canonical generic body, specialized only for the evidenced original pair types.
#include "shared/ini_class.hpp"
#include "shared/map_region.hpp"
template<> bool IndexClass<int,MapRegionClass *>::Increase_Table_Size(int amount)
{
    if(amount>=0) {
        NodeElement *table=new NodeElement[(int)((unsigned)IndexSize+(unsigned)amount)];
        if(table!=0) {
            for(int index=0;index<IndexCount;index++)table[index]=IndexTable[index];
            delete[] IndexTable;
            IndexTable=table;
            IndexSize=(int)((unsigned)IndexSize+(unsigned)amount);
            Invalidate_Archive();
            return true;
        }
    }
    return false;
}
