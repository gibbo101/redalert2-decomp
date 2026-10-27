unsigned long __stdcall EnumConnectionPointsClass::Release() { --COMReferences_00a6eb14; unsigned long count=InterlockedDecrement(&RefCount); if (!count) delete this; return count; }
