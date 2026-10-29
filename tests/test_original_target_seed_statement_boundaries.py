"""Preserve control tails and empty branches when repairing Ghidra syntax."""
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed

class AssignmentBoundaries(unittest.TestCase):
    def cast(self,statement):
        body='{\n  int value;\n'+statement+'\n}'
        return seed.cast_assignments(body,())
    def test_complete_rhs_still_gets_implicit_conversion(self):
        self.assertIn('value = (int)(other + 1);',self.cast('  value = other + 1;'))
    def test_call_arguments_do_not_end_rhs(self):
        self.assertIn('value = (int)(read(a,b[2]));',self.cast('  value = read(a,b[2]);'))
    def test_parenthesized_comma_is_part_of_rhs(self):
        self.assertIn('value = (int)((first(),second()));',self.cast('  value = (first(),second());'))
    def test_unparenthesized_comma_keeps_assignment_before_next_effect(self):
        statement='  value = first(),observe(value);'
        self.assertIn(statement,self.cast(statement))
    def test_conditional_goto_tail_is_not_inside_conversion(self):
        statement='  if ((other == 0) &&\n      (part = word,\n      value = part == limit, value)) goto done;'
        self.assertIn(statement,self.cast(statement))
    def test_for_tail_is_not_inside_conversion(self):
        statement='  for (\n      value = 0; value < limit; value++) consume(value);'
        self.assertIn(statement,self.cast(statement))
    def test_second_statement_stays_outside_conversion(self):
        statement='  value = first(); observe(value);'
        self.assertIn(statement,self.cast(statement))
    def test_mismatched_rhs_delimiters_are_untouched(self):
        for rhs in ('call(a))','array[index)','call((a)','array[(index]'):
            statement='  value = '+rhs+';'
            self.assertIn(statement,self.cast(statement))
    def test_comments_and_strings_cannot_supply_final_semicolon(self):
        for statement in ('  value = other // comment;', '  // value = other;',
                          '  use("value = other;");'):
            self.assertIn(statement,self.cast(statement))
    def test_balanced_comment_inside_rhs_keeps_text(self):
        self.assertIn('value = (int)(other /* ) , ; */ + 1);',self.cast('  value = other /* ) , ; */ + 1;'))
    def test_existing_cast_stays_identical(self):
        statement='  value = (int)(other);'
        self.assertIn(statement,self.cast(statement))
    def test_unsupported_preprocessing_and_alternate_tokens_are_untouched(self):
        for prefix in ('#define value other','%:define value other','??=define value other',
                       '<%', '%>', '<:', ':>', 'use(R"x(value;)x");','other\\\nvalue'):
            body='{\n  int value;\n'+prefix+'\n  value = other;\n}'
            self.assertEqual(seed.cast_assignments(body,()),body)
    def test_unclosed_comment_or_literal_is_unresolved(self):
        for prefix in ('/* unclosed','"unclosed',"'unclosed"):
            body='{\n  int value;\n'+prefix+'\n  value = other;\n}'
            self.assertEqual(seed.cast_assignments(body,()),body)

class TerminalLabels(unittest.TestCase):
    def repair(self,body):return seed.terminal_label_statements(body)
    def test_case_terminal_gets_null_statement(self):
        self.assertEqual(self.repair('{ switch(x) {\ncase 0x10:\n} }'),'{ switch(x) {\ncase 0x10:;\n} }')
    def test_default_terminal_gets_null_statement(self):
        self.assertIn('default:;',self.repair('{ switch(x) {\ndefault:\n} }'))
    def test_chained_case_labels_keep_fallthrough(self):
        self.assertIn('case 5:\ncase 6:;',self.repair('{ switch(x) {\ncase 5:\ncase 6:\n} }'))
    def test_switch_export_label_is_repaired(self):
        self.assertIn('switchD_00503825_caseD_3:;',self.repair('{ if(x) {\nswitchD_00503825_caseD_3:\n} }'))
    def test_do_while_join_label_preserves_loop_test(self):
        self.assertEqual(self.repair('{ do {\njoined_r0x0078240e:\n} while(count); }'),'{ do {\njoined_r0x0078240e:;\n} while(count); }')
    def test_terminal_function_label_can_have_empty_statement(self):
        self.assertIn('done:;',self.repair('{ goto done;\ndone:\n}'))
    def test_comments_between_label_and_end_stay_in_place(self):
        self.assertIn('done:; /* empty */\n// end\n}',self.repair('{\ndone: /* empty */\n// end\n}'))
    def test_nonterminal_label_and_existing_null_statement_are_unchanged(self):
        for body in ('{\ndone: return;\n}', '{\ndone:;\n}', '{\ncase 1: break;\n}'):
            self.assertEqual(self.repair(body),body)
    def test_comment_and_literal_pseudolabels_are_unchanged(self):
        for body in ('{\n// done:\n}', '{\n/* done:\n} */\n}', '{ use("done:\\n}"); }'):
            self.assertEqual(self.repair(body),body)
    def test_case_constants_stay_spelled_as_exported(self):
        for value in ('-1','0x10U','SYMBOL'):
            self.assertIn('case '+value+':;',self.repair('{ switch(x) {\ncase '+value+':\n} }'))
    def test_general_case_expressions_stay_unresolved(self):
        for value in ('flag ? one : two','sizeof(Type)','one + two',"':'"):
            body='{ switch(x) {\ncase '+value+':\n} }'
            self.assertEqual(self.repair(body),body)
    def test_ternary_operand_is_not_a_user_label(self):
        body='{ result = flag ?\nvalue:\n} '
        self.assertEqual(self.repair(body),body)
    def test_record_access_specifiers_and_bitfields_are_not_labels(self):
        for body in ('{ struct S {\nprivate:\n}; }', '{ struct S { int\nfield:\n}; }',
                     '{ class S {\npublic:\n}; }'):
            self.assertEqual(self.repair(body),body)
    def test_mismatched_body_does_not_get_partially_repaired(self):
        for body in ('{ if(x] {\ndone:\n} }','{\ndone:\n}'):
            if body=='{\ndone:\n}':body+='}'
            self.assertEqual(self.repair(body),body)
    def test_unsupported_lexical_scope_grammar_is_untouched(self):
        for prefix in ('#define end }','%:define end }','??=define end }','<%',':>',
                       'namespace N {}','use(R"x(done:)x");','other\\\nname'):
            body='{ '+prefix+'\ndone:\n}'
            self.assertEqual(self.repair(body),body)

if __name__=='__main__':unittest.main()
