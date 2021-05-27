# Maya to glTF exporter
 
## Poll

If you believe this plugin is good enough to request Github Sponsoring, please say so [here](https://github.com/iimachines/Maya2glTF/issues/144)

## News

* Version [1.4.0 released](https://github.com/iimachines/Maya2glTF/releases) for Windows! 

* Support for Maya 2017-2022

* Added feature to detect step animations by using super sampling

* Added `-ext` option (`-externalTextures`) to keep textures outside of `glb` file

* Cameras can be exported, either by selecting them, or by passing one or more by name with the `-cam <name>` flag

* Skin weights are normalized to 1 now

* Export node order is now deterministic

* Fixed wrong exported frame count 

* Added donet core tool to merge multiple GLTF files into one
  - This allows exporting one animation per Maya file

* Added scripts to generate animated GIF and VP9s 

* Exports small animation metadata JSON file.

See the [releases](https://github.com/iimachines/Maya2glTF/releases) tab.

![Maya Tiger screenshot](/img/tiger-wim@koetan.gif)

![Maya Helmet screenshot](/img/maya_screenshot.jpg)

## Installation

- Supports Maya 2017-2020, Windows 10 x64, macOS High Sierra+ and Linux

- *Windows 10 x64*
  - install the [Microsoft Visual C++ redistributables](https://aka.ms/vs/16/release/vc_redist.x64.exe).
    - on many systems this is already installed, so you might want to skip this step.
  - download the desired [release](https://github.com/iimachines/Maya2glTF/releases)
  - extract the downloaded `zip` file to any location (e.g. your desktop)
  - open the created `maya2glTF` folder
  - double click on the `deploy` batch file
    - This will copy the plug-in and scripts to your `Documents` folder
  - re-launch Maya
- *macOS High Sierra* and *Linux*
    - must currently be build from source, see below

## Usage

  - load a scene
  - in the Maya script window, type `maya2glTF_UI` to launch the UI.
    - You might want to select the `maya2glTF_UI` script text and drag it using the middle-mouse-button to the `Custom` shelf, or even better, make a `glTF` shelf...
  - select the meshes and cameras you want export
    - or click the `select all polygon meshes` button
  - select the desired animation clips source using the dropdown box
    - TRAX animation clips are also supported.
      - _only enabled clips on the first track are exported_.
      - if you have multiple characters, select the desired one.
  - hit the `export selected meshes` button.
    - _currently the user interface is not automatically updated when you change or load a scene; just re-run the `maya2glTF_UI` script or hit the `refresh user interface` button_.
  - good luck! ;-)

## Contributions

- let me know if this doesn't work for you
  - ideally make an issue, providing the OS, Maya and plug-in version, and a test-scene.
- if it _does_ work, please give maya2glTF a :star: on GitHUB, and spread the word :sunglasses:

## Shading
- _I assume you already used something like Substance Painter to create glTF-PBR textures_
- select the polygons you want to shade
- click the `assign PBR shader to selection` button
- the first time, you need to select our PBR OpenGL shader at:
  - `Documents\maya\maya2glTF\PBR\shaders\glTF_PBR.ogsfx`
- next, select all the PBR textures you want to apply in one go:
  - for example, for the [damaged helmet model](https://github.com/KhronosGroup/glTF-Sample-Models/tree/master/2.0/DamagedHelmet/glTF), multi-select the following textures:
    - `Default_normal.jpg`
    - `Default_albedo.jpg`
    - `Default_AO.jpg`
    - `Default_emissive.jpg`
    - `Default_metalRoughness.jpg`
- now the PBR shader and all textures should be applied to your selection
- by default we use the following keyword-in-filename convention to detect the kind of texture:
  - `basecolor` or `albedo` => base color texture
  - `metal` or `_orm` => metallic texture
  - `rough` or `_orm` => roughness texture
  - `occl` or `_orm` or `_ao` => occlusion texture
  - `normal` => tangent space normal texture
    - see also the `-mts` flag for MikkTSpace information if your models come from Blender
  - `emissive` => emissive texture
  - `diffuse_env` => Image-based-lighting (IBL) prefiltered diffuse environment map (PMREM)
  - `specular_env` => Image-based-lightning (IBL) prefiltered specular environment map (PMREM)
  - `brdf` => Bidirectional reflectance distribution function lookup table texture
  - _you can customize these conventions, see `maya2glTF_assignPbrShader.mel`_
- all textures are optional
- set the [technique to transparent if desired](https://github.com/iimachines/Maya2glTF/issues/150)
- see the [glTF PBR page](https://github.com/KhronosGroup/glTF-WebGL-PBR) page for more info.
- the metallic and roughness textures are always merged into a single texture when exporting.
  - _If you provide JPEGs, we use Maya's JPEG encoder to generate this texture. However, the default Maya JPEG encoding settings are very low quality_.
    - The following MEL snippet sets the JPEG encoder quality:
      ```
      putenv "AW_JPEG_Q_FACTOR" "92";
      ```
    - The following MEL code enables maximum possible JPEG quality:
      ```
      putenv "AW_JPEG_Q_FACTOR" "100";
      putenv "AW_JPEG_SUB_SAMPLING" "1x1,1x1,1x1";
      ```

## Rationale

At **[IIM](https://www.iim.media)**, we are specialized in creating realtime interactive 3D animation, for web, education, events and broadcast television, since 1992. We have developed our own multi-machine real-time 3D puppeteering software called **AnimationNow**, and we are about to upgrade this to make use of up-to-date rendering techniques.

If something goes wrong in our production pipeline, it usually is exporting our complex rigged Maya characters. In the past, we contributed both donations and patches to the open source OGRE exporter, but now we want to dig deep into the Maya API ourselves, so we can help out our artists if something goes wrong during the export.

**[glTF 2.0](https://www.khronos.org/gltf)** seems to contain most of the features we need, and is extensible. IMHO [glTF](https://www.khronos.org/gltf) must become the defacto standard for animated 3D content. At [IIM](https://www.iim.media), we plan to use [glTF](https://www.khronos.org/gltf) for all our 3D assets.

## Limitations

Maya interally uses a dataflow architecture (called the _dependency graph_). This means that power-users can connect the dependency nodes in the graph in any way they like. Unfortunately this awesome flexibility also makes it insanely difficult to develop an exporter that always works ;-)

## Plugin Command Arguments
  _ `-outputFolder (-of) STRING` _(required)\* \* the output folder

  - `-scaleFactor (-sf) FLOAT` _(optional)_

    - scale factor to apply to the vertices

  - `-copyright (-cpr) STRING` _(optional)_

    - copyright text to be embedded in the GLTF file

  - `-selectedNodesOnly (-sno)` _(optional)_

    - only exports the directly selected nodes
    - by default all descendants of the selected nodes are exported too

  - `-sceneName (-sn) STRING` _(optional)_

    - the name of the glTF filename
    - default is Maya scene name

  - `-binary (-glb)` _(optional)_

    - exports a single `glb` asset file
    - default is a JSON `glTF` and binary `bin` file containing the buffers

  - `-externalTextures (-ext)` _(optional)_

    - doesn't embed textures in the `glb` files. 
    - only valid when exporting a `-glb`

  - `-camera (-cam) STRING` _(optional, multiple)_

    - exports camera given by name.

  - `-initialValuesTime (-ivt) TIME` _(optional)_

    - the time where the initial/default values can be found
    - by default frame 0 is used
    - this frame should match the **skin bind pose**
    - all nodes and meshes get their default transforms and weights from this time

  - `-animationClipName (-acn) STRING` _(optional, multiple)_

    - the name of the animation clip

  - `-animationClipStartTime (-ast) TIME` _(optional, multiple)_

    - the start time of the animation clip
    - required when exporting animation clips

  - `-animationClipEndTime (-aet) TIME` _(optional, multiple)_

    - the end time of the animation clip
    - required when exporting animation clips

  - `-animationClipFrameRate (-afr) FLOAT` _(optional, multiple)_

    - the frames-per-second of the animation clip
    - required when exporting animation clips
    - either you pass this for each clip, or once

  - `-detectStepAnimations (-dsa) NUMBER` _(optional)_

    - pass `-dsa 2` to detect `STEP` "interpolations" in the sampled animations curves. 
    - enable this e.g. when binding the `shape.visiblity` to `node.scale.x, y z`, to prevent interpolation.
    - currently this is all or nothing, animation curves are not yet split into discrete and continuous parts
    
  - `-meshPrimitiveAttributes (-mpa) STRING` _(optional)_

    - the attributes for the shapes to export, separated by a vertical bar |
    - by default all attributes are exported, e.g.
      - `-mpa POSITION|NORMAL|TANGENT|TEXCOORD|COLOR|JOINTS|WEIGHTS`

  - `-blendPrimitiveAttributes (-bpa) STRING` _(optional)_

    - the attributes for the blend-shapes to export, separated by a vertical bar |
    - by default all GLTF supported attributes are exported, e.g.
      - `-mpa POSITION|NORMAL|TANGENT`

  - `-force32bitIndices (-i32)` _(optional)_

    - forces 32-bit indices to be written to the GLTF buffers
    - by default 16-bit indices are used whenever possible

  - `-disableNameAssignment (-dnn)` _(optional)_

    - do not assign Maya node names to GLTF nodes
    - by default names are copied

  - `-mikkelsenTangentSpace (-mts)` _(optional)_

    - use the 'MikkTSpace' algoritm for computing the tangents instead of those from Maya
    - by default the Maya tangents are exported
      - if you imported meshes from Blender without importing the tangents, and you just use Maya for doing animation, you should use this flag.

  - `-mikkelsenTangentAngularThreshold (-mta)` _(optional)_

    - the angular threshold to be passed to the 'MikkTSpace' algoritm
      - by default 180 is passed
      - in general you should not use this flag, it is mainly for debugging

  - `-skipStandardMaterials (-ssm)` _(optional)_

    - do not export standard materials (lambert, phong, etc), only GLTF PBR materials.
    - by default standard materials are converted
      - but just the color and transparency is copied for now.

  - `-excludeUnusedTexcoord (-eut)` _(optional)_

    - exclude texture coordinates when the mesh primitive doesn't have textures?
      - by default texture coordinates are always exported

  - `-defaultMaterial (-dm)` _(optional)_

    - always generates a glTF PBR material, even if no material is assigned to a mesh in Maya
    - by default no default materials are generated

  - `-colorizeMaterials (-cm)` _(optional)_

    - for debugging, generate a unique PBR material with a different color for each material
    - by default no debug materials are generated

  - `-dumpMaya (-dmy) STRING` _(optional)_

    - dumps debugging info of the Maya objects to the given filepath argument
    - use the word `CONSOLE` to print to the Maya output window
      - _WARNING: this can take a very long time if you have complex meshes!_
    - by default nothing is printed

  - `-dumpGLTF (-dgl) STRING` _(optional)_

    - dumps a formatted version of the glTF asset file to the given filepath argument
    - use the word `CONSOLE` to print to the Maya output window
      - _WARNING: this can take a very long time if you have complex meshes!_
    - by default nothing is printed

  - `-ignoreMeshDeformers (-imd) STRING` _(optional, multiple)_

    - blend-shape or skin-cluster deformers to be ignored
    - by default no deformers are ignored
    - use this if you have deformers that are used to generate different characters, but not for animation
	- you can also add the custom attribute `Maya2glTF_ignored` (short name `MGi`) to the deformer to ignore it.
		- to `maya2glTF_UI` has a button to add this attribute to the selected deformer(s)

  - `-skipSkinClusters (-ssc)` _(optional)_

    - skip all skin cluster deformers, as if the mesh was not skinned
    - by default no skin clusters are skipped

  - `-skipBlendShapes (-sbs)` _(optional)_

    - skip all blend-shape deformers, as if the mesh was not morphed
    - by default no blend-shape deformers are skipped

  - `-redrawViewport (-rvp)` _(optional)_
    - redraw the viewport when exporting animation.
    - by default the viewport is not refreshed, since this slows down the exporter

## Status

I consider this plugin to be production quality now, but use it at your own risk :)

- Supports **Maya 2017-2020** (64-bit only)

  - Maya 2016 is not supported any more

- Linux support hasn't been tested a lot.

- Supports **static and animated, skinned and morphed meshes**

  - Currently all animation is _baked_ per frame, no compression is done yet

- Supports **multiple animation clips** (node and joint transforms, blend shape weights)

  - Blend shape targets are not sparse yet

- Exports `POSITION`, `NORMAL`, `COLOR`, `NORMAL`, `TANGENT`, `TEXCOORD`, `JOINTS` and `WEIGHTS` attributes

- Supports exporting to `glTF + bin`, single `glTF` or single `glb` files.

- Uses a modified fork of the glTF code from the COLLADA2GLTF project

- Currently Phong, Lambert and Blinn shaders are converted to PBR, but only the color texture and transparency is taken into account (this is mainly done for testing with existing models).

- Comes with GLSL code with a friendly UI ported from the official Khronos PBR WebGL code.

  - See `maya2glTF\maya\renderData\shaders\glTF_PBR.ogsfx`
  - To use this hardware shader
    - make sure the GLSL shader plugin is loaded
    - use the _OpenGL/Core Profile_ in Preferences/Display
  - You can use the `maya2glTF\maya\scripts\assign_glTF_PBR_material_and_textures.mel` script to assign multiple textures at once, based on filename patterns

- Supports exporting cameras

- No lights yet

  - support for the [KHR_lights_punctual](https://github.com/KhronosGroup/glTF/tree/master/extensions/2.0/Khronos/KHR_lights_punctual) will be added at some point, PR welcome, see issues

## Building

- Currently out-of-the-box downloads are only provided for Windows x64 

  - _If you want to try the exporter, but you can't build it, give me a sign_

- I assume you already installed a [GIT client](https://git-scm.com/downloads)

- Some versions of Maya require a **[Maya devkit](https://www.autodesk.com/developer-network/platform-technologies/maya)**
  - *Seems not needed for Maya 2018+*

* Clone this repository

  - Open a command prompt (aka terminal), and run

  ```
  git clone https://github.com/iimachines/Maya2glTF.git --branch master
  ```

### Building for **Windows**
- Install **[Visual Studio 2019](https://www.visualstudio.com/downloads)**

  - Select at least the **C++ desktop development** payload
  - In the individual components tab, select:
    - the **Windows 8.1 SDK**
    - the **Windows Universal CRT SDK**
  - This document was written for Visual Studio 2019, other versions might not work.

- Install the Win64-x64 version of **[CMAKE](https://cmake.org)**

  - Make sure to add CMake to the system path

* Enter the `maya2glTF` folder, and run

  ```
  windows_create_vs_project -D MAYA_VERSION=2020
  ```

  - Change 2020 in the Maya version you want to target.
  - After a couple of seconds, a Visual Studio solution should be generated in the `build` folder.

* Next build the `maya2glTF` plugin itself

  - Launch Visual Studio 2019

  - Open the solution `maya2glTF\build\maya2glTF.sln`

  - Select the desired configuration target (e.g. `release`)

  - Build

  - If all goes well, the plugin and all scripts will be copied to your `%userprofile%\Documents\maya` folders

### Building for **MacOS**
    - install [XCode](https://www.apple.com/us/search/xcode) from the app-store
    - install [CMake](https://cmake.org/download/)
    - open a Terminal window
        - See `Finder` `Utilities` `Terminal`
    - clone this repository
        - e.g. `git clone https://github.com/iimachines/Maya2glTF.git ~/Documents/Maya2glTF`
    - enter the cloned directory
        - e.g. `cd ~/Documents/Maya2glTF`
    - create the build script by running
        - `./osx_create_project.sh 2020`
        - Replace 2020 with the Maya version you're targetting
    - enter the generated `build` folder, and `make` the plugin
        - `make`
    - if all goes well, the plugin should be ready to be used.

### Building for **Linux**
    - TODO

#### Testing the build

  - Start Maya

  - Load a scene 
  
    - **NOTE** to load scenes from this project, first set the Maya project to the `maya2glTF\maya` folder

    - to see if the plugin was built correctly, it's best to use a scene from this repository, for example `maya2glTF\maya\scenes\damaged_helmet.ma`

  - select the meshes and cameras you want to export

    - by default all descendants are also exported, unless you add the -selectedNodesOnly (sno) flag.

  - run the following MEL script

  ```
  maya2glTF -outputFolder "<your output folder>"
  ```

  - I use the [vscode](https://code.visualstudio.com/) [glTF viewer](https://github.com/AnalyticalGraphicsInc/gltf-vscode)

    - Make sure to switch between BabylonJS, Cesium and ThreeJS, they all give different results... For our own assets, it seems ThreeJS gives the best results.

  - If you want to contribute to the development, you might want to use the MEL script `maya2glTF\maya\scripts\test-iteration.mel`. This unloads and reloads the plugin everytime, unlocking the DLL.

