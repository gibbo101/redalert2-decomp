# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import compare_message_node as c
class MessageNodeEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'font_sha256':c.FONT_SHA},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  expected=[]
  for _,cmd in rows:
   n=c.parse(cmd)['repeats'];expected.append(['R',str(n),*['1']*n,'B','backing','T','trace','S',*['0']*8,'D',*['0']*8,'E','0','0','O',*['0']*10,'F','0','G','0','H','0','0','C',*['0']*6])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),371);parsed=[c.parse(cmd) for _,cmd in rows]
  self.assertEqual({p['nodeMutation'] for p in parsed},set(range(8)));self.assertEqual({p['focus'] for p in parsed},{0,1});self.assertEqual({p['repeats'] for p in parsed},{1,2,3});self.assertEqual({p['typewriter'] for p in parsed},{0,1})
  self.assertTrue(c.FLAGS['complete_message_node_parent']);self.assertTrue(c.FLAGS['actual_admission_focus_font_HSV_consumer_pixels']);self.assertTrue(c.FLAGS['same_mutable_list_node_slot_focus_records']);self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_binary_and_asset_guards(self):
  for cmd in ('','N','X',c.command(enabled=256),c.command(focus=2),c.command(dirty=-1),c.command(initialScroll=-1),c.command(force=2**32),c.command(nodeX=2**31),c.command(repeats=4),c.command(hsv1=(256,1,1)),c.command(text='a'*162)):
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
