"""Synthetic generator tests; no compiler or proprietary original required."""
import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import tempfile
import unittest
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools/original_target'))

HERE = Path(__file__).resolve().parent
GENERATOR = HERE / 'generate_word_storage_family.py'
if not GENERATOR.exists():
    GENERATOR = HERE.parent / 'tools/original_target/generate_word_storage_family.py'
spec = importlib.util.spec_from_file_location('word_generator', GENERATOR)
generator = importlib.util.module_from_spec(spec)
spec.loader.exec_module(generator)
sha = generator.digest


class ReadableGeneratorTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.repo = Path(self.tmp.name)
        self.work = self.repo / 'private/fixture'
        self.work.mkdir(parents=True)
        self.exe = self.work / 'original.bin'
        self.exe.write_bytes(b'synthetic original input')
        self.template = self.work / 'storage.cpp.in'
        text = '// @TARGET_SHA256@\nclass WordStorage_@ENTRY@ {};\n'
        self.template.write_bytes(text.encode('utf-8'))
        self.entry = 0x401000
        key = '%08x' % self.entry
        self.fact = dict(entry=self.entry, body_bytes=93, padding_bytes=3, refusals=[],
                         body_sha256=sha(b'body'), full_region_sha256=sha(b'body-plus-padding'),
                         allocation_target=0x402000, base_table=0x403000, derived_table=0x403040)
        self.review = dict(status=generator.APPROVED_STATUS, ready_regions=1, body_bytes=93,
                           padding_bytes=3, held_entry='00402000')
        evidence = dict(functions=b'synthetic independent function rows', gaps=b'synthetic paired gap rows',
                        facts=(json.dumps(self.fact)+'\n'+json.dumps(dict(entry=0x402000, refusals=['held']))+'\n').encode(),
                        peer_review=json.dumps(self.review).encode())
        self.bindings = {}
        for name, data in evidence.items():
            path = self.work / (name+'.json')
            path.write_bytes(data)
            self.bindings[name] = str(path)
        source = text.replace('@ENTRY@', key).replace('@TARGET_SHA256@', sha(self.exe.read_bytes())).encode()
        self.plan = dict(schema='ra2-readable-word-storage-plan-v1',
                         target=dict(size=self.exe.stat().st_size, sha256=sha(self.exe.read_bytes())),
                         template_sha256=sha(self.template.read_bytes()),
                         evidence_sha256={name:sha(data) for name,data in evidence.items()},
                         held_entries=[0x402000], regions=[dict(entry=self.entry, body_bytes=93, padding_bytes=3,
                         body_sha256=self.fact['body_sha256'], full_extent_sha256=self.fact['full_region_sha256'],
                         source_sha256=sha(source), references={'_allocate_storage_'+key:0x402000,
                         '_base_dispatch_'+key:0x403000, '_derived_dispatch_'+key:0x403040})])
        self.plan_path = self.work / 'plan.json'
        self.plan_path.write_text(json.dumps(self.plan))
        self.canonical_source='src/recovered/storage/InitializeStorage_00401000.cpp'
        (self.repo/'manifests').mkdir()
        self.catalog_path=self.repo/'manifests/original_target.json'
        self.catalog_path.write_text(json.dumps(dict(target=self.plan['target'],
            regions=[dict(entry=self.entry,source=self.canonical_source)])))

    def generate(self, output):
        return generator.render_family(self.repo, self.plan_path, self.template,
                                       self.exe, self.bindings, output)

    def test_manual_canonical_comments_and_names_survive_regeneration(self):
        canonical = self.repo / self.canonical_source
        canonical.parent.mkdir(parents=True)
        canonical.write_text('// Hand-edited context must survive.\nclass ManuallyNamedStorage {};\n')
        before = canonical.read_bytes()
        first = self.repo / 'private/candidates-first'
        second = self.repo / 'private/candidates-second'
        self.generate(first)
        self.generate(second)
        self.assertEqual(canonical.read_bytes(), before)
        self.assertEqual((first/self.canonical_source).read_bytes(), (second/self.canonical_source).read_bytes())
        self.assertNotEqual(canonical.read_bytes(), (first/self.canonical_source).read_bytes())

    def test_unsafe_canonical_mapping_refuses_before_output(self):
        for source in ['../outside.cpp','/outside.cpp','src/recovered/../../outside.cpp']:
            catalog=json.loads(self.catalog_path.read_bytes());catalog['regions'][0]['source']=source
            self.catalog_path.write_text(json.dumps(catalog))
            output=self.repo/'private/rejected-path'
            with self.subTest(source=source),self.assertRaises(ValueError):self.generate(output)
            self.assertFalse(output.exists())

    def test_canonical_or_existing_output_refuses(self):
        for output in [self.repo/'src/recovered/new', self.work]:
            with self.subTest(output=output), self.assertRaises(ValueError):
                self.generate(output)

    def test_nonapproved_status_cannot_pass_via_seeded_pass2_path(self):
        self.review['status'] = 'refused; input path seeded-pass2'
        data = json.dumps(self.review).encode()
        Path(self.bindings['peer_review']).write_bytes(data)
        self.plan['evidence_sha256']['peer_review'] = sha(data)
        self.plan_path.write_text(json.dumps(self.plan))
        output = self.repo/'private/rejected'
        with self.assertRaisesRegex(ValueError, 'not independently approved'):
            self.generate(output)
        self.assertFalse(output.exists())

    def test_evidence_or_template_drift_refuses_before_output(self):
        for name in ['facts', 'template']:
            with self.subTest(name=name):
                path = self.template if name == 'template' else Path(self.bindings[name])
                before = path.read_bytes()
                path.write_bytes(before+b'changed')
                output = self.repo/('private/bad-'+name)
                with self.assertRaisesRegex(ValueError, 'hash drift'):
                    self.generate(output)
                self.assertFalse(output.exists())
                path.write_bytes(before)


    def enable_shared_variant(self):
        header='src/shared/word_storage_layout.hpp'
        path=self.repo/header;path.parent.mkdir(parents=True);path.write_text('// Shared fixture.\n')
        catalog=json.loads(self.catalog_path.read_bytes())
        catalog['regions'][0]['shared_declaration_header']=header
        catalog['headers']=[dict(path=header,sha256=sha(path.read_bytes()))]
        self.catalog_path.write_text(json.dumps(catalog))
        shared=self.template.with_name('word_storage_shared.cpp.in')
        shared.write_bytes(b'#include "shared/word_storage_layout.hpp"\n// Shared @ENTRY@ @TARGET_SHA256@\n')
        self.plan['shared_template_sha256']=sha(shared.read_bytes())
        self.plan_path.write_text(json.dumps(self.plan))
        return path,shared

    def test_shared_variant_preserves_original_pin_and_manual_canonical(self):
        header,shared=self.enable_shared_variant()
        canonical=self.repo/self.canonical_source;canonical.parent.mkdir(parents=True)
        canonical.write_text('// Manual shared class context.\n')
        before=canonical.read_bytes();output=self.repo/'private/shared'
        receipt=self.generate(output)
        expected=shared.read_text().replace('@ENTRY@','00401000').replace('@TARGET_SHA256@',self.plan['target']['sha256']).encode()
        self.assertEqual((output/self.canonical_source).read_bytes(),expected)
        self.assertEqual(canonical.read_bytes(),before)
        self.assertEqual((output/'src/shared/word_storage_layout.hpp').read_bytes(),header.read_bytes())
        self.assertEqual(receipt['candidates'][0]['source_sha256'],sha(expected))
        self.assertEqual(receipt['observed_canonical_sha256'][self.canonical_source],sha(before))

    def test_shared_variant_cannot_bypass_original_source_hash(self):
        self.enable_shared_variant()
        self.plan['regions'][0]['source_sha256']='wrong'
        self.plan_path.write_text(json.dumps(self.plan))
        output=self.repo/'private/refused'
        with self.assertRaisesRegex(ValueError,'frozen readable family'):self.generate(output)
        self.assertFalse(output.exists())

    def test_shared_variant_or_header_drift_refuses_before_output(self):
        header,shared=self.enable_shared_variant()
        for path in [header,shared]:
            before=path.read_bytes();path.write_bytes(before+b'changed')
            output=self.repo/'private/refused'
            with self.assertRaisesRegex(ValueError,'hash drift'):self.generate(output)
            self.assertFalse(output.exists());path.write_bytes(before)

if __name__ == '__main__':
    unittest.main()
