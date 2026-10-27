# SPDX-License-Identifier: GPL-3.0-or-later
"""Invocation-local reuse of immutable-input binary inspections, never execution.

Only explicitly installed, already loaded tools/verify_*.py functions are reused.
Their aliases share one cache. Mutable arguments bypass it, exceptions are not
cached, and every result crosses a defensive-copy boundary. No state persists
between processes. run_evidence.py adds source/input/runner identity guards.
Within these inspectors only, pefile's byte histograms also share immutable
snapshots. Each PE parse still runs with a fresh, independently mutable Counter.
"""
from collections import Counter
import copy
import functools
from pathlib import Path
import struct
import sys
import time


def immutable_key(value):
    """Keep bool/int, signed zero and exact float bits distinct; reject subclasses."""
    kind = type(value)
    if kind in (bytes, str, int, bool, type(None)):
        return kind.__name__, value
    if kind is float:
        return 'float', struct.pack('!d', value)
    raise TypeError('Mutable or unsupported inspection argument')


class InspectionReuse:
    def __init__(self, *, byte_histograms=True):
        self._wrappers = {}
        self._originals = {}
        self._inspection_depth = 0
        self._histogram_binding = None
        self._byte_histograms = byte_histograms
        self._stats = {'hits': 0, 'misses': 0, 'bypasses': 0,
                       'byte_histogram_hits': 0, 'byte_histogram_misses': 0,
                       'nested_inspection_seconds': 0.0, 'copy_seconds': 0.0}

    @property
    def stats(self):
        return {**self._stats, 'functions': len(self._wrappers)}

    def wrap(self, function):
        if function in self._originals:
            return function
        if function in self._wrappers:
            return self._wrappers[function]
        cache = {}

        def clone(value):
            start = time.monotonic()
            result = copy.deepcopy(value)
            self._stats['copy_seconds'] += time.monotonic() - start
            return result

        @functools.wraps(function)
        def call(*args, **kwargs):
            try:
                key = (tuple(map(immutable_key, args)),
                       tuple((name, immutable_key(value)) for name, value in sorted(kwargs.items())))
            except TypeError:
                self._stats['bypasses'] += 1
                return function(*args, **kwargs)
            if key in cache:
                self._stats['hits'] += 1
                return clone(cache[key])
            self._stats['misses'] += 1
            start = time.monotonic()
            self._inspection_depth += 1
            try:
                result = function(*args, **kwargs)
            finally:
                self._inspection_depth -= 1
            # Inclusive nested calls overlap. This is diagnostic cost, not wall time.
            self._stats['nested_inspection_seconds'] += time.monotonic() - start
            cache[key] = clone(result)
            return clone(cache[key])

        self._wrappers[function] = call
        self._originals[call] = function
        return call

    def _install_byte_histograms(self):
        # pefile fully parses every PE and counts its bytes before inspecting
        # directories. Distinct verifiers repeat that count for identical data.
        # Reuse just the count, never a mutable PE/parser or any oracle execution.
        module = sys.modules.get('pefile')
        if (self._histogram_binding is not None or module is None or
                getattr(module, 'Counter', None) is not Counter):
            return
        cache = {}

        def histogram(*args, **kwargs):
            if (not self._inspection_depth or len(args) != 1 or kwargs or
                    type(args[0]) not in (bytes, bytearray)):
                return Counter(*args, **kwargs)
            key = bytes(args[0])  # Snapshot pefile's temporary mutable buffer.
            if key in cache:
                self._stats['byte_histogram_hits'] += 1
            else:
                self._stats['byte_histogram_misses'] += 1
                cache[key] = Counter(key)
            return cache[key].copy()

        self._histogram_binding = (module, histogram)
        module.Counter = histogram

    def install_loaded_verifiers(self, tools_directory):
        directory = Path(tools_directory).resolve()
        for module in list(sys.modules.values()):
            if module is None:
                continue
            for name, function in list(vars(module).items()):
                if not callable(function) or getattr(function, '__name__', '') != 'verify':
                    continue
                owner = sys.modules.get(getattr(function, '__module__', ''))
                filename = getattr(owner, '__file__', None)
                if not filename:
                    continue
                path = Path(filename).resolve()
                if path.parent == directory and path.name.startswith('verify_') and path.suffix == '.py':
                    setattr(module, name, self.wrap(function))
        if self._wrappers and self._byte_histograms:
            self._install_byte_histograms()

    def restore(self):
        if self._histogram_binding is not None:
            module, histogram = self._histogram_binding
            if module.Counter is histogram:
                module.Counter = Counter
            self._histogram_binding = None
        # Also restore aliases imported while the context was active.
        for module in list(sys.modules.values()):
            if module is None:
                continue
            for name, function in list(vars(module).items()):
                if callable(function):
                    try:
                        original = self._originals.get(function)
                    except TypeError:  # An unrelated unhashable callable.
                        continue
                    if original is not None:
                        setattr(module, name, original)

    def __enter__(self):
        return self

    def __exit__(self, *exception):
        self.restore()
