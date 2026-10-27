
// @ref ??_E?$VectorCursor@V?$rc_ptr@VGameOption@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VGameOption@WorldDominationTour@@@@@@@@UAEPAXI@Z=00727d80
// @ref ?Valid@?$VectorCursor@V?$rc_ptr@VGameOption@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VGameOption@WorldDominationTour@@@@@@@@UBE_NXZ=00727cb0
// @ref ?Next@?$VectorCursor@V?$rc_ptr@VGameOption@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VGameOption@WorldDominationTour@@@@@@@@UAEAAV1@XZ=00728330
// @ref ?Prev@?$VectorCursor@V?$rc_ptr@VGameOption@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VGameOption@WorldDominationTour@@@@@@@@UAEAAV1@XZ=00728340
// @ref ??_7?$VectorCursor@V?$rc_ptr@VGameOption@WorldDominationTour@@@@V?$DynamicVectorClass@V?$rc_ptr@VGameOption@WorldDominationTour@@@@@@@@6B@=007af0e4
namespace WorldDominationTour {

// The description of this battle's settings: up to six options, first those
// whose value for the territory is 0, then the rest that are not forced (2);
// an option's Flag bit keeps a second option of the same kind out.
WideString Conflict::Describe_Options() const
{
    if (unknown_game_options_b256c0.Count() == 0) {
        Init_Options();
    }
    int remaining = 6;
    WideString text;
    int used = 0;
    VectorCursor<rc_ptr<GameOption>, DynamicVectorClass<rc_ptr<GameOption> > > cursor(unknown_game_options_b256c0);
    for (; remaining != 0 && cursor; ++cursor) {
        rc_ptr<GameOption> option = *cursor;
        if (!(option->Flag & used) && option->Get_Value(Territory) == 0) {
            text = option->Describe(Territory, text);
            remaining--;
            used |= option->Flag;
        }
    }
    cursor.Index = 0;
    for (; remaining != 0 && cursor; ++cursor) {
        rc_ptr<GameOption> option = *cursor;
        if (!(option->Flag & used) && option->Get_Value(Territory) != 2) {
            text = option->Describe(Territory, text);
            remaining--;
            used |= option->Flag;
        }
    }
    return text;
}

}
