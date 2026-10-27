HRESULT __stdcall EnumConnectionsClass::QueryInterface(GUID const &iid,void **object) {
 if (!object) return E_POINTER;
 *object=0;
 if (!memcmp(&iid,&IID_IUnknown,sizeof(GUID))) *object=this;
 if (!memcmp(&iid,&IID_IEnumConnections,sizeof(GUID))) *object=this;
 if (*object) { AddRef(); return 0; }
 return E_NOINTERFACE;
}
