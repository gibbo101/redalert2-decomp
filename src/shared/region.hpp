// RegionClass: Westwood name hypothesis for HouseClass's four-byte threat records.
// Target004E5DC0 adjusts a signed32-bit value and clamps it at zero;
//004F3420 resets16900 records. No polymorphism or additional fields evidenced.
// The user-provided default constructor and destructor leave Threat unchanged.
#ifndef RA2_SHARED_REGION_HPP
#define RA2_SHARED_REGION_HPP
class RegionClass {
public:
    RegionClass() {}
    ~RegionClass() {}
    int Threat;
};
typedef char RegionClass_size_is_4[(sizeof(RegionClass)==4)?1:-1];
#endif
