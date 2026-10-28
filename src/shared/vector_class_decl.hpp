// VectorClass<T> and DynamicVectorClass<T> declarations only (the layout and
// the member list; shared/vector_class.hpp documents them and holds the
// member definitions).
//
// A class with a container member includes this header instead of
// shared/vector_class.hpp, so that the member definitions a translation unit
// gets stay selected by that unit's own VECTOR_IMPLEMENT_* guards at its
// first inclusion of shared/vector_class.hpp (UnknownIDSource's TypeList
// members, shared/id_source.hpp, which shared/abstract.hpp includes early).

#ifndef SHARED_VECTOR_CLASS_DECL_HPP
#define SHARED_VECTOR_CLASS_DECL_HPP

class NoInitClass;

template <class T>
class VectorClass {
public:
    VectorClass(NoInitClass const &noinit);
    VectorClass(unsigned size = 0, T const *array = 0);
    VectorClass(VectorClass<T> const &vector);
    virtual ~VectorClass();

    T &operator[](unsigned index);
    T const &operator[](unsigned index) const;
    int Length() const;

    // Not virtual in RA2: the vtables have no assignment slot.
    VectorClass<T> &operator=(VectorClass<T> const &vector);

    virtual bool operator==(VectorClass<T> const &vector) const;
    virtual bool Resize(int newsize, T const *array = 0);
    virtual void Clear();
    virtual int ID(T const *ptr);
    virtual int ID(T const &object);
    virtual T Fetch(int index) const;

protected:
    T *Vector;
    int VectorMax;
    bool IsValid;
    bool IsAllocated;
};

template <class T>
class DynamicVectorClass : public VectorClass<T> {
public:
    DynamicVectorClass(NoInitClass const &noinit);
    DynamicVectorClass(unsigned size = 0, T const *array = 0);

    int Count() const;
    DynamicVectorClass<T> &operator=(DynamicVectorClass<T> const &rvalue);
    // Capacity increment for later growth (inlined into the map's hash-table
    // construction, MapClass::One_Time 0x005480D0).
    void Set_Growth_Step(int step);

    virtual bool Resize(int newsize, T const *array = 0);
    virtual void Clear();
    virtual int ID(T const *ptr);
    virtual int ID(T const &object);

    bool Add(T const &object);
    bool Add_Head(T const &object);
    bool Add_After(T const &object, T const &after);
    bool Delete(T const &object);
    bool Delete(int index);

protected:
    int ActiveCount;
    int GrowthStep;
};

#endif
