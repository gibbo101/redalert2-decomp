# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from pathlib import Path
import compare_message_text_lookup as c
from prepare_message_color_data import extract,destination
class MessageTextLookupEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[['R','0'] if c.parse(cmd)['op']=='P' else ['C','1','V','0','R','1'] for _,cmd in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),4816)
  parsed=[c.parse(cmd) for _,cmd in rows];self.assertEqual(sum(p['op']=='J' for p in parsed),720)
  self.assertTrue(c.FLAGS['complete_action11_through_actual_color_and_found_lookup'])
  self.assertFalse(c.FLAGS['message_insertion_and_display_recovered']);self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_and_binary_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0','P 1 0','J 0 0 - 1 0 0 0 0 0 0 0 0 0','P 2147483648 '+'0 '*9,'P 0 '+'128 '*9):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
  with self.assertRaises(ValueError):extract(b'wrong executable')
 def test_preparation_destination_guards(self):
  root=Path(__file__).resolve().parents[1];source=root/'private/source/game.exe'
  for output in (source,source.parent/'color.bin',root/'src/color.bin'):
   with self.assertRaises(ValueError):destination(source,output)
  self.assertEqual(destination(source,root/'private/derived/color.bin'),root/'private/derived/color.bin')
 def test_reuse_allows_rebuilt_native_only(self):
  e,r,i=self.fixture();c.validate(e,r,'receipt',dict(i,native_sources={'native':'new'}))
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(i,original={'engine':'changed'}))
  with self.assertRaises(ValueError):c.validate(e,r,'changed receipt',i)
 def test_scope_and_inputs_cannot_be_relabelled(self):
  e,r,i=self.fixture()
  for flag in c.FLAGS:
   bad=copy.deepcopy(e);bad['evidence'][flag]=not c.FLAGS[flag]
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',i)
  for key,value in (('commands',e['commands'][::-1]),('labels',[]),('expected',[]),('profile','other'),('executable_sha256','other')):
   bad=copy.deepcopy(e);bad[key]=value
   with self.assertRaises(ValueError):c.validate(bad,r,'receipt',i)
if __name__=='__main__':unittest.main()
