// The waypoint names (WaypointPath.cpp; moved out of shared/waypoint_path.hpp
// so a unit can name waypoints without the path classes and their vector
// instantiations).
#ifndef RA2_SHARED_WAYPOINT_STRING_HPP
#define RA2_SHARED_WAYPOINT_STRING_HPP

// A waypoint number as letters: 0..25 "A".."Z", then "AA", "AB", ...; -1
// the empty string (static buffer 0x00B255D0; names hypotheses).
char const *__fastcall Waypoint_As_String(int index);  // 0x007249F0
int __fastcall Waypoint_From_String(char const *string);   // 0x00724A70 (inverse; -1 when not a letter)

#endif
