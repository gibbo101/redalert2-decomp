# SPDX-License-Identifier: GPL-3.0-or-later
import copy
import unittest
from compare_owned_scheduled_preview import parse, validate
import test_owned_orders_world_evidence as legacy

class ScheduledEvidence(unittest.TestCase):
    def fixture(self):
        e,r,c=legacy.OrdersWorldEvidence().fixture()
        e['evidence']['same_schedule_original_Process0_Process1_finish0_finish1']=r['same_schedule_original_Process0_Process1_finish0_finish1']=True
        # Retain valid original authored map/reset/initialize/join inputs only.
        rows=[(cmd,res,label) for cmd,res,label in zip(e['commands'],e['expected'],e['labels']) if cmd.split()[0] in ('P','O','I','J')]
        rows += [(f'M {id} 100 384 384 0 1 2',{'state':[]},'commands') for id in (0,1)]
        rows += [('H 101',{'events0':[['R',0,1]],'events1':[['R',1,0]],'state':[]},'schedule')]
        draw=next(c for c in e['commands'] if c.startswith('D '))
        draws=[]
        for id in (0,1):
            words=draw.split();words[1]=str(id);draws.append((' '.join(words),{'tokens':[]},'draw'))
        step=('H 102',{'events0':[['R',0,1]],'events1':[['R',1,0]],'state':[]},'schedule')
        rows += draws+[('X 0',{'state':[]},'isolation')]+draws+[step,('X 1',{'state':[]},'isolation')]+draws+[step]
        e['commands'],e['expected'],e['labels']=map(list,zip(*rows))
        return e,r,c
    def test_valid_and_strict_protocol(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
        for cmd in ('H','H 1 2','H 2147483648','X 2','X -1','T 0 101','F 0 101','U 0 100 0 0 0 0 0'):
            with self.subTest(cmd=cmd),self.assertRaises(ValueError):parse(cmd)
    def test_order_returns_and_modes(self):
        for mutation in ('order','return','mode','counts','identity','original'):
            e,r,c=self.fixture()
            if mutation=='order':e['commands'][0]='O 0 0'
            if mutation=='return':e['expected'][6]['events1']=[['R',0,1]]
            if mutation=='mode':e['commands'][e['commands'].index('X 1')]='X 0'
            if mutation=='counts':e['labels'].pop()
            if mutation=='identity':c={'wrong':True}
            if mutation=='original':e['evidence']['same_schedule_original_Process0_Process1_finish0_finish1']=r['same_schedule_original_Process0_Process1_finish0_finish1']=False
            with self.subTest(mutation=mutation),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)

if __name__=='__main__':unittest.main()
