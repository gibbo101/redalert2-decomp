# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual Scatter children on the existing distinct Process/drawing guest.

Only routing, heap/atomic and named mission effects are supplied. Actor identity
changes only for the dynamic extent of an actual Cell -> Unit dispatch. There
is no second guest or copied actor arena.
"""
import struct
from collections import Counter
from original_owned_unit_processes import AttachedProcesses, ACTORS, DRIVES, CODE
from original_owned_unit_world import VT, RULES, CELLS, TACTICAL
from original_owned_orders_world import OwnedOrdersWorldOracle
from original_map_preparation import MAP
from verify_process_preparation_scatter import verify, RANGES, TABLES
from verify_advance_terminal import STORES as TERMINAL_STORES
from unicorn.x86_const import UC_X86_REG_ESP, UC_X86_REG_ECX, UC_X86_REG_EIP

HEAP, HEAP_SIZE = 0x4400000, 0x10000
INC, DEC = 0x3c7594, 0x3c757c
DESTINATION_FIELDS = ((0x190, 1), (0x47c, 4), (0x480, 8), (0x488, 4),
                      (0x490, 8), (0x598, 1))
DESTINATION_STORES = {
    0x705491: (0x190, 1), 0x70581c: (0x4d0, 4),
    0x4cde39: (0x488, 4), 0x4cde4e: (0x47c, 4),
    0x4cde51: (0x485, 1), 0x4cde54: (0x480, 4),
    0x4c8041: (0x490, 4), 0x4c8047: (0x494, 4),
    0x4c8119: (0x598, 1), 0x4c81c4: (0x494, 4),
    0x4c81ca: (0x5a1, 1), 0x4c81ea: (0x558, 4),
    0x4c81f0: (0x55c, 4), 0x4c81f3: (0x560, 4),
    0x4c8207: (0x530, 4), 0x4c820a: (0x534, 4), 0x4c820d: (0x538, 4),
}
TERMINAL_DRIVE_STORES = {ip:(off,n) for ip,(owner,off,n) in TERMINAL_STORES.items() if owner == 'd'}


class AttachedScatterProcesses(AttachedProcesses):
    code_ranges = {a: max(CODE.get(a, 0), RANGES.get(a, 0)) for a in CODE.keys() | RANGES.keys()}
    allowed_advance_results = (0, 2, 6, 7)
    # Other ordinary-profile exclusions remain inherited and explicit.
    unsupported_entries = (0x4a3ab5,)

    def __init__(self, owner):
        self.cell_scope = self.unit_scope = self.destination_scope = None
        self.scatter_counts = Counter()
        self.pending_routes = [False, False]
        self.scatter_destinations = []
        self.route_attempted = False
        self.heap_buffer = self.heap_capacity = 0
        super().__init__(owner)
        self.scatter_inspection = verify(owner.exe.read_bytes())
        self.u.mem_map(HEAP, HEAP_SIZE)
        self.u.mem_map(0x3c7000, 0x1000)

    def actor_fields(self, id):
        # Whole-call arena audit plus the narrower per-instruction store guard.
        return (*super().actor_fields(id), *DESTINATION_FIELDS, (0x4d0, 108),
                (0x558, 12), (0x5a1, 1), (0x53c, 4))

    def drive_fields(self, id):
        return (*super().drive_fields(id), (0x14, 4), (0x34, 12), (0x50, 8))

    def extra_call_writes(self):
        return ((HEAP, HEAP_SIZE), (0xa6eb14, 4))

    def extra_call_inputs(self):
        return (*TABLES.items(), (0x83996c, 4), (0xa6f238, 4), (0x852998, 12),
                (0xa403b0 + 64, 32), (MAP + 0xf0, 24), (0xa35dec, 4),
                (0xa40d2c, 4), (0x8529d0, 4))

    def begin(self, *args):
        super().begin(*args)
        self.pending_routes = [False, False]
        self.scatter_destinations = []
        self.put(VT + 0x410, 0x7053f0)  # Actual destination, not mission414.
        self.virtual(0x414, 8, self.mission, 'supplied mission414')
        self.put(RULES + 0x13d0, 8)
        self.put(RULES + 0x1380, 0)
        self.put(RULES + 0x10b4, 0)
        self.put(RULES + 0x1431, 1, 'B')
        self.put(0xa6eb14, 0)
        self.put(0xa6f238, 0)
        # Separate Drive global: the graphics guest initializes Cell/shadow
        # globals only. The distinct ten-root Drive initializer proof already
        # establishes 104; here this remains an explicit supplied initial value.
        assert self.owner.map_config[4] == 104
        self.put(0x8529d0, 104)
        self.u.mem_write(0x852998, bytes(12))
        self.u.mem_write(0xa403b0 + 64, bytes(32))
        for actor, drive in zip(ACTORS, DRIVES):
            self.put(actor + 0x478, 0x7a177c)
            self.put(actor + 0x574, -1, 'b')
            self.put(actor + 0x5c0, -1)
            self.put(actor + 0x58c, -1)
            self.put(actor + 0x53c, 0)
            self.put(drive + 0x14, 1)
            self.put(drive + 0x18, 0x7a04a8)
        self.hooks[0x40cd40] = (8, self.grow_snapshot, 'supplied snapshot growth')
        self.hooks[0x781d3b] = (0, self.release_snapshot, 'supplied snapshot release')
        self.hooks[INC] = (4, lambda: self.atomic(1), 'supplied atomic increment')
        self.hooks[DEC] = (4, lambda: self.atomic(-1), 'supplied atomic decrement')
        assert self.get(0x83996c) == TACTICAL  # Projection reads static Map itself.

    def grow_snapshot(self):
        sp = self.u.reg_read(UC_X86_REG_ESP)
        vector = self.u.reg_read(UC_X86_REG_ECX)
        assert self.cell_scope and self.get(sp) == 0x4769e6
        assert self.arg(0) == self.heap_capacity + 10 and self.arg(1) == 0
        assert self.heap_capacity == 0 and self.get(vector + 16) == 0
        self.heap_buffer, self.heap_capacity = HEAP, 10
        self.put(vector + 4, HEAP)
        self.put(vector + 8, 10)
        self.put(vector + 13, 1, 'B')
        self.scatter_counts['supplied.snapshot_growth'] += 1
        return 1

    def release_snapshot(self):
        assert self.cell_scope and self.get(self.u.reg_read(UC_X86_REG_ESP)) == 0x476ab4
        assert self.arg(0) == self.heap_buffer
        self.scatter_counts['supplied.snapshot_release'] += 1
        return 0

    def atomic(self, delta):
        assert (self.destination_scope or self.unit_scope) and self.arg(0) == DRIVES[self.actor] + 0x14
        value = self.get(self.arg(0)) + delta
        assert 0 < value < 0x80000000
        self.put(self.arg(0), value)
        self.scatter_counts['supplied.atomic.' + str(delta)] += 1
        return value

    def actor_store_guard(self, id, off, n, ip):
        if self.destination_scope:
            assert id == self.actor and DESTINATION_STORES.get(ip) == (off, n), ('destination actor store', id, hex(ip), hex(off), n)
            return
        if ip in (0x4cd9b2, 0x4cd9b8):
            assert id == self.actor and (off, n) == (0x490 if ip == 0x4cd9b2 else 0x494, 4)
            return
        if off == 0x53c:
            assert id == self.actor and n == 4 and ip == 0x4a32b7
            self.scatter_counts['actual.counter.' + str(id)] += 1
            return
        return super().actor_store_guard(id, off, n, ip)

    def drive_store_guard(self, id, off, n, ip):
        if self.destination_scope:
            sites = {0x49fe89: (0x34, 4), 0x49fe8c: (0x38, 4), 0x49fe8f: (0x3c, 4),
                     0x49ffa0: (0x34, 4), 0x49ffa7: (0x38, 4), 0x49ffb0: (0x3c, 4), 0x49ff94: (0x50, 8)}
            assert id == self.actor and sites.get(ip) == (off, n), ('destination Drive store', id, hex(ip), off, n)
            return
        return super().drive_store_guard(id, off, n, ip)

    def observe(self, u, a, n, ctx):
        if not self.active:
            return
        sp, ecx = u.reg_read(UC_X86_REG_ESP), u.reg_read(UC_X86_REG_ECX)
        if self.destination_scope and self.destination_scope[:2] == (a, sp):
            self.destination_scope = None
        if self.unit_scope and self.unit_scope[:2] == (a, sp):
            assert self.destination_scope is None and self.phase is None
            _, _, self.actor = self.unit_scope
            self.unit_scope = None
        if self.cell_scope and self.cell_scope[:2] == (a, sp):
            assert self.unit_scope is None
            self.cell_scope = None
        if a == 0x476920:
            assert self.cell_scope is None and self.unit_scope is None and self.phase is None
            assert self.get(sp) in (0x4a32b4, 0x4a3936, 0x4a43fd, 0x4a1f8d)
            assert [self.arg(i) for i in range(3)] == [0x852998, 1, 1]
            self.cell_scope = (self.get(sp), sp + 20, ecx)
            self.heap_capacity = self.heap_buffer = 0
            self.scatter_counts['actual.Cell.' + hex(self.get(sp))] += 1
        if a == 0x7072d0:
            assert self.cell_scope and self.unit_scope is None and self.get(sp) == 0x476a89
            assert ecx in ACTORS and self.arg(0) == 0x852998
            self.unit_scope = (self.get(sp), sp + 16, self.actor)
            self.actor = ACTORS.index(ecx)
            self.scatter_counts['actual.Unit.' + str(self.actor)] += 1
        if a == 0x7053f0:
            assert self.destination_scope is None and ecx == ACTORS[self.actor]
            target = self.arg(0)
            assert target == 0 or (self.unit_scope and CELLS <= target < CELLS + self.prepared.count * 512 and (target-CELLS) % 512 == 0)
            self.destination_scope = (self.get(sp), sp + 12, target)
            self.scatter_counts['actual.destination.' + str(self.actor)] += 1
        if a == 0x4c8030:
            assert self.destination_scope and ecx == ACTORS[self.actor]
            self.put(sp - 0x18, 0)  # Supplied skipped-query scratch.
        if a == 0x5502e0:
            assert self.unit_scope and ecx == MAP
            self.scatter_counts['actual.nearby.' + str(self.actor)] += 1
        assert a not in (0x54f8f0, 0x47c200, 0x7055bc, 0x7056bb, 0x7056e0, 0x7057d3), ('unsupported Scatter child', hex(a))
        return super().observe(u, a, n, ctx)

    def store(self, u, access, p, n, value, ctx):
        if self.active:
            ip = u.reg_read(UC_X86_REG_EIP)
            if ip in TERMINAL_DRIVE_STORES:
                off, width = TERMINAL_DRIVE_STORES[ip]
                assert self.destination_scope is self.unit_scope is self.cell_scope is None
                assert (p, n) == (DRIVES[self.actor] + off, width), ('terminal Drive store', hex(ip), hex(p), n)
                self.drive_store_sites[hex(ip)] += 1
                self.event('write-Drive', self.actor, off, n, value & ((1 << (8*n))-1))
                return
            if HEAP <= p < HEAP + HEAP_SIZE:
                assert self.cell_scope and ip == 0x4769f9 and n == 4 and self.heap_buffer <= p < self.heap_buffer + self.heap_capacity * 4
                assert value in ACTORS
                return
            if p == 0xa6eb14:
                assert (self.destination_scope or self.unit_scope) and n == 4 and ip in (0x53d25f, 0x53d280), ('reference store', hex(ip), self.actor)
                assert value & 0xffffffff == (self.get(p) + (1 if ip == 0x53d25f else -1)) & 0xffffffff
                return
            if self.destination_scope and p == ACTORS[self.actor] + 0x494:
                self.pending_routes[self.actor] = bool(value)
        return super().store(u, access, p, n, value, ctx)

    def pathfinder(self):
        assert self.u.reg_read(UC_X86_REG_ECX) == ACTORS[self.actor]
        caller = self.get(self.u.reg_read(UC_X86_REG_ESP))
        assert caller in (0x4a28e7, 0x4a3a0a), ('unsupported routing caller', hex(caller))
        if caller == 0x4a3a0a:
            # Production's moving-wait service supplies failure; only initial
            # preparation has the separately supplied positive route callback.
            self.scatter_counts['supplied.failed_route.' + str(self.actor)] += 1
            return super().pathfinder()
        assert [self.arg(1), self.arg(2)] == [0, 0]
        self.scatter_counts['supplied.route_attempt.' + str(self.actor)] += 1
        if self.route_attempted:
            return 0
        self.route_attempted = True
        destination = struct.unpack('<3i', self.u.mem_read(DRIVES[self.actor] + 0x34, 12))
        if destination == (0, 0, 0):
            return 0
        return int(self.owner.supply_route(self.actor, destination[0] // 256, destination[1] // 256))

    def advance_actor(self, id, tick):
        self.route_attempted = False
        result = super().advance_actor(id, tick)
        assert self.cell_scope is self.unit_scope is self.destination_scope is None
        return result


class OwnedScatterWorldOracle(OwnedOrdersWorldOracle):
    movement_type = AttachedScatterProcesses

    def __init__(self, exe, *args):
        self.exe = exe
        super().__init__(exe, *args)

    def hook(self, u, a, n, ctx):
        # RasterOracle owns loader allocations during loading/drawing. This
        # actual Cell snapshot owns a disjoint heap; its attached service alone
        # validates and releases it. Do not run both service implementations.
        m = getattr(self, 'movement', None)
        if a == 0x781d3b and m is not None and m.active:
            assert m.cell_scope and a in m.hooks
            return
        return super().hook(u, a, n, ctx)

    def supply_route(self, id, x, y):
        """Same explicitly supplied direct-routing policy as the production owner."""
        m = self.movement
        drive, actor = DRIVES[id], ACTORS[id]
        anchor = drive + 0x40 if m.get(drive + 0x63, 'B') else actor + 0x88
        ax, ay, _ = struct.unpack('<3i', self.u.mem_read(anchor, 12))
        dx, dy = x - int(ax / 256), y - int(ay / 256)
        if not 0 <= x < 512 or not 0 <= y < 512 or not 0 < max(abs(dx), abs(dy)) <= 23:
            return False
        directions = [(0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1)]
        route = []
        while dx or dy:
            sx, sy = (dx > 0) - (dx < 0), (dy > 0) - (dy < 0)
            route.append(directions.index((sx, sy)))
            dx, dy = dx - sx, dy - sy
        self.u.mem_write(actor + 0x4d0, struct.pack('<24i', *(route + [-1] * (24-len(route)))))
        self.navigation[id] = struct.unpack('<3i', self.u.mem_read(drive + 0x34, 12))
        self.pending[id], self.manual[id], self.stopped[id] = None, False, False
        m.scatter_counts['supplied.positive_route.' + str(id)] += 1
        return True

    def follow_scatter(self):
        m = self.movement
        for id in (0, 1):
            if not m.pending_routes[id]:
                continue
            p = m.get(ACTORS[id] + 0x494)
            assert p and self.supply_route(id, *struct.unpack('<2h', self.u.mem_read(p + 0x24, 4)))
            m.scatter_destinations.append([m.tick, id, *struct.unpack('<3i', self.u.mem_read(DRIVES[id] + 0x34, 12))])
            m.pending_routes[id] = False
