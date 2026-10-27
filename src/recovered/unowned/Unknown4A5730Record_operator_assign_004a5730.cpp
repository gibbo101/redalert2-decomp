GadgetClass &GadgetClass::operator=(GadgetClass const &gadget)
{
 LinkClass::operator=(const_cast<GadgetClass &>(gadget));
 X=gadget.X;
 Y=gadget.Y;
 Width=gadget.Width;
 Height=gadget.Height;
 IsToRepaint=gadget.IsToRepaint;
 IsSticky=gadget.IsSticky;
 IsDisabled=gadget.IsDisabled;
 Flags=gadget.Flags;
 return *this;
}
