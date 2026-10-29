// The COM server registration helpers of the unit at 0x0068D950 (its
// registration routine 0x0068DC70 writes the class keys through them).
#ifndef RA2_SHARED_COM_REGISTRATION_HPP
#define RA2_SHARED_COM_REGISTRATION_HPP

// Creates HKEY_CLASSES_ROOT\key[\subkey] and, given a value, sets its
// default value; false when a registry call fails (0x0068DBC0).
bool __fastcall Set_Class_Root_Key(char const *key, char const *subkey, char const *value);

#include "shared/com_api.hpp"
// The game's COM server class ("WW.TiberianSun.1", 0x007A1A90) and its type library
// (RA2.TLB, 0x007A1A80); names are hypotheses from the registered ProgID.
extern "C" GUID const CLSID_TiberianSun;
extern "C" GUID const LIBID_TiberianSun;

// Writes the server's HKEY_CLASSES_ROOT keys and loads its type library (0x0068DC70);
// Unregister_Com_Server deletes them again (0x0068E040). Both return 0.
int __fastcall Register_Com_Server();
int __fastcall Unregister_Com_Server();

// The class object registrations (CoRegisterClassObject cookies) Prog_End revokes (0x00ABD428;
// defined by the unit's header statics source).
#include "shared/vector_class_decl.hpp"
extern DynamicVectorClass<unsigned long> unknown_unsigned_long_list_00abd428;

#endif
