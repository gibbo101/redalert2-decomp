# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual turret calls on the same two original Process/drawing actors."""
import struct
from collections import Counter
from original_owned_unit_processes import OwnedUnitProcessesOracle, ACTORS, DRIVES, TYPE, VT
from original_presentation import PresentationOracle, STACK, ARG
from original_foot_lit import ret
from verify_owned_turret_world import verify, RANGES
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EAX

TARGETS = (0x4300000, 0x4301000)


class OwnedTurretWorldOracle(OwnedUnitProcessesOracle):
    def va(self, address):
        return address if address in RANGES else super().va(address)

    def __init__(self, *args):
        self.turret_active = False
        super().__init__(*args)
        self.turret_inspection = verify(args[0].read_bytes())
        self.u.mem_map(TARGETS[0], 0x3000)
        for target in TARGETS:
            self.put(target, VT)
        self.manual = [False, False]
        self.turning = [False, False]
        self.turret_counts = Counter()
        self.turret_stores = []
        self.turret_instructions = set()
        self.u.hook_add(UC_HOOK_CODE, self.turret_code)
        self.u.hook_add(UC_HOOK_MEM_WRITE, self.turret_store)

    def turret_code(self, u, address, size, ctx):
        if not self.turret_active:
            return
        ecx = u.reg_read(UC_X86_REG_ECX)
        if address in (0x6d85a0, 0x6d8640):
            assert ecx == ACTORS[self.turret_actor]
            self.turret_counts[(self.turret_actor, 'weapon-slot' if address == 0x6d85a0 else 'weapon-disabled')] += 1
            ret(u, 0 if address == 0x6d85a0 else 4,
                TARGETS[0] + 0x2000 if address == 0x6d85a0 else 0)
            return
        assert any(a <= address and address + size <= a + n for a, n in {**self.movement_code, **RANGES}.items()), ('uninspected turret instruction', hex(address))
        self.turret_instructions.add(address)
        if address in (0x6fb890, 0x4b8a30, 0x4b8be0, 0x4b8c90):
            self.turret_counts[(self.turret_actor, hex(address))] += 1
        for branch, label in ((0x6fba10, 'busy'), (0x6fba64, 'destination'), (0x6fba76, 'body')):
            if address == branch:
                self.turret_counts[(self.turret_actor, label)] += 1
        # Facing SetDesired copies opaque padding from the temporary timer.
        if address == 0x4b8aec:
            self.put(u.reg_read(UC_X86_REG_ESP) + 0x18, 23 if self.turret_actor == 0 else -31)

    @property
    def movement_code(self):
        from original_owned_unit_processes import CODE
        return CODE

    def turret_store(self, u, access, address, size, value, ctx):
        if self.turret_active:
            for id, actor in enumerate(ACTORS):
                if actor <= address < actor + 0x1000:
                    assert id == self.turret_actor
                    self.turret_stores.append([id, address - actor, size, value & ((1 << (8 * size)) - 1)])

    def turret_call(self, id, tick, address, args=(), this=None, writes=()):
        assert not self.turret_active and id in (0, 1)
        self.turret_actor = id
        self.put(0xa40d2c, tick)
        actors = [bytes(self.u.mem_read(p, 0x1000)) for p in ACTORS]
        self.turret_active = True
        try:
            PresentationOracle.checked_call(self, address, args, ACTORS[id] + 0x2f8 if this is None else this,
                writes=[*writes, (ARG, 4)],
                inputs=[(p, 0x100) for p in DRIVES] + [(TYPE, 0xc00), (VT, 0x600),
                        *[(p, n) for p, n in RANGES.items()]])
            for actor, old in zip(ACTORS, actors):
                after = bytearray(self.u.mem_read(actor, 0x1000))
                for p, n in writes:
                    if actor <= p and p + n <= actor + 0x1000:
                        after[p - actor:p - actor + n] = old[p - actor:p - actor + n]
                assert after == old, ('turret changed unrelated actor bytes', hex(actor))
            return self.u.reg_read(UC_X86_REG_EAX)
        finally:
            self.turret_active = False

    def command_turret(self, id, tick, delta):
        self.manual[id] = True
        self.put(ARG, (self.movement.get(ACTORS[id] + 0x2f8, 'H') + delta) & 65535)
        self.turret_call(id, tick, 0x4b8a30, [ARG], writes=[(ACTORS[id] + 0x2f8, 24)])

    def update_turret(self, id, tick, manual, target, point):
        self.manual[id] = bool(manual)
        actor = ACTORS[id]
        old = self.movement.get(actor + 0x494)
        if target == 1:
            self.u.mem_write(TARGETS[id] + 0x88, struct.pack('<3i', *point))
        self.put(actor + 0x494, 0 if target == 0 else TARGETS[id] if target == 1 else ACTORS[1-id])
        # This scoped target association is supplied. Drawing retains its own
        # contact/lifetime boundary; it never imports a target from a receipt.
        try:
            if not manual:
                assert self.movement.get(actor + 0x228) == 0
                assert self.u.mem_read(TYPE + 0xaed, 1) == b'\0'
                self.turret_call(id, tick, 0x6fb890, this=actor,
                    writes=[(actor + 0x2f8, 24), (actor + 0x3f0, 4), (actor + 0x599, 1)])
            else:
                self.turret_counts[(id, 'manual-supplied-root-skip')] += 1
            rotating = bool(self.turret_call(id, tick, 0x4b8c90))
            self.turning[id] = rotating if manual else bool(self.movement.get(actor + 0x3f0))
            assert self.turning[id] == rotating, 'Original parent turning flag differs'
        finally:
            self.put(actor + 0x494, old)

    def turret_views(self, tick):
        result = []
        for id, actor in enumerate(ACTORS):
            self.turret_call(id, tick, 0x4b8be0, [ARG])
            current = self.movement.get(ARG, 'H')
            rotating = self.turret_call(id, tick, 0x4b8c90)
            result.extend(['turret-view', id, current, rotating & 255,
                           int(self.manual[id]), int(self.turning[id])])
        return result

    def initialize(self, *args):
        super().initialize(*args)
        self.manual = [False, False]
        self.turning = [False, False]
