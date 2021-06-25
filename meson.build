project('libacm', ['c', 'cpp'],
  license: ['BSD', 'ISC'],
  version: '1.2.1',
  default_options: [
    'warning_level=3',
    'c_std=c99',
    'cpp_std=c++20'
    ]
  )

acm_defines = []
acm_deps = []

if get_option('use_libao')
  libao = dependency('libao', required: false)
  acm_deps += libao
  acm_defines += '-DHAVE_AO'
endif

acm_files = files(
  'src/acmtool.c',
  'src/decode.c',
  'src/util.c',
)

acm_inc = include_directories('src/')

acm = library('acm', 
  acm_files,
  include_directories: acm_inc,
  c_args: acm_defines,
  dependencies: acm_deps,
  build_by_default: true,
  install: true
)

libacm = declare_dependency(
  include_directories: acm_inc,
  dependencies: acm_deps,
  compile_args: acm_defines,
  link_with: acm
)

acm_cpp = library('acm_cpp', files('src/libacm.cpp'),
  include_directories: acm_inc,
  cpp_args: acm_defines,
  dependencies: [ acm_deps, libacm ],
  build_by_default: true,
  install: true
)

libacm_cpp = declare_dependency(
  include_directories: acm_inc,
  dependencies: [ acm_deps, libacm ],
  compile_args: acm_defines,
  link_with: acm_cpp
)
