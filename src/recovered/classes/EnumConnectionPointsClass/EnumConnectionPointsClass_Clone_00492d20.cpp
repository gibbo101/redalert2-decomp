HRESULT __stdcall EnumConnectionPointsClass::Clone(IEnumConnectionPoints **result) {
 if (!result) return E_POINTER;
 EnumConnectionPointsClass *copy=new EnumConnectionPointsClass(*this);
 if (!copy) return (HRESULT)0x8007000e;
 copy->AddRef(); *result=copy; return 0;
}
