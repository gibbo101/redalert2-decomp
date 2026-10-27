# SPDX-License-Identifier: GPL-3.0-or-later
import unittest,copy
from unittest.mock import patch
import compare_surface_startup as c
class StartupDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),160)
  for _,cmd in rows:self.assertEqual(c.command(*c.parse(cmd)),cmd)
  for at,v in ((0,2**31),(1,-2**31-1),(2,256),(3,-1),(4,2),(5,-1),(6,2**32),(7,-1)):
   f=c.parse(rows[0][1]);f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(*f))
 def test_truncated_or_foreign_trace(self):
  cmd=next(c.scenarios())[1]
  for row in ([],['O','3','4','0'],['D','108','4','0'],['foreign']):
   with self.assertRaises(ValueError):c.validate_row(cmd,row)
 def test_provenance_refusals(self):
  rows=list(c.scenarios());identity=dict(original={'source':'one'},native_sources={'n':'old'})
  meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[[] for _ in rows],evidence=meta)
  r=dict(meta,expectations_sha256='receipt')
  # Row semantics are tested separately; these checks exercise provenance gates.
  with patch.object(c,'validate_row'):
   c.validate(e,r,'receipt',dict(identity,native_sources={'n':'rebuilt'}))
   for kind in ('source','receipt','scope','input'):
    bad=copy.deepcopy(e);report=copy.deepcopy(r);current=copy.deepcopy(identity);digest='receipt'
    if kind=='source':current['original']['source']='changed'
    if kind=='receipt':digest='wrong'
    if kind=='scope':bad['evidence']['production_or_SDL_adoption']=True;report['production_or_SDL_adoption']=True
    if kind=='input':bad['commands'][0]='S 0'
    with self.assertRaises(ValueError):c.validate(bad,report,digest,current)
if __name__=='__main__':unittest.main()
