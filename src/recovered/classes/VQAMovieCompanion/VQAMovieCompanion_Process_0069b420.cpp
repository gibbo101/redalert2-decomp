// bool VQAMovieCompanion::Unknown_0069B420(int time) (0x0069B420): shows every subtitle due at the movie
// time and clears the one that ran out; true when the surface changed.
bool VQAMovieCompanion::Unknown_0069B420(int time)
{
    if (SubTitles == 0) {
        return false;
    }
    bool update = false;
    while (SubTitleIndex < SubTitles->Count()) {
        SubTitle *subtitle = (*SubTitles)[SubTitleIndex];
        if (subtitle->Get_Display_Time() > (unsigned long)time) {
            break;
        }
        ActiveSubTitle = subtitle;
        SubTitleIndex++;
        if (Callback != 0) {
            Callback(subtitle);
        } else {
            Draw_Sub_Title(subtitle);
            update = true;
        }
    }
    if (ActiveSubTitle != 0) {
        if ((unsigned long)time >= ActiveSubTitle->Get_Display_Time() + ActiveSubTitle->Get_Display_Duration()) {
            ActiveSubTitle = 0;
            if (Callback == 0 && unknown_10 != 0) {
                unknown_10->Fill_Rect(unknown_14, 0);
                update = true;
                unknown_24 = unknown_14;
                unknown_14.Set(0, 0, 0, 0);
            }
        }
    }
    return update;
}
