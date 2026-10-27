"""Assign functions to original classes from manifests/rtti_classes.json.

A virtual slot belongs to the most-base class whose vtable contains it (the
class that introduced or last overrode it for all others). A vptr-writing
function (constructor/destructor candidate) belongs to the most-derived class
whose primary vtable it stores. Functions shared by unrelated classes, or seen
only in secondary vtables, get no owner rather than a guess.
"""
import json
from pathlib import Path

REPOSITORY = Path(__file__).resolve().parents[2]


class ClassOwners:
    def __init__(self, path=REPOSITORY / 'manifests/rtti_classes.json'):
        tables = json.loads(Path(path).read_text())['vtables'] if Path(path).exists() else []
        self.primary = {t['class_name']: t for t in tables if t['class_name'] and not t['object_offset']}
        self.ancestors = {name: [b['name'] for b in t['bases']] for name, t in self.primary.items()}
        self.slots, self.writers = {}, {}
        for name, t in self.primary.items():
            for index, entry in enumerate(t['slots']):
                self.slots.setdefault(int(entry, 16), []).append((name, index))
            for entry in t['vptr_writers']:
                self.writers.setdefault(int(entry, 16), []).append(name)

    def is_base(self, base, derived):
        return base == derived or base in self.ancestors.get(derived, [])

    def owner(self, entry):
        """(class name, description) or None."""
        holders = self.slots.get(entry)
        if holders:
            names = {n for n, _ in holders}
            roots = [n for n in names if all(self.is_base(n, other) for other in names)]
            if len(roots) == 1:
                index = min(i for n, i in holders if n == roots[0])
                return roots[0], 'virtual slot %d (vtable +0x%x)' % (index, 4 * index)
            return None
        writers = self.writers.get(entry)
        if writers:
            names = set(writers)
            leaves = [n for n in names if all(self.is_base(other, n) for other in names)]
            if len(leaves) == 1:
                return leaves[0], 'stores the %s vtable (constructor or destructor)' % leaves[0]
        return None
