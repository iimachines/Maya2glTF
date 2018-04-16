# Maya to glTF exporter

![Maya Tiger screenshot](/img/tiger-wim@koetan.gif)

![Maya Helmet screenshot](/img/maya_screenshot.jpg)


## Update

The first BETA is released! See the [releases](https://github.com/Ziriax/Maya2glTF/releases) tab. Maya 2018 on Windows x64 only for now.

## Rationale

At **[Wonder Media](https://wondermedia.tv)**, we are specialized in creating realtime interactive 3D animation, for education, events and broadcast television, since 1992. We have developed our own multi-machine real-time 3D puppeteering software called **AnimationNow**, and we are about to upgrade this to make use of up-to-date rendering techniques. 

If something goes wrong in our production pipeline, it usually is exporting our complex rigged Maya characters. In the past, we contributed both donations and patches to the open source OGRE exporter, but now we want to dig deep into the Maya API ourselves, so we can help out our artists if something goes wrong during the export. 

**[glTF 2.0](https://www.khronos.org/gltf)** seems to contain most of the features we need, and is extensible. IMHO [glTF](https://www.khronos.org/gltf) must become the defacto standard for animated 3D content. At [Wonder Media](https://wondermedia.tv), we plan to use [glTF](https://www.khronos.org/gltf) for all our 3D assets.

## Limitations

Maya interally uses a dataflow architecture (called the *dependency graph*). This means that power-users can connect the dependency nodes in the graph in any way they like. Unfortunately this awesome flexibility also makes it insanely difficult to develop an exporter that always works ;-)

## Status

I consider this plugin to be in *beta* stage, use it at your own risk :) 

* Supports **Maya 2016 EXT2, 2017, 2018** (64-bit only)
    * Maya 2016 is a different product from Maya 2016 EXT2 and is ***not supported***, since I can't find a compatible devkit for it.

* Windows only for now
    * although the code is written using C++ 17 and should be platform independent, so can be ported by people with this experience (PR welcome! :) 

* Supports **static and animated, skinned and morphed meshes**
    * Currently all animation is *baked* per frame, no compression is done yet

* Supports **multiple animation clips** (node and joint transforms, blend shape weights)
    * Blend shape targets are not sparse yet

* Exports `POSITION`, `NORMAL`, `COLOR`, `NORMAL`, `TANGENT`, `TEXCOORD`, `JOINTS` and `WEIGHTS` attributes 
 
* Supports exporting to `glTF + bin`, single `glTF` or single `glb` files.

* Uses the same glTF code as the COLLADA2GLTF project

* Currently Phong, Lambert and Blinn shaders are converted to PBR, but only the color texture and transparency is taken into account (this is mainly done for testing with existing models). 

* Comes with GLSL code with a friendly UI ported from the official Khronos PBR WebGL code.
    * See `Maya2glTF\maya\renderData\shaders\glTF_PBR.ogsfx`  
    * To use this hardware shader
        * make sure the GLSL shader plugin is loaded 
        * use the *OpenGL/Core Profile* in Preferences/Display 
    * You can use the `Maya2glTF\maya\scripts\assign_glTF_PBR_material_and_textures.mel` script to assign multiple textures at once, based on filename patterns

* No lights or cameras yet
    * unlikely to be added, we don't really need this, although not a lot of work
  

## Building

* No out-of-the-box downloads are available yet, currently you have to build the plugin from sources.
    * *If you want to try the exporter, but you can't build it, give me a sign*

* Right now this project requires **Microsoft Windows x64 8.1 or higher**
    * It should be easily ported to OSX and Linux, or older versions of Windows.
    * Feel free to provide a patch request, e.g. one that uses CMake :)

