"""Maya Capture

Playblasting with independent viewport, camera and display options

https://github.com/PearlStudio/maya-capture

"""

import re
import sys
import contextlib

from maya import cmds
from maya import mel

try:
    from PySide2 import QtGui, QtWidgets
except ImportError:
    from PySide import QtGui
    QtWidgets = QtGui

version_info = (2, 3, 0)

__version__ = "%s.%s.%s" % version_info
__license__ = "MIT"


def capture(camera=None,
            width=None,
            height=None,
            filename=None,
            start_frame=None,
            end_frame=None,
            frame=None,
            format='qt',
            compression='H.264',
            quality=100,
            off_screen=False,
            viewer=True,
            show_ornaments=True,
            sound=None,
            isolate=None,
            maintain_aspect_ratio=True,
            overwrite=False,
            frame_padding=4,
            raw_frame_numbers=False,
            camera_options=None,
            display_options=None,
            viewport_options=None,
            viewport2_options=None,
            complete_filename=None):
    """Playblast in an independent panel

    Arguments:
        camera (str, optional): Name of camera, defaults to "persp"
        width (int, optional): Width of output in pixels
        height (int, optional): Height of output in pixels
        filename (str, optional): Name of output file. If
            none is specified, no files are saved.
        start_frame (float, optional): Defaults to current start frame.
        end_frame (float, optional): Defaults to current end frame.
        frame (float or tuple, optional): A single frame or list of frames.
            Use this to capture a single frame or an arbitrary sequence of
            frames.
        format (str, optional): Name of format, defaults to "qt".
        compression (str, optional): Name of compression, defaults to "H.264"
        quality (int, optional): The quality of the output, defaults to 100
        off_screen (bool, optional): Whether or not to playblast off screen
        viewer (bool, optional): Display results in native player
        show_ornaments (bool, optional): Whether or not model view ornaments
            (e.g. axis icon, grid and HUD) should be displayed.
        sound (str, optional):  Specify the sound node to be used during 
            playblast. When None (default) no sound will be used.
        isolate (list): List of nodes to isolate upon capturing
        maintain_aspect_ratio (bool, optional): Modify height in order to
            maintain aspect ratio.
        overwrite (bool, optional): Whether or not to overwrite if file
            already exists. If disabled and file exists and error will be
            raised.
        frame_padding (bool, optional): Number of zeros used to pad file name
            for image sequences.
        raw_frame_numbers (bool, optional): Whether or not to use the exact
            frame numbers from the scene or capture to a sequence starting at
            zero. Defaults to False. When set to True `viewer` can't be used
            and will be forced to False.
        camera_options (dict, optional): Supplied camera options,
            using `CameraOptions`
        display_options (dict, optional): Supplied display
            options, using `DisplayOptions`
        viewport_options (dict, optional): Supplied viewport
            options, using `ViewportOptions`
        viewport2_options (dict, optional): Supplied display
            options, using `Viewport2Options`
        complete_filename (str, optional): Exact name of output file. Use this
            to override the output of `filename` so it excludes frame padding.

    Example:
        >>> # Launch default capture
        >>> capture()
        >>> # Launch capture with custom viewport settings
        >>> capture('persp', 800, 600,
        ...         viewport_options={
        ...             "displayAppearance": "wireframe",
        ...             "grid": False,
        ...             "polymeshes": True,
        ...         },
        ...         camera_options={
        ...             "displayResolution": True
        ...         }
        ... )


    """

    camera = camera or "persp"

    # Ensure camera exists
    if not cmds.objExists(camera):
        raise RuntimeError("Camera does not exist: {0}".format(camera))

    width = width or cmds.getAttr("defaultResolution.width")
    height = height or cmds.getAttr("defaultResolution.height")
    if maintain_aspect_ratio:
        ratio = cmds.getAttr("defaultResolution.deviceAspectRatio")
        height = round(width / ratio)

    if start_frame is None:
        start_frame = cmds.playbackOptions(minTime=True, query=True)
    if end_frame is None:
        end_frame = cmds.playbackOptions(maxTime=True, query=True)

    # (#74) Bugfix: `maya.cmds.playblast` will raise an error when playblasting
    # with `rawFrameNumbers` set to True but no explicit `frames` provided.
    # Since we always know what frames will be included we can provide it
    # explicitly
    if raw_frame_numbers and frame is None:
        frame = range(int(start_frame), int(end_frame) + 1)

    # We need to wrap `completeFilename`, otherwise even when None is provided
    # it will use filename as the exact name. Only when lacking as argument
    # does it function correctly.
    playblast_kwargs = dict()
    if complete_filename:
        playblast_kwargs['completeFilename'] = complete_filename
    if frame is not None:
        playblast_kwargs['frame'] = frame
    if sound is not None:
        playblast_kwargs['sound'] = sound

    # We need to raise an error when the user gives a custom frame range with
    # negative frames in combination with raw frame numbers. This will result
    # in a minimal integer frame number : filename.-2147483648.png for any
    # negative rendered frame
    if frame and raw_frame_numbers:
        check = frame if isinstance(frame, (list, tuple)) else [frame]
        if any(f < 0 for f in check):
            raise RuntimeError("Negative frames are not supported with "
                               "raw frame numbers and explicit frame numbers")

    # (#21) Bugfix: `maya.cmds.playblast` suffers from undo bug where it
    # always sets the currentTime to frame 1. By setting currentTime before
    # the playblast call it'll undo correctly.
    cmds.currentTime(cmds.currentTime(query=True))

    padding = 10  # Extend panel to accommodate for OS window manager
    with _independent_panel(width=width + padding,
                            height=height + padding,
                            off_screen=off_screen) as panel:
        cmds.setFocus(panel)

        with contextlib.nested(
             _disabled_inview_messages(),
             _maintain_camera(panel, camera),
             _applied_viewport_options(viewport_options, panel),
             _applied_camera_options(camera_options, panel),
             _applied_display_options(display_options),
             _applied_viewport2_options(viewport2_options),
             _isolated_nodes(isolate, panel),
             _maintained_time()):

                output = cmds.playblast(
                    compression=compression,
                    format=format,
                    percent=100,
                    quality=quality,
                    viewer=viewer,
                    startTime=start_frame,
                    endTime=end_frame,
                    offScreen=off_screen,
                    showOrnaments=show_ornaments,
                    forceOverwrite=overwrite,
                    filename=filename,
                    widthHeight=[width, height],
                    rawFrameNumbers=raw_frame_numbers,
                    framePadding=frame_padding,
                    **playblast_kwargs)

        return output


