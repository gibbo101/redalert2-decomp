// @ref ??_7?$TClassFactory@VTEventClass@@@@6B@=007abbf0
#include "shared/class_factory.hpp"
class TEventClass;
template <> TClassFactory<TEventClass>::TClassFactory() : references(0) {}
