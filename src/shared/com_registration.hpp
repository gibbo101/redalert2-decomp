// The COM server registration helpers of the unit at 0x0068D950 (its
// registration routine 0x0068DF20 writes the class keys through them).
#ifndef RA2_SHARED_COM_REGISTRATION_HPP
#define RA2_SHARED_COM_REGISTRATION_HPP

// Creates HKEY_CLASSES_ROOT\key[\subkey] and, given a value, sets its
// default value; false when a registry call fails (0x0068DBC0).
bool __fastcall Set_Class_Root_Key(char const *key, char const *subkey, char const *value);

#endif
