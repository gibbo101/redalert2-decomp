# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual Walk commands followed by complete queued Process on the same owners."""
import struct
from original_walk_speed import WalkSpeedOracle
from original_walk_commands import WalkCommandHooks
from original_walk_head import WALK
from original_walk_queued import identity
from original_infantry_subcell import ARENA,SIZE,ACTOR,CELLS
from original_presentation import STOP
from verify_walk_commands import RANGES,TABLES
class WalkCommandProcessOracle(WalkCommandHooks,WalkSpeedOracle):
 def __init__(self,exe):
  self.command_ready=False;self.in_command=False;super().__init__(exe)
  self.command_actor=ACTOR;self.command_walk=WALK;self.command_ready=True
 def code(self,u,a,n,ctx):
  if self.in_command:
   if a!=STOP:self.command_code(u,a,n)
   return
  return super().code(u,a,n,ctx)
 def store(self,u,access,p,n,value,ctx):
  if self.in_command:return self.command_store(p,n,value)
  return super().store(u,access,p,n,value,ctx)
 def command_lookup(self,p):return CELLS[identity(p)]
 def command_animation(self):raise AssertionError('Joined commands keep initial reset5CC zero')
 def checked_call(self,root,*args,**kwargs):
  if self.command_ready and root==0x71dff0:
   if self.prepare_commands:
    self.u.mem_write(ACTOR+0x204,bytes(2));self.u.mem_write(ACTOR+0x5cc,b'\0')
    self.u.mem_write(WALK+0x1c,bytes(12));self.u.mem_write(WALK+0x34,b'\0');self.u.mem_write(0xabe520,struct.pack('<d',1.))
   writes=[(WALK+0x1c,27),(ACTOR+0x5cc,1)];inputs=[];cursor=ARENA
   for p,n in sorted(writes):
    if cursor<p:inputs.append((cursor,p-cursor))
    cursor=p+n
   inputs += [(cursor,ARENA+SIZE-cursor),*RANGES.items(),*TABLES.items(),(0xaf9060,12),(0xabe520,8)]
   if self.prepare_commands:
    self.invoke_command(0,self.v[3:6],inputs,writes);self.prepare_commands=False
   if self.ints(0xa40d2c,1)[0]==self.stop_at:self.invoke_command(1,(0,0,0),inputs,writes)
  return super().checked_call(root,*args,**kwargs)
 def run_command_process(self,v,options,speed,stop_at):
  self.prepare_commands=True;self.stop_at=stop_at;return self.run_speed_join(v,options,speed)
