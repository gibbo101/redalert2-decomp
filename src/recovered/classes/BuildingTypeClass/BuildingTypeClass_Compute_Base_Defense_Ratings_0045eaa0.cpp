// Derive the three base-defense ratings from the primary weapon. Full292+12.
#include "shared/building_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/rules.hpp"
extern double const Defense_Rate_Scale_0079d2e8;
// @ref ?Defense_Rate_Scale_0079d2e8@@3NB=0079d2e8
// @ref ?Get_Weapon@TechnoTypeClass@@QAEPAUWeaponStruct@@H@Z=006df5c0
inline double Limit_Defense_Rating(double amount,double cap)
{
    return cap<amount?cap:amount;
}
void BuildingTypeClass::unknown_func_45eaa0()
{
    if(IsBaseDefense) {
        WeaponTypeClass *weapon=Get_Weapon(0)->WeaponType;
        if(weapon) {
            int rate=(int)((double)weapon->unknown_a4/((double)weapon->unknown_b0*Defense_Rate_Scale_0079d2e8));
            if(weapon->Projectile->AA) {
                unknown_11d8=(int)Limit_Defense_Rating((double)rate*weapon->Warhead->Verses[3],(double)Rules->MaximumBaseDefenseValue);
            }
            if(weapon->Projectile->AG) {
                unknown_11dc=(int)Limit_Defense_Rating((double)rate*weapon->Warhead->Verses[4],(double)Rules->MaximumBaseDefenseValue);
                unknown_11e0=(int)Limit_Defense_Rating((double)rate*weapon->Warhead->Verses[0],(double)Rules->MaximumBaseDefenseValue);
            }
        }
    }
}
