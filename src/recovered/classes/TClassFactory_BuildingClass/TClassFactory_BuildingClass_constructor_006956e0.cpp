// @ref ??_7?$TClassFactory@VBuildingClass@@@@6B@=007abe00
#include "shared/class_factory.hpp"
class BuildingClass;
template <> TClassFactory<BuildingClass>::TClassFactory() : references(0) {}
