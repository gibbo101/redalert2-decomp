#include "shared/wol_sink.hpp"
template<> bool WolArrayList<Wstring>::Remove_007661f0(int index)
{
    if(Count==0) return false;
    if(index<0) index=0;
    if(index>=Count) index=Count-1;
    (Items+index)->~Wstring();
    memmove(Items+index,Items+index+1,sizeof(Wstring)*(Count-index-1));
    --Count;
    if(Count*3<=Capacity) {
        int capacity=Capacity/2;
        if(capacity<10) capacity=10;
        if(capacity<Capacity) {
            Wstring *items=(Wstring *)operator new(capacity*sizeof(Wstring));
            if(Items) memcpy(items,Items,Count*sizeof(Wstring));
            operator delete(Items);
            Items=items;
            Capacity=capacity;
        }
    }
    return true;
}
