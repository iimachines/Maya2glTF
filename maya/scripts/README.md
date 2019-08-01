# WMP internal notes

## To run these python scripts in Maya

    import sys
    sys.path.append('C:/dev/glTF/Maya2glTF/maya/scripts/')
    from maya2glTF_capture import capture
    from maya2glTF_playblast import playblast

# To reload the python scripts after changes

    reload(sys.modules['maya2glTF_capture'])
    reload(sys.modules['maya2glTF_playblast'])


