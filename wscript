import Options
from os import unlink, symlink, popen
from os.path import exists 

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "rfb-protocols"
  obj.source = "src/common.cpp src/hextile.cpp src/hextilenode.cpp src/module.cpp"
  obj.cxxflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE"]

def shutdown():
  if Options.commands['clean']:
    if exists('rfb-protocols.node'): unlink('rfb-protocols.node')
  else:
    if exists('build/default/rfb-protocols.node') and not exists('rfb-protocols.node'):
      symlink('build/default/rfb-protocols.node', 'rfb-protocols.node')

