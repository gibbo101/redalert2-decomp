// Westwood container templates: VectorClass<T> and DynamicVectorClass<T>
// (TypeList<T> is in shared/type_list.hpp).
//
// Evidence: RTTI names 192 VectorClass<...>, 166 DynamicVectorClass<...> and
// 14 TypeList<...> vtables in the base RA2 executable (SHA256 e6418111...).
// Every vtable has seven slots. The layout and slot behaviour below were read
// from the AnimTypeClass * instantiation (vtables 0x007A3B5C VectorClass,
// 0x007A3B7C DynamicVectorClass, 0x007A3B3C TypeList) and confirmed by
// byte-exact recompilation across many element types. The linker did not
// fold identical instantiations: each original translation unit kept its own
// COMDAT copies, so one class can own several vtable copies
// (VectorClass<AnimTypeClass *> has 0x007A2844 and 0x007A3B5C) and the same
// machine code recurs once per (translation unit, element type).
//
// Member names follow Westwood's published container conventions (Resize,
// Clear, ID, Add, Delete, ActiveCount, GrowthStep). They are naming
// hypotheses checked against behaviour only; original symbol names are not
// recovered. Slot 6 (`Fetch`) is a placeholder name for a by-value element
// read whose original name is unknown.
//
// Layout (32-bit, /Zp4):
//   VectorClass<T>
//     +0x00  vtable pointer
//     +0x04  T *Vector        element storage (owned when IsAllocated)
//     +0x08  int VectorMax    capacity in elements (signed compares)
//     +0x0C  bool IsValid     false only while Resize allocates; both ID
//                             lookups return 0 when false
//     +0x0D  bool IsAllocated Vector came from operator new and is freed
//     +0x0E  2 bytes alignment padding, never written
//   DynamicVectorClass<T> : VectorClass<T>
//     +0x10  int ActiveCount  number of used elements
//     +0x14  int GrowthStep   capacity increment (constructors set 10)
//   TypeList<T> : DynamicVectorClass<T>   (no fields of its own)
//
// Virtual interface (slot order, same in all three vtables):
//   0  scalar deleting destructor
//   1  bool operator==(VectorClass<T> const &) const   (never overridden)
//   2  bool Resize(int newsize, T const *array)
//   3  void Clear()
//   4  int  ID(T const &object)
//   5  int  ID(T const *ptr)
//   6  T    Fetch(int index) const                     (never overridden)
// DynamicVectorClass overrides slots 2-5; TypeList only the destructor.
// VC6 groups overloaded virtuals in reverse declaration order, so
// ID(T const *) is declared before ID(T const &).
//
// Compiling one member at a time
// ------------------------------
// VC6 ignores explicit instantiation of a single member function, and a
// whole-class explicit instantiation (`template class X<T>;`) emits every
// member whose definition is visible. Member definitions are therefore
// grouped below under VECTOR_IMPLEMENT_<CLASS>_<MEMBER> guards (or
// VECTOR_IMPLEMENT_ALL for ordinary users). A recovery source defines the
// guard of its one member, includes this header and explicitly instantiates
// the class; only that member is emitted (no vtable, no other members).
// Bodies access fields directly instead of through inline accessors so no
// accessor copy is emitted either.

#ifndef SHARED_VECTOR_CLASS_HPP
#define SHARED_VECTOR_CLASS_HPP

// "No suitable definition provided for explicit template instantiation":
// expected for every member whose guard is off.
#pragma warning(disable : 4661)

#include "shared/crt_string.hpp"

// Placement form used for caller-supplied storage (no allocation).
inline void *operator new(unsigned int, void *pointer)
{
    return pointer;
}

// Tag selecting the constructors that only install the vtable.
class NoInitClass {
public:
    void operator()() const {}
};

#include "shared/vector_class_decl.hpp"


#ifdef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_NOINIT_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_COPY_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_SET_GROWTH_STEP
#define VECTOR_IMPLEMENT_DYNAMIC_NOINIT_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_ADD_HEAD
#define VECTOR_IMPLEMENT_DYNAMIC_ADD_AFTER
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#endif

// Derived constructors inline the base constructor and destructors;
// overridden members inline their base version (a qualified call).
#ifdef VECTOR_IMPLEMENT_DYNAMIC_NOINIT_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_NOINIT_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#endif
#ifdef VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#endif
#ifdef VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#endif
#ifdef VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#endif
#ifdef VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#endif
#ifdef VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#endif
#ifdef VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#endif

// ---------------------------------------------------------------- VectorClass

#ifdef VECTOR_IMPLEMENT_VECTOR_ACCESSORS
template <class T>
inline T &VectorClass<T>::operator[](unsigned index)
{
    return Vector[index];
}

template <class T>
inline T const &VectorClass<T>::operator[](unsigned index) const
{
    return Vector[index];
}

