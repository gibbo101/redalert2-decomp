"""Ambiguous named thunk values need the original owner's encoded reference."""
from pathlib import Path
import struct
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed
import seed_thunk_values as evidence

OWNER, FIRST, SECOND, DEST = 0x401000, 0x402000, 0x402010, 0x408000
NAME = 'thunk_FUN_00408000'


def row(entry, data, **kw):
    return dict(name=kw.pop('name', 'FUN_%08x' % entry), contiguous=True,
                ranges=[dict(start='%08x' % entry, end_inclusive='%08x' % (entry+len(data)-1), bytes_hex=data.hex())], **kw)


class Fixture:
    def __init__(self, addresses=(SECOND,)):
        self.memory = {OWNER:b''.join(b'\x68'+struct.pack('<I', at) for at in addresses)+b'\xc3'}
        self.passes = ['first', 'second']
        self.table = {OWNER:row(OWNER,self.memory[OWNER])}
        for at in (FIRST, SECOND):
            data = b'\xe9'+struct.pack('<i', DEST-at-5);self.memory[at]=data
            refs = [dict(type='DATA', **{'from':'%08x' % (OWNER+i*5)}) for i,target in enumerate(addresses) if target==at]
            self.table[at]=row(at,data,name=NAME,thunk=True,entry_references=refs)
    def rows(self, directory):return self.table
    def function(self, entry):return 'first', self.table.get(entry)
    def body_length(self, entry):return len(self.memory[entry])
    def read(self, at, size):return self.memory[at][:size]
    def executable(self, at):return at in (OWNER,FIRST,SECOND,DEST)
    def prove(self):return evidence.prove_thunk_address(OWNER,[FIRST,SECOND],self,self.read,self.executable)


