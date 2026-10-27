# SPDX-License-Identifier: GPL-3.0-or-later
"""Per-actor commands on genuine shared Process/drawing guest records."""
import struct
from collections import Counter
from original_owned_turret_world import OwnedTurretWorldOracle, ACTORS, DRIVES
from original_owned_unit_world import FALLBACK, TYPE, VT, PresentationOracle
from original_presentation import ARG
from original_foot_lit import ret
from verify_owned_orders_world import RANGES, verify
from verify_owned_turret_world import RANGES as TURRET_RANGES
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX, UC_X86_REG_ESP


class OwnedOrdersWorldOracle(OwnedTurretWorldOracle):
    def va(self, address):
        return address if address in RANGES else super().va(address)

    def __init__(self, *args):
        self.order_active = False
        super().__init__(*args)
        self.order_inspection = verify(args[0].read_bytes())
        self.allowed = sorted(set(self.allowed + [(a, a+n) for a, n in RANGES.items()]), reverse=True)
        self.order_counts = Counter()
        self.order_stores = []
        self.order_instructions = set()
        self.u.hook_add(UC_HOOK_CODE, self.order_code)
        self.u.hook_add(UC_HOOK_MEM_WRITE, self.order_store)

    def initialize(self, *args):
        super().initialize(*args)
        self.navigation = [None, None]
        self.pending = [None, None]
        self.stopped = [False, False]

    def order_code(self, u, address, size, ctx):
        if not self.order_active:
            return
        id = self.order_actor
        if address in self.movement.hooks:
            count, fn, label = self.movement.hooks[address]
            assert label in ('disabled A', 'disabled B') and u.reg_read(UC_X86_REG_ECX) == ACTORS[id]
            self.order_counts[(id, label+'-supplied')] += 1
            ret(u, count, fn())
            return
        assert any(a <= address and address+size <= a+n for a, n in
                   {**self.movement_code, **TURRET_RANGES, **RANGES}.items()), ('uninspected command', hex(address))
        self.order_instructions.add(address)
        if address in RANGES:
            self.order_counts[(id, hex(address))] += 1
        if address == 0x4b8aec:
            self.movement.put(u.reg_read(UC_X86_REG_ESP)+0x18, 23 if id == 0 else -31)

    def order_store(self, u, access, address, size, value, ctx):
        if self.order_active:
            self.order_stores.append([self.order_actor, address, size, value & ((1 << (8*size))-1)])

    def order_call(self, id, tick, address, args, writes):
        assert id in (0, 1) and not self.order_active and not self.turret_active
        self.order_actor = id
        self.movement.put(0xa40d2c, tick)
        arenas = [(p, bytes(self.u.mem_read(p, n))) for p, n in
                  [*[(p, 0x1000) for p in ACTORS], *[(p, 0x100) for p in DRIVES]]]
        self.order_active = True
        try:
            PresentationOracle.checked_call(self, address, args, 0, writes=[*writes, (ARG, 4)],
                inputs=[(TYPE, 0xc00), (VT, 0x600), *RANGES.items(), *TURRET_RANGES.items(),
                        (0x79ea48, 8), (0x852998, 12)])
            for p, old in arenas:
                after = bytearray(self.u.mem_read(p, len(old)))
                for start, n in writes:
                    if p <= start and start+n <= p+len(old):
                        after[start-p:start-p+n] = old[start-p:start-p+n]
                assert after == old, ('command changed unrelated actor/Drive', hex(p))
        finally:
            self.order_active = False

    def order(self, id, tick, target, directions):
        assert 1 <= len(directions) <= 23 and all(0 <= d <= 7 for d in directions)
        self.order_call(id, tick, 0x49fe30, [DRIVES[id]+4, *target],
                        [(DRIVES[id]+0x34, 12), (FALLBACK+0x24, 4)])
        self.u.mem_write(ACTORS[id]+0x4d0, struct.pack('<24i', *(directions+[-1]*(24-len(directions)))))
        self.navigation[id] = tuple(target)
        self.pending[id] = None
        self.manual[id] = False
        self.stopped[id] = False

    def stop_order(self, id, tick):
        assert self.movement.get(TYPE+0xaa0, 'B') == 0
        assert self.u.mem_read(0x852998, 12) == bytes(12)
        self.order_call(id, tick, 0x49fef0, [DRIVES[id]+4], [(DRIVES[id]+0x34, 12), (DRIVES[id]+0x50, 8)])
        self.u.mem_write(ACTORS[id]+0x4d0, struct.pack('<24i', *([-1]*24)))
        self.navigation[id] = self.pending[id] = None
        self.stopped[id] = True

    def do_turn(self, id, tick, heading):
        self.order_call(id, tick, 0x4a0fd0, [DRIVES[id]+4, heading], [(ACTORS[id]+0x2e0, 24)])

    def turn_body(self, id, tick, delta):
        wanted = (self.movement.get(ACTORS[id]+0x2e0, 'H') + delta) & 65535
        self.stop_order(id, tick)
        if self.movement.get(DRIVES[id]+0x63, 'B'):
            self.pending[id] = wanted
            self.order_counts[(id, 'deferred-body')] += 1
        else:
            self.do_turn(id, tick, wanted)
            self.order_counts[(id, 'idle-body')] += 1

    def finish_tick(self, id, tick):
        driving = self.movement.get(DRIVES[id]+0x63, 'B')
        if not driving and self.movement.get(ACTORS[id]+0x4d0, 'i') == -1:
            self.u.mem_write(DRIVES[id]+0x34, bytes(12))
            self.navigation[id] = None
        self.update_turret(id, tick, int(self.manual[id]), int(self.navigation[id] is not None),
                           self.navigation[id] or (0, 0, 0))
        if not driving and self.pending[id] is not None:
            self.do_turn(id, tick, self.pending[id])
            self.pending[id] = None
            self.order_counts[(id, 'applied-deferred-body')] += 1

    def command_views(self):
        result = []
        for id in (0, 1):
            result.extend(['command-view', id, int(self.navigation[id] is not None), *(self.navigation[id] or (0, 0, 0)),
                           int(self.pending[id] is not None), self.pending[id] or 0, int(self.stopped[id])])
        return result
