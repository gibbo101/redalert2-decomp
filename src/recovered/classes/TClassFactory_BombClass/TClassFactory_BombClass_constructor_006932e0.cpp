// @ref ??_7?$TClassFactory@VBombClass@@@@6B@=007abbc0
#include "shared/class_factory.hpp"
class BombClass;
template <> TClassFactory<BombClass>::TClassFactory() : references(0) {}