def snap(*args, **kwargs):
    """Single frame playblast in an independent panel.

    The arguments of `capture` are all valid here as well, except for
    `start_frame` and `end_frame`.

    Arguments:
        frame (float, optional): The frame to snap. If not provided current
            frame is used.
        clipboard (bool, optional): Whether to add the output image to the
            global clipboard. This allows to easily paste the snapped image
            into another application, eg. into Photoshop.

    Keywords:
        See `capture`.

    """

    # capture single frame
    frame = kwargs.pop('frame', cmds.currentTime(q=1))
    kwargs['start_frame'] = frame
    kwargs['end_frame'] = frame
    kwargs['frame'] = frame

    if not isinstance(frame, (int, float)):
        raise TypeError("frame must be a single frame (integer or float). "
                        "Use `capture()` for sequences.")

    # override capture defaults
    format = kwargs.pop('format', "image")
    compression = kwargs.pop('compression', "png")
    viewer = kwargs.pop('viewer', False)
    raw_frame_numbers = kwargs.pop('raw_frame_numbers', True)
    kwargs['compression'] = compression
    kwargs['format'] = format
    kwargs['viewer'] = viewer
    kwargs['raw_frame_numbers'] = raw_frame_numbers

    # pop snap only keyword arguments
    clipboard = kwargs.pop('clipboard', False)

    # perform capture
    output = capture(*args, **kwargs)

    def replace(m):
        """Substitute # with frame number"""
        return str(int(frame)).zfill(len(m.group()))

    output = re.sub("#+", replace, output)

    # add image to clipboard
    if clipboard:
        _image_to_clipboard(output)

    return output


