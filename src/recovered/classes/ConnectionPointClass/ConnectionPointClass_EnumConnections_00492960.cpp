HRESULT __stdcall ConnectionPointClass::EnumConnections(IEnumConnections **result) {
 if (!result) return E_POINTER;
 EnumConnectionsClass *copy=new EnumConnectionsClass(Connections);
 if (!copy) return (HRESULT)0x8007000e;
 return copy->QueryInterface(IID_IEnumConnections,(void **)result);
}
