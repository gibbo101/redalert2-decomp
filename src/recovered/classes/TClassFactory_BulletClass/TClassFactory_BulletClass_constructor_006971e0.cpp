// @ref ??_7?$TClassFactory@VBulletClass@@@@6B@=007abfb0
#include "shared/class_factory.hpp"
class BulletClass;
template <> TClassFactory<BulletClass>::TClassFactory() : references(0) {}
