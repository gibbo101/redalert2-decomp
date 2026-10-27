#include "shared/coop_campaign.hpp"
#include "shared/crt_string.hpp"
char *__fastcall Unknown_006FA120(unsigned short const *string);
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
void CoopCampaignClass::Set_Names(unsigned short const *first, unsigned short const *second)
{
    if(first) strcpy(FirstName,Unknown_006FA120(first));
    else FirstName[0]=0;
    if(second) strcpy(SecondName,Unknown_006FA120(second));
    else SecondName[0]=0;
}
