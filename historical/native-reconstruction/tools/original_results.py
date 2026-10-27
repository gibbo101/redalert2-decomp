# SPDX-License-Identifier: GPL-3.0-or-later
"""Opt-in, whole-generation original expectations; native comparisons always run.

Only the reviewed drivers below may opt in. They do not use a native helper to
produce original inputs. Legacy replay remains strict, including mixed source
identities. No historical receipt can be imported into this store.
"""
import ast
import copy
from functools import lru_cache
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import platform
import shutil
import sys
import sysconfig
import tempfile
import time

ROOT = Path(__file__).resolve().parents[1]
SUPPORTED = frozenset(('compare_ground_drive_stores', 'compare_moving_unit_world',
    'compare_shared_ground_world', 'compare_owned_unit_world',
    'compare_owned_unit_processes', 'compare_owned_command_world',
    'compare_owned_advance_world', 'compare_owned_advance_runtime',
    'compare_borrowed_process_scatter', 'compare_owned_scatter_world'))
# Reviewed comparison-only runner. Neither the generator nor its input producer
# reads this binary. Preserve it in current identities and during-run guards.
COMPARISON_ONLY = {'compare_borrowed_process_scatter':
                   {'legacy_native': 'legacy_native_sha256'}}
NATIVE_SUFFIXES = ('.cpp', '.hpp', '.h', '.cmake')
FORMAT = 'ra2-whole-original-generation-v2'
# Reviewed orchestration context, not an input to any supported original oracle.
# Unknown CODEX variables and all other environment inputs remain in the key.
INVOCATION_ONLY_ENV = frozenset(('CODEX_TOOL_CALL_ID', 'CODEX_SANDBOX'))


def digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':'),
                                     allow_nan=False).encode()).hexdigest()


