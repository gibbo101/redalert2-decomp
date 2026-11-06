// @ref ??_7?$TClassFactory@VParasiteClass@@@@6B@=007abba8
#include "shared/class_factory.hpp"
class ParasiteClass;
template <> TClassFactory<ParasiteClass>::TClassFactory() : references(0) {}
