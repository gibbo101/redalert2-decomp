// VectorClass<rc_ptr<WDTTerritory>>::operator=(VectorClass<rc_ptr<WDTTerritory>> const &) (0x0072CAC0).
// Replaces the contents with an owned copy (shared/vector_class.hpp); the copy kept out of line
// (0x0072BEF0 calls it).
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0rc_ptr_base@@QAE@XZ=006394e0
// @ref ??1rc_ptr_base@@UAE@XZ=00639510
// @ref ?Set@rc_ptr_base@@QAEXPAVReferenceCounted@@@Z=00639530
// @ref ??_E?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??_G?$rc_ptr@VWDTTerritory@@@@UAEPAXI@Z=0051e600
// @ref ??_7?$rc_ptr@VWDTTerritory@@@@6B@=007a452c
#define VECTOR_IMPLEMENT_VECTOR_ASSIGN
#include "shared/vector_class.hpp"
#include "shared/reference_counted.hpp"

class WDTTerritory;

template class VectorClass<rc_ptr<WDTTerritory> >;
