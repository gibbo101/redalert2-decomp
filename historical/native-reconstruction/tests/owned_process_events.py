# SPDX-License-Identifier: GPL-3.0-or-later
"""Selected Process stores/queries/decisions; never every machine store.

Genuine guest actor addresses normalize to explicit logical ids. Unknown events,
addresses and malformed streams fail; no event is sorted or deduplicated.
"""
ACTORS = (0x1100000, 0x4100000)
MEMBER = {0x30, 0x75, 0x373, 0x374, 0xa0, 0xa4}
ACTOR = {0x74, 0x88, 0x8c, 0x90, 0x450, 0x558, 0x55c, 0x560, 0x57a, 0x57b, 0x5a0, 0x5a1}
ACTOR.update(range(0x4d0, 0x53c, 4))
# Include the new selected ordinary Advance stores and all logged word queries.
# This is still a selected projection, not every original machine store.
DRIVE = {*range(0x1c, 0x34, 4),0x40,0x44,0x48,0x4c,0x58,0x5c,0x63}

def actor_id(raw):
    assert raw in (0, *ACTORS), hex(raw)
    return ACTORS.index(raw) if raw else 0xffffffff

def original(events):
    selected = []
    i = 0
    while i < len(events):
        kind = events[i]
        if kind in ('write-actor', 'write-Drive'):
            id, off, size, value = map(int, events[i+1:i+5])
            if kind == 'write-actor' and off in MEMBER:
                selected.append(['w', 'a', id, off, actor_id(value) if off == 0x30 else value])
            elif kind == 'write-actor' and off in ACTOR:
                selected.append(['A', id, off, value])
            elif kind == 'write-Drive' and off in DRIVE:
                selected.append(['L', id, off, value])
            i += 5
        elif kind == 'query':
            id = int(events[i+1]); address = int(events[i+2], 16)
            count = 2 if address == 0x548070 else 3
            if address == 0x548070:
                selected.append(['Q','W',id,*map(int,events[i+3:i+5])])
            else:
                assert address in (0x548000, 0x55a280)
                selected.append(['Q', 'C' if address == 0x548000 else 'F', id, *map(int, events[i+3:i+3+count])])
            i += 3+count
        elif kind == 'w':
            selected.append(['w', events[i+1], *map(int, events[i+2:i+5])]); i += 5
        elif kind == 'decision':
            id, phase, caller, value = events[i+1:i+5]
            if phase in ('D', 'G'):
                selected.append([phase, int(id), int(value) & (255 if phase == 'G' else 0xffffffff)])
            i += 5
        elif kind == 'pathfinder':
            selected.append(['B', *map(int, events[i+1:i+3])]); i += 3
        elif kind == 'result':
            selected.append(['R', *map(int, events[i+1:i+3])]); i += 3
        elif kind == 'notify':
            i += 3
        elif kind in ('post', 'accessible'):
            i += 2
        elif kind == 'mission':
            i += 4
        else:
            raise ValueError(('Unknown original event', i, events[i:i+12]))
    return selected

def native(words, id):
    selected = []
    i = 0
    while i < len(words):
        kind = words[i]
        if kind in ('A', 'L'):
            off, value = map(int, words[i+1:i+3])
            if off in (ACTOR if kind == 'A' else DRIVE): selected.append([kind, id, off, value])
            i += 3
        elif kind == 'r':
            assert words[i+1] == 'A'
            off, value = map(int, words[i+2:i+4])
            if off in ACTOR: selected.append(['A', 1, off, value])
            i += 4
        elif kind == 'o':
            phase = words[i+1]
            count = 3 if phase == 'L' else 2
            value = [phase, *map(int, words[i+2:i+2+count])]
            if phase != 'L' or value[2] in DRIVE: selected.append(value)
            i += 2+count
        elif kind == 'w':
            selected.append(['w', words[i+1], *map(int, words[i+2:i+5])]); i += 5
        elif kind in ('C', 'F'):
            selected.append(['Q', kind, id, *map(int, words[i+1:i+4])]); i += 4
        elif kind == 'W':
            selected.append(['Q','W',id,*map(int,words[i+1:i+3])]);i += 3
        elif kind == 'T':
            i += 3
        elif kind == 'N':
            i += 2
        elif kind == 'P':
            i += 1
        elif kind == 'B':
            assert words[i:i+5] == ['B', 'J', 'V', '0', '1']; selected.append(['B', id, -1]); i += 5
        else:
            raise ValueError(('Unknown native event', i, words[i:i+12]))
    return selected

