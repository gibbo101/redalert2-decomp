# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import compare_message_pipeline as c
class MessagePipelineEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'font_sha256':c.FONT_SHA},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[]
  for _,cmd in rows:
   n=len(c.parse(cmd)['actions']);expected.append(['R',str(n),*[x for _ in range(n) for x in ('0','state')],'T','trace'])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),242);parsed=[c.parse(cmd) for _,cmd in rows]
  self.assertEqual({a[0] for p in parsed for a in p['actions']},{'I','D','G','E','F','H','T'});self.assertTrue(any(any(a[0]=='G' and a[1]==256 for a in p['actions']) for p in parsed))
  self.assertEqual({p['pipelineMutation'] for p in parsed},{0,1,2,3,4,8,16,31});self.assertTrue(c.FLAGS['actual_shared_insertion_expiry_list_gadget_node_pixels']);self.assertTrue(c.FLAGS['complete_gadget_low_byte_force_and_late_Next']);self.assertTrue(c.FLAGS['ordinary_list_editor_byte_zero']);self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_binary_and_asset_guards(self):
  for cmd in ('','P','X',c.command(stock=2),c.command(mode3=256),c.command(listX=2**31),c.command(start=-1),c.command(missing=4),c.command(pipelineMutation=32),c.command([('G',2**32)]),c.command([('H',1,256,0,0,0,0,0)]),c.command([('F',257)]),c.command([('X',)]),c.command([('D',)])+' extra'):
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
