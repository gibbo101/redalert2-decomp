#include "shared/wol_sink.hpp"
// @ref ??_GWstring@@QAEPAXI@Z=007667c0
void Refresh_Buddy_Status_007570e0();
void Reset_Buddy_Name_List_00757530();
inline void WolNameTable::Clear_007662f0()
{
    unsigned int index;
    for (index = 0; index < BucketCount; index++) {
        Node *node = Buckets[index];
        while (node != 0) {
            Node *old = node;
            node = node->Next;
            if (old) delete old;
        }
        Buckets[index] = 0;
    }
    Count = 0;
    while (Get_Size() > MinimumBuckets && ResizeLocked == false) Shrink_Table();
}

inline void WolChannelDictionary::Clear_00766400()
{
    unsigned int index;
    for (index = 0; index < BucketCount; index++) {
        Node *node = Buckets[index];
        while (node != 0) {
            Node *old = node;
            node = node->Next;
            if (old) delete old;
        }
        Buckets[index] = 0;
    }
    Count = 0;
    while (Get_Size() > MinimumBuckets && ResizeLocked == false) Shrink_Table();
}

inline void Restart_Buddy_Requests()
{
    unknown_chat_a72cfc->unknown_slot55();
    if (!Is_Online_Session()) Refresh_Buddy_Status_007570e0();
    Reset_Buddy_Name_List_00757530();
}

void __fastcall Reset_Buddy_State_00757720()
{
    unknown_strings_b26920.Clear();
    unknown_strings_b29838.Clear();
    unknown_names_b29848.Clear_007662f0();
    unknown_channels_b29478.Clear_00766400();
    Restart_Buddy_Requests();
}
