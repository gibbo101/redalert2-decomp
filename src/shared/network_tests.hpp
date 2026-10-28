// Two session tests used by the multiplayer lobby and the game-mode classes
// (no data: safe to include anywhere).
#ifndef RA2_SHARED_NETWORK_TESTS_HPP
#define RA2_SHARED_NETWORK_TESTS_HPP

// A network-session test (0x0073C370; false unless game mode 4).
bool unknown_73c370();
// A second network-session test (0x0073C3A0; hypothesis).
bool unknown_73c3a0();

#endif
