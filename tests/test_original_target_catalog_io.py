import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import catalog_io


def region(entry, population, references, **extra):
    return dict(entry=entry, source='src/recovered/%08x.cpp' % entry, body_bytes=4, padding_bytes=0,
                population=population, references=references, **extra)


def sample():
    # Regions interleave populations (runs), one population has no regions,
    # one region's population has no table, top-level keys in a fixed order.
    a, b = {'?A@@YAXXZ': 0x401000, '?B@@YAXXZ': 0x401010}, {'?C@@YAXXZ': 0x402000}
    catalog = dict(schema='ra2-canonical-source-v1', target=dict(sha256='00' * 32, size=1),
                   populations=[dict(id='population-10', inventory_sha256='1'), dict(id='population-2', inventory_sha256='2'),
                                dict(id='population-3', inventory_sha256='3', separate_units=True)],
                   regions=[region(0x401000, 'population-10', a), region(0x401010, 'population-10', a),
                            region(0x402000, 'population-2', b), region(0x401020, 'population-10', a, note='x'),
                            region(0x403000, 'population-3', {})],
                   headers=[dict(path='src/shared/a.hpp', sha256='ab' * 32)], tail=dict(z=1, a=2))
    return catalog_io.loads(catalog_io.dumps(catalog))


class CatalogShardTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.root = Path(self.temporary.name)
        self.path = self.root / catalog_io.SHARDED

    def tearDown(self):
        self.temporary.cleanup()

    def test_round_trip_presents_the_legacy_catalog(self):
        catalog = sample()
        legacy = catalog_io.dumps(catalog)
        written = catalog_io.dump(catalog, self.path)
        self.assertEqual(written[-1], catalog_io.INDEX)
        self.assertEqual(len(written), 4)
        loaded = catalog_io.load(self.path)
        self.assertEqual(loaded, catalog_io.loads(legacy))
        self.assertEqual(catalog_io.dumps(loaded), legacy)    # key order at every level
        stored = catalog_io.load(self.path, references=False)
        self.assertEqual(json.dumps(stored, indent=2) + '\n', legacy)
        self.assertNotIn('references', stored['regions'][0])
        tables = loaded['population_references']
        self.assertIs(loaded['regions'][0]['references'], tables['population-10'])
        self.assertIs(loaded['regions'][1]['references'], loaded['regions'][3]['references'])
        self.assertEqual(loaded['regions'][4]['references'], {})
        self.assertNotIn('population-3', tables)
        self.assertEqual(catalog_io.shard_files(loaded), catalog_io.shard_files(catalog))
        self.assertEqual(catalog_io.dump(loaded, self.path), [])

    def test_only_changed_shards_are_rewritten(self):
        catalog_io.dump(sample(), self.path)
        before = {p: p.read_bytes() for p in catalog_io.files(self.path)}
        catalog = catalog_io.load(self.path)
        catalog['regions'][2]['body_bytes'] = 8
        self.assertEqual(catalog_io.dump(catalog, self.path), ['populations/population-2.json', catalog_io.INDEX])
        after = {p: p.read_bytes() for p in catalog_io.files(self.path)}
        self.assertEqual([p.name for p in before if before[p] != after[p]], [catalog_io.INDEX, 'population-2.json'])
        # A new population: one new shard plus the index.
        catalog['populations'].append(dict(id='population-4'))
        catalog['regions'].append(region(0x404000, 'population-4', {'?D@@YAXXZ': 0x404000}))
        self.assertEqual(catalog_io.dump(catalog, self.path), ['populations/population-4.json', catalog_io.INDEX])
        # A population gone from the catalog: its shard is removed.
        catalog['populations'] = [p for p in catalog['populations'] if p['id'] != 'population-3']
        catalog['regions'] = [r for r in catalog['regions'] if r['population'] != 'population-3']
        self.assertEqual(catalog_io.dump(catalog, self.path), [catalog_io.INDEX, 'populations/population-3.json'])
        self.assertEqual(catalog_io.dumps(catalog_io.load(self.path)), catalog_io.dumps(catalog))

    def test_torn_or_edited_catalog_refuses(self):
        catalog_io.dump(sample(), self.path)
        shard = self.path / 'populations/population-2.json'
        original = shard.read_bytes()
        shard.write_bytes(original.replace(b'"body_bytes": 4', b'"body_bytes": 5'))
        with self.assertRaisesRegex(ValueError, 'differs from the index'):
            catalog_io.load(self.path)
        shard.write_bytes(original)
        (self.path / 'populations/population-9.json').write_text('{"id": "population-9"}\n')
        with self.assertRaisesRegex(ValueError, 'extra'):
            catalog_io.digest(self.path)
        (self.path / 'populations/population-9.json').unlink()
        shard.unlink()
        with self.assertRaisesRegex(ValueError, 'missing'):
            catalog_io.load(self.path)

    def test_conflicting_binding_and_bad_ids_refuse(self):
        catalog = sample()
        catalog['regions'][1]['references'] = {'?A@@YAXXZ': 1}
        with self.assertRaisesRegex(ValueError, 'bound to two addresses'):
            catalog_io.dump(catalog, self.path)
        catalog = sample()
        catalog['populations'].append(dict(id='../x'))
        with self.assertRaisesRegex(ValueError, 'shard name'):
            catalog_io.dump(catalog, self.path)

    def test_legacy_form_and_locate(self):
        legacy = self.root / catalog_io.LEGACY
        legacy.parent.mkdir(parents=True)
        catalog_io.dump(sample(), legacy)
        self.assertEqual(catalog_io.locate(self.root), legacy)
        self.assertEqual(catalog_io.load(legacy), sample())
        self.assertEqual(catalog_io.digest(legacy), catalog_io.sha(legacy.read_bytes()))
        catalog_io.dump(sample(), self.path)
        with self.assertRaisesRegex(ValueError, 'Both'):
            catalog_io.locate(self.root)
        legacy.unlink()
        self.assertEqual(catalog_io.locate(self.root), self.path)
        self.assertEqual(catalog_io.digest(self.path), catalog_io.sha((self.path / catalog_io.INDEX).read_bytes()))
        index = json.loads((self.path / catalog_io.INDEX).read_bytes())
        self.assertEqual(catalog_io.header_document(index)['headers'], sample()['headers'])

    def test_load_git_reads_both_forms(self):
        def git(*args):
            subprocess.run(['git', *args], cwd=self.root, check=True, capture_output=True)
        git('init', '-q'); git('config', 'user.email', 't@t'); git('config', 'user.name', 't')
        legacy = self.root / catalog_io.LEGACY
        legacy.parent.mkdir(parents=True)
        catalog_io.dump(sample(), legacy)
        git('add', '-A'); git('commit', '-qm', 'legacy')
        legacy.unlink()
        catalog = sample(); catalog['regions'][0]['body_bytes'] = 12
        catalog_io.dump(catalog, self.path)
        git('add', '-A'); git('commit', '-qm', 'sharded')
        self.assertEqual(catalog_io.load_git(self.root, 'HEAD~1'), sample())
        self.assertEqual(catalog_io.load_git(self.root, 'HEAD'), catalog)
        self.assertEqual(catalog_io.load_git(self.root, 'HEAD', references=False),
                         catalog_io.load(self.path, references=False))


if __name__ == '__main__':
    unittest.main()
