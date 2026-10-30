"""Read the frozen Ghidra function inventories for iteration tools.

The seeded pass is preferred because it covers more entries; the baseline pass
is the fallback. Rows are analysis hypotheses, not verified function bounds.
"""
import json
import os
from pathlib import Path

REPOSITORY = Path(__file__).resolve().parents[2]
INVENTORY = REPOSITORY / 'private/original-target-20261020/inventory'
# Newest discovery pass first; earlier passes supply entries it dropped.
PASSES = [INVENTORY / 'seeded-pass5', INVENTORY / 'seeded-pass3', INVENTORY / 'seeded-pass2', INVENTORY]
def split_inventory_paths(value, separator=os.pathsep):
    """Native path lists; retain legacy colon lists without splitting drive letters."""
    if separator != ';':
        return [p for p in value.split(separator) if p]
    result=[]
    for native in value.split(';'):
        start=0
        for i,char in enumerate(native):
            drive = i == start+1 and native[start:start+1].isalpha()
            if char == ':' and not drive:
                if native[start:i]:result.append(native[start:i])
                start=i+1
        if native[start:]:result.append(native[start:])
    return result


# Trial/newer passes precede frozen ones. Native separators also support
# Windows absolute paths; legacy relative colon lists remain valid.
PASSES = [Path(p) for p in split_inventory_paths(os.environ.get('RA2_INVENTORY_PASSES', ''))] + PASSES


class Inventory:
    def __init__(self, passes=None):
        self.passes = [Path(p) for p in (PASSES if passes is None else passes)]
        self._rows = {}

    def rows(self, directory):
        if directory not in self._rows:
            path = directory / 'functions.jsonl'
            self._rows[directory] = ({int(r['entry'], 16): r for r in map(json.loads, path.read_text().splitlines())}
                                     if path.exists() else {})
        return self._rows[directory]

    def function(self, entry):
        """Return (pass directory, row) for the first pass that knows entry."""
        for directory in self.passes:
            row = self.rows(directory).get(entry)
            if row is not None:
                return directory, row
        return None, None

    def body_length(self, entry):
        """Body bytes from the first pass with a contiguous body at entry.

        Later passes sometimes split a body (Ghidra mistakes operator new or
        delete for non-returning calls); earlier passes may still hold it
        whole.
        """
        problem = None
        for directory in self.passes:
            row = self.rows(directory).get(entry)
            if row is None:
                continue
            if not row['contiguous'] or len(row['ranges']) != 1:
                problem = problem or 'Inventory body for %08x is noncontiguous; pass --length' % entry
                continue
            span = row['ranges'][0]
            if int(span['start'], 16) != entry:
                problem = problem or 'Inventory body for %08x does not start at its entry' % entry
                continue
            return int(span['end_inclusive'], 16) + 1 - entry
        raise ValueError(problem or 'No inventory row for %08x; pass --length' % entry)

    def decompiled(self, entry):
        for directory in self.passes:
            path = directory / 'decompiled' / ('%08x.c' % entry)
            if path.exists():
                return path.read_text(encoding='utf-8', errors='replace')
        return None

    def all_functions(self):
        """Merged entry -> row, seeded rows taking precedence."""
        merged = {}
        for directory in reversed(self.passes):
            merged.update(self.rows(directory))
        return merged
