"""Calendar/version SDK records retain real aliases, widths and ownership."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class CalendarRecordTypes(unittest.TestCase):
    def test_system_time_tag_and_public_pointer_aliases(self):
        for name in ('_SYSTEMTIME', 'SYSTEMTIME', 'PSYSTEMTIME', 'LPSYSTEMTIME'):
            with self.subTest(name=name):
                text = seed.sdk_preamble('{ ' + name + ' time; }')
                self.assertIn('struct _SYSTEMTIME {', text)
                self.assertIn('typedef _SYSTEMTIME SYSTEMTIME;', text)
                self.assertIn('typedef SYSTEMTIME *PSYSTEMTIME, *LPSYSTEMTIME;', text)
                self.assertNotIn('struct SYSTEMTIME {', text)

    def test_time_zone_tag_alias_pointers_and_fields(self):
        for name in ('_TIME_ZONE_INFORMATION', 'TIME_ZONE_INFORMATION',
                     'PTIME_ZONE_INFORMATION', 'LPTIME_ZONE_INFORMATION'):
            with self.subTest(name=name):
                text = seed.sdk_preamble('{}', (name + ' zone',))
                self.assertIn('struct _TIME_ZONE_INFORMATION {', text)
                self.assertIn('WCHAR StandardName[32];', text)
                self.assertIn('SYSTEMTIME StandardDate;', text)
                self.assertIn('WCHAR DaylightName[32];', text)
                self.assertIn('LONG DaylightBias;', text)
                self.assertNotIn('struct TIME_ZONE_INFORMATION;', text)

    def test_version_record_tag_alias_pointers_and_result(self):
        for name in ('_OSVERSIONINFOA', 'OSVERSIONINFOA', 'POSVERSIONINFOA', 'LPOSVERSIONINFOA'):
            with self.subTest(name=name):
                text = seed.sdk_preamble('{}', result=name)
                self.assertIn('struct _OSVERSIONINFOA {', text)
                self.assertIn('CHAR szCSDVersion[128];', text)
                self.assertIn('DWORD dwOSVersionInfoSize, dwMajorVersion, dwMinorVersion, dwBuildNumber, dwPlatformId;', text)
                self.assertNotIn('struct OSVERSIONINFOA;', text)

    def test_import_prototype_dependencies(self):
        text = seed.sdk_preamble('extern void read(LPSYSTEMTIME, LPTIME_ZONE_INFORMATION, LPOSVERSIONINFOA);')
        for tag in ('_SYSTEMTIME', '_TIME_ZONE_INFORMATION', '_OSVERSIONINFOA'):
            self.assertIn('struct ' + tag + ' {', text)

    def test_unrelated_seed_stays_identical(self):
        self.assertEqual(seed.sdk_preamble('{ int ordinary; }'), seed.SDK_PREAMBLE)

    def test_comments_literals_and_longer_identifiers_do_not_trigger(self):
        self.assertEqual(seed.sdk_preamble('{ use("_SYSTEMTIME _TIME_ZONE_INFORMATION _OSVERSIONINFOA"); /* SYSTEMTIME */ }'), seed.SDK_PREAMBLE)
        self.assertEqual(seed.sdk_preamble('{ int my_SYSTEMTIME; int TIME_ZONE_INFORMATION_suffix; }'), seed.SDK_PREAMBLE)

    def test_authored_alias_and_forward_declaration_block_group(self):
        for tag, public in (('_SYSTEMTIME', 'SYSTEMTIME'),
                            ('_TIME_ZONE_INFORMATION', 'TIME_ZONE_INFORMATION'),
                            ('_OSVERSIONINFOA', 'OSVERSIONINFOA')):
            for own in ('typedef int ' + tag + ';', 'typedef int ' + public + ';',
                        'struct ' + tag + ';', 'struct ' + public + ' { int own; };'):
                with self.subTest(own=own):
                    text = seed.sdk_preamble('{ ' + own + ' }', (public + ' value',))
                    self.assertNotIn('struct ' + tag + ' {', text)

    def test_variable_macro_callable_and_function_pointer_shadows(self):
        for tag in ('_SYSTEMTIME', '_TIME_ZONE_INFORMATION', '_OSVERSIONINFOA'):
            for body in ('{ int ' + tag + '; }', '#define ' + tag + ' custom\n{}',
                         '{ ' + tag + '(); }', '{ int (*' + tag + ')(int); }'):
                with self.subTest(tag=tag, body=body):
                    self.assertNotIn('struct ' + tag + ' {', seed.sdk_preamble(body))

    def test_parameter_identifier_owns_spelling(self):
        for tag in ('_SYSTEMTIME', '_TIME_ZONE_INFORMATION', '_OSVERSIONINFOA'):
            self.assertNotIn('struct ' + tag + ' {', seed.sdk_preamble('{}', ('int ' + tag,)))

    def test_qualified_foreign_spelling_is_not_a_global_sdk_type(self):
        for tag in ('_SYSTEMTIME', '_TIME_ZONE_INFORMATION', '_OSVERSIONINFOA'):
            for body in ('{ foreign::' + tag + ' value; }', '{ obj.' + tag + '; }',
                         '{ ptr->' + tag + '; }', '{ ' + tag + '::value; }'):
                self.assertNotIn('struct ' + tag + ' {', seed.sdk_preamble(body))

    def test_time_zone_depends_on_unshadowed_system_time(self):
        for name in ('_SYSTEMTIME', 'SYSTEMTIME', 'PSYSTEMTIME', 'LPSYSTEMTIME', 'LONG', 'WORD', 'WCHAR'):
            with self.subTest(name=name):
                text = seed.sdk_preamble('#define ' + name + ' custom\n{ _TIME_ZONE_INFORMATION zone; }')
                self.assertNotIn('struct _TIME_ZONE_INFORMATION {', text)

    def test_qualified_parameters_and_results_do_not_add_global_record(self):
        for tag in ('_SYSTEMTIME', '_TIME_ZONE_INFORMATION', '_OSVERSIONINFOA'):
            self.assertNotIn('struct ' + tag + ' {', seed.sdk_preamble('{}', ('foreign::' + tag + ' value',)))
            self.assertNotIn('struct ' + tag + ' {', seed.sdk_preamble('{}', result='foreign::' + tag))

    def test_anonymous_and_tagged_typedef_bodies_refuse_owned_alias(self):
        for record in ('struct', 'struct Other', 'union', 'union Other'):
            for alias in ('_SYSTEMTIME', 'SYSTEMTIME', '*LPSYSTEMTIME'):
                body = '{ typedef ' + record + ' { int x; int y; } ' + alias + '; _TIME_ZONE_INFORMATION zone; }'
                text = seed.sdk_preamble(body)
                self.assertNotIn('struct _TIME_ZONE_INFORMATION {', text)
                self.assertNotIn('struct _SYSTEMTIME {', text)

    def test_qualified_function_pointer_dependency_refuses_record(self):
        for pointer in ('* const', '* volatile', '* const volatile', '__cdecl *', '__stdcall * const', '* const *'):
            text = seed.sdk_preamble('{ int (' + pointer + ' SYSTEMTIME)(int); _TIME_ZONE_INFORMATION zone; }')
            self.assertNotIn('struct _TIME_ZONE_INFORMATION {', text)

    def test_typedef_nested_braces_arrays_and_function_pointers(self):
        for declaration in ('typedef struct { struct { int x; } inner; int y[2]; } SYSTEMTIME;',
                            'typedef void (*SYSTEMTIME)(int);',
                            'typedef struct { int (*fn)(int); } *LPSYSTEMTIME;'):
            self.assertNotIn('struct _TIME_ZONE_INFORMATION {', seed.sdk_preamble('{ ' + declaration + ' _TIME_ZONE_INFORMATION zone; }'))

    def test_scalar_dependency_conflicts_refuse_the_coupled_record(self):
        for tag, name in (('_SYSTEMTIME', 'WORD'), ('_OSVERSIONINFOA', 'DWORD'), ('_OSVERSIONINFOA', 'CHAR')):
            self.assertNotIn('struct ' + tag + ' {', seed.sdk_preamble('{ typedef int ' + name + '; ' + tag + ' value; }'))

    def test_one_conflict_does_not_erase_independent_record(self):
        text = seed.sdk_preamble('{ typedef int _SYSTEMTIME; _OSVERSIONINFOA version; _TIME_ZONE_INFORMATION zone; }')
        self.assertIn('struct _OSVERSIONINFOA {', text)
        self.assertNotIn('struct _TIME_ZONE_INFORMATION {', text)

    def test_unicode_extended_and_unidentified_records_remain_unknown(self):
        for name in ('_OSVERSIONINFOW', 'OSVERSIONINFOEXA', '_TIME_DYNAMIC_ZONE_INFORMATION', 'GameTime'):
            self.assertEqual(seed.sdk_preamble('{ ' + name + ' value; }'), seed.SDK_PREAMBLE)

    def test_no_headers_helpers_macros_or_packing_directives(self):
        text = seed.sdk_preamble('{ _SYSTEMTIME now; _OSVERSIONINFOA version; _TIME_ZONE_INFORMATION zone; }')
        for forbidden in ('#include', '#define', '#pragma', '__forceinline', '__asm'):
            self.assertNotIn(forbidden, text)


if __name__ == '__main__':
    unittest.main()
