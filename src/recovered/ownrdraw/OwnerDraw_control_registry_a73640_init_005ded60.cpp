// The ownrdraw control registry at 0x00A73640 as wlib's chained dictionary (shared/wol_dictionary.hpp),
// keyed by window handle value: its dynamic initializer (0x005DED60) inlines the constructor and
// registers the atexit destructor (0x005DEE00, the next draft), which inlines the destructor with each
// record's destructor, clear() and shrink(). The same object is unknown_registry_a73640
// (UnknownControlIndex) to the unit's other functions (hypothesis: one wlib Dictionary instance).
// @ref ?unknown_control_table_a73640@@3V?$WolDictionary@IUUnknownControlRecord@OwnerDraw@@@@A=00a73640
// @ref ?unknown_hash_key_5de970@@YIIABI@Z=005de970
// @ref ??_GWideString@@QAEPAXI@Z=00601430
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

inline UnknownControlRecord::~UnknownControlRecord()
{
    Set_Wide_Text_600510(0);
    while (list_34) {
        ((UnknownNodeList_006003d0 *)this)->unknown_remove_node(list_34);
    }
    delete unknown_3c;
}

}

// The key's value as its hash (0x005DE970, shared with the window tables).
unsigned int __fastcall unknown_hash_key_5de970(unsigned int const &key);

WolDictionary<unsigned int, OwnerDraw::UnknownControlRecord> unknown_control_table_a73640(unknown_hash_key_5de970);