CameraOptions = {
    "displayGateMask": False,
    "displayResolution": False,
    "displayFilmGate": False,
    "displayFieldChart": False,
    "displaySafeAction": False,
    "displaySafeTitle": False,
    "displayFilmPivot": False,
    "displayFilmOrigin": False,
    "overscan": 1.0,
    "depthOfField": False,
}

DisplayOptions = {
    "displayGradient": True,
    "background": (0.631, 0.631, 0.631),
    "backgroundTop": (0.535, 0.617, 0.702),
    "backgroundBottom": (0.052, 0.052, 0.052),
}

# These display options require a different command to be queried and set
_DisplayOptionsRGB = set(["background", "backgroundTop", "backgroundBottom"])

ViewportOptions = {
    # renderer
    "rendererName": "vp2Renderer",
    "fogging": False,
    "fogMode": "linear",
    "fogDensity": 1,
    "fogStart": 1,
    "fogEnd": 1,
    "fogColor": (0, 0, 0, 0),
    "shadows": False,
    "displayTextures": True,
    "displayLights": "default",
    "useDefaultMaterial": False,
    "wireframeOnShaded": False,
    "displayAppearance": 'smoothShaded',
    "selectionHiliteDisplay": False,
    "headsUpDisplay": True,
    # object display
    "imagePlane": True,
    "nurbsCurves": False,
    "nurbsSurfaces": False,
    "polymeshes": True,
    "subdivSurfaces": False,
    "planes": True,
    "cameras": False,
    "controlVertices": True,
    "lights": False,
    "grid": False,
    "hulls": True,
    "joints": False,
    "ikHandles": False,
    "deformers": False,
    "dynamics": False,
    "fluids": False,
    "hairSystems": False,
    "follicles": False,
    "nCloths": False,
    "nParticles": False,
    "nRigids": False,
    "dynamicConstraints": False,
    "locators": False,
    "manipulators": False,
    "dimensions": False,
    "handles": False,
    "pivots": False,
    "textures": False,
    "strokes": False
}

Viewport2Options = {
    "consolidateWorld": True,
    "enableTextureMaxRes": False,
    "bumpBakeResolution": 64,
    "colorBakeResolution": 64,
    "floatingPointRTEnable": True,
    "floatingPointRTFormat": 1,
    "gammaCorrectionEnable": False,
    "gammaValue": 2.2,
    "lineAAEnable": False,
    "maxHardwareLights": 8,
    "motionBlurEnable": False,
    "motionBlurSampleCount": 8,
    "motionBlurShutterOpenFraction": 0.2,
    "motionBlurType": 0,
    "multiSampleCount": 8,
    "multiSampleEnable": False,
    "singleSidedLighting": False,
    "ssaoEnable": False,
    "ssaoAmount": 1.0,
    "ssaoFilterRadius": 16,
    "ssaoRadius": 16,
    "ssaoSamples": 16,
    "textureMaxResolution": 4096,
    "threadDGEvaluation": False,
    "transparencyAlgorithm": 1,
    "transparencyQuality": 0.33,
    "useMaximumHardwareLights": True,
    "vertexAnimationCache": 0
}


def apply_view(panel, **options):
    """Apply options to panel"""

    camera = cmds.modelPanel(panel, camera=True, query=True)

    # Display options
    display_options = options.get("display_options", {})
    for key, value in display_options.iteritems():
        if key in _DisplayOptionsRGB:
            cmds.displayRGBColor(key, *value)
        else:
            cmds.displayPref(**{key: value})

    # Camera options
    camera_options = options.get("camera_options", {})
    for key, value in camera_options.iteritems():
        cmds.setAttr("{0}.{1}".format(camera, key), value)

    # Viewport options
    viewport_options = options.get("viewport_options", {})
    for key, value in viewport_options.iteritems():
        cmds.modelEditor(panel, edit=True, **{key: value})

    viewport2_options = options.get("viewport2_options", {})
    for key, value in viewport2_options.iteritems():
        attr = "hardwareRenderingGlobals.{0}".format(key)
        cmds.setAttr(attr, value)


