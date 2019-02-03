import os
import shutil
import maya.cmds as cmds
from maya2glTF_capture import capture

def defaultPlayblastFilename(scenename):
    name = os.path.splitext(scenename)[0]
    root = cmds.workspace(q=1, active=True)
    folder = os.path.abspath(os.path.join(root, 'playblast', name, 'video'))
    if os.path.exists(folder):
       shutil.rmtree(folder)
    os.makedirs(folder)
    return  os.path.abspath(os.path.join(folder, 'frame'))

    # folder = os.path.abspath(os.path.join(root, 'playblast'))
    # if not os.path.exists(folder):
    #     os.makedirs(folder)
    # return  os.path.abspath(os.path.join(folder, name))

def playblast(
    filename=None,
    camera='camera1', 
    width=1280,
    height=720, 
    format='image',
    compression='png', 
    overwrite=True):

    scenename = cmds.file(q=1, sceneName=True, shortName=True)

    filename = filename or defaultPlayblastFilename(scenename)
    frame = None if "anim" in scenename.lower() else 1

    capture(
        camera=camera,
        width=width, 
        height=height, 
        format=format, 
        compression=compression, 
        filename=filename, 
        overwrite=overwrite,
        viewer=False,
        frame=frame,
        viewport_options={
            "grid": False,
            "headsUpDisplay": False, 
        },
        display_options={
            "displayGradient": False,
            "background": (0, 0, 0),
        },
        camera_options={
            "displayResolution": False
        }
    )
