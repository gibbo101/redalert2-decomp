// RulesClass::Powerups (0x0064D490)
// @ref ?CrateShares@@3PAHA=007d38dc
// @ref ?CrateAnims@@3PAHA=007d3928
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_02ELCB@no?$AA@=007db4cc
// @ref ??_C@_03LGKI@yes?$AA@=007db4d0
// @ref ??_C@_06KMJB@0?0NONE?$AA@=007f1a08
// @ref ?CrateData@@3PANA=00851080
// @ref ?CrateWater@@3PA_NA=00851118
// @ref _RulesSection_Powerups=007a9094
// @ref ??_C@_08KJFI@Powerups?$AA@=007eebec
// Each crate kind's [Powerups] entry: "share, animation, water (yes/no), data";
// a data value with a percent sign is a fraction (times 0.01).
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/anim.hpp"

extern "C" int __cdecl _stricmp(char const *left, char const *right);
extern "C" double __cdecl atof(char const *string);

bool RulesClass::Powerups(CCINIClass &ini)
{
    if (ini.Is_Present(RulesSection_Powerups)) {
        for (int crate = 0; crate < 19; crate++) {
            char buffer[128];
            if (ini.Get_String(RulesSection_Powerups, CrateNames[crate], "0,NONE", buffer, sizeof(buffer))) {
                char *token = strtok(buffer, ",");
                if (token != 0) {
                    strtrim(token);
                    CrateShares[crate] = atoi(token);
                }
                token = strtok(0, ",");
                if (token != 0) {
                    strtrim(token);
                    CrateAnims[crate] = Anim_From_Name(token);
                }
                token = strtok(0, ",");
                if (token != 0) {
                    strtrim(token);
                    if (_stricmp(token, "yes") == 0) {
                        CrateWater[crate] = true;
                    } else if (_stricmp(token, "no") == 0) {
                        CrateWater[crate] = false;
                    }
                }
                token = strtok(0, ",");
                if (token != 0) {
                    if (strchr(token, '%') != 0) {
                        CrateData[crate] = atof(token) * 0.01;
                    } else {
                        strtrim(token);
                        CrateData[crate] = atof(token);
                    }
                }
            }
        }
        return true;
    }
    return false;
}
