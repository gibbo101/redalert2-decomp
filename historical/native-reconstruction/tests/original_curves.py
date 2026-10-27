# SPDX-License-Identifier: GPL-3.0-or-later
"""Flat-world curve fixture; original track selection and advance code is unmodified."""
import struct
from collections import Counter
from original_movement import Oracle,UNIT,TYPE,LOCO
from unicorn.x86_const import UC_X86_REG_ECX

class CurveOracle(Oracle):
    def __init__(self,executable,terrain=1.0,**kwargs):
        self.branches=Counter()
        self.branch_addresses=set()
        super().__init__(executable,terrain,**kwargs)
        self.branch_addresses={self.va(v) for v in (0x4a3bcb,0x4a415c,0x4a4187,0x4a187f,0x4a189d,0x4a18a3)}
        self.bind(0x4766c0,4,self.neighbour,'neighbour cell')
    def hook(self,u,address,size,context):
        if address in self.branch_addresses:
            self.branches[hex(address)]+=1
        super().hook(u,address,size,context)
    def neighbour(self):
        cell=self.u.reg_read(UC_X86_REG_ECX);direction=self.arg(0)&7
        x,y=struct.unpack('<hh',self.u.mem_read(cell+0x24,4))
        dx,dy=struct.unpack('<hh',self.u.mem_read(self.va(0x839d80)+4*direction,4))
        return self.cell(x+dx,y+dy)
    def path(self,directions):
        if len(directions)>23 or any(d<0 or d>7 for d in directions):raise ValueError('Invalid supplied route')
        base=LOCO+0x40 if self.get(LOCO+0x63,'B') else UNIT+0x88
        x,y,z=struct.unpack('<iii',self.u.mem_read(base,12))
        for direction in directions:
            dx,dy=struct.unpack('<ii',self.u.mem_read(self.va(0x839dd0)+8*direction,8));x+=dx;y+=dy
        self.call(0x49fa00,[LOCO+4,x,y,z],this=0)
        for i in range(24):self.put(UNIT+0x4d0+4*i,directions[i] if i<len(directions) else -1)
    def detail(self,tick):
        return self.step(tick)+[self.get(LOCO+0x40+i,'i') for i in (0,4)]+[self.get(UNIT+0x4d0+4*i,'i') for i in range(4)]