* I assume you already installed a [GIT client for Windows](https://git-scm.com/downloads)

* Install **[Visual Studio 2017](https://www.visualstudio.com/downloads)**
    * Select at least the **C++ desktop development** payload
    * In the individual components tab, select:
        * the **Windows 8.1 SDK**
        * the **Windows Universal CRT SDK**
    * This document was written for Visual Studio 2017 15.5.2, newer versions might not work. 

* Install the Win64-x64 version of **[CMAKE](https://cmake.org)**
    * Make sure to add CMake to the system path

* Install the **[latest Maya devkit matching your Maya application version](https://apps.autodesk.com/All/en/List/Search?isAppSearch=True&searchboxstore=All&facet=&collection=&sort=&query=maya+devkit)**
    
* We need to tell the Maya2glTF project where it can find the Maya devkit header and library files. Declare the following environment variables, or add `user macros` to the Visual Studio `Microsoft.Cpp.x64.user` property page
    * For Maya 2018:
        * `MAYA_2018_SDK` -> *the `devkitBase` sub-folder of the Maya devkit*, e.g. `C:\dev\Maya-2018-SDK\devkitBase`
    * For Maya 2017:
        * `MAYA_2017_INC` -> *the `include` folder of the devkit*, e.g `C:\dev\Maya-2017-SDK\devkitBase\include`
        * `MAYA_2017_LIB` -> *the `lib` folder of **your Maya 2017 program installation***, e.g. `C:\Program Files\Autodesk\Maya2017\lib`
    * For Maya 2016 EXT2:
        * `MAYA_2016_EXT2` -> *the folder of **your Maya 2016.5 program installation***, e.g. `C:\Program Files\Autodesk\Maya2016.5`
     

* Run the `Developer Command Prompt for VS 2017`, and then clone this repository, including ***all dependencies***. *Oh, did I mention not to forget the dependencies? ;-)*
    
    ```
    git clone https://github.com/Ziriax/Maya2glTF --branch develop --recursive
    ```

* Enter the `Maya2glTF` folder, and run 
    ```
    windows_build_dependencies
    ```
    * After a couple of minutes, your console should turn green if this succeeds, or red if this fails. In the latter case, make sure you cloned the GIT dependencies, see the previous step...

* Next build the `Maya2glTF` plugin itself, by running the following command inside the `Maya2glTF` folder
    ```
    windows_build_plugin *MAYA_VERSION*
    ```

    Where  *MAYA_VERSION* is either 2016, 2017 or 2018.
    
    Obviously you can also use Visual Studio to build and debug the plugin.

* Now export a 3D model:
    * Start Maya
    
    * Load a scene
		* **NOTE** to load scenes from this project, first set the Maya project to the `Maya2glTF\maya` folder
        * to see if the plugin was built correctly, it's best to use a scene from this repository, for example `Maya2glTF\maya\scenes\damaged_helmet.ma`
    
    * select the mesh(es) you want to export
    
    * run the following MEL script
    ```
    maya2glTF -outputFolder "<your output folder>"
    ```
    
    * I use the [vscode](https://code.visualstudio.com/) [glTF viewer](https://github.com/AnalyticalGraphicsInc/gltf-vscode)
        * Make sure to switch between BabylonJS, Cesium and ThreeJS, they all give different results...

    * If you want to contribute to the development, you might want to use the MEL script `Maya2glTF\maya\scripts\test-iteration.mel`. This unloads and reloads the plugin everytime, unlocking the DLL.

* The supported plugin arguments are
	* `-outputFolder (-of) STRING` *(required)* 
        * the output folder  

    * `-scaleFactor (-sf) FLOAT` *(optional)* 
        * scale factor to apply to the vertices

    * `-copyright (-cpr) STRING` *(optional)* 
        * copyright text to be embedded in the GLTF file

    * `-sceneName (-sn) STRING` *(optional)* 
        * the name of the glTF filename
        * default is Maya scene name
    
    * `-binary (-glb)` *(optional)* 
        * exports a single `glb` asset file 
        * default is a JSON `glTF` and binary `bin` file containing the buffers
    
    * `-embedded (-emb)` *(optional)* 
        * embeds buffers into the `glTF` file, as base-64 encoded strings
        * by default the buffers are stored in a separate `bin` file

    * `-initialValuesTime (-ivt) TIME` *(optional)* 
        * the time where the initial/default values can be found
        * by default frame 0 is used
        * this frame should match the **skin bind pose**
        * all nodes and meshes get their default transforms and weights from this time 

    * `-animationClipName (-acn) STRING` *(optional, multiple)* 
        * the name of the animation clip

    * `-animationClipStartTime (-ast) TIME` *(optional, multiple)* 
        * the start  time of the animation clip
        * required when exporting animation clips

    * `-animationClipEndTime (-aet) TIME` *(optional, multiple)* 
        * the end time of the animation clip
        * required when exporting animation clips

    * `-animationClipFrameRate (-afr) FLOAT` *(optional, multiple)* 
        * the frames-per-second of the animation clip
        * required when exporting animation clips
        * either you pass this for each clip, or once

    * `-meshPrimitiveAttributes (-mpa) STRING` *(optional)* 
        * the attributes for the shapes to export, separated by a vertical bar |
        * by default all attributes are exported, e.g.
            * `-mpa POSITION|NORMAL|TANGENT|TEXCOORD|COLOR|JOINTS|WEIGHTS`

    * `-blendPrimitiveAttributes (-bpa) STRING` *(optional)* 
        * the attributes for the blend-shapes to export, separated by a vertical bar |
        * by default all GLTF supported attributes are exported, e.g.
            * `-mpa POSITION|NORMAL|TANGENT`

    * `-force32bitIndices (-i32)` *(optional)* 
        * forces 32-bit indices to be written to the GLTF buffers
        * by default 16-bit indices are used whenever possible

    * `-disableNameAssignment (-dnn)` *(optional)* 
        * do not assign Maya node names to GLTF nodes
        * by default names are copied

    * `-mikkelsenTangentSpace (-mts)` *(optional)* 
        * use the 'MikkTSpace' algoritm for computing the tangents instead of those from Maya
        * by default the Maya tangents are exported
            * if you imported meshes from Blender without importing the tangents, and you just use Maya for doing animation, you should use this flag.

    * `-mikkelsenTangentAngularThreshold (-mta)` *(optional)* 
        * the angular threshold to be passed to the 'MikkTSpace' algoritm
            * by default 180 is passed 
            * in general you should not use this flag, it is mainly for debugging

    * `-skipStandardMaterials (-ssm)` *(optional)* 
        * do not export standard materials (lambert, phong, etc), only GLTF PBR materials.
        * by default standard materials are converted
            * but just the color and transparency is copied for now.
	
    * `-defaultMaterial (-dm)` *(optional)* 
        * always generates a glTF PBR material, even if no material is assigned to a mesh in Maya
        * by default no default materials are generated
    
    * `-colorizeMaterials (-cm)` *(optional)* 
        * for debugging, generate a unique PBR material with a different color for each material
        * by default no debug materials are generated
    
    * `-dumpMaya (-dmy) STRING` *(optional)* 
        * dumps debugging info of the Maya objects to the given filepath argument
        * use the word `CONSOLE` to print to the Maya output window
            * *WARNING: this can take a very long time if you have complex meshes!*
        * by default nothing is printed
    
    * `-dumpGLTF (-dgl) STRING` *(optional)* 
        * dumps a formatted version of the glTF asset file to the given filepath argument
        * use the word `CONSOLE` to print to the Maya output window
            * *WARNING: this can take a very long time if you have complex meshes!*
        * by default nothing is printed

    * `-ignoreMeshDeformers (-imd) STRING` *(optional, multiple)* 
        * blend-shape or skin-cluster deformers to be ignored  
        * by default no deformers are ignored
        * use this if you have deformers that are used to generate different characters, but not for animation

    * `-skipSkinClusters (-ssc)` *(optional)* 
        * skip all skin cluster deformers, as if the mesh was not skinned
        * by default no skin clusters are skipped

    * `-skipBlendShapes (-sbs)` *(optional)* 
        * skip all blend-shape deformers, as if the mesh was not morphed
        * by default no blend-shape deformers are skipped

    * `-redrawViewport (-rvp)` *(optional)* 
        * redraw the viewport when exporting animation.
        * by default the viewport is not refreshed, since this slows down the exporter
