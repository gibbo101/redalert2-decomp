HRESULT __stdcall ConnectionPointClass::GetConnectionInterface(GUID *iid) { if (!iid) return E_POINTER; *iid=InterfaceID; return 0; }
