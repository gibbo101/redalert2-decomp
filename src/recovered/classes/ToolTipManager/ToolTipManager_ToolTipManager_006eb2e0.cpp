// ToolTipManager::ToolTipManager(HWND window) (0x006EB2E0)
// @ref ??_7?$DynamicVectorClass@PAVToolTip@@@@6B@=007ad950
// @ref ??_7?$VectorClass@PAVToolTip@@@@6B@=007ad970
// @ref ??_G?$DynamicVectorClass@PAVToolTip@@@@UAEPAXI@Z=006ec220
// @ref ??8?$VectorClass@PAVToolTip@@@@UBE_NABV0@@Z=006ebf70
// @ref ?Resize@?$DynamicVectorClass@PAVToolTip@@@@UAE_NHPBQAVToolTip@@@Z=006ec0f0
// @ref ?Clear@?$DynamicVectorClass@PAVToolTip@@@@UAEXXZ=006ebf10
// @ref ?ID@?$DynamicVectorClass@PAVToolTip@@@@UAEHABQAVToolTip@@@Z=006ec1a0
// @ref ?ID@?$DynamicVectorClass@PAVToolTip@@@@UAEHPBQAVToolTip@@@Z=006ebf40
// @ref ?Fetch@?$VectorClass@PAVToolTip@@@@UBEPAVToolTip@@H@Z=006ebf60
// @ref ??_G?$VectorClass@PAVToolTip@@@@UAEPAXI@Z=006ec1d0
// @ref ?Resize@?$VectorClass@PAVToolTip@@@@UAE_NHPBQAVToolTip@@@Z=006ebfb0
// @ref ?Clear@?$VectorClass@PAVToolTip@@@@UAEXXZ=006ec060
// @ref ?ID@?$VectorClass@PAVToolTip@@@@UAEHABQAVToolTip@@@Z=006ec090
// @ref ?ID@?$VectorClass@PAVToolTip@@@@UAEHPBQAVToolTip@@@Z=006ec0d0
// @ref ??_7ToolTipManager@@6B@=007ad934
// @ref ??_GToolTipManager@@UAEPAXI@Z=006ebef0
// @ref ?Show@ToolTipManager@@UAE_NPAUToolTipRecord@@@Z=006ebd80
// @ref ?Hide@ToolTipManager@@UAEXPAUToolTipRecord@@@Z=006ebd90
// @ref ?Refresh@ToolTipManager@@UAEX_N@Z=006ebe60
// @ref ?Debug_Print@ToolTipManager@@UAEXPAUToolTipRecord@@@Z=006ebe90
// @ref ?Get_Text@ToolTipManager@@UAEPBGH@Z=006ebeb0
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/tool_tip.hpp"

ToolTipManager::ToolTipManager(HWND window) :
    Current(0),
    Window(window),
    Enabled(false),
    Delay(1000),
    Duration(10000)
{
    Tips.Clear();
    Index.Clear();
}
