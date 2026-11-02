// WOnline's chained hash dictionary template (moved from shared/wol_sink.hpp so the lobby's
// name set, shared/lobby_name_set.hpp, can use it without the WOnline headers).
#ifndef RA2_SHARED_WOL_DICTIONARY_HPP
#define RA2_SHARED_WOL_DICTIONARY_HPP

#include "shared/wstring.hpp"
#include "shared/crt_memory.hpp"

// WOnline's chained hash dictionary (the shape of Westwood's WOL library
// Dictionary<K,V>: table, entries, size, tableBits, log2Size, keepSize,
// hashFunc, then SHRINK_THRESHOLD 0.2, EXPAND_THRESHOLD 0.8 and
// MIN_TABLE_SIZE 128). The file statics' initializers and atexit destructors
// (0x0073AA80..0x0073BC30) inline the constructor and destructor; the
// destructor inlines clear() and shrink().
unsigned int __fastcall Hash_Name_005c2ba0(Wstring const &name);
// Vendor dictionary ABI: sizeof 0x38, eight-byte alignment.
// Original 0073FEE0 proves the local extent; natural padding supplies +0x1C.
#pragma pack(push, 8)
template<class K, class V> class WolDictionary {
public:
    struct Node { K Key; V Value; Node *Next; };
    WolDictionary(unsigned int (__fastcall *hash)(K const &key))
        : ShrinkLimit(0.2), GrowLimit(0.8), MinimumBuckets(0x80)
    {
        unknown_10 = MinimumBuckets;
        BucketCount = MinimumBuckets;
        Bits = 0;
        while (unknown_10) {
            ++Bits;
            unknown_10 >>= 1;
        }
        --Bits;
        BucketCount = 1 << Bits;
        Count = 0;
        ResizeLocked = false;
        Buckets = new Node *[BucketCount];
        memset(Buckets, 0, BucketCount * sizeof(Node *));
        Hash = hash;
    }
    ~WolDictionary()
    {
        for (unsigned int index = 0; index < BucketCount; ++index) {
            Node *node = Buckets[index];
            while (node) {
                Node *old = node;
                node = node->Next;
                delete old;
            }
            Buckets[index] = 0;
        }
        Count = 0;
#ifdef RA2_WOL_DICTIONARY_SHRINK_ACCESSORS
        // wlib clear()'s shrink loop through the size accessors (two more /Ob2 sites after the node
        // deletes: the ownrdraw registry's atexit destructor 0x005DEE00 then calls ??_GWideString 0x00601430).
        while (Get_Size() > Get_Minimum_Size() && Can_Resize()) Shrink_Buckets();
#else
        while (Get_Size() > MinimumBuckets && !ResizeLocked) Shrink_Table();
#endif
        delete [] Buckets;
    }
    unsigned int Get_Size() const { return BucketCount; }
#ifdef RA2_WOL_DICTIONARY_SHRINK_ACCESSORS
    unsigned int Get_Minimum_Size() const { return MinimumBuckets; }
    bool Can_Resize() const { return !ResizeLocked; }
    // wlib shrink()'s body as the inline member the destructor expands (the out-of-line instance of this
    // population, 0x006027E0, is an explicit specialization of Shrink_Table that forwards here; its real
    // out-of-line users, 0x00601C50 and two unrecovered window procedures, are not in the unit yet).
    void Shrink_Buckets()
    {
        if (BucketCount > MinimumBuckets && ResizeLocked != true) {
            int old_count = BucketCount;
            Node **old_buckets = Buckets;
            BucketCount >>= 1;
            --Bits;
            Buckets = new Node *[BucketCount];
            memset(Buckets, 0, BucketCount * sizeof(Node *));
            for (int index = 0; index < old_count; ++index) {
                Node *node = old_buckets[index];
                while (node) {
                    unsigned int hash = Hash(node->Key);
                    unsigned int bucket = ((1u << Bits) - 1) & hash;
                    Node *head = Buckets[bucket];
                    Buckets[bucket] = node;
                    Node *next = node->Next;
                    node->Next = head;
                    node = next;
                }
            }
            delete [] old_buckets;
        }
    }
#endif
    unsigned int Key_Hash(K const &key) const
    {
        unsigned int hash = Hash(key);
        return ((1u << Bits) - 1) & hash;
    }
    bool Get_Pointer(K const &key, V **value) const
    {
        if (Count == 0) return false;
        Node *node = Buckets[Key_Hash(key)];
        if (node == 0) return false;
        while (node != 0 && !(node->Key == key)) node = node->Next;
        if (node == 0) return false;
        *value = &node->Value;
        return true;
    }
    // Copies the value for PCX cache and Wonline buddy-status callers.
    // wlib Dictionary::getValue(key, value): copies the value out when the key is present.
    bool Get_Value(K const &key, V &value) const
    {
        V *pointer = 0;
        bool found = Get_Pointer(key, &pointer);
        if (found && pointer) value = *pointer;
        return found;
    }

    // wlib Dictionary::remove(key, value) (inline; WolChannelNameSet's out-of-line copy is
    // Remove_007675e0).
    bool Remove_Entry(K const &key, V *old_value)
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
    // wlib Dictionary::remove(key).
    bool Remove(K const &key)
    {
        V old_value;
        return Remove_Entry(key, &old_value);
    }
    // wlib Dictionary::contains(key).
    bool Contains(K const &key) const
    {
        for (Node *node = Buckets[Key_Hash(key)]; node != 0; node = node->Next) {
            if (node->Key == key) return true;
        }
        return false;
    }
    // wlib Dictionary::removeAny(key, value): takes out the first entry of the first non-empty bucket.
    bool Remove_Any(K &key, V &value)
    {
        if (Count == 0) return false;
        float load = (float)(Count - 1);
        load /= (float)BucketCount;
        int found = -1;
        for (int index = 0; index < (int)BucketCount; ++index) {
            if (Buckets[index] != 0) {
                found = index;
                break;
            }
        }
        if (found == -1) return false;
        Node *node = Buckets[found];
        key = node->Key;
        value = node->Value;
        Node *next = Buckets[found]->Next;
        delete Buckets[found];
        Buckets[found] = next;
        --Count;
        if (load <= ShrinkLimit) Shrink_Table();
        return true;
    }
    // wlib Dictionary::add without its replacing remove: a new entry at the head of its bucket.
    bool Add(K const &key, V value)
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
        float load = (float)Count;
        load /= (float)Get_Size();
        if (load >= GrowLimit) Grow_Table();
        return true;
    }
    void Grow_Table();
    void Shrink_Table();
    Node **Buckets;
    unsigned int Count;
    unsigned int BucketCount;
    unsigned int Bits;
    unsigned int unknown_10;            // log2Size (scratch of the constructor)
    bool ResizeLocked;
    char unknown_15[3];
    unsigned int (__fastcall *Hash)(K const &key);
    double ShrinkLimit;
    double GrowLimit;
    unsigned int MinimumBuckets;
};

