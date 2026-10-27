// HRESULT __stdcall TClassFactory<UnknownFactoryProduct_6b4570>::QueryInterface(GUID const &iid, void **object) (0x00694370)
// IUnknown and IClassFactory give the factory itself (body: shared/class_factory_query_interface.hpp).
// The product class is not named by RTTI; UnknownFactoryProduct_6b4570 stands for the class whose constructor is 0x006B4570.
#include "shared/class_factory_query_interface.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IClassFactory=007afcf0

class UnknownFactoryProduct_6b4570;

template class TClassFactory<UnknownFactoryProduct_6b4570>;
