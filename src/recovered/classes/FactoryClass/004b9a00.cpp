extern "C" GUID const CLSID_FactoryClass;
// @ref _CLSID_FactoryClass=007a1d90
HRESULT __stdcall FactoryClass::GetClassID(GUID *id)
{
 if(!id) return 0x80004003;
 *id=CLSID_FactoryClass;
 return 0;
}
