// The priority queue of map cells the veinhole monsters and the tiberium types
// grow and spread through (TS/YR's PriorityQueueClass<MapSurfaceData>: a binary
// min-heap of node pointers ordered by the node's float). Moved out of
// shared/veinhole.hpp so shared/tiberium.hpp can use it.
#ifndef RA2_SHARED_VEIN_HEAP_CORE_HPP
#define RA2_SHARED_VEIN_HEAP_CORE_HPP

#include "shared/coord.hpp"
struct IStream;

// One vein node (8 bytes; the rules' +0xD4 of them per monster; the heap
// orders them by the float at +4; hypothesis).
struct UnknownVeinNode {
    UnknownVeinNode() {}
    UnknownVeinNode(::Cell const &cell) : Position(cell) {}
    ::Cell Position;                        // +0x00 the vein cell
    float Key;                              // +0x04
};

// A min-heap of vein nodes (0x14 bytes; 1-based array of Capacity + 1
// pointers, built inline by the constructor 0x0070F820; hypothesis).
class UnknownVeinHeap {
public:
    ~UnknownVeinHeap() { delete[] Array; }
    UnknownVeinHeap(int capacity)
    {
        Highest = 0;
        Lowest = (UnknownVeinNode *)-1;
        Count = 0;
        Capacity = capacity;
        Array = new UnknownVeinNode *[Capacity + 1];
        for (int index = 0; index <= Capacity; index++) {
            Array[index] = 0;
        }
    }
#ifdef RA2_VEIN_HEAP_CLEAR_SOURCE
    void Clear();                           // own out-of-line provider0x00712A10
#else
    void Clear()                            // out-of-line copy 0x00712A10
    {
        for (int index = 0; index <= Count; index++) {
            Array[index] = 0;
        }
        Count = 0;
    }
#endif
    // Sifts the node up to its place by Key (inlined by 0x00711AA0).
    void Insert(UnknownVeinNode *node)
    {
        unsigned index = Count + 1;
        unsigned parent = index >> 1;
        float key = node->Key;
        if (index < (unsigned)Capacity) {
            while (index > 1) {
                if (Array[parent]->Key <= key) {
                    break;
                }
                Array[index] = Array[parent];
                index = parent;
                parent = index >> 1;
            }
            Array[index] = node;
            Count++;
            if (node > Highest) {
                Highest = node;
            }
            if (node < Lowest) {
                Lowest = node;
            }
        }
    }
    // Restores the heap order below index (out-of-line copy 0x0058F090;
    // expanded twice by 0x00710FF0).
    void Sift_Down(int index)
    {
        int left = index << 1;
        int right = index * 2 + 1;
        int child = left <= Count && Key_At(left) < Key_At(index) ? left : index;
        if (right <= Count && Key_At(right) < Key_At(child)) {
            child = right;
        }
        while (child != index) {
            UnknownVeinNode *swap = Array[index];
            Array[index] = Array[child];
            Array[child] = swap;
            index = child;
            left = index << 1;
            right = index * 2 + 1;
            if (left <= Count && Key_At(left) < Key_At(child)) {
                child = left;
            }
            if (right <= Count && Key_At(right) < Key_At(child)) {
                child = right;
            }
        }
    }
    float Key_At(int index) const { return Array[index]->Key; }
    int Active_Count() const { return Count; }
    // Takes the node at the item's cell out of the heap (inlined by
    // 0x00712300).
    // Each repair is followed by a check that faults when a slot points
    // outside the nodes ever inserted.
    bool Remove_Matching(UnknownVeinNode const &item);
    // Reads what Save writes, turning each node index back into a pointer
    // (inlined by Load_All 0x00711E60).
    bool Load(IStream *stream, UnknownVeinNode *nodes);
    // Writes the count, the capacity and each slot as a node index (inlined by
    // Save_All 0x00712150, which ignores the result).
    bool Save(IStream *stream, UnknownVeinNode *nodes);
    // Takes the node with the lowest Key off the heap.
#ifdef RA2_VEIN_HEAP_REMOVE_MIN_IMPLEMENTATION
    UnknownVeinNode *Remove_Min();
#else
    UnknownVeinNode *Remove_Min()
    {
        if (Count == 0) {
            return 0;
        }
        UnknownVeinNode *top = Array[1];
        Array[1] = Array[Count];
        Array[Count] = 0;
        Count--;
        Sift_Down(1);
        return top;
    }
#endif
    int Count;                              // +0x00
    int Capacity;                           // +0x04
    UnknownVeinNode **Array;                // +0x08
    UnknownVeinNode *Highest;               // +0x0C the highest node address inserted
    UnknownVeinNode *Lowest;                // +0x10 the lowest (-1 when empty)
};

#endif
