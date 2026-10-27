// CoopCampaignClass: original name proved by RTTI vector007A6844 and MPCooperative005A2960.
// Allocation at 005A4BD3 is 0x70; constructor 0048E090 establishes the fields.
#ifndef RA2_SHARED_COOP_CAMPAIGN_HPP
#define RA2_SHARED_COOP_CAMPAIGN_HPP
template<class T> class DynamicVectorClass;
class UnknownDescriptionList_00490E00;
class MPlayerScoreType;
class CoopCampaignClass {
public:
    CoopCampaignClass();
    ~CoopCampaignClass();
    CoopCampaignClass(unsigned short const *first, unsigned short const *second);
    bool Add_Score_0048f730(int index, int time, MPlayerScoreType first, MPlayerScoreType second);
    bool Save_Campaign_0048f040();
    bool Send_Campaign_Options_00490150(UnknownDescriptionList_00490E00 &campaigns);
    bool Get_Map_Name_0048fb40(char **name,int index);
    bool Get_First_Player_Settings_0048fb90(int *house,int *color);
    bool Get_Second_Player_Settings_0048fbc0(int *house,int *color);
    bool Has_Saved_Campaign_0048fbf0();
    bool Saved_Map_Is_Undefined_0048fe70(char *map);
    bool Load_Saved_Campaign_0048eb30();
    bool Clear_Saved_Campaign_0048e870();
    bool Next_Map_0048e360();
    bool Get_Player_Scores_0048e710(DynamicVectorClass<MPlayerScoreType *> &scores, int *time);
    bool Get_Campaign_Type_0048e6b0(int *value);
    bool Get_Map_Count_0048e6d0(int *value);
    bool Get_Current_Map_0048e6f0(int *value);
    bool Load_Campaign_0048f590(int index);
    bool Set_Campaign_Info_0048f7d0(UnknownDescriptionList_00490E00 const &campaigns, int index, DynamicVectorClass<int> choices, char const *second_name, char const *first_name);
    void Set_Names(unsigned short const *first, unsigned short const *second);
    char FirstName[20];
    int FirstHouse;
    int FirstColor;
    char SecondName[20];
    int SecondHouse;
    int SecondColor;
    int CurrentMap;
    char **MapNames;
    int MapCount;
    int CampaignType;
    int Kills[2];
    int Built[2];
    int Lost[2];
    int Score[2];
    int Time;
    bool Initialized;
};
typedef char CoopCampaignClass_size[(sizeof(CoopCampaignClass)==0x70)?1:-1];
#endif
