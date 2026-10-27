HRESULT __stdcall ConnectionPointClass::Advise(IUnknown *sink,unsigned long *cookie) {
 if (!sink || !cookie) return E_POINTER;
 tagCONNECTDATA connection;
 connection.dwCookie=unknown_id_source_a3d290->Next_ID();
 if (FAILED(sink->QueryInterface(InterfaceID,(void **)&connection.pUnk))) return (HRESULT)0x80040202;
 if (!Connections.Add(connection)) return (HRESULT)0x80040201;
 *cookie=connection.dwCookie; return 0;
}
