// UnknownGrowArray<T>: a plain growable array without a vtable, found in two
// out-of-line copies for 8-byte elements (0x004F8C60 in House.cpp's neighbourhood,
// 0x004C25B0 next to FoggedObjectClass). Layout from Grow: the element pointer, the
// used count, the capacity, one untouched word and a word Grow resets. Names and
// the Westwood origin are hypotheses.
//
// A user-provided element constructor is needed: `new T[n]` then keeps the
// dead `n - 1` loop counter store the original has.
#ifndef RA2_SHARED_UNKNOWN_GROW_ARRAY_HPP
#define RA2_SHARED_UNKNOWN_GROW_ARRAY_HPP

// An 8-byte element with an (empty) constructor.
struct UnknownGrowElement8 {
    int unknown_00;
    int unknown_04;
    UnknownGrowElement8() {}
};

template <class T>
struct UnknownGrowArray {
    T *Vector;                  // +0x00
    int Count;                  // +0x04 elements in use
    int Capacity;               // +0x08
    int unknown_0c;             // +0x0C
    int unknown_10;             // +0x10 (Grow clears it)

    // A larger allocation: the used elements move there and Capacity grows by amount
    // (false for a negative amount or when the allocation fails).
    bool Grow(int amount);
};

template <class T>
bool UnknownGrowArray<T>::Grow(int amount)
{
    if (amount >= 0) {
        T *array = new T[Capacity + amount];
        if (array != 0) {
            for (int index = 0; index < Count; index++) {
                array[index] = Vector[index];
            }
            delete [] Vector;
            Vector = array;
            Capacity += amount;
            unknown_10 = 0;
            return true;
        }
    }
    return false;
}

#endif