def parse_active_panel():
    """Parse the active modelPanel.

    Raises
        RuntimeError: When no active modelPanel an error is raised.

    Returns:
        str: Name of modelPanel

    """

    panel = cmds.getPanel(withFocus=True)

    # This happens when last focus was on panel
    # that got deleted (e.g. `capture()` then `parse_active_view()`)
    if not panel or "modelPanel" not in panel:
        raise RuntimeError("No active model panel found")

    return panel


def parse_active_view():
    """Parse the current settings from the active view"""
    panel = parse_active_panel()
    return parse_view(panel)


def parse_view(panel):
    """Parse the scene, panel and camera for their current settings

    Example:
        >>> parse_view("modelPanel1")

    Arguments:
        panel (str): Name of modelPanel

    """

    camera = cmds.modelPanel(panel, query=True, camera=True)

    # Display options
    display_options = {}
    for key in DisplayOptions:
        if key in _DisplayOptionsRGB:
            display_options[key] = cmds.displayRGBColor(key, query=True)
        else:
            display_options[key] = cmds.displayPref(query=True, **{key: True})

    # Camera options
    camera_options = {}
    for key in CameraOptions:
        camera_options[key] = cmds.getAttr("{0}.{1}".format(camera, key))

    # Viewport options
    viewport_options = {}
    
    # capture plugin display filters first to ensure we never override 
    # built-in arguments if ever possible a plugin has similarly named 
    # plugin display filters (which it shouldn't!)
    plugins = cmds.pluginDisplayFilter(query=True, listFilters=True)
    for plugin in plugins:
        plugin = str(plugin)  # unicode->str for simplicity of the dict
        state = cmds.modelEditor(panel, query=True, queryPluginObjects=plugin)
        viewport_options[plugin] = state
    
    for key in ViewportOptions:
        viewport_options[key] = cmds.modelEditor(
            panel, query=True, **{key: True})

    viewport2_options = {}
    for key in Viewport2Options.keys():
        attr = "hardwareRenderingGlobals.{0}".format(key)
        try:
            viewport2_options[key] = cmds.getAttr(attr)
        except ValueError:
            continue

    return {
        "camera": camera,
        "display_options": display_options,
        "camera_options": camera_options,
        "viewport_options": viewport_options,
        "viewport2_options": viewport2_options
    }


def parse_active_scene():
    """Parse active scene for arguments for capture()

    *Resolution taken from render settings.

    """

    time_control = mel.eval("$gPlayBackSlider = $gPlayBackSlider")

    return {
        "start_frame": cmds.playbackOptions(minTime=True, query=True),
        "end_frame": cmds.playbackOptions(maxTime=True, query=True),
        "width": cmds.getAttr("defaultResolution.width"),
        "height": cmds.getAttr("defaultResolution.height"),
        "compression": cmds.optionVar(query="playblastCompression"),
        "filename": (cmds.optionVar(query="playblastFile")
                     if cmds.optionVar(query="playblastSaveToFile") else None),
        "format": cmds.optionVar(query="playblastFormat"),
        "off_screen": (True if cmds.optionVar(query="playblastOffscreen")
                       else False),
        "show_ornaments": (True if cmds.optionVar(query="playblastShowOrnaments")
                       else False),
        "quality": cmds.optionVar(query="playblastQuality"),
        "sound": cmds.timeControl(time_control, q=True, sound=True) or None
    }


def apply_scene(**options):
    """Apply options from scene

    Example:
        >>> apply_scene({"start_frame": 1009})

    Arguments:
        options (dict): Scene options

    """

    if "start_frame" in options:
        cmds.playbackOptions(minTime=options["start_frame"])

    if "end_frame" in options:
        cmds.playbackOptions(maxTime=options["end_frame"])

    if "width" in options:
        cmds.setAttr("defaultResolution.width", options["width"])

    if "height" in options:
        cmds.setAttr("defaultResolution.height", options["height"])

    if "compression" in options:
        cmds.optionVar(
            stringValue=["playblastCompression", options["compression"]])

    if "filename" in options:
        cmds.optionVar(
            stringValue=["playblastFile", options["filename"]])

    if "format" in options:
        cmds.optionVar(
            stringValue=["playblastFormat", options["format"]])

    if "off_screen" in options:
        cmds.optionVar(
            intValue=["playblastFormat", options["off_screen"]])

    if "show_ornaments" in options:
        cmds.optionVar(
            intValue=["show_ornaments", options["show_ornaments"]])

    if "quality" in options:
        cmds.optionVar(
            floatValue=["playblastQuality", options["quality"]])


