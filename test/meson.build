gtest_dep = dependency('gtest', required : true)

test_arc = executable('test_arc',
  'test_arc.cpp',
  dependencies: [gtest_dep, libcrust_dep],
  cpp_args: ['-fpermissive']
)
test('arc_test', test_arc)

test_box = executable('test_box',
  'test_box.cpp',
  dependencies: [gtest_dep, libcrust_dep],
  cpp_args: ['-fpermissive']
)
test('box_test', test_box)

test_option = executable('test_option',
  'test_option.cpp',
  dependencies: [gtest_dep, libcrust_dep],
  cpp_args: ['-fpermissive']
)
test('option_test', test_option)

test_rc = executable('test_rc',
  'test_rc.cpp',
  dependencies: [gtest_dep, libcrust_dep],
  cpp_args: ['-fpermissive']
)
test('rc_test', test_rc)

test_result = executable('test_result',
  'test_result.cpp',
   dependencies: [gtest_dep, libcrust_dep],
  cpp_args: ['-fpermissive']
)
test('result_test', test_result)

