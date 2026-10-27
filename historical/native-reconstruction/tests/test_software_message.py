# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from pathlib import Path
from tempfile import TemporaryDirectory
from types import SimpleNamespace
import compare_software_message as c
class SoftwareMessageEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'font_sha256':c.FONT_SHA},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[]
  for _,cmd in rows:
   n=len(c.parse(cmd)['actions']);expected.append(['R',str(n),*[x for _ in range(n) for x in ('0','state')]])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_scope_and_same_parent_inputs(self):
  self.assertEqual(list(c.scenarios()),list(c.parent.scenarios()));self.assertEqual(len(list(c.scenarios())),123)
  self.assertTrue(c.FLAGS['actual_display_software_fill']);self.assertTrue(c.FLAGS['hardware_enable_byte_zero_supplied']);self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_binary_font_guards(self):
  for cmd in ('','W','X',c.parent.command([],width=2**31),c.parent.command([])+' extra'):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
  with TemporaryDirectory() as d:
   p=Path(d)/'font';p.write_bytes(b'wrong font')
   with self.assertRaises(ValueError):c.identities(SimpleNamespace(font_file=p))
 def test_identity_receipt_and_scope_guards(self):
  e,r,i=self.fixture();c.validate(e,r,'receipt',dict(i,native_sources={'native':'new'}))
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(i,original={'font_sha256':'different'}))
  with self.assertRaises(ValueError):c.validate(e,r,'bad receipt',i)
  for flag in c.FLAGS:
   bad=copy.deepcopy(e);bad['evidence'][flag]=not c.FLAGS[flag]
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',i)
  for key,value in (('commands',[]),('labels',[]),('expected',[]),('profile','other'),('executable_sha256','other')):
   bad=copy.deepcopy(e);bad[key]=value
   with self.assertRaises(ValueError):c.validate(bad,r,'receipt',i)
if __name__=='__main__':unittest.main()
