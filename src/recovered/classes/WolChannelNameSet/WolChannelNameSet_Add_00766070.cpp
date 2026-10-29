#include "shared/wol_sink.hpp"
bool WolChannelNameSet::Add_00766070(Wstring const &key, int const &value)
{
    Node *node = new Node;
    node->Key = key;
    node->Value = value;
    node->Next = 0;
    unsigned int bucket = Key_Hash(key);
    Node *head = Buckets[bucket];
    Buckets[bucket] = node;
    if (head) node->Next = head;
    ++Count;
    if ((float)Count / (float)Get_Size() >= GrowLimit) Grow_Table();
    return true;
}
