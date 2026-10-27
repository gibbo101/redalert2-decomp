// HRESULT __stdcall TClassFactory<InfantryClass>::QueryInterface(GUID const &iid, void **object) (0x006959F0)
// IUnknown and IClassFactory give the factory itself (body: shared/class_factory_query_interface.hpp).
#include "shared/class_factory_query_interface.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IClassFactory=007afcf0

class InfantryClass;

template class TClassFactory<InfantryClass>;
