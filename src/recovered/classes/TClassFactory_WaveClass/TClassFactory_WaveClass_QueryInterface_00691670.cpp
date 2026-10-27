// HRESULT __stdcall TClassFactory<WaveClass>::QueryInterface(GUID const &iid, void **object) (0x00691670)
// IUnknown and IClassFactory give the factory itself (body: shared/class_factory_query_interface.hpp).
#include "shared/class_factory_query_interface.hpp"
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IClassFactory=007afcf0

class WaveClass;

template class TClassFactory<WaveClass>;
