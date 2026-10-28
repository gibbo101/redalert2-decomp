"""Generator boundary tests: canonical edits preserved and drift refused."""
import importlib.util
import hashlib
import json
from pathlib import Path
import tempfile
import unittest
import sys

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))

HERE=Path(__file__).resolve().parent
TOOL=HERE/'generate_message_gadget.py'
if not TOOL.exists(): TOOL=HERE.parent/'tools/original_target/generate_message_gadget.py'
spec=importlib.util.spec_from_file_location('message_generator',TOOL);generator=importlib.util.module_from_spec(spec);spec.loader.exec_module(generator)
sha=lambda data:hashlib.sha256(data).hexdigest()

class MessageGeneratorTests(unittest.TestCase):
    def fixture(self, root):
        original=b'synthetic target fixture';source=b'// reviewed synthetic source\n';header=b'// synthetic shared declaration\n';fact={'entry':0x400010,'body_bytes':2,'body_sha256':'fixture-body','region_bytes':2,'region_sha256':'fixture-region'}
        row=dict(fact,proposed_source='src/recovered/messages/Fixture.cpp',source_sha256=sha(source),template='Fixture.cpp.in');target={'size':len(original),'sha256':sha(original)};pin={'path':'src/shared/message_gadget_layout.hpp','sha256':sha(header)}
        for sub in ('manifests','src/shared','src/recovered/messages','templates','private'): (root/sub).mkdir(parents=True,exist_ok=True)
        (root/'src/shared/message_gadget_layout.hpp').write_bytes(header);(root/'templates/Fixture.cpp.in').write_bytes(source);(root/'original').write_bytes(original);(root/'facts.json').write_text(json.dumps([fact]));(root/'review.json').write_text('{}');evidence={'original_facts':root/'facts.json','peer_source_review':root/'review.json'};plan={'schema':'ra2-readable-message-gadget-plan-v1','target':target,'shared_header':pin,'evidence_sha256':{k:sha(p.read_bytes()) for k,p in evidence.items()},'regions':[row]};(root/'plan.json').write_text(json.dumps(plan));(root/'manifests/original_target.json').write_text(json.dumps({'target':target,'headers':[pin],'regions':[dict(row,source=row['proposed_source'])]}));return evidence
    def render(self, root,evidence):
        return generator.render_family(root,root/'plan.json',root/'templates',root/'original',evidence,root/'private/generated')
    def test_manual_canonical_edits_preserved_not_used_as_template(self):
        with tempfile.TemporaryDirectory() as t:
            r=Path(t);e=self.fixture(r);p=r/'src/recovered/messages/Fixture.cpp';p.write_text('// manual maintained edit\n');before=p.read_bytes();receipt=self.render(r,e);self.assertEqual(p.read_bytes(),before);self.assertEqual((r/'private/generated/src/recovered/messages/Fixture.cpp').read_bytes(),b'// reviewed synthetic source\n');self.assertEqual(receipt['observed_canonical_sha256'][p.relative_to(r).as_posix()],sha(before))
    def test_template_drift_refused_before_output(self):
        with tempfile.TemporaryDirectory() as t:
            r=Path(t);e=self.fixture(r);(r/'templates/Fixture.cpp.in').write_text('// unreviewed\n')
            with self.assertRaisesRegex(ValueError,'Template drift'):self.render(r,e)
            self.assertFalse((r/'private/generated').exists())
    def test_catalog_paths_override_old_plan_paths(self):
        with tempfile.TemporaryDirectory() as t:
            r=Path(t);e=self.fixture(r);catalog=r/'manifests/original_target.json';c=json.loads(catalog.read_bytes())
            path='src/recovered/another_purpose/Fixture.cpp';p=r/path;p.parent.mkdir();p.write_text('// canonical manual comment\n')
            c['regions'][0]['source']=path;catalog.write_text(json.dumps(c));self.render(r,e)
            self.assertTrue((r/'private/generated'/path).is_file())
            self.assertFalse((r/'private/generated/src/recovered/messages/Fixture.cpp').exists())
    def test_unsafe_catalog_path_refuses_before_output(self):
        with tempfile.TemporaryDirectory() as t:
            r=Path(t);e=self.fixture(r);catalog=r/'manifests/original_target.json';c=json.loads(catalog.read_bytes())
            for path in ['/outside.cpp','src/recovered/../../../outside.cpp']:
                c['regions'][0]['source']=path;catalog.write_text(json.dumps(c))
                with self.subTest(path=path),self.assertRaises(ValueError):self.render(r,e)
                self.assertFalse((r/'private/generated').exists())
    def test_wrong_target_refused(self):
        with tempfile.TemporaryDirectory() as t:
            r=Path(t);e=self.fixture(r);(r/'original').write_text('wrong')
            with self.assertRaisesRegex(ValueError,'Wrong original'):self.render(r,e)
    def test_output_cannot_overwrite_canonical(self):
        with tempfile.TemporaryDirectory() as t:
            r=Path(t);e=self.fixture(r)
            with self.assertRaisesRegex(ValueError,'Ignored private/build'):generator.render_family(r,r/'plan.json',r/'templates',r/'original',e,r/'src/recovered/unsafe')
    def test_connected_family_copies_all_pinned_headers(self):
        with tempfile.TemporaryDirectory() as t:
            r=Path(t);e=self.fixture(r);p=r/'plan.json';plan=json.loads(p.read_bytes())
            (r/'src/recovered/messages/Fixture.cpp').write_text('// maintained source\n')
            second={'path':'src/shared/connected.hpp','sha256':sha(b'// connected\n')}
            (r/second['path']).write_bytes(b'// connected\n')
            plan['schema']='ra2-readable-connected-family-plan-v1'
            plan['shared_headers']=[plan.pop('shared_header'),second];p.write_text(json.dumps(plan))
            p=r/'manifests/original_target.json';catalog=json.loads(p.read_bytes());catalog['headers'].append(second);p.write_text(json.dumps(catalog))
            self.render(r,e)
            for pin in plan['shared_headers']:
                self.assertEqual((r/'private/generated'/pin['path']).read_bytes(),(r/pin['path']).read_bytes())
    def test_connected_header_escape_and_duplicates_refused_before_output(self):
        with tempfile.TemporaryDirectory() as t:
            r=Path(t);e=self.fixture(r);p=r/'plan.json';plan=json.loads(p.read_bytes());pin=plan.pop('shared_header')
            for headers,error in (([pin,pin],'duplicate'),([dict(pin,path='src/shared/../outside.hpp')],'Unsafe')):
                plan['shared_headers']=headers;p.write_text(json.dumps(plan))
                with self.subTest(headers=headers),self.assertRaisesRegex(ValueError,error):self.render(r,e)
                self.assertFalse((r/'private/generated').exists())
if __name__=='__main__':unittest.main()
