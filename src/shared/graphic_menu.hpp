// The graphic menu items (RTTI GraphicMenuItem, vtable 0x007A2BD0, and its
// subclasses GraphicMenuAnimItem 0x007A2B98, GraphicMenuImageItem 0x007A2BB4,
// GraphicMenuShortcutItem 0x007A2BEC); one unit per class around
// 0x004DE880-0x004E06D0. Layout from the constructor 0x004E0120 and the
// destructor 0x004E0140; slot names past the destructor are hypotheses.
#ifndef RA2_SHARED_GRAPHIC_MENU_HPP
#define RA2_SHARED_GRAPHIC_MENU_HPP

#include "shared/shape_file.hpp"   // its empty-rect static is each GraphicMenu unit's first initializer
#include "shared/ms_choice.hpp"
#include "shared/ms_anim.hpp"
#include "shared/vector_class.hpp"

struct Point2D;
struct INIRect;
class Wstring;

class GraphicMenuItem {
public:
    GraphicMenuItem(int id);                                     // 0x004E0120
    virtual ~GraphicMenuItem();                                  // 0x004E0140 (scalar deleting 0x004E01F0)
    virtual bool unknown_slot1(int unknown);                     // 0x004E01D0 (false)
    virtual bool Contains(Point2D const &point);                 // 0x004E01C0 (false; the subclasses hit-test their rectangle)
    virtual void Play_Sound(int unknown);                        // 0x004E01E0
    virtual void Enabled_Changed(bool enabled);                  // 0x004E01A0 (empty)
    virtual void Visible_Changed(bool visible);                  // 0x004E01B0 (empty)

    void Set_Enabled(bool enabled);                              // 0x004E0160
    void Set_Visible(bool visible);                              // 0x004E0180

    int ID;                                                      // +0x04
    bool Enabled;                                                // +0x08
    bool Visible;                                                // +0x09
    MSSfxEntry *Sound;                                           // +0x0C
};

// An item showing an animation (constructor 0x004DF5F0, made by Create_Anim_Item 0x004DF350).
class GraphicMenuAnimItem : public GraphicMenuItem {
public:
    // unknown_list receives the loaded animation (0x005B2D60); argument names are hypotheses.
    GraphicMenuAnimItem(int id, void *unknown_list, Point2D const &origin, INIRect const &area,
                        Wstring const &image, Wstring const &palette, int rate, bool loop);   // 0x004DF5F0
    virtual ~GraphicMenuAnimItem();                              // 0x004DF740 (scalar deleting 0x004DF7B0)
    virtual bool Contains(Point2D const &point);                 // 0x004DF760

    Rect Area;                                                   // +0x10
    int unknown_20;                                              // +0x20
    MSAnim *Anim;                                                // +0x24 (made by 0x005AC560, deleted here)
};

// An item with three PCX images and a hover sound (constructor 0x004DFB30, made by
// Create_Image_Item 0x004DF810).
class GraphicMenuImageItem : public GraphicMenuItem {
public:
    // Argument names are hypotheses (Create_Image_Item 0x004DF810 reads them from the menu INI).
    GraphicMenuImageItem(int id, void *unknown_list, Point2D const &origin, INIRect const &area,
                         Wstring const &image, Wstring const &highlighted, Wstring const &disabled,
                         Wstring const &highlight_sound, Wstring const &select_vq);   // 0x004DFB30
    virtual ~GraphicMenuImageItem();                             // 0x004DFCD0 (scalar deleting 0x004DFF10)
    virtual bool Contains(Point2D const &point);                 // 0x004DFD10
    virtual void Play_Sound(int unknown);                        // 0x004DFE70 (vtable 0x007A2BB4 slot 3)
    virtual void Enabled_Changed(bool enabled);                  // 0x004DFD60 (slot 4)
    virtual void Visible_Changed(bool visible);                  // 0x004DFDF0 (slot 5)

    int unknown_10;                                              // +0x10
    Rect Area;                                                   // +0x14
    MSPCXAnim *unknown_image_24;                                 // +0x24
    MSPCXAnim *unknown_image_28;                                 // +0x28
    MSPCXAnim *unknown_image_2c;                                 // +0x2C
    MSSfxEntry *unknown_sound_30;                                // +0x30
    Wstring unknown_name_34;                                     // +0x34
};

// An item with a list of keyboard shortcuts (constructor 0x004E0310, made by
// Create_Shortcut_Item 0x004E0250).
class GraphicMenuShortcutItem : public GraphicMenuItem {
public:
    GraphicMenuShortcutItem(int id, Wstring const &keys);       // 0x004E0310
    virtual ~GraphicMenuShortcutItem();                          // 0x004E0560 (scalar deleting 0x004E0630)
    virtual bool unknown_slot1(int key);                         // 0x004E05B0

    DynamicVectorClass<unsigned int> Keys;                       // +0x10 (vtable 0x0079C4DC, growth step 10; key codes from Parse_Shortcut_Key)
};

#endif
