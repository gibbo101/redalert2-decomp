// WOnline.cpp file statics: COM library lifetime (OleInitialize at startup, OleUninitialize at exit).
// @ref __imp__OleUninitialize@0=0079a5c4
// @ref __imp__OleInitialize@4=0079a5c8
#include "shared/wol_sink.hpp"
WIN32_IMPORT HRESULT WINAPI OleInitialize(void *reserved);
WIN32_IMPORT void WINAPI OleUninitialize();
// @ref _atexit=0078298a
struct OleLibrary {
    OleLibrary() { OleInitialize(0); }
    ~OleLibrary() { OleUninitialize(); }
};
static OleLibrary unknown_ole_library;
