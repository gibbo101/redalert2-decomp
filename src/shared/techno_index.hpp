// The techno ID index (0x00ABFF58) shared by Building.CPP, Unit.cpp and the
// other techno units (moved out of shared/building.hpp).
#ifndef RA2_SHARED_TECHNO_INDEX_HPP
#define RA2_SHARED_TECHNO_INDEX_HPP

#include "shared/techno.hpp"

#include "shared/ini_class.hpp"     // qsort, Binary_Search

// An ID-to-object index like IndexClass (shared/ini_class.hpp) but without
// the last-hit archive lookup and with a hand-written binary search
// (Increase_Table_Size 0x0041B900, Search_For_Node 0x0041B990 and the qsort
// comparison 0x0041BA10 are kept in another unit; names hypotheses).
template<class INDEX, class T>
class UnknownIndexClass {
public:
    struct NodeElement {
        NodeElement() {}
        INDEX ID;
        T Data;
    };

    bool Increase_Table_Size(int amount);
    bool Add_Index(INDEX const &id, T const &data)
    {
        if (IndexCount + 1 > IndexSize) {
            if (!Increase_Table_Size(IndexSize == 0 ? 10 : IndexSize)) {
                return false;
            }
        }
        IndexTable[IndexCount].ID = id;
        IndexTable[IndexCount].Data = data;
        IndexCount++;
        IsSorted = false;
        return true;
    }
    bool Remove_Index(INDEX const &id)
    {
        int found_index = -1;
        NodeElement const *node = Search_For_Node(id);
        if (node != 0) {
            found_index = node - IndexTable;
        }
        if (found_index != -1) {
            for (int index = found_index + 1; index < IndexCount; index++) {
                IndexTable[index - 1] = IndexTable[index];
            }
            IndexCount--;
            NodeElement empty;
            empty.ID = 0;
            empty.Data = 0;
            IndexTable[IndexCount] = empty;
            Invalidate_Archive();
            return true;
        }
        return false;
    }
    void Invalidate_Archive() { Archive = 0; }
    NodeElement const *Search_For_Node(INDEX const &id);  // 0x0041B990
    static int __cdecl search_compfunc(void const *left, void const *right);   // 0x0041BA10

    NodeElement *IndexTable;        // +0x00
    int IndexCount;                 // +0x04
    int IndexSize;                  // +0x08
    bool IsSorted;                  // +0x0C
    NodeElement const *Archive;     // +0x10
};

template<class INDEX, class T>
bool UnknownIndexClass<INDEX, T>::Increase_Table_Size(int amount)
{
    if (amount >= 0) {
        NodeElement *table = new NodeElement[IndexSize + amount];
        if (table != 0) {
            for (int index = 0; index < IndexCount; index++) {
                table[index] = IndexTable[index];
            }
            delete[] IndexTable;
            IndexTable = table;
            IndexSize += amount;
            Archive = 0;
            return true;
        }
    }
    return false;
}

// Sorts the table if needed, then binary searches it for the ID.
template<class INDEX, class T>
typename UnknownIndexClass<INDEX, T>::NodeElement const *UnknownIndexClass<INDEX, T>::Search_For_Node(INDEX const &id)
{
    if (IndexCount == 0) {
        return 0;
    }
    if (!IsSorted) {
        qsort(&IndexTable[0], IndexCount, sizeof(IndexTable[0]), search_compfunc);
        Invalidate_Archive();
        IsSorted = true;
    }
    NodeElement node;
    node.ID = id;
    return Binary_Search(IndexTable, IndexCount, node);
}

// qsort comparator: orders records by ID (signed).
template<class INDEX, class T>
int __cdecl UnknownIndexClass<INDEX, T>::search_compfunc(void const *left, void const *right)
{
    if (*(INDEX const *)left == *(INDEX const *)right) {
        return 0;
    }
    if (*(INDEX const *)left < *(INDEX const *)right) {
        return -1;
    }
    return 1;
}

// The techno index keyed by Fetch_ID (0x00ABFF58; its constructor runs at
// 0x006B5440).
extern UnknownIndexClass<long, ObjectClass *> unknown_object_index_abff58;

#endif
