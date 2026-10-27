# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import compare_mission_message as c
class MissionMessageEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'font_sha256':c.FONT_SHA},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[]
  for _,cmd in rows:
   n=len(c.parse(cmd)['actions']);expected.append(['R',str(n),*[x for _ in range(n) for x in ('0','state')]])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),123);parsed=[c.parse(cmd) for _,cmd in rows]
  self.assertEqual({a[0] for p in parsed for a in p['actions']},{'M','D','E','T'})
  self.assertTrue(c.FLAGS['complete_action11_actual_color_found_localization_insertion']);self.assertTrue(c.FLAGS['actual_global_list_receiver']);self.assertTrue(c.FLAGS['owned_native_message_presentation']);self.assertFalse(c.FLAGS['production_UI_enabled'])
  self.assertTrue(any(any(b'\x00\x00' in r[2] for r in p['labels']) for p in parsed))
 def test_input_binary_and_asset_guards(self):
  for cmd in ('','W','X',c.command([],mode3=256),c.command([],width=2**31),c.command([],start=-1),c.command([('T',2**32)]),c.command([('M',256,0,'-')]),c.command([('X',)]),c.command([('D',)])+' extra'):
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