@contextlib.contextmanager
def _applied_view(panel, **options):
    """Apply options to panel"""

    original = parse_view(panel)
    apply_view(panel, **options)

    try:
        yield
    finally:
        apply_view(panel, **original)


@contextlib.contextmanager
def _independent_panel(width, height, off_screen=False):
    """Create capture-window context without decorations

    Arguments:
        width (int): Width of panel
        height (int): Height of panel

    Example:
        >>> with _independent_panel(800, 600):
        ...   cmds.capture()

    """

    # center panel on screen
    screen_width, screen_height = _get_screen_size()
    topLeft = [int((screen_height-height)/2.0),
               int((screen_width-width)/2.0)]

    window = cmds.window(width=width,
                         height=height,
                         topLeftCorner=topLeft,
                         menuBarVisible=False,
                         titleBar=False,
                         visible=not off_screen)
    cmds.paneLayout()
    panel = cmds.modelPanel(menuBarVisible=False,
                            label='CapturePanel')

    # Hide icons under panel menus
    bar_layout = cmds.modelPanel(panel, q=True, barLayout=True)
    cmds.frameLayout(bar_layout, edit=True, collapse=True)

    if not off_screen:
        cmds.showWindow(window)

    # Set the modelEditor of the modelPanel as the active view so it takes
    # the playback focus. Does seem redundant with the `refresh` added in.
    editor = cmds.modelPanel(panel, query=True, modelEditor=True)
    cmds.modelEditor(editor, edit=True, activeView=True)

    # Force a draw refresh of Maya so it keeps focus on the new panel
    # This focus is required to force preview playback in the independent panel
    cmds.refresh(force=True)

    try:
        yield panel
    finally:
        # Delete the panel to fix memory leak (about 5 mb per capture)
        cmds.deleteUI(panel, panel=True)
        cmds.deleteUI(window)


@contextlib.contextmanager
def _applied_camera_options(options, panel):
    """Context manager for applying `options` to `camera`"""

    camera = cmds.modelPanel(panel, query=True, camera=True)
    options = dict(CameraOptions, **(options or {}))

    old_options = dict()
    for opt in options.copy():
        try:
            old_options[opt] = cmds.getAttr(camera + "." + opt)
        except:
            sys.stderr.write("Could not get camera attribute "
                             "for capture: %s" % opt)
            options.pop(opt)

    for opt, value in options.iteritems():
        cmds.setAttr(camera + "." + opt, value)

    try:
        yield
    finally:
        if old_options:
            for opt, value in old_options.iteritems():
                cmds.setAttr(camera + "." + opt, value)


@contextlib.contextmanager
def _applied_display_options(options):
    """Context manager for setting background color display options."""

    options = dict(DisplayOptions, **(options or {}))

    colors = ['background', 'backgroundTop', 'backgroundBottom']
    preferences = ['displayGradient']

    # Store current settings
    original = {}
    for color in colors:
        original[color] = cmds.displayRGBColor(color, query=True) or []

    for preference in preferences:
        original[preference] = cmds.displayPref(
            query=True, **{preference: True})

    # Apply settings
    for color in colors:
        value = options[color]
        cmds.displayRGBColor(color, *value)

    for preference in preferences:
        value = options[preference]
        cmds.displayPref(**{preference: value})

    try:
        yield

    finally:
        # Restore original settings
        for color in colors:
            cmds.displayRGBColor(color, *original[color])
        for preference in preferences:
            cmds.displayPref(**{preference: original[preference]})