template <class T>
inline int VectorClass<T>::Length() const
{
    return VectorMax;
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_NOINIT_CONSTRUCTOR
// Installs the vtable only (objects restored in place).
template <class T>
VectorClass<T>::VectorClass(NoInitClass const &)
{
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR

// Empty storage of `size` elements: uses `array` in place without owning it
// when supplied, otherwise allocates and owns. A zero size ignores `array`.
template <class T>
VectorClass<T>::VectorClass(unsigned size, T const *array)
    : Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
    if (size) {
        if (array) {
            Vector = new ((void *)array) T[size];
        } else {
            Vector = new T[size];
            IsAllocated = true;
        }
    }
}

#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_COPY_CONSTRUCTOR
// Deep copy through the (non-virtual) assignment operator.
template <class T>
VectorClass<T>::VectorClass(VectorClass<T> const &vector)
    : Vector(0), VectorMax(0), IsValid(true), IsAllocated(false)
{
    *this = vector;
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
// Releases owned storage (the base Clear, never an override).
template <class T>
VectorClass<T>::~VectorClass()
{
    VectorClass<T>::Clear();
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_ASSIGN
// Replaces the contents with an owned copy of `vector`'s whole capacity.
template <class T>
VectorClass<T> &VectorClass<T>::operator=(VectorClass<T> const &vector)
{
    if (this != &vector) {
        Clear();
        VectorMax = vector.VectorMax;
        if (VectorMax) {
            Vector = new T[VectorMax];
            if (Vector) {
                IsAllocated = true;
                for (int index = 0; index < VectorMax; index++) {
                    Vector[index] = vector.Vector[index];
                }
            }
        } else {
            Vector = 0;
            IsAllocated = false;
        }
    }
    return *this;
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_EQUAL
// Slot 1: same capacity and equal elements over the whole capacity.
template <class T>
bool VectorClass<T>::operator==(VectorClass<T> const &vector) const
{
    if (VectorMax == vector.VectorMax) {
        for (int index = 0; index < VectorMax; index++) {
            if (Vector[index] != vector.Vector[index]) {
                return false;
            }
        }
        return true;
    }
    return false;
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_RESIZE
// Slot 2: changes the capacity, keeping min(old, new) leading elements.
// Zero frees everything through the virtual Clear(). Supplied storage is used
// in place and not owned. Returns false only when allocation fails, leaving
// the old storage untouched (IsValid is restored first).
template <class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
    if (newsize) {
        T *newptr;
        IsValid = false;
        if (!array) {
            newptr = new T[newsize];
        } else {
            newptr = new ((void *)array) T[newsize];
        }
        IsValid = true;
        if (!newptr) {
            return false;
        }
        if (Vector) {
            int copycount = (newsize < VectorMax) ? newsize : VectorMax;
            for (int index = 0; index < copycount; index++) {
                newptr[index] = Vector[index];
            }
            if (IsAllocated) {
                delete[] Vector;
                Vector = 0;
            }
        }
        Vector = newptr;
        VectorMax = newsize;
        IsAllocated = (Vector && !array);
    } else {
        Clear();
    }
    return true;
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_CLEAR
// Slot 3: frees owned storage and forgets the capacity.
template <class T>
void VectorClass<T>::Clear()
{
    if (Vector && IsAllocated) {
        delete[] Vector;
        Vector = 0;
    }
    IsAllocated = false;
    VectorMax = 0;
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_ID_POINTER
// Slot 5: index of the element at `ptr` (unsigned byte distance divided by
// the element size); 0 while invalid. No range check.
template <class T>
int VectorClass<T>::ID(T const *ptr)
{
    if (!IsValid) {
        return 0;
    }
    return ((unsigned long)ptr - (unsigned long)Vector) / sizeof(T);
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
// Slot 4: first index over the whole capacity whose element equals
// `object`; -1 when absent, 0 while invalid.
template <class T>
int VectorClass<T>::ID(T const &object)
{
    if (!IsValid) {
        return 0;
    }
    for (int index = 0; index < VectorMax; index++) {
        if (Vector[index] == object) {
            return index;
        }
    }
    return -1;
}
#endif

#ifdef VECTOR_IMPLEMENT_VECTOR_FETCH
// Slot 6: copy of the element at `index`; no range check.
template <class T>
T VectorClass<T>::Fetch(int index) const
{
    return Vector[index];
}
#endif

// --------------------------------------------------------- DynamicVectorClass

#ifdef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
template <class T>
inline int DynamicVectorClass<T>::Count() const
{
    return ActiveCount;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_SET_GROWTH_STEP
// Defined only on request so explicit instantiations do not emit it.
template <class T>
inline void DynamicVectorClass<T>::Set_Growth_Step(int step)
{
    GrowthStep = step;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_NOINIT_CONSTRUCTOR
template <class T>
DynamicVectorClass<T>::DynamicVectorClass(NoInitClass const &noinit)
    : VectorClass<T>(noinit)
{
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR

// Base construction, then an empty list growing by 10.
template <class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned size, T const *array)
    : VectorClass<T>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_RESIZE
// Slot 2: base Resize, then clamps ActiveCount to the new capacity.
template <class T>
bool DynamicVectorClass<T>::Resize(int newsize, T const *array)
{
    if (VectorClass<T>::Resize(newsize, array)) {
        if (Length() < ActiveCount) {
            ActiveCount = Length();
        }
        return true;
    }
    return false;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_CLEAR
// Slot 3: empties the list and frees owned storage.
template <class T>
void DynamicVectorClass<T>::Clear()
{
    ActiveCount = 0;
    VectorClass<T>::Clear();
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
// Slot 5: same as the base lookup (a separate COMDAT in the original).
template <class T>
int DynamicVectorClass<T>::ID(T const *ptr)
{
    return VectorClass<T>::ID(ptr);
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
// Slot 4: first index among the active elements equal to `object`, or -1.
// Unlike the base lookup it does not consult IsValid.
template <class T>
int DynamicVectorClass<T>::ID(T const &object)
{
    for (int index = 0; index < ActiveCount; index++) {
        if (Vector[index] == object) {
            return index;
        }
    }
    return -1;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_ASSIGN
// Copies the storage (base assignment) and both counters.
template <class T>
DynamicVectorClass<T> &DynamicVectorClass<T>::operator=(DynamicVectorClass<T> const &rvalue)
{
    VectorClass<T>::operator=(rvalue);
    ActiveCount = rvalue.ActiveCount;
    GrowthStep = rvalue.GrowthStep;
    return *this;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_ADD
// Appends `object`. When full, grows by GrowthStep through the virtual
// Resize, but only for owned or still unallocated storage and a positive
// step; returns false when it cannot grow.
template <class T>
bool DynamicVectorClass<T>::Add(T const &object)
{
    if (ActiveCount >= Length()) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            if (!Resize(Length() + GrowthStep)) {
                return false;
            }
        } else {
            return false;
        }
    }
    int index = ActiveCount++;
    Vector[index] = object;
    return true;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_ADD_AFTER
// Inserts `object` after the first element equal to `after` (at index 0 when
// absent), shifting the later active elements up; grows like Add. Name is a
// hypothesis; expanded inline in MSEngine::Replace_Anim (0x005B2DD0).
template <class T>
bool DynamicVectorClass<T>::Add_After(T const &object, T const &after)
{
    int index = ID(after);
    if (ActiveCount >= VectorMax) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            if (!Resize(VectorMax + GrowthStep)) {
                return false;
            }
        } else {
            return false;
        }
    }
    if (index < ActiveCount - 1) {
        memmove(&Vector[index + 2], &Vector[index + 1], (ActiveCount - (index + 1)) * sizeof(T));
    }
    Vector[index + 1] = object;
    ActiveCount++;
    return true;
}
#endif
#ifdef VECTOR_IMPLEMENT_DYNAMIC_INSERT_AFTER
// Inserts `object` after the element at `index`, shifting the later active
// elements up; grows like Add. Name is a hypothesis; the out-of-line copy
// for BaseNodeClass is 0x004F7270.
template <class T>
bool DynamicVectorClass<T>::Insert_After(T const &object, int index)
{
    if (ActiveCount >= VectorMax) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            if (!Resize(VectorMax + GrowthStep)) {
                return false;
            }
        } else {
            return false;
        }
    }
    if (index < ActiveCount - 1) {
        memmove(&Vector[index + 2], &Vector[index + 1], (ActiveCount - (index + 1)) * sizeof(T));
    }
    Vector[index + 1] = object;
    ActiveCount++;
    return true;
}
#endif
#ifdef VECTOR_IMPLEMENT_DYNAMIC_ADD_HEAD
// Inserts `object` at index 0, shifting the active elements up; grows like
// Add.
template <class T>
bool DynamicVectorClass<T>::Add_Head(T const &object)
{
    if (ActiveCount >= Length()) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            if (!Resize(Length() + GrowthStep)) {
                return false;
            }
        } else {
            return false;
        }
    }
    if (ActiveCount) {
        memmove(&Vector[1], &Vector[0], ActiveCount * sizeof(T));
    }
    Vector[0] = object;
    ActiveCount++;
    return true;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
// Removes the first active element equal to `object` (virtual ID lookup).
template <class T>
bool DynamicVectorClass<T>::Delete(T const &object)
{
    int index = ID(object);
    if (index != -1) {
        return Delete(index);
    }
    return false;
}
#endif

#ifdef VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
// Removes the element at `index`, shifting later active elements down.
template <class T>
bool DynamicVectorClass<T>::Delete(int index)
{
    // No lower bound check: the expansions in MSEngine (0x005B2EC0,
    // 0x005B2FB0) compare only against ActiveCount.
    if (index < ActiveCount) {
        ActiveCount--;
        for (int i = index; i < ActiveCount; i++) {
            Vector[i] = Vector[i + 1];
        }
        return true;
    }
    return false;
}
#endif

// TypeList<T>: shared/type_list.hpp.

#endif
