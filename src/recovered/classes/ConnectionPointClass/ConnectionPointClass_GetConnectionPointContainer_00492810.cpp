HRESULT __stdcall ConnectionPointClass::GetConnectionPointContainer(IConnectionPointContainer **container) { return Container->QueryInterface(IID_IConnectionPointContainer,(void **)container); }
