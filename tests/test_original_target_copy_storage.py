"""Synthetic candidate-only rendering and canonical preservation checks."""
from pathlib import Path
import hashlib
import importlib.util
import json
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools/original_target'))
try:
    from generate_copy_word_storage import generate
except ImportError:
    # Proposal-local execution; the tracked test uses the normal import above.
    sys.path.insert(0, str(Path(__file__).parent))
    from generate_copy_word_storage import generate

sha = lambda data: hashlib.sha256(data).hexdigest()

class CopyWordStorageGenerationTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        (self.root / 'private').mkdir()
        (self.root / 'manifests').mkdir()
        (self.root / 'src/recovered').mkdir(parents=True)
        self.target = dict(size=9, sha256=sha(b'synthetic'))
        self.exe = self.root / 'private/game.bin'; self.exe.write_bytes(b'synthetic')
        self.template = self.root / 'private/template.in'
        self.template.write_bytes(b'// Reviewed candidate @ENTRY@ owner @OWNER_CLASS@\n')
        self.header = self.root/'src/shared/word_storage_layout.hpp'
        self.header.parent.mkdir(parents=True);self.header.write_text('// Synthetic shared declarations.\n')
        self.rows = []
        facts = []
        for index in range(17):
            entry = 0x401000 + index * 0x100
            key = '%08x' % entry
            owner='Owner_'+key
            payload = self.template.read_text().replace('@ENTRY@', key).replace('@OWNER_CLASS@',owner).encode()
            self.rows.append(dict(entry=entry, owner_class=owner, semantic_name='CopyWordStorage_'+key,
                source='src/recovered/word_storage/CopyWordStorage_'+key+'.cpp',
                source_sha256=sha(payload), body_bytes=136, region_bytes=144,
                body_sha256='body', region_sha256='region'))
            facts.append(dict(entry=entry,body_bytes=136,full_extent_bytes=144,
                body_sha256='body',full_extent_sha256='region',original_inventory_row={},
                padding_hex='90'*8,padding_provenance={}))
        fact_bytes=json.dumps(dict(target=self.target,facts=facts)).encode()
        peer_bytes=json.dumps(dict(status='approved',regions=17,readiness_sha256=sha(fact_bytes))).encode()
        evidence=dict(functions=b'function-fixture',gaps=b'gap-fixture',facts=fact_bytes,peer_review=peer_bytes)
        mapping={}
        for key,data in evidence.items():
            path=self.root/'private'/key;path.write_bytes(data);mapping[key]=str(path)
        self.mapping=self.root/'private/inputs.json';self.mapping.write_text(json.dumps(mapping))
        self.plan=self.root/'private/plan.json'
        self.plan.write_text(json.dumps(dict(schema='bounded-copy-word-storage-shared-v3',
            shared_header=dict(path='src/shared/word_storage_layout.hpp',sha256=sha(self.header.read_bytes())),
            target=self.target,regions=self.rows,evidence_sha256={k:sha(v)for k,v in evidence.items()},
            peer_review_status='approved',source_template_sha256=sha(self.template.read_bytes()))))
        self.catalog=self.root/'manifests/original_target.json'
        self.catalog.write_text(json.dumps(dict(target=self.target,regions=[])))

    def render(self, output):
        return generate(self.root,self.plan,self.template,self.exe,self.mapping,output)

    def test_new_candidates_are_descriptive_and_repeatable(self):
        first=self.root/'private/first';second=self.root/'private/second'
        self.render(first);self.render(second)
        for row in self.rows:
            self.assertEqual((first/row['source']).read_bytes(),(second/row['source']).read_bytes())
        self.assertEqual(list((self.root/'src/recovered').rglob('*.cpp')),[])

    def test_catalog_paths_and_manual_comments_remain_authoritative(self):
        row=dict(self.rows[0]);row['source']=row['source'].replace('word_storage/','changed_purpose/')
        path=self.root/row['source'];path.parent.mkdir();path.write_text('// Manual canonical explanation.\n')
        self.catalog.write_text(json.dumps(dict(target=self.target,regions=[row])))
        before=path.read_bytes();out=self.root/'private/candidates';receipt=self.render(out)
        self.assertEqual(path.read_bytes(),before)
        self.assertTrue((out/row['source']).is_file())
        self.assertEqual(receipt['observed_canonical_sha256'][row['source']],sha(before))
        self.assertFalse((out/self.rows[0]['source']).exists())

    def test_unsafe_catalog_mapping_and_existing_output_refuse(self):
        row=dict(self.rows[0],source='/outside.cpp')
        self.catalog.write_text(json.dumps(dict(target=self.target,regions=[row])))
        out=self.root/'private/refused'
        with self.assertRaises(ValueError):self.render(out)
        self.assertFalse(out.exists())
        with self.assertRaises(ValueError):self.render(self.root/'src/recovered/new')
        with self.assertRaises(ValueError):self.render(self.root/'private')

    def test_shared_declaration_drift_refuses_before_output(self):
        self.header.write_text('// Changed shared layout.\n')
        out=self.root/'private/refused'
        with self.assertRaisesRegex(ValueError,'Shared declaration drift'):self.render(out)
        self.assertFalse(out.exists())

    def test_evidence_drift_refuses_before_output(self):
        (self.root/'private/facts').write_text('changed')
        out=self.root/'private/refused'
        with self.assertRaisesRegex(ValueError,'hash drift'):self.render(out)
        self.assertFalse(out.exists())

if __name__ == '__main__':unittest.main()
