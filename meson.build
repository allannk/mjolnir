project('blink', 'cpp', default_options: ['cpp_std=c++17', 'b_lto=false', 'b_asneeded=false'])

# ────────────────
# Set default args
srcs      = [] #'examples/main.cc']
incdirs   = []
c_args    = []
link_args = []
link_deps = []

linkfiles = files(['ldscripts/stm32f030f4p6.ld'])
startfile = files(['startup/stm32f030f4p6.S', 'startup/vector-table.S'])

# ──────────────────────────────────
# Define micro controller parameters
# ──────────────────────────────────
#c_args += '-DSTM32F030x6'
c_args += '-D@0@'.format(get_option('mcu'))
c_args += get_option('buildtype') == 'release' ? '-DNDEBUG' : '-DDEBUG'

c_args += '-mcpu=@0@'.format(host_machine.cpu())

objcopy = find_program('objcopy').path()
size = find_program('size').path()

foreach linkfile : linkfiles
  link_args += ['-Wl,-T,@0@/@1@'.format(meson.current_source_dir(), linkfile)]
endforeach

link_deps += meson.get_compiler('cpp').find_library('/usr/lib/gcc/arm-none-eabi/10.2.0/libgcc')

main = executable(
  'example',
  ['examples/main.cc', startfile],
  name_suffix: 'elf',
  cpp_args: [c_args], 
  link_args: [link_args],
  dependencies: [link_deps],
  include_directories: [incdirs]
)


# Create other outputs
dotbin = custom_target(
  'bin',
  input: main,
  output: '@BASENAME@.bin',
  build_by_default: true,
  command: [objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@'],
)

dothex = custom_target(
  'hex',
  input: main,
  output: '@BASENAME@.hex',
  build_by_default: true,
  command: [objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@'],
)

# Create build/main.size for size debug info
dotsize = custom_target(
  'size',
  input: main,
  output: '@BASENAME@.size',
  build_by_default: true,
  capture: true,
  command: [size, '--format=berkeley', '-x', '@INPUT@'],
)

