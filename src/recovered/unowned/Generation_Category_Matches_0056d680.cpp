// Category meanings and fastcall/bool source spelling remain hypotheses.
bool __fastcall Generation_Category_Matches_0056d680(int category, int value)
{
    switch (category) {
    case 0: return value == 3;
    case 1:
    case 3:
    case 4: return value != 3;
    case 2: return true;
    default: return false;
    }
}
