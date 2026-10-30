// Full heap operations, including diagnostics and stream persistence.
#ifndef RA2_SHARED_VEIN_HEAP_HPP
#define RA2_SHARED_VEIN_HEAP_HPP
#include "shared/vein_heap_core.hpp"
#include "shared/debug_printf.hpp"

inline bool UnknownVeinHeap::Remove_Matching(UnknownVeinNode const &item)
{
        for (int index = 1; index <= Count; index++) {
            if (Array[index]->Position == item.Position) {
                if (index == Count) {
                    Count--;
                } else {
                    UnknownVeinNode *last = Array[Count];
                    float key = last->Key;
                    int parent = index >> 1;
                    Count--;
                    if (index != 1 && Array[parent]->Key >= key) {
                        while ((unsigned)index > 1) {
                            if (Array[parent]->Key <= key) {
                                break;
                            }
                            Array[index] = Array[parent];
                            index = parent;
                            parent = index >> 1;
                        }
                        Array[index] = last;
                        for (int check = 1; check <= Count; check++) {
                            if (Array[check] < Lowest || Array[check] > Highest) {
                                volatile int zero = 0;
                                zero = 1 / zero;
                            }
                        }
                    } else {
                        Array[index] = last;
                        Sift_Down(index);
                        for (int check = 1; check <= Count; check++) {
                            if (Array[check] < Lowest || Array[check] > Highest) {
                                volatile int zero = 0;
                                zero = 1 / zero;
                            }
                        }
                    }
                }
                Debug_Printf("Exiting Remove_Matching\n");
                return true;
            }
        }
        Debug_Printf("Exiting Remove_Matching\n");
        return false;
    }

inline bool UnknownVeinHeap::Load(IStream *stream, UnknownVeinNode *nodes)
{
        if (FAILED(stream->Read(&Count, sizeof(Count), 0))) {
            return false;
        }
        if (FAILED(stream->Read(&Capacity, sizeof(Capacity), 0))) {
            return false;
        }
        for (int slot = 0; slot < Capacity; slot++) {
            int index;
            if (FAILED(stream->Read(&index, sizeof(index), 0))) {
                return false;
            }
            Array[slot] = &nodes[index];
        }
        return true;
    }

inline bool UnknownVeinHeap::Save(IStream *stream, UnknownVeinNode *nodes)
{
        if (FAILED(stream->Write(&Count, sizeof(Count), 0))) {
            return false;
        }
        if (FAILED(stream->Write(&Capacity, sizeof(Capacity), 0))) {
            return false;
        }
        for (int index = 0; index < Capacity; index++) {
            int node = Array[index] - nodes;
            if (FAILED(stream->Write(&node, sizeof(node), 0))) {
                return false;
            }
        }
        return true;
    }

#endif
