#define RA2_PLANNING_COMMIT_PLANS
#define RA2_PLANNING_PICK_ROWS
#define RA2_COORD_EQUAL_MEMBER
// Header-static dynamic initializers of the unit at 0x006101B0 and its
// list globals (EventClass, PlanningNodeClass, PlanningTokenClass, TechnoClass); the other drafts of this plan are emitted by this file.
// A list whose atexit thunk tests and sets a guard bit is a static data
// member (VC6 guards their destruction); its owner class is a hypothesis
// (shared/planning.hpp, shared/event.hpp, shared/techno.hpp).
#include "shared/unknown_geometry.hpp"
#include "shared/unknown_static_rect.hpp"
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"

#include "shared/planning.hpp"

DynamicVectorClass<EventClass *> PlanningLists::unknown_list_00a76648;
DynamicVectorClass<PlanningNodeClass *> PlanningNodeClass::unknown_list_00a76758;
DynamicVectorClass<TechnoClass *> PlanningLists::unknown_list_00a76700;
DynamicVectorClass<PlanningNodeClass *> PlanningNodeClass::unknown_list_00a76628;
DynamicVectorClass<PlanningNodeClass *> PlanningNodeClass::unknown_list_00a766d8;
DynamicVectorClass<PlanningTokenClass *> PlanningTokenClass::unknown_list_00a76738;
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??8?$VectorClass@PAVEventClass@@@@UBE_NABV0@@Z=0061b410
// @ref ??8?$VectorClass@PAVPlanningNodeClass@@@@UBE_NABV0@@Z=0061b0d0
// @ref ??8?$VectorClass@PAVPlanningTokenClass@@@@UBE_NABV0@@Z=0061b710
// @ref ??8?$VectorClass@PAVTechnoClass@@@@UBE_NABV0@@Z=0040b870
// @ref ??_7?$DynamicVectorClass@PAVEventClass@@@@6B@=007a81dc
// @ref ??_7?$DynamicVectorClass@PAVPlanningNodeClass@@@@6B@=007a821c
// @ref ??_7?$DynamicVectorClass@PAVPlanningTokenClass@@@@6B@=007a825c
// @ref ??_7?$DynamicVectorClass@PAVTechnoClass@@@@6B@=0079a79c
// @ref ??_7?$VectorClass@PAVEventClass@@@@6B@=007a81fc
// @ref ??_7?$VectorClass@PAVPlanningNodeClass@@@@6B@=007a823c
// @ref ??_7?$VectorClass@PAVPlanningTokenClass@@@@6B@=007a827c
// @ref ??_7?$VectorClass@PAVTechnoClass@@@@6B@=0079a7fc
// @ref ??_G?$DynamicVectorClass@PAVEventClass@@@@UAEPAXI@Z=0061bc40
// @ref ??_G?$DynamicVectorClass@PAVPlanningNodeClass@@@@UAEPAXI@Z=0061bba0
// @ref ??_G?$DynamicVectorClass@PAVPlanningTokenClass@@@@UAEPAXI@Z=0061bce0
// @ref ??_G?$DynamicVectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bbc0
// @ref ??_G?$VectorClass@PAVEventClass@@@@UAEPAXI@Z=0061bbf0
// @ref ??_G?$VectorClass@PAVPlanningNodeClass@@@@UAEPAXI@Z=0061bb50
// @ref ??_G?$VectorClass@PAVPlanningTokenClass@@@@UAEPAXI@Z=0061bc90
// @ref ??_G?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ?Clear@?$DynamicVectorClass@PAVEventClass@@@@UAEXXZ=0061aa40
// @ref ?Clear@?$DynamicVectorClass@PAVPlanningNodeClass@@@@UAEXXZ=0061a9e0
// @ref ?Clear@?$DynamicVectorClass@PAVPlanningTokenClass@@@@UAEXXZ=0061aaa0
// @ref ?Clear@?$DynamicVectorClass@PAVTechnoClass@@@@UAEXXZ=0040b5b0
// @ref ?Clear@?$VectorClass@PAVEventClass@@@@UAEXXZ=0061b500
// @ref ?Clear@?$VectorClass@PAVPlanningNodeClass@@@@UAEXXZ=0061b1c0
// @ref ?Clear@?$VectorClass@PAVPlanningTokenClass@@@@UAEXXZ=0061b800
// @ref ?Clear@?$VectorClass@PAVTechnoClass@@@@UAEXXZ=0040b960
// @ref ?Fetch@?$VectorClass@PAVEventClass@@@@UBEPAVEventClass@@H@Z=0061aa90
// @ref ?Fetch@?$VectorClass@PAVPlanningNodeClass@@@@UBEPAVPlanningNodeClass@@H@Z=0061aa30
// @ref ?Fetch@?$VectorClass@PAVPlanningTokenClass@@@@UBEPAVPlanningTokenClass@@H@Z=0061aaf0
// @ref ?Fetch@?$VectorClass@PAVTechnoClass@@@@UBEPAVTechnoClass@@H@Z=0040b600
// @ref ?ID@?$DynamicVectorClass@PAVEventClass@@@@UAEHABQAVEventClass@@@Z=0061b690
// @ref ?ID@?$DynamicVectorClass@PAVEventClass@@@@UAEHPBQAVEventClass@@@Z=0061aa70
// @ref ?ID@?$DynamicVectorClass@PAVPlanningNodeClass@@@@UAEHABQAVPlanningNodeClass@@@Z=0061b3e0
// @ref ?ID@?$DynamicVectorClass@PAVPlanningNodeClass@@@@UAEHPBQAVPlanningNodeClass@@@Z=0061aa10
// @ref ?ID@?$DynamicVectorClass@PAVPlanningTokenClass@@@@UAEHABQAVPlanningTokenClass@@@Z=0061b9e0
// @ref ?ID@?$DynamicVectorClass@PAVPlanningTokenClass@@@@UAEHPBQAVPlanningTokenClass@@@Z=0061aad0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040baa0
// @ref ?ID@?$DynamicVectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b5e0
// @ref ?ID@?$VectorClass@PAVEventClass@@@@UAEHABQAVEventClass@@@Z=0061b530
// @ref ?ID@?$VectorClass@PAVEventClass@@@@UAEHPBQAVEventClass@@@Z=0061b570
// @ref ?ID@?$VectorClass@PAVPlanningNodeClass@@@@UAEHABQAVPlanningNodeClass@@@Z=0061b1f0
// @ref ?ID@?$VectorClass@PAVPlanningNodeClass@@@@UAEHPBQAVPlanningNodeClass@@@Z=0061b230
// @ref ?ID@?$VectorClass@PAVPlanningTokenClass@@@@UAEHABQAVPlanningTokenClass@@@Z=0061b830
// @ref ?ID@?$VectorClass@PAVPlanningTokenClass@@@@UAEHPBQAVPlanningTokenClass@@@Z=0061b870
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040b990
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b9d0
// @ref ?Resize@?$DynamicVectorClass@PAVEventClass@@@@UAE_NHPBQAVEventClass@@@Z=0061b590
// @ref ?Resize@?$DynamicVectorClass@PAVPlanningNodeClass@@@@UAE_NHPBQAVPlanningNodeClass@@@Z=0061b250
// @ref ?Resize@?$DynamicVectorClass@PAVPlanningTokenClass@@@@UAE_NHPBQAVPlanningTokenClass@@@Z=0061b890
// @ref ?Resize@?$DynamicVectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b9f0
// @ref ?Resize@?$VectorClass@PAVEventClass@@@@UAE_NHPBQAVEventClass@@@Z=0061b450
// @ref ?Resize@?$VectorClass@PAVPlanningNodeClass@@@@UAE_NHPBQAVPlanningNodeClass@@@Z=0061b110
// @ref ?Resize@?$VectorClass@PAVPlanningTokenClass@@@@UAE_NHPBQAVPlanningTokenClass@@@Z=0061b750
// @ref ?Resize@?$VectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b8b0
// @ref ?unknown_list_00a76628@PlanningNodeClass@@2V?$DynamicVectorClass@PAVPlanningNodeClass@@@@A=00a76628
// @ref ?unknown_list_00a76648@PlanningLists@@2V?$DynamicVectorClass@PAVEventClass@@@@A=00a76648
// @ref ?unknown_list_00a766d8@PlanningNodeClass@@2V?$DynamicVectorClass@PAVPlanningNodeClass@@@@A=00a766d8
// @ref ?unknown_list_00a76700@PlanningLists@@2V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a76700
// @ref ?unknown_list_00a76738@PlanningTokenClass@@2V?$DynamicVectorClass@PAVPlanningTokenClass@@@@A=00a76738
// @ref ?unknown_list_00a76758@PlanningNodeClass@@2V?$DynamicVectorClass@PAVPlanningNodeClass@@@@A=00a76758
// @ref ?unknown_math_4ba520@@YANN@Z=004ba520
// @ref ?unknown_math_4ba5b0@@YANN@Z=004ba5b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref _$E47=006103e0
// @ref _$E53=00610480
// @ref _$E59=00610520
// @ref _$E65=006105c0
// @ref _$E71=00610660
// @ref _$E76=00610700
// @ref _$S48=00a76641
// @ref _$S54=00a76640
// @ref _$S60=00a76661
// @ref _$S66=00a76660
// @ref __CIpow=007821b0
// @ref __ftol=0077f110
// @ref __real@8@3ff78000000000000000=0079a730
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@40008000000000000000=0079a6f8
// @ref __real@8@4004b400000000000000=0079a710
// @ref __real@8@4004f000000000000000=0079a718
// @ref __real@8@4005b400000000000000=0079a720
// @ref __real@8@40078000000000000000=0079a700
// @ref _atexit=0078298a
// @ref _unknown_geometry_angle45=00a76778
// @ref _unknown_geometry_angle60=00a766d0
// @ref _unknown_geometry_angle90=00a76668
// @ref _unknown_geometry_b=00a76798
// @ref _unknown_geometry_c=00a76780
// @ref _unknown_geometry_deg_to_rad=007a81d0
// @ref _unknown_geometry_diagonal=00a766a8
// @ref _unknown_geometry_g=00a767a0
// @ref _unknown_geometry_h=00a766f0
// @ref _unknown_geometry_i=00a76730
// @ref _unknown_geometry_j=00a76794
// @ref _unknown_geometry_k=00a766a4
// @ref _unknown_geometry_l=00a76718
// @ref _unknown_geometry_sixty=007a81c8
// @ref _unknown_static_rect=00a76670
