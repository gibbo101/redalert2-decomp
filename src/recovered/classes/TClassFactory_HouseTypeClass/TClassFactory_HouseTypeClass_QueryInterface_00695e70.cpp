// HRESULT __stdcall TClassFactory<HouseTypeClass>::QueryInterface(GUID const &iid, void **object) (0x00695E70)
// IUnknown and IClassFactory give the factory itself (body: shared/class_factory_query_interface.hpp).
#include "shared/class_factory_query_interface.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IClassFactory=007afcf0

class HouseTypeClass;

template class TClassFactory<HouseTypeClass>;
