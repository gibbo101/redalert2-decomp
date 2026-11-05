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
#ifdef VECTOR_CURSOR_REFERENCE_FORM
    struct CountHelper {
        static unsigned Count(VectorClass<T> const &vector) { return vector.Length(); }
        static unsigned Count(DynamicVectorClass<T> const &vector) { return vector.Count(); }
    };
#endif
    // The index argument shows where the constructor goes out of line: the copies
    // 0x00730340/0x00730370 (WDTSel.cpp) store it and the callers push 0.
#ifdef VECTOR_CURSOR_REFERENCE_FORM
    VectorCursor(V &vector);
    VectorCursor(V &vector, int index);
    VectorCursor &operator=(VectorCursor const &other);
#else
#ifdef VECTOR_CURSOR_OUT_OF_CLASS_CONSTRUCTOR
    VectorCursor(V &vector, unsigned index = 0);
#else
    VectorCursor(V &vector, unsigned index = 0) : Vector(&vector), Index(index) {}
#endif
#endif
    virtual ~VectorCursor() {}
#ifdef VECTOR_CURSOR_VIRTUAL_OPERATORS
    virtual operator bool() const {
#else
    virtual bool Valid() const {
#endif
#ifdef VECTOR_CURSOR_REFERENCE_FORM
        return Index < CountHelper::Count(*Vector);
#else
        return Index < (unsigned)Vector->Count();
#endif
    }
#ifdef VECTOR_CURSOR_VIRTUAL_OPERATORS
    virtual VectorCursor<T, V> &operator++()
#else
    virtual VectorCursor<T, V> &Next()
#endif
    {
        Index++;
        return *this;
    }
#ifdef VECTOR_CURSOR_VIRTUAL_OPERATORS
    virtual VectorCursor<T, V> &operator--()
#else
    virtual VectorCursor<T, V> &Prev()
#endif
    {
        Index--;
        return *this;
    }

    T &Current() const { return (*Vector)[Index]; }

    // Iterator spelling; the slots stay virtual calls through these (Conflict::
    // Describe_Options 0x00727960 calls Valid/Next through the vtable).
#ifdef VECTOR_CURSOR_VIRTUAL_OPERATORS
    VectorCursor<T, V> &operator++(int) { return ++(*this); }
    VectorCursor<T, V> &operator--(int) { return --(*this); }
#else
    operator bool() const { return Valid(); }
    VectorCursor<T, V> &operator++() { return Next(); }
    VectorCursor<T, V> &operator--() { return Prev(); }
#endif
    T &operator*() const { return Current(); }

    V *Vector;          // +0x04
    unsigned Index;     // +0x08
};


#ifdef VECTOR_CURSOR_REFERENCE_FORM
template<class T, class V>
VectorCursor<T,V>::VectorCursor(V &vector) : Vector(&vector), Index(0) {}
template<class T, class V>
VectorCursor<T,V>::VectorCursor(V &vector, int index) : Vector(&vector), Index(index) {}
template<class T, class V>
VectorCursor<T,V> &VectorCursor<T,V>::operator=(VectorCursor const &other)
{
    VectorCursor copy(*other.Vector, other.Index);
    Vector = copy.Vector;
    Index = copy.Index;
    return *this;
}
#endif

#if defined(VECTOR_CURSOR_OUT_OF_CLASS_CONSTRUCTOR) && !defined(VECTOR_CURSOR_REFERENCE_FORM)
template<class T, class V>
VectorCursor<T,V>::VectorCursor(V &vector, unsigned index) : Vector(&vector), Index(index) {}
#endif

#endif
