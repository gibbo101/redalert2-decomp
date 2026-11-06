// @ref ??_7?$TClassFactory@VSuperClass@@@@6B@=007aba58
#include "shared/class_factory.hpp"
class SuperClass;
template <> TClassFactory<SuperClass>::TClassFactory() : references(0) {}
