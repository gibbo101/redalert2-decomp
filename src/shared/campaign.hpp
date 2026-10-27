// CampaignClass: a single-player campaign (Campaign.cpp, 0x00465450-
// 0x004659FD; RTTI vtables 0x0079D6A0 primary, 0x0079D684 at +4, 0x0079D67C,
// 0x0079D674). Layout from the constructor 0x00465450 and Compute_CRC
// 0x004658A0; Size_Of 0x3A0, Kind_Of 0x0A. Every campaign is listed in
// Campaigns (defined in the unit at 0x004D2BA0).
#ifndef RA2_SHARED_CAMPAIGN_HPP
#define RA2_SHARED_CAMPAIGN_HPP

#include "shared/abstract_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/vector_class.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

extern "C" GUID const CLSID_CampaignClass;     // 0x007A1E40
extern "C" wchar_t *__cdecl wcscpy(wchar_t *dest, wchar_t const *source);   // 0x00783689

void __fastcall Detach_This_From_All(AbstractClass *object, bool all);     // 0x006ECB90
// Converts a narrow string into wide characters (0x006FA0C0; -1: to its end).
void __fastcall Unknown_006FA0C0(wchar_t *buffer, char const *text, int length);
extern "C" char *__cdecl _strupr(char *string);                             // 0x007961E4
extern "C" char *__cdecl strcat(char *dest, char const *source);

// INIClass::Get_Wide_String (0x0050F010) is not declared in
// shared/ini_class.hpp yet (proposal: add it there); this view supplies it.
class CampaignINI : public CCINIClass {
public:
    int Get_Wide_String(char const *section, char const *entry, wchar_t *buffer, int length) const;   // 0x0050F010
};

class CampaignClass : public AbstractTypeClass {
public:
    CampaignClass(char const *ini_name);                        // 0x00465450
    CampaignClass(NoInitClass const &noinit) : AbstractTypeClass(noinit) {}
    virtual ~CampaignClass();                                   // 0x00465500

    static int __fastcall Find_Index(char const *name);         // 0x00465580
    // Makes (or finds) the campaign of every [Battles] entry and reads its
    // section (0x004656F0; name hypothesis).
    static void __fastcall Read_Battles(CCINIClass &ini);

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x00465860
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x004658E0
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00465930
    virtual int Kind_Of() const;                                // 0x00465960
    virtual int Size_Of() const;                                // 0x00465950
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x004658A0
    virtual bool Read_INI(CCINIClass &ini);                     // 0x004655C0

    int unknown_98;                 // +0x098 (-1)
    char Scenario[0x200];           // +0x09C (CRC'd as a string; size from the next field)
    int unknown_29c;                // +0x29C (-1)
    wchar_t Description[0x80];      // +0x2A0
};

extern DynamicVectorClass<CampaignClass *> Campaigns;   // 0x00A35D60

#endif
