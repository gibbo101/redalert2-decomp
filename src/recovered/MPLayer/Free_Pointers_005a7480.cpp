// void __fastcall Free_Pointers_005a7480(DynamicVectorClass<NodeNameType *> *list) (0x005A7480)
// TibSun mplayer.cpp's Clear_Vector: deletes every node of the list, then clears it.
#include "shared/lobby.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void __fastcall Free_Pointers_005a7480(DynamicVectorClass<NodeNameType *> *list)
{
    int i;

    for (i = 0; i < list->Count(); i++) {
        delete (*list)[i];
    }
    list->Clear();
}
