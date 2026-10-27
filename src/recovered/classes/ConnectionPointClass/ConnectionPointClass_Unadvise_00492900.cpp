HRESULT __stdcall ConnectionPointClass::Unadvise(unsigned long cookie) {
 for (int i=0;i<Connections.Count();++i) if (Connections[i].dwCookie==cookie) { Connections.Delete(i); return 0; }
 return (HRESULT)0x80040200;
}
