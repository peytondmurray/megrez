project(
  'mtfsim',
  'cpp',
  version: '0.1',
  default_options: [
    'cpp_std=c++20',
    'buildtype=debug',
    'optimization=g'
  ],
)

cpp = meson.get_compiler('cpp')
xtensor = dependency('xtensor')

qt6_mod = import('qt6')
qt6 = dependency(
  'qt6',
  modules : [
    'Widgets',
    'PrintSupport',
  ],
)

moc_headers = [
  'mainwindow.h',
  'qcustomplot/qcustomplot.h'
]
sources = [
  'main.cpp',
  'mainwindow.cpp',
  'mathutils.cpp',
  'qcustomplot/qcustomplot.cpp'
]

forms = [
  'mainwindow.ui'
]

ui = qt6_mod.compile_ui(sources: forms)
moc = qt6_mod.compile_moc(headers: moc_headers, dependencies: qt6)

executable(
  'mtfsim',
  sources : [sources, ui, moc],
  dependencies: [
    qt6, xtensor
  ],
)
