# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_message_font as c
class MessageFontEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[['R','1','FW','0','FH','0'] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),6177)
  parsed=[c.parse(cmd) for _,cmd in rows];self.assertEqual({p['op'] for p in parsed},{'M','W','F'});self.assertEqual({p['output'] for p in parsed},set(range(5)))
  self.assertFalse(c.FLAGS['message_insertion_recovered']);self.assertFalse(c.FLAGS['font_loader_and_drawing_recovered']);self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_and_binary_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('M ','X ',1),c.command(text='x',rows=[(65536,1,3)]),c.command(base=0x123456,rows=[(97,1,3)]),c.command(fallback=256),c.command(tab=2**31)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
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
