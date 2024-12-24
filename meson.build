# SPDX Licence-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

project(
  'libcrust',
  ['c', 'cpp'],
  default_options: ['c_std=c11', 'cpp_std=c++17', 'default_library=static' ],
)

subdir('src')

inc = include_directories('include')

install_subdir('include', install_dir: 'include')

libcrust = library(
  'libcrust',
  libcrust_src,
  include_directories: inc,
  version: '1.0.0',
  soversion: '1',
  install: true,
)

libcrust_dep = declare_dependency(include_directories: inc, link_with: libcrust)

gtest_dep = dependency('gtest', required: true, fallback: ['gtest', 'gtest_dep'])

subdir('test')
