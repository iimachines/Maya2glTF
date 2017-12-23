# Maya to glTF exporter

## Status

* I consider this plugin to be in *pre-alpha* stage, use it at your own risk :) 
    * However, it works for 3D models we use at [Wonder Media](https://wondermedia.tv), so give your model a try

* Supports **Maya 2017-x64** and **Maya 2018-x64** 

* Windows only
    * although the code is written using C++ 17 and should be platform independent, so can be ported by people with this experience (PR welcome! :) 

* Uses the same glTF code as the COLLADA2GLTF project
    * albeit with some patches of mine.
    
* Exporting static meshes with POSITION, NORMAL, COLOR, NORMAL, TANGENT, and TEXCOORD attributes (aka semantics) seems to work, although on some meshes the BabylonJS viewer renders incorrectly (the ThreeJS and Cesium viewers render correctly).

* Exports the position, rotation and scale of nodes, but no animation yet.

* Supports exporting to `glTF + bin`, single `glTF` or single `glb` files.

* Currently Phong, Lambert and Blinn shaders are converted to PBR, but only the color texture and transparency is taken into account (this is mainly done for testing with existing models). 

* Converts the StingrayPBS material to glTF PBR.
    * You should use the ShaderFX graph in `Maya2glTF\maya\renderData\shaders\glTF_maya_shader.sfx` to emulate the glTF PBR shader
    * Now since Autodesk cancelled Stingray, we will provide our own `OGSFX/GLSL` and `FX/HLSL` PBR shaders for Maya (this is completed but we are having some colorspace troubles) 

* Code for exporting blend-shape deltas exists, but is not fully working yet.

* No skinning nor animation yet
    * but my company needs this urgently, so it's high on our TODO

* No lights, cameras, meshes only
    * unlikely to be added, we don't really need this
    

## Building

* Currently this project requires **Microsoft Windows 10 x64**
    * It can easily be ported to OSX and Linux, or older versions of Windows.
    * Feel free to provide a patch request, e.g. one that uses CMake :)

* All development happens in the *develop* branch, the *master* branch will contain so called 'stable' code and hot-fixes. 

* I assume you already installed a [GIT client for Windows](https://git-scm.com/downloads)

* Install [Visual Studio 2017](https://www.visualstudio.com/downloads)
    * Select at least the C++ desktop development payload

* Install the Win64-x64 version of [CMAKE](https://cmake.org)

* Install the [latest Maya devkit matching your Maya application version](https://apps.autodesk.com/All/en/List/Search?isAppSearch=True&searchboxstore=All&facet=&collection=&sort=&query=maya+devkit)
    
* We need to tell the Maya2glTF project where it can find the Maya devkit header and library files. Declare the following environment variables, or add `user macros` to the Visual Studio `Microsoft.Cpp.x64.user` property page
    * For Maya 2018:
        * `MAYA_2018_SDK` -> *the devkit folder*
    * For Maya 2017:
        * `MAYA_2017_INC` -> *the `include` folder of the devkit*, e.g `C:\dev\Maya-2017-x64\devkitBase\include`
        * `MAYA_2017_LIB` -> *the `lib` folder of **your Maya program installation***, e.g. `C:\Program Files\Autodesk\Maya2017\lib`
     

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
    windows_build_plugin 2018
    ```
    or
    ```
    windows_build_plugin 2017
    ```
    
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

