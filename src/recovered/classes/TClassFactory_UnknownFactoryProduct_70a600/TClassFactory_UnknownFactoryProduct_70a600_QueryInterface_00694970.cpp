// HRESULT __stdcall TClassFactory<UnknownFactoryProduct_70a600>::QueryInterface(GUID const &iid, void **object) (0x00694970)
// IUnknown and IClassFactory give the factory itself (body: shared/class_factory_query_interface.hpp).
// The product class is not named by RTTI; UnknownFactoryProduct_70a600 stands for the class whose constructor is 0x0070A600.
#include "shared/class_factory_query_interface.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IClassFactory=007afcf0

class UnknownFactoryProduct_70a600;

template class TClassFactory<UnknownFactoryProduct_70a600>;
