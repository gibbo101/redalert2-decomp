# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import compare_font_glyph as c
class FontGlyphEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'font_sha256':c.FONT_SHA},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  row=['R','0','B','backing','T','trace']
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[row[:] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),363)
  parsed=[c.parse(cmd) for _,cmd in rows];self.assertEqual({p['width'] for p in parsed},{0,1,7,8,9,15,16,17,24})
  self.assertFalse(c.FLAGS['text_drawing_recovered']);self.assertFalse(c.FLAGS['production_UI_enabled'])
  self.assertTrue(c.FLAGS['ordered_reads_and_pixel_writes'])
 def test_input_binary_and_asset_guards(self):
  for cmd in ('','G','X','G 0 extra',c.command(width=25),c.command(present=2)):
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
