HRESULT __stdcall EnumConnectionPointsClass::Next(unsigned long requested,IConnectionPoint **data,unsigned long *fetched) {
 if (!data) return E_POINTER;
 if (requested>1 && !fetched) return E_POINTER;
 if (fetched) *fetched=0;
 unsigned long count=0;
 for (unsigned long i=0;i<requested && Position<Points.Count();++i) { Points[Position]->AddRef(); *data++=Points[Position++]; ++count; }
 if (fetched) *fetched=count;
 return count ? 0 : (HRESULT)0x80004005;
}
