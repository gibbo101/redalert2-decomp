# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import compare_font_text as c
class FontTextEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'font_sha256':c.FONT_SHA},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  row=['R','0','B','backing','T','trace','S',*['0']*8]
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[row[:] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),278)
  parsed=[c.parse(cmd) for _,cmd in rows];self.assertEqual({p['op'] for p in parsed},{'J','D','B'})
  self.assertEqual({p['offset'] for p in parsed},{0,256,4096})
  self.assertTrue(c.FLAGS['complete_text_to_actual_pixels']);self.assertTrue(c.FLAGS['actual_glyph_intersection_metrics_color'])
  self.assertFalse(c.FLAGS['message_drawing_recovered']);self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_binary_and_asset_guards(self):
  for cmd in ('','J','X','J 0 extra',c.command(stock=2),c.command(color=65536),c.command(count=-1),c.command(targetR=256),c.command(offset=4097)):
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