def hash_file(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def original_identity(value):
    """Drop only native file entries in named source maps; keep every other bit."""
    if isinstance(value, dict):
        result = {}
        for key, child in value.items():
            if key == 'sources':
                if not isinstance(child, dict):
                    raise ValueError('Malformed original source map')
                result[key] = {p: h for p, h in child.items()
                               if not (p.endswith(NATIVE_SUFFIXES) or Path(p).name == 'CMakeLists.txt')}
            else:
                result[key] = original_identity(child)
        return result
    if isinstance(value, list):
        return [original_identity(child) for child in value]
    return value


def source_paths(value):
    if isinstance(value, dict):
        for key, child in value.items():
            if key == 'sources':
                yield from (p for p in child if p.endswith('.py'))
            else:
                yield from source_paths(child)


@lru_cache(maxsize=512)
def source_imports(data, filename):
    """Reuse only immutable parsed imports, never file identities or resolution.

    Exact source bytes are reread by every closure check. Keep the diagnostic
    filename in the key and return immutable names; failed parses are not cached.
    This bounded cache lives only in the current Python process.
    """
    names = []
    for node in ast.walk(ast.parse(data.decode(), filename=filename)):
        if isinstance(node, ast.Import):
            names.extend(alias.name for alias in node.names)
        elif isinstance(node, ast.ImportFrom) and node.module:
            names.append(node.module)
    return tuple(names)


def python_closure(driver, identities, root=ROOT):
    """Include imports inside functions and all declared Python helpers/tests.

    Resolve the project's absolute imports from the same tests/tools roots as
    run_evidence. Dynamic imports are outside this reviewed protocol.
    """
    root = root.resolve()
    pending = [Path(driver), root/'tools/original_results.py', root/'tools/run_evidence.py',
               root/'tools/inspection_reuse.py', *(root/p for p in source_paths(identities))]
    result = {}
    while pending:
        path = pending.pop().resolve(strict=True)
        relative = str(path.relative_to(root))
        if relative in result:
            continue
        data = path.read_bytes()
        result[relative] = hashlib.sha256(data).hexdigest()
        for name in source_imports(data, relative):
            for folder in ('tests', 'tools'):
                local = root/folder/(name.replace('.', '/')+'.py')
                if local.is_file():
                    pending.append(local)
                    break
    return result


def tree_identity(path):
    path = path.absolute()
    if any(p.is_symlink() for p in (path, *path.parents)):
        raise ValueError('Symlink original data/cache paths are refused')
    if path.is_file():
        return {'path': str(path), 'sha256': hash_file(path)}
    if not path.is_dir():
        raise ValueError('Missing original input: '+str(path))
    files = {}
    for child in sorted(path.rglob('*')):
        if child.is_symlink():
            raise ValueError('Symlink original input tree is refused')
        if child.is_file():
            files[str(child.relative_to(path))] = hash_file(child)
    return {'path': str(path), 'files': files}


def environment_identity():
    return {k: hashlib.sha256(v.encode()).hexdigest() for k, v in sorted(os.environ.items())
            if k not in INVOCATION_ONLY_ENV}


def invocation_context():
    # Explicit null distinguishes absence from an empty value without exposing
    # either value. Retain this in original and current receipts, outside the key.
    return {'environment_value_sha256': {
        k: hashlib.sha256(os.environ[k].encode()).hexdigest() if k in os.environ else None
        for k in sorted(INVOCATION_ONLY_ENV)}}


def validate_invocation_context(context):
    if not isinstance(context, dict) or set(context) != {'environment_value_sha256'}:
        raise ValueError('Original cache invocation metadata differs')
    values = context['environment_value_sha256']
    if not isinstance(values, dict) or set(values) != INVOCATION_ONLY_ENV:
        raise ValueError('Original cache invocation metadata differs')
    for value in values.values():
        if value is not None and (not isinstance(value, str) or len(value) != 64 or
                                  any(c not in '0123456789abcdef' for c in value)):
            raise ValueError('Original cache invocation metadata differs')


def runtime_identity():
    """Fingerprint the interpreter, stdlib, JIT/disassembler/PE libraries and OS.

    Hash environment values rather than exposing possible credentials. Package
    trees include shared libraries, not just version strings. Ignore disposable
    bytecode; require -B and a fixed Python hash seed for this optional protocol.
    """
    if (os.environ.get('PYTHONHASHSEED') != '0' or sys.flags.hash_randomization != 0 or
            not sys.dont_write_bytecode):
        raise ValueError('Original reuse requires PYTHONHASHSEED=0 and Python -B')
    files = {}
    stdlib = Path(sysconfig.get_path('stdlib'))
    for path in stdlib.rglob('*'):
        relative = path.relative_to(stdlib)
        if ('site-packages' in relative.parts or '__pycache__' in relative.parts or
                path.suffix in ('.pyc', '.pyo')):
            continue
        if path.is_file():
            files[str(path)] = hash_file(path)
    for name in ('unicorn', 'capstone', 'pefile', 'ordlookup'):
        spec = importlib.util.find_spec(name)
        if spec is None or spec.origin is None:
            raise ValueError('Missing original research dependency: '+name)
        paths = (Path(spec.origin).parent.rglob('*') if spec.submodule_search_locations
                 else (Path(spec.origin),))
        for path in paths:
            if '__pycache__' not in path.parts and path.suffix not in ('.pyc', '.pyo') and path.is_file():
                files[str(path)] = hash_file(path)
    for folder in dict.fromkeys(sysconfig.get_path(name) for name in ('purelib', 'platlib')):
        for path in Path(folder).glob('*.pth'):
            files[str(path)] = hash_file(path)
    config = Path(sys.prefix)/'pyvenv.cfg'
    if config.is_file():
        files[str(config)] = hash_file(config)
    return {'python': str(Path(sys.executable).absolute()),
            'python_sha256': hash_file(Path(sys.executable)), 'version': sys.version,
            'flags': repr(sys.flags), 'xoptions': sys._xoptions, 'byteorder': sys.byteorder,
            'module_search_path': list(dict.fromkeys(str(Path(p).resolve()) for p in sys.path)),
            'system': platform.system(), 'release': platform.release(),
            'version_os': platform.version(), 'machine': platform.machine(),
            'files': files, 'environment_value_sha256': environment_identity()}


def add_arguments(parser):
    parser.add_argument('--original-cache', type=Path,
                        help='Opt-in private whole-original-generation store (default: off)')
    parser.add_argument('--original-cache-mode', choices=('use', 'refresh'), default='use',
                        help='refresh executes originals as an uncached control, retaining old entries')
    parser.add_argument('--original-cache-require-hit', action='store_true',
                        help='Refuse a cold key before original execution; requires cache in use mode')


def streams(envelope):
    return {key: envelope[key] for key in ('commands', 'expected', 'labels')}


class OriginalResults:
    def __init__(self, args, identities, driver):
        self.enabled = bool(getattr(args, 'original_cache', None))
        self.require_hit = bool(getattr(args, 'original_cache_require_hit', False))
        self.entry = None
        self.record = None
        self.hashes = None
        self.identity = copy.deepcopy(identities)
        if not self.enabled:
            if getattr(args, 'original_cache_mode', 'use') != 'use':
                raise ValueError('--original-cache-mode requires --original-cache')
            if self.require_hit:
                raise ValueError('--original-cache-require-hit requires --original-cache')
            return
        if self.require_hit and args.original_cache_mode != 'use':
            raise ValueError('--original-cache-require-hit requires use mode, not refresh')
        from presentation_evidence import private_path
        self.driver = Path(driver).resolve(strict=True)
        if self.driver.parent != ROOT/'tests' or self.driver.stem not in SUPPORTED:
            raise ValueError('Driver not reviewed for original result reuse')
        if Path.cwd() != ROOT:
            raise ValueError('Run original reuse from the project root')
        if args.expectations or args.report or not args.output:
            raise ValueError('Original reuse needs a new --output, without --expectations/--report')
        self.output = private_path(args.output, args.exe)
        self.store = private_path(args.original_cache, args.exe)
        if (self.output.exists() or self.store.is_relative_to(self.output) or
                self.output.is_relative_to(self.store)):
            raise ValueError('Use a new output separate from the original store')
        comparison_only = COMPARISON_ONLY.get(self.driver.stem, {})
        self.comparison_runners = {k: tree_identity(getattr(args, k)) for k in comparison_only}
        self.args = {k: v for k, v in vars(args).items() if k not in comparison_only and k not in (
            'native', 'output', 'expectations', 'report', 'original_cache', 'original_cache_mode',
            'original_cache_require_hit')}
        self.runner = tree_identity(args.native)
        self.invocation_context = invocation_context()
        self.provenance = self.snapshot()
        self.key = digest(self.provenance)
        self.entry = self.store/self.key
        self.state = 'refresh' if args.original_cache_mode == 'refresh' else 'miss'
        if self.state == 'miss' and self.entry.exists():
            self.record, self.hashes = self.read_entry()
            self.state = 'hit'
            args.expectations = self.entry/'expected.json'
            args.report = self.output/'report.json'
        if self.require_hit and self.state != 'hit':
            raise ValueError('Original cache hit required; cold key '+self.key+
                             ' (no original execution performed)')
        print('Original result reuse:', self.state, self.key, flush=True)

    def original_identity(self, identities):
        result = original_identity(identities)
        for field in COMPARISON_ONLY.get(self.driver.stem, {}).values():
            result.pop(field, None)
        return result

    def snapshot(self):
        now = time.monotonic()
        inputs = {k: tree_identity(v) if isinstance(v, Path) else v for k, v in self.args.items()}
        # Inspectors/oracles in the supported drawing families also read this
        # explicit retained binary, independent of the supplied target argument.
        if self.driver.stem not in ('compare_ground_drive_stores', 'compare_borrowed_process_scatter'):
            inputs['retained_disc_executable'] = tree_identity(ROOT/'private/disc-allied/game.exe')
        result = {'format': FORMAT, 'driver': str(self.driver.relative_to(ROOT)),
                'identity': self.original_identity(self.identity), 'inputs': inputs,
                'python_sources': python_closure(self.driver, self.identity),
                'runtime': runtime_identity()}
        self.provenance_seconds = getattr(self, 'provenance_seconds', 0.) + time.monotonic()-now
        return result

    def check_unchanged(self):
        if self.enabled and invocation_context() != self.invocation_context:
            raise ValueError('Original invocation context changed during invocation')
        if self.enabled and (self.snapshot() != self.provenance or
                             tree_identity(Path(self.runner['path'])) != self.runner or
                             any(tree_identity(Path(v['path'])) != v for v in self.comparison_runners.values())):
            raise ValueError('Original provenance/current native runner changed during invocation')

    def read_entry(self):
        from presentation_evidence import private_path, validate_receipt
        private_path(self.entry, self.args['exe'])
        manifest_path = private_path(self.entry/'manifest.json', self.args['exe'])
        manifest = json.loads(manifest_path.read_text())
        if (manifest.get('format') != FORMAT or manifest.get('key') != self.key or
                manifest.get('provenance') != self.provenance or digest(manifest['provenance']) != self.key):
            raise ValueError('Original cache provenance/key differs')
        hashes = manifest.get('files')
        if not isinstance(hashes, dict) or set(hashes) != {'expected.json', 'report.json'}:
            raise ValueError('Incomplete original cache manifest')
        for name, expected in hashes.items():
            path = private_path(self.entry/name, self.args['exe'])
            if not path.is_file() or hash_file(path) != expected:
                raise ValueError('Original cache content hash differs: '+name)
        e = json.loads((self.entry/'expected.json').read_text())
        r = json.loads((self.entry/'report.json').read_text())
        validate_receipt(e, r, hashes['expected.json'])
        proof = e['evidence']
        if (proof.get('original_instructions_executed') is not True or
                proof.get('original_instructions_modified') is not False or
                proof.get('original_result_reuse', {}).get('key') != self.key or
                self.original_identity(proof['identities']) != self.original_identity(self.identity)):
            raise ValueError('Original cache origin identity/execution differs')
        reuse = proof['original_result_reuse']
        if (reuse.get('format') != FORMAT or reuse.get('state') not in ('miss', 'refresh') or
                reuse.get('invocation_context_in_original_key') is not False or
                reuse.get('require_hit') is not False or
                reuse.get('native_comparison_cached') is not False or
                reuse.get('original_execution_performed') is not True):
            raise ValueError('Original cache origin execution/context metadata differs')
        validate_invocation_context(reuse.get('invocation_context'))
        return (e, r), hashes

    def validate(self, validator, envelope, receipt, fingerprint, current):
        if not self.enabled or self.state != 'hit':
            return validator(envelope, receipt, fingerprint, current)
        if (current != self.identity or (envelope, receipt) != self.record or
                fingerprint != self.hashes['expected.json']):
            raise ValueError('Original replay origin/current identity differs')
        # The key has already checked all original dependencies against CURRENT
        # inputs. Validate the untouched receipt's historical identity and every
        # existing structural/scope guard. Never substitute historical identities
        # into a current report or alter the driver's identities() implementation.
        validator(envelope, receipt, fingerprint, envelope['evidence']['identities'])

    def report_fields(self):
        if not self.enabled:
            return {}
        self.check_unchanged()
        return {'original_result_reuse': {'format': FORMAT, 'state': self.state, 'key': self.key,
                    'entry': str(self.entry), 'origin_files': self.hashes,
                    'native_comparison_cached': False,
                    'original_execution_performed': self.state != 'hit',
                    'invocation_context': copy.deepcopy(self.invocation_context),
                    'invocation_context_in_original_key': False,
                    'require_hit': self.require_hit,
                    'provenance_check_seconds': self.provenance_seconds}}

    def annotate(self, result):
        # A strict legacy replay can read a cache-origin envelope. Never inherit
        # that origin's miss/refresh annotation as the CURRENT invocation's mode.
        result.pop('original_result_reuse', None)
        result.update(self.report_fields())

    def finish(self, source, report, validator):
        if not self.enabled:
            return
        self.check_unchanged()
        result = json.loads(report.read_text())
        if result['identities'] != self.identity or result['native_sha256'] != self.runner['sha256']:
            raise ValueError('Current native report identity differs')
        metadata = result.get('original_result_reuse', {})
        validate_invocation_context(metadata.get('invocation_context'))
        if (metadata['invocation_context'] != self.invocation_context or
                metadata.get('invocation_context_in_original_key') is not False or
                metadata.get('require_hit') is not self.require_hit):
            raise ValueError('Current invocation context metadata differs')
        if self.state == 'hit':
            if (result['evidence_mode'] != 'cached-original-replay' or
                    result['original_instructions_executed'] is not False or self.read_entry() != (self.record, self.hashes)):
                raise ValueError('Original replay receipt/cache changed')
            return
        from presentation_evidence import validate_receipt
        envelope = json.loads(source.read_text())
        validate_receipt(envelope, result, hash_file(source))
        validator(envelope, result, hash_file(source), self.identity)
        if self.entry.exists():
            retained, _ = self.read_entry()
            if streams(retained[0]) != streams(envelope):
                raise ValueError('Uncached original control differs from retained generation')
            return  # Existing entries/receipts are immutable, including on refresh.
        self.store.mkdir(parents=True, exist_ok=True)
        pending = Path(tempfile.mkdtemp(prefix='.pending-', dir=self.store))
        try:
            files = {}
            for name, path in (('expected.json', source), ('report.json', report)):
                with (pending/name).open('xb') as stream:
                    stream.write(path.read_bytes()); stream.flush(); os.fsync(stream.fileno())
                files[name] = hash_file(pending/name)
            manifest = {'format': FORMAT, 'key': self.key, 'provenance': self.provenance,
                        'files': files, 'origin': {'expected': str(source), 'receipt': str(report)}}
            with (pending/'manifest.json').open('x') as stream:
                json.dump(manifest, stream, indent=2); stream.write('\n')
                stream.flush(); os.fsync(stream.fileno())
            self.check_unchanged()
            try:
                os.rename(pending, self.entry)
            except OSError:
                if not self.entry.exists():
                    raise
                retained, _ = self.read_entry()
                if streams(retained[0]) != streams(envelope):
                    raise ValueError('Concurrent original generation differs') from None
            self.read_entry()  # A published entry must pass the same hit guards.
        finally:
            if pending.exists():
                shutil.rmtree(pending)
