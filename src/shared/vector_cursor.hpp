// VectorCursor<T, V>: a polymorphic position in a (Dynamic)VectorClass
// (RTTI names, e.g. VectorCursor<rc_ptr<WorldDominationTour::Conflict>,
// DynamicVectorClass<rc_ptr<WorldDominationTour::Conflict>>> vtable
// 0x007AF054: slot 0 the scalar deleting destructor 0x00726B20, slot 1
// 0x00726AB0, slot 2 0x00726EF0, slot 3 0x00726F00).
//
// Layout: +0x00 vptr, +0x04 V *Vector, +0x08 Index. Slot 1 tests
// Index < Vector->Count() (unsigned), slot 2 increments and slot 3
// decrements the index, both returning the cursor. Names are hypotheses.
#ifndef RA2_SHARED_VECTOR_CURSOR_HPP
#define RA2_SHARED_VECTOR_CURSOR_HPP

template <class T, class V>
class VectorCursor {
public:
    // The index argument shows where the constructor goes out of line: the copies
    // 0x00730340/0x00730370 (WDTSel.cpp) store it and the callers push 0.
    VectorCursor(V &vector, unsigned index = 0) : Vector(&vector), Index(index) {}
    virtual ~VectorCursor() {}
    virtual bool Valid() const { return Index < (unsigned)Vector->Count(); }
    virtual VectorCursor<T, V> &Next()
    {
        Index++;
        return *this;
    }
    virtual VectorCursor<T, V> &Prev()
    {
        Index--;
        return *this;
    }

    T &Current() const { return (*Vector)[Index]; }

    // Iterator spelling; the slots stay virtual calls through these (Conflict::
    // Describe_Options 0x00727960 calls Valid/Next through the vtable).
    operator bool() const { return Valid(); }
    VectorCursor<T, V> &operator++() { return Next(); }
    VectorCursor<T, V> &operator--() { return Prev(); }
    T &operator*() const { return Current(); }

    V *Vector;          // +0x04
    unsigned Index;     // +0x08
};

#endif
