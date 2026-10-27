// HRESULT __stdcall TClassFactory<UnknownFactoryProduct_457ac0>::QueryInterface(GUID const &iid, void **object) (0x00694AF0)
// IUnknown and IClassFactory give the factory itself (body: shared/class_factory_query_interface.hpp).
// The product class is not named by RTTI; UnknownFactoryProduct_457ac0 stands for the class whose constructor is 0x00457AC0.
#include "shared/class_factory_query_interface.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IClassFactory=007afcf0

class UnknownFactoryProduct_457ac0;

template class TClassFactory<UnknownFactoryProduct_457ac0>;
