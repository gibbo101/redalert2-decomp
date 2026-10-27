HRESULT __stdcall EnumConnectionsClass::Next(unsigned long requested,tagCONNECTDATA *data,unsigned long *fetched) {
 if (!data) return E_POINTER;
 if (requested>1 && !fetched) return (HRESULT)0x80070057;
 if (fetched) *fetched=0;
 unsigned long count=0;
 for (unsigned long i=0; i<requested && Position<Connections.Count(); ++i) {
  Connections[Position].pUnk->AddRef();
  *data++=Connections[Position++]; ++count;
 }
 if (fetched) *fetched=count;
 return count ? 0 : (HRESULT)0x80004005;
}
