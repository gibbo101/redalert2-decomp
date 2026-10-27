UnknownDescriptionList_00490E00::~UnknownDescriptionList_00490E00()
{
    if (Entries) {
        for (int i=0; i<Count; ++i) {
            if (Entries[i].Maps) {
                delete [] Entries[i].Name;
                delete [] Entries[i].AIName;
                delete [] Entries[i].Maps;
            }
            for (int j=0; j<Entries[i].Enemies.Count(); ++j) {
                delete [] Entries[i].Enemies[j];
            }
            Entries[i].Enemies.Clear();
            for (j=0; j<Entries[i].Players.Count(); ++j) {
                delete [] Entries[i].Players[j];
            }
            Entries[i].Players.Clear();
        }
        delete [] Entries;
        Entries = 0;
        Initialized = false;
    }
}
