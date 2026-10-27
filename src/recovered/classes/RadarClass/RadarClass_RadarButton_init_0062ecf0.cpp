// Dynamic initializer of RadarClass::RadarButton (0x0062ECF0, _$E) and its
// guarded atexit destructor (0x0062ED20), emitted by this definition; the
// two shape buttons' pairs (0x0062ED50/0x0062ED70, 0x0062EDA0/0x0062EDC0)
// follow from theirs, with the do-nothing initializers of the cell and
// coordinate statics (0x0062ED40, 0x0062ED90) between them. The guard byte of the three is 0x00AB6308.
#include "shared/radar.hpp"
// @ref ??0GadgetClass@@QAE@HHHHI_N@Z=004cefe0
// @ref ??1GadgetClass@@UAE@XZ=004cf080
// @ref ??_7RTacticalClass@@6B@=007a8694
// @ref ??0ShapeButtonClass@@QAE@XZ=00675020
// @ref ??1ShapeButtonClass@@UAE@XZ=006750f0
// @ref _atexit=0078298a
// @ref ?RadarButton@RadarClass@@2VRTacticalClass@@A=00ab6478
// @ref ?unknown_button_ab63e8@RadarClass@@2VShapeButtonClass@@A=00ab63e8
// @ref ?unknown_button_ab6380@RadarClass@@2VShapeButtonClass@@A=00ab6380

RTacticalClass RadarClass::RadarButton;
Cell RadarClass::unknown_cell_ab6330;
ShapeButtonClass RadarClass::unknown_button_ab63e8;
CoordStruct RadarClass::unknown_coord_ab6370;
ShapeButtonClass RadarClass::unknown_button_ab6380;
// @ref _$E61=0062ed20
// @ref _$E61=0062ed70
// @ref _$E66=0062edc0
// @ref _$S56=00ab6308
// @ref ?unknown_cell_ab6330@RadarClass@@2VCell@@A=00ab6330
// @ref ?unknown_coord_ab6370@RadarClass@@2UCoordStruct@@A=00ab6370
