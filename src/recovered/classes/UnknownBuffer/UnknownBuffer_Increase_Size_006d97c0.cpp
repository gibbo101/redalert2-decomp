// Grow the existing signed-key voxel-cache node table.
#include "shared/techno.hpp"
bool UnknownBuffer::Increase_Size_006d97c0(int amount)
{
    if(amount>=0) {
        NodeElement *table=new NodeElement[unknown_08+amount];
        if(table) {
            for(int index=0;index<unknown_04;++index) table[index]=static_cast<NodeElement *>(unknown_00)[index];
            delete[] static_cast<NodeElement *>(unknown_00);
            unknown_00=table;
            unknown_08+=amount;
            unknown_10=0;
            return true;
        }
    }
    return false;
}
