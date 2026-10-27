int __fastcall operator!=(tagCONNECTDATA const &a,tagCONNECTDATA const &b) { if (a.dwCookie==b.dwCookie && a.pUnk==b.pUnk) return 0; return 1; }
