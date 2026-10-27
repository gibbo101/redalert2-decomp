#ifndef RA2_SHARED_UNKNOWN_LOADOUT_HPP
#define RA2_SHARED_UNKNOWN_LOADOUT_HPP
#include "shared/cd_timer.hpp"
#include "shared/id_source.hpp"
class TechnoTypeClass;
// Existing canonical owner name retained. Original class name unresolved;
// one five-entry type collection, count+10 and aggregate raw cost+28.
class Unknown4A6AE0Owner {
public:
    Unknown4A6AE0Owner();
    bool Add_Type_004A6940(TechnoTypeClass *type);
    bool Remove_Index_004A6A10(int index);
    void Clear_004A6AE0();
    // C++ void return is a source hypothesis; original leaves last Count in EAX.
    // Complete-body equality preserves that physical32-bit result; caller use unreviewed.
    void Swizzle_Types_004A6B10();
    TechnoTypeClass *Get_Type_004A6B40(int index);
    static int __fastcall Find_Type_Index_004A6B50(TechnoTypeClass *type);
    CDTimerClass<FrameTimerClass> Timer; // +00, ctor004A6910 starts atFrame withINT_MAX delay
    bool unknown_0c;
    char unknown_0d[3];
    int Count;
    TechnoTypeClass *Types[5];
    int Cost;
};
typedef char Unknown4A6AE0Owner_size_check[(sizeof(Unknown4A6AE0Owner)==44)?1:-1];
// Definitions are local to collection consumers, preserving implementation
// guards and compiler-local labels in unrelated users of id_source.hpp.
inline TypeList<TechnoTypeClass *> &UnknownIDSource::Loadout_Types_2254()
{ return *(TypeList<TechnoTypeClass *> *)((char *)this + 0x2254); }
inline TypeList<int> &UnknownIDSource::Loadout_Limits_2270()
{ return *(TypeList<int> *)((char *)this + 0x2270); }
inline TypeList<int> &UnknownIDSource::Loadout_Counts_228c()
{ return *(TypeList<int> *)((char *)this + 0x228C); }
#endif