#pragma pack(pop)

// wlib Dictionary::expand and shrink, defined out of the class (explicitly instantiable).
template<class K, class V> void WolDictionary<K, V>::Grow_Table()
{
    if (ResizeLocked != true) {
        int old_count = BucketCount;
        Node **old_buckets = Buckets;
        BucketCount *= 2;
        ++Bits;
        Buckets = new Node *[BucketCount];
        memset(Buckets, 0, BucketCount * sizeof(Node *));
        for (int index = 0; index < old_count; ++index) {
            Node *node = old_buckets[index];
            while (node) {
                unsigned int hash = Hash(node->Key);
                unsigned int bucket = ((1u << Bits) - 1) & hash;
                Node *head = Buckets[bucket];
                Buckets[bucket] = node;
                Node *next = node->Next;
                node->Next = head;
                node = next;
            }
        }
        delete [] old_buckets;
    }
}
template<class K, class V> void WolDictionary<K, V>::Shrink_Table()
{
    if (BucketCount > MinimumBuckets && ResizeLocked != true) {
        int old_count = BucketCount;
        Node **old_buckets = Buckets;
        BucketCount >>= 1;
        --Bits;
        Buckets = new Node *[BucketCount];
        memset(Buckets, 0, BucketCount * sizeof(Node *));
        for (int index = 0; index < old_count; ++index) {
            Node *node = old_buckets[index];
            while (node) {
                unsigned int hash = Hash(node->Key);
                unsigned int bucket = ((1u << Bits) - 1) & hash;
                Node *head = Buckets[bucket];
                Buckets[bucket] = node;
                Node *next = node->Next;
                node->Next = head;
                node = next;
            }
        }
        delete [] old_buckets;
    }
}

#endif
