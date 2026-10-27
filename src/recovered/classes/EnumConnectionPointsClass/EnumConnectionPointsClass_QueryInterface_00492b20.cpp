HRESULT __stdcall EnumConnectionPointsClass::QueryInterface(GUID const &iid,void **object) {
 if (!object) return E_POINTER;
 IUnknown *found=0;
 if (!memcmp(&iid,&IID_IEnumConnectionPoints,sizeof(GUID)) || !memcmp(&iid,&IID_IUnknown,sizeof(GUID))) found=this;
 *object=found;
 if (found) { AddRef(); return 0; }
 return E_NOINTERFACE;
}
