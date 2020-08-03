import sys

sys.path.append(cmds.workspace( expandName = 'scripts'))

def remove_module(module_name):
    print('info', 'Removing {} module'.format(module_name))
    to_delete = []
    for module in sys.modules:
        if module.split('.')[0] == module_name:
            to_delete.append(module)
    for module in to_delete:
        del (sys.modules[module])

remove_module("maya2glTF_capture")
remove_module("maya2glTF_playblast")

from maya2glTF_playblast import playblast
from maya2glTF_capture import capture
