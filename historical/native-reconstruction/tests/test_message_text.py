# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import compare_message_text as c
class MessageTextEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'font_sha256':c.FONT_SHA},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  row=['R','0','B','backing','T','trace','S',*['0']*8,'Q',*['0']*4,'Z',*['0']*6]
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[row[:] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),348);parsed=[c.parse(cmd) for _,cmd in rows]
  for k in ('ime','mask','background','nullText','imeContext'):self.assertEqual({p[k] for p in parsed},{0,1})
  self.assertTrue(any(len(p['text'])==8192 for p in parsed));self.assertTrue(any(p['composition'] for p in parsed))
  self.assertTrue(c.FLAGS['actual_CRT_stack_probe_fit_width_alignment_pixels']);self.assertTrue(c.FLAGS['nonzero_IME_fill_cursor_services_supplied']);self.assertFalse(c.FLAGS['node_consumer_recovered']);self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_binary_and_asset_guards(self):
  for cmd in ('','C','X',c.command(enabled=256),c.command(ime=2),c.command(scroll=-1),c.command(scroll=2048),c.command(rgb=-1),c.command(box=(0,0,2**31,1)),c.command(composition='a'*257)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
  with TemporaryDirectory() as d:
   p=Path(d)/'font';p.write_bytes(b'wrong font')
   with self.assertRaises(ValueError):c.identities(SimpleNamespace(font_file=p))
 def test_reuse_allows_rebuilt_native_only(self):
  e,r,i=self.fixture();c.validate(e,r,'receipt',dict(i,native_sources={'native':'new'}))
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(i,original={'font_sha256':'different asset'}))
  with self.assertRaises(ValueError):c.validate(e,r,'changed receipt',i)
 def test_scope_inputs_and_records_cannot_be_relabelled(self):
  e,r,i=self.fixture()
  for flag in c.FLAGS:
   bad=copy.deepcopy(e);bad['evidence'][flag]=not c.FLAGS[flag]
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',i)
  for key,value in (('commands',e['commands'][::-1]),('labels',[]),('expected',[]),('profile','other'),('executable_sha256','other')):
   bad=copy.deepcopy(e);bad[key]=value
   with self.assertRaises(ValueError):c.validate(bad,r,'receipt',i)
if __name__=='__main__':unittest.main()
