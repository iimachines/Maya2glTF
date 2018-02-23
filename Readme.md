# Maya to glTF exporter

![Maya screenshot](/img/maya_screenshot.jpg)

## Rationale

At **[Wonder Media](https://wondermedia.tv)**, we are specialized in creating realtime interactive 3D animation, for education, events and broadcast television, since 1992. We have developed our own multi-machine real-time 3D puppeteering software called **AnimationNow**, and we are about to upgrade this to make use of up-to-date rendering techniques. 

If something goes wrong in our production pipeline, it usually is exporting our complex rigged Maya characters. In the past, we contributed both donations and patches to the open source OGRE exporter, but now we want to dig deep into the Maya API ourselves, so we can help out our artists if something goes wrong during the export. 

**[glTF 2.0](https://www.khronos.org/gltf)** seems to contain most of the features we need, and is extensible. IMHO [glTF](https://www.khronos.org/gltf) must become the defacto standard for animated 3D content. At [Wonder Media](https://wondermedia.tv), we plan to use [glTF](https://www.khronos.org/gltf) for all our 3D assets.

## Limitations

Maya interally uses a dataflow architecture (called the *dependency graph*). This means that power-users can connect these nodes in any way they like. Unfortunately this flexibility also makes it insanely difficult to develop an exporter that always works ;-)

## Status

I consider this plugin to be in *pre-alpha* stage, use it at your own risk :) 

* Supports **Maya 2016 EXT2, 2017, 2017** (64-bit only)
    * Maya 2016 is a different product from Maya 2016 EXT2 and is ***not supported***, since I can't find a compatible devkit for it.

* Windows only
    * although the code is written using C++ 17 and should be platform independent, so can be ported by people with this experience (PR welcome! :) 

* Uses the same glTF code as the COLLADA2GLTF project
    
* Exporting static meshes with POSITION, NORMAL, COLOR, NORMAL, TANGENT, and TEXCOORD attributes (aka semantics) seems to work
    * although on some meshes the BabylonJS viewer renders incorrectly (the ThreeJS and Cesium viewers render correctly).

* Exports the position, rotation and scale of nodes, but no animation yet.

* Supports exporting to `glTF + bin`, single `glTF` or single `glb` files.

* Currently Phong, Lambert and Blinn shaders are converted to PBR, but only the color texture and transparency is taken into account (this is mainly done for testing with existing models). 

* Comes with GLSL code with a friendly UI ported from the official Khronos PBR WebGL code.
    * See `Maya2glTF\maya\renderData\shaders\glTF_PBR.ogsfx`  
    * To use this hardware shader
        * make sure the GLSL shader plugin is loaded 
        * use the *OpenGL/Core Profile* in Preferences/Display 

* Code for exporting blend-shape deltas exists, but is not fully working yet.

* No skinning nor animation yet
    * but my company needs this urgently, so it's high on our TODO

* No lights, cameras, meshes only
    * unlikely to be added, we don't really need this
    

## Building

* No out-of-the-box downloads are available yet, currently you have to build the plugin from sources.

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
        * to see if the plugin was built correctly, it's best to use a scene from this repository, for example `Maya2glTF\maya\scenes\damaged_helmet.ma`
    
    * select the mesh(es) you want to export
    
    * run the following MEL script
    ```
    maya2glTF -fpm -sep -outputFolder "<your output folder>"
    ```
    
    * I use the [vscode](https://code.visualstudio.com/) [glTF viewer](https://github.com/AnalyticalGraphicsInc/gltf-vscode)
        * Make sure to switch between BabylonJS, Cesium and ThreeJS, they all give different results...

    * If you want to contribute to the development, you might want to use the MEL script `Maya2glTF\maya\mel\test-iteration.mel`. This unloads and reloads the plugin everytime, unlocking the DLL.

* The supported plugin arguments are
	* `-outputFolder (-of) STRING` *(required)* 
        * the output folder  
    
    * `-sceneName (-sn) STRING` *(optional)* 
        * the name of the glTF filename
        * default is Maya scene name
    
    * `-glb` *(optional)* 
        * exports a single `glb` asset file 
        * default is a single `glTF` asset file
    
    * `-sep` *(optional)* 
        * seperates resources from the asset file in a `bin` file
        * default is to embed all resources in the asset file
    
    * `-forcePbrMaterials (-fpm)` *(optional)* 
        * force exporting PBR materials for Phong, Lambert and Blinn materials
        * by default these materials are not converted
            * they might be converted to a compatible material in the future
	
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

