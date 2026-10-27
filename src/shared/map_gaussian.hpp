// Research hypothesis: non-polymorphic Gaussian callback state in MapGen.
// Actual00579810 stores bool+0,spare+8,callback+10;0057A10D copies24 bytes.
// Formal original type name is not evidenced. No canonical wrapper refit here.
#ifndef RA2_MAP_GAUSSIAN_HPP
#define RA2_MAP_GAUSSIAN_HPP
#pragma pack(push,8)
class MapGaussianClass {
public:
    typedef double (__cdecl *UniformCallback)();
    MapGaussianClass(UniformCallback callback);
    double Next();
    bool HasSpare;
    double Spare;
    UniformCallback Uniform;
};
#pragma pack(pop)
typedef char MapGaussianClass_size[(sizeof(MapGaussianClass)==24)?1:-1];
extern MapGaussianClass unknown_map_gaussian_a6fd50;
#endif
