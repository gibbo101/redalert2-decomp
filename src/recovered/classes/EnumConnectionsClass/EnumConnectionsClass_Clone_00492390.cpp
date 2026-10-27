HRESULT __stdcall EnumConnectionsClass::Clone(IEnumConnections **result) {
 if (!result) return E_POINTER;
 EnumConnectionsClass *copy=new EnumConnectionsClass(*this);
 if (!copy) return (HRESULT)0x8007000e;
 copy->RefCount=0;
 copy->AddRef(); *result=copy; return 0;
}
