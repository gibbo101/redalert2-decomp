// PlayerProfile::PlayerProfile(Wstring const &server, int locale, bool verified, int unknown_18, int country,
//                              int color, int rank, int points, int wins, int losses, int disconnects) (0x00738C40)
// The profile of a WOnline player: the server name, locale, verified flag and the ladder numbers
// (Load_Default 0x00738670 builds one from wolinfo.ini with -1 for the numbers; the field names are
// hypotheses after the parameters).
// @ref ??_7ReferenceCounted@@6B@=007a8d14
// @ref ??_7PlayerProfile@@6B@=007af554
// @ref ??0Wstring@@QAE@ABV0@@Z=0076d980
#include "shared/wol_sink.hpp"

PlayerProfile::PlayerProfile(Wstring const &server, int locale, bool verified, int unknown_18_value, int country,
                             int color, int rank, int points, int wins, int losses, int disconnects)
    : unknown_08(false), Server(server), unknown_10(locale), Verified(verified), unknown_18(unknown_18_value),
      Country(country), Color(color), Rank(rank), Points(points), Wins(wins), Losses(losses),
      Disconnects(disconnects)
{
}
