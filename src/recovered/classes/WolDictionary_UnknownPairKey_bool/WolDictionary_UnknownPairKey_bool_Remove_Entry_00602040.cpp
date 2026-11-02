// 00602040: pair-keyed active-message dictionary removal,607 code bytes +1 padding.
// Explicit specialization stands in for the unrecovered CtrlProc005ee460 caller.
// The original copies a one-byte value from node+8 and links at node+12.
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"
template<> bool WolDictionary<OwnerDraw::UnknownPairKey, bool>::Remove_Entry(OwnerDraw::UnknownPairKey const &key, bool *old_value)
{
        if (Count == 0) return false;
        float load = (float)(Count - 1);
        load /= (float)BucketCount;
        unsigned int bucket = Key_Hash(key);
        Node *head = Buckets[bucket];
        Node *previous = head;
        if (!head) return false;
        if (head->Key == key) {
            *old_value = head->Value;
            Node *removed = Buckets[bucket];
            Node *next = removed->Next;
            delete removed;
            Buckets[bucket] = next;
            --Count;
            if (load <= ShrinkLimit) Shrink_Table();
            return true;
        }
        Node *node = head->Next;
        bool removed = false;
        while (node) {
            if (node->Key == key) {
                *old_value = node->Value;
                previous->Next = node->Next;
                --Count;
                delete node;
                removed = true;
                break;
            }
            previous = node;
            node = node->Next;
        }
        if (load <= ShrinkLimit) Shrink_Table();
        return removed;
    }
// @ref ?Key_Hash@?$WolDictionary@UUnknownPairKey@OwnerDraw@@_N@@QBEIABUUnknownPairKey@OwnerDraw@@@Z=00602340
// @ref ?Shrink_Table@?$WolDictionary@UUnknownPairKey@OwnerDraw@@_N@@QAEXXZ=00602890