class OriginalThunkValueTests(unittest.TestCase):
    def test_original_data_push_selects_second_not_first_or_suffix(self):
        proof=Fixture().prove()
        self.assertEqual(proof['entry'],SECOND)
        self.assertEqual(proof['common_jump_target'],DEST)
        self.assertEqual(proof['push_sites'],[OWNER])

    def test_inventory_order_does_not_select_the_address(self):
        f=Fixture();p=evidence.prove_thunk_address(OWNER,[SECOND,FIRST],f,f.read,f.executable)
        self.assertEqual(p['entry'],SECOND)

    def test_repeated_pushes_and_duplicate_pass_references_are_deduplicated(self):
        proof=Fixture((SECOND,SECOND)).prove()
        self.assertEqual(proof['push_sites'],[OWNER,OWNER+5])

    def test_two_encoded_candidate_addresses_remain_ambiguous(self):
        self.assertIsNone(Fixture((FIRST,SECOND)).prove())

    def test_missing_reference_is_not_inferred_from_bytes_alone(self):
        f=Fixture();f.table[SECOND]['entry_references']=[]
        self.assertIsNone(f.prove())

    def test_all_occurrences_must_be_explained(self):
        f=Fixture((SECOND,SECOND));f.table[SECOND]['entry_references'].pop()
        self.assertIsNone(f.prove())

    def test_direct_call_is_not_an_address_push(self):
        f=Fixture();f.memory[OWNER]=b'\xe8'+struct.pack('<i',SECOND-OWNER-5)+b'\xc3';f.table[OWNER]=row(OWNER,f.memory[OWNER])
        self.assertIsNone(f.prove())

    def test_reference_type_and_position_must_agree(self):
        for change in (dict(type='UNCONDITIONAL_CALL'), {'from':'00400fff'}):
            f=Fixture();f.table[SECOND]['entry_references'][0].update(change)
            self.assertIsNone(f.prove())

    def test_stale_original_owner_bytes_refuse(self):
        f=Fixture();f.table[OWNER]['ranges'][0]['bytes_hex']='90'*len(f.memory[OWNER])
        self.assertIsNone(f.prove())

    def test_truncated_owner_read_refuses(self):
        f=Fixture();read=f.read
        with patch.object(f,'read',side_effect=lambda at,size:read(at,size)[:-1] if at==OWNER else read(at,size)):
            self.assertIsNone(f.prove())

    def test_stale_thunk_bytes_refuse(self):
        f=Fixture();f.table[FIRST]['ranges'][0]['bytes_hex']='90'*5
        self.assertIsNone(f.prove())

    def test_thunks_to_different_targets_refuse(self):
        f=Fixture();data=b'\xe9'+struct.pack('<i',OWNER-FIRST-5);f.memory[FIRST]=data;f.table[FIRST]['ranges'][0]['bytes_hex']=data.hex()
        self.assertIsNone(f.prove())

    def test_external_non_thunk_and_noncontiguous_candidates_refuse(self):
        for key,value in [('external',True),('thunk',False),('contiguous',False)]:
            f=Fixture();f.table[FIRST][key]=value
            self.assertIsNone(f.prove())

    def test_non_executable_target_refuses(self):
        f=Fixture();f.executable=lambda at:at!=DEST
        self.assertIsNone(f.prove())

    def test_unknown_owner_extent_refuses(self):
        f=Fixture()
        with patch.object(f,'body_length',side_effect=ValueError('unknown extent')):
            self.assertIsNone(f.prove())

    def test_generator_declares_only_an_address_no_new_call_or_body(self):
        f=Fixture();body='{ code *callback; callback=(code *)'+NAME+'; }'
        with patch.object(evidence,'original_thunk_address',return_value=f.prove()):
            lines=seed.named_thunk_values(body,OWNER,f)
        self.assertIn('extern code '+NAME+'; // @ref ?'+NAME+'@seed_00401000@@=00402010',lines)
        self.assertNotIn('{','\n'.join(lines))
        self.assertIn('callable ABI remain hypotheses','\n'.join(lines))

    def test_two_seed_namespaces_do_not_share_a_reference_key(self):
        f=Fixture();body='{use('+NAME+');}'
        with patch.object(evidence,'original_thunk_address',return_value=f.prove()):
            a=seed.named_thunk_values(body,OWNER,f)
        proof=f.prove();proof['entry']=FIRST
        with patch.object(evidence,'original_thunk_address',return_value=proof):
            b=seed.named_thunk_values(body,OWNER+0x100,f)
        self.assertIn('@seed_00401000@@=00402010','\n'.join(a))
        self.assertIn('@seed_00401100@@=00402000','\n'.join(b))
        self.assertNotIn('extern "C"','\n'.join(a+b))

    def test_direct_or_parenthesized_invocation_is_not_repaired(self):
        for body in ('{'+NAME+'();}','{((code *)'+NAME+')();}'):
            with patch.object(evidence,'original_thunk_address') as proof:
                self.assertEqual(seed.named_thunk_values(body,OWNER,Fixture()),[])
                proof.assert_not_called()

    def test_comments_literals_local_and_parameter_names_are_not_references(self):
        for body,params in [('{use("'+NAME+'"); /* '+NAME+' */}',()),
                            ('{int '+NAME+';}',()),('{}',['int '+NAME])]:
            with patch.object(evidence,'original_thunk_address') as proof:
                self.assertEqual(seed.named_thunk_values(body,OWNER,Fixture(),params),[])
                proof.assert_not_called()

    def test_qualified_member_and_array_uses_remain_unresolved(self):
        for body in ('{use(Type::'+NAME+');}','{use(p->'+NAME+');}','{use('+NAME+'[0]);}'):
            with patch.object(evidence,'original_thunk_address') as proof:
                self.assertEqual(seed.named_thunk_values(body,OWNER,Fixture()),[])
                proof.assert_not_called()

    def test_missing_original_proof_emits_no_declaration(self):
        with patch.object(evidence,'original_thunk_address',return_value=None):
            self.assertEqual(seed.named_thunk_values('{use('+NAME+');}',OWNER,Fixture()),[])

    def test_bad_target_hash_is_not_swallowed(self):
        with patch.object(evidence,'original_thunk_address',side_effect=ValueError('wrong target')):
            with self.assertRaisesRegex(ValueError,'wrong target'):
                seed.named_thunk_values('{use('+NAME+');}',OWNER,Fixture())


if __name__=='__main__':unittest.main()