@contextlib.contextmanager
def _applied_viewport_options(options, panel):
    """Context manager for applying `options` to `panel`"""

    options = dict(ViewportOptions, **(options or {}))
    
    # separate the plugin display filter options since they need to
    # be set differently (see #55)
    plugins = cmds.pluginDisplayFilter(query=True, listFilters=True)
    plugin_options = dict()
    for plugin in plugins:
        if plugin in options:
            plugin_options[plugin] = options.pop(plugin)
    
    # default options
    cmds.modelEditor(panel, edit=True, **options)

    # plugin display filter options
    for plugin, state in plugin_options.items():
        cmds.modelEditor(panel, edit=True, pluginObjects=(plugin, state))
    
    yield


@contextlib.contextmanager
def _applied_viewport2_options(options):
    """Context manager for setting viewport 2.0 options.

    These options are applied by setting attributes on the
    "hardwareRenderingGlobals" node.

    """

    options = dict(Viewport2Options, **(options or {}))

    # Store current settings
    original = {}
    for opt in options.copy():
        try:
            original[opt] = cmds.getAttr("hardwareRenderingGlobals." + opt)
        except ValueError:
            options.pop(opt)

    # Apply settings
    for opt, value in options.iteritems():
        cmds.setAttr("hardwareRenderingGlobals." + opt, value)

    try:
        yield
    finally:
        # Restore previous settings
        for opt, value in original.iteritems():
            cmds.setAttr("hardwareRenderingGlobals." + opt, value)


@contextlib.contextmanager
def _isolated_nodes(nodes, panel):
    """Context manager for isolating `nodes` in `panel`"""

    if nodes is not None:
        cmds.isolateSelect(panel, state=True)
        for obj in nodes:
            cmds.isolateSelect(panel, addDagObject=obj)
    yield


@contextlib.contextmanager
def _maintained_time():
    """Context manager for preserving (resetting) the time after the context"""

    current_time = cmds.currentTime(query=1)
    try:
        yield
    finally:
        cmds.currentTime(current_time)


@contextlib.contextmanager
def _maintain_camera(panel, camera):
    state = {}

    if not _in_standalone():
        cmds.lookThru(panel, camera)
    else:
        state = dict((camera, cmds.getAttr(camera + ".rnd"))
                     for camera in cmds.ls(type="camera"))
        cmds.setAttr(camera + ".rnd", True)

    try:
        yield
    finally:
        for camera, renderable in state.iteritems():
            cmds.setAttr(camera + ".rnd", renderable)


@contextlib.contextmanager
def _disabled_inview_messages():
    """Disable in-view help messages during the context"""
    original = cmds.optionVar(q="inViewMessageEnable")
    cmds.optionVar(iv=("inViewMessageEnable", 0))
    try:
        yield
    finally:
        cmds.optionVar(iv=("inViewMessageEnable", original))


def _image_to_clipboard(path):
    """Copies the image at path to the system's global clipboard."""
    if _in_standalone():
        raise Exception("Cannot copy to clipboard from Maya Standalone")

    image = QtGui.QImage(path)
    clipboard = QtWidgets.QApplication.clipboard()
    clipboard.setImage(image, mode=QtGui.QClipboard.Clipboard)


def _get_screen_size():
    """Return available screen size without space occupied by taskbar"""
    if _in_standalone():
        return [0, 0]

    rect = QtWidgets.QDesktopWidget().screenGeometry(-1)
    return [rect.width(), rect.height()]


def _in_standalone():
    return not hasattr(cmds, "about") or cmds.about(batch=True)


# --------------------------------
#
# Apply version specific settings
#
# --------------------------------

version = mel.eval("getApplicationVersionAsFloat")
if version > 2015:
    Viewport2Options.update({
        "hwFogAlpha": 1.0,
        "hwFogFalloff": 0,
        "hwFogDensity": 0.1,
        "hwFogEnable": False,
        "holdOutDetailMode": 1,
        "hwFogEnd": 100.0,
        "holdOutMode": True,
        "hwFogColorR": 0.5,
        "hwFogColorG": 0.5,
        "hwFogColorB": 0.5,
        "hwFogStart": 0.0,
    })
