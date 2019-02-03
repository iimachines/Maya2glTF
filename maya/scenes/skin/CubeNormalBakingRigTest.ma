//Maya ASCII 2018ff07 scene
//Name: CubeNormalBakingRigTest.ma
//Last modified: Sun, Feb 03, 2019 12:01:29 PM
//Codeset: 1252
requires maya "2018ff07";
requires "stereoCamera" "10.0";
requires -nodeType "GLSLShader" "glslShader" "1.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2018";
fileInfo "version" "2018";
fileInfo "cutIdentifier" "201711281015-8e846c9074";
fileInfo "osv" "Microsoft Windows 8 Business Edition, 64-bit  (Build 9200)\n";
createNode transform -s -n "persp";
	rename -uid "1CE062EA-477A-B7B8-D645-5596AADC08E7";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1.2467578062684366 1.1323375426957325 2.9371773274417161 ;
	setAttr ".r" -type "double3" -19.538352671432211 -1056.9999999995421 -8.6380714603115357e-16 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "C4935601-467D-7DF4-2F6E-BA8B414677C4";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 3.3857944401459124;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "9A2D5671-4DA0-64AC-9677-34AC14010C2A";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 1000.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "DFD81D49-4D88-3BEF-AAEF-9A8148720AF3";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	rename -uid "49DC5B17-4BEE-D096-E459-66A8B2E3C6D3";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 1000.1 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "78D375D8-4146-766F-36FD-00A495F441DA";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	rename -uid "CA189366-4A50-D1A3-0246-86AF70E583CF";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "3049F159-4EB9-7FD6-030E-C0B8F616FC15";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "SoftCube";
	rename -uid "47CA52D6-44C3-4712-AF9D-2DABBABE3F8B";
	addAttr -is true -ci true -k true -sn "currentUVSet" -ln "currentUVSet" -dt "string";
	setAttr -l on ".tx";
	setAttr -l on ".ty";
	setAttr -l on ".tz";
	setAttr -l on ".rx";
	setAttr -l on ".ry";
	setAttr -l on ".rz";
	setAttr -l on ".sx";
	setAttr -l on ".sy";
	setAttr -l on ".sz";
	setAttr -k on ".currentUVSet" -type "string" "map1";
createNode mesh -n "SoftCubeShape" -p "SoftCube";
	rename -uid "D87CCB43-42A8-8CD1-94C1-4A92802095F4";
	setAttr -k off ".v";
	setAttr -s 4 ".iog[0].og";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".tsa" 10;
	setAttr ".tnt" 10;
	setAttr ".vcs" 2;
createNode mesh -n "SoftCubeShapeOrig" -p "SoftCube";
	rename -uid "936BD0DA-4637-7202-838E-3B917E184A3D";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 14 ".uvst[0].uvsp[0:13]" -type "float2" 0.375 0 0.625 0 0.375
		 0.25 0.625 0.25 0.375 0.5 0.625 0.5 0.375 0.75 0.625 0.75 0.375 1 0.625 1 0.875 0
		 0.875 0.25 0.125 0 0.125 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 8 ".vt[0:7]"  -0.5 -0.5 0.5 0.5 -0.5 0.5 -0.5 0.5 0.5 0.5 0.5 0.5
		 -0.5 0.5 -0.5 0.5 0.5 -0.5 -0.5 -0.5 -0.5 0.5 -0.5 -0.5;
	setAttr -s 18 ".ed[0:17]"  0 1 0 1 2 0 2 0 0 1 3 0 3 2 0 3 4 0 4 2 0
		 3 5 0 5 4 0 5 6 0 6 4 0 5 7 0 7 6 0 7 0 0 0 6 0 7 1 0 7 3 0 0 4 0;
	setAttr -s 36 ".n[0:35]" -type "float3"  -0.5773502 -0.5773502 0.5773502
		 0.5773502 -0.5773502 0.5773502 -0.5773502 0.5773502 0.5773502 -0.5773502 0.5773502
		 0.5773502 0.5773502 -0.5773502 0.5773502 0.5773502 0.5773502 0.5773502 -0.5773502
		 0.5773502 0.5773502 0.5773502 0.5773502 0.5773502 -0.5773502 0.5773502 -0.5773502
		 -0.5773502 0.5773502 -0.5773502 0.5773502 0.5773502 0.5773502 0.5773502 0.5773502
		 -0.5773502 -0.5773502 0.5773502 -0.5773502 0.5773502 0.5773502 -0.5773502 -0.5773502
		 -0.5773502 -0.5773502 -0.5773502 -0.5773502 -0.5773502 0.5773502 0.5773502 -0.5773502
		 0.5773502 -0.5773502 -0.5773502 -0.5773502 -0.5773502 -0.5773502 0.5773502 -0.5773502
		 -0.5773502 -0.5773502 -0.5773502 0.5773502 -0.5773502 -0.5773502 0.5773502 0.5773502
		 -0.5773502 -0.5773502 0.5773502 -0.5773502 0.5773502 0.5773502 -0.5773502 0.5773502
		 0.5773502 -0.5773502 -0.5773502 0.5773502 0.5773502 0.5773502 0.5773502 0.5773502
		 0.5773502 0.5773502 -0.5773502 -0.5773502 0.5773502 0.5773502 -0.5773502 -0.5773502
		 -0.5773502 -0.5773502 -0.5773502 -0.5773502 0.5773502 -0.5773502 0.5773502 -0.5773502
		 -0.5773502 0.5773502 -0.5773502 -0.5773502 -0.5773502 0.5773502 -0.5773502 0.5773502
		 0.5773502;
	setAttr -s 12 -ch 36 ".fc[0:11]" -type "polyFaces" 
		f 3 0 1 2
		mu 0 3 0 1 2
		f 3 -2 3 4
		mu 0 3 2 1 3
		f 3 -5 5 6
		mu 0 3 2 3 4
		f 3 -6 7 8
		mu 0 3 4 3 5
		f 3 -9 9 10
		mu 0 3 4 5 6
		f 3 -10 11 12
		mu 0 3 6 5 7
		f 3 -13 13 14
		mu 0 3 6 7 8
		f 3 -14 15 -1
		mu 0 3 8 7 9
		f 3 -16 16 -4
		mu 0 3 1 10 3
		f 3 -17 -12 -8
		mu 0 3 3 10 11
		f 3 -15 17 -11
		mu 0 3 12 0 13
		f 3 -18 -3 -7
		mu 0 3 13 0 2;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
createNode joint -n "joint1";
	rename -uid "836A9B7B-4CBB-B597-C788-79812D324F8B";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".uoc" 1;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".bps" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1;
	setAttr ".radi" 0.5;
createNode transform -n "camera1";
	rename -uid "41F63FCF-4F0A-82F9-EE56-25950636C7D2";
	setAttr ".t" -type "double3" 1.8381223547324517 2.2718973820580297 1.8245075111097255 ;
	setAttr ".r" -type "double3" -42.199746004868231 45.799999999999343 2.2810627414084531e-15 ;
createNode camera -n "cameraShape1" -p "camera1";
	rename -uid "6889194D-422A-89DE-DEAE-B9823B3751C7";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".cap" -type "double2" 1.4173 0.9449 ;
	setAttr ".ff" 0;
	setAttr ".coi" 3.4026052934301578;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "camera1";
	setAttr ".den" -type "string" "camera1_depth";
	setAttr ".man" -type "string" "camera1_mask";
	setAttr ".dr" yes;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "2984B45B-4525-6665-DA9D-AFB8F3B94FE6";
	setAttr -s 8 ".lnk";
	setAttr -s 8 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "BD521BE9-436E-5A62-03A5-4A9FA43BDF0B";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "3C8734FB-4E68-AFA6-E482-6EB13BC993EB";
createNode displayLayerManager -n "layerManager";
	rename -uid "E2A21F78-484B-B2AA-4BC3-8FBA7A07E2F9";
createNode displayLayer -n "defaultLayer";
	rename -uid "ACC974D7-479D-0951-16D3-EB9D8126CD3A";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "2E3A2847-4220-3554-6979-259B840A3B75";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "ADB67A05-48B0-5365-362C-C59134C2F4AE";
	setAttr ".g" yes;
createNode lambert -n "surfaceSamplingEnvelopeShader";
	rename -uid "58450C19-4F0D-09C2-972A-29ADA85AD11F";
	setAttr ".c" -type "float3" 1 0.5 0.5 ;
	setAttr ".it" -type "float3" 0.25 0.25 0.25 ;
createNode shadingEngine -n "surfaceSamplingEnvelopeShaderSG";
	rename -uid "7527CA41-4E9F-440C-D16D-26AF290A1D19";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
	rename -uid "9C849DEA-451D-FC57-AEBD-6E93DAD6036F";
createNode GLSLShader -n "GLSL_PBR_Shader";
	rename -uid "A83DA730-4D91-1876-C551-15A14C515CFE";
	addAttr -ci true -sn "Light_0_use_implicit_lighting" -ln "Light_0_use_implicit_lighting" 
		-dv 1 -min 0 -max 1 -at "bool";
	addAttr -s false -ci true -sn "Light_0_connected_light" -ln "Light_0_connected_light" 
		-at "message";
	addAttr -ci true -sn "Light_1_use_implicit_lighting" -ln "Light_1_use_implicit_lighting" 
		-dv 1 -min 0 -max 1 -at "bool";
	addAttr -s false -ci true -sn "Light_1_connected_light" -ln "Light_1_connected_light" 
		-at "message";
	addAttr -ci true -sn "Light_2_use_implicit_lighting" -ln "Light_2_use_implicit_lighting" 
		-dv 1 -min 0 -max 1 -at "bool";
	addAttr -s false -ci true -sn "Light_2_connected_light" -ln "Light_2_connected_light" 
		-at "message";
	addAttr -s false -is true -ci true -k true -sn "te" -ln "techniqueEnum" -nn "Technique" 
		-min 0 -max 1 -en "Solid:Transparent" -at "enum";
	addAttr -is true -ci true -h true -sn "u_LightColor_Name" -ln "u_LightColor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_LightColor_Type" -ln "u_LightColor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_LightColor" -ln "u_LightColor" -nn "Light Color" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_LightColorR" -ln "u_LightColorR" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_LightColor";
	addAttr -is true -ci true -sn "u_LightColorG" -ln "u_LightColorG" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_LightColor";
	addAttr -is true -ci true -sn "u_LightColorB" -ln "u_LightColorB" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_LightColor";
	addAttr -is true -ci true -h true -sn "u_LightIntensity_Name" -ln "u_LightIntensity_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_LightIntensity_Type" -ln "u_LightIntensity_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_LightIntensity" -ln "u_LightIntensity" -nn "Light Intensity" 
		-ct "HW_shader_parameter" -dv 1 -min 0 -max 10 -smn 0 -smx 10 -at "float";
	addAttr -is true -ci true -h true -sn "u_LightRotation_Name" -ln "u_LightRotation_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_LightRotation_Type" -ln "u_LightRotation_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_LightRotation" -ln "u_LightRotation" -nn "Light rotation (deg)" 
		-ct "HW_shader_parameter" -dv 75 -min 0 -max 360 -at "float";
	addAttr -is true -ci true -h true -sn "u_LightPitch_Name" -ln "u_LightPitch_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_LightPitch_Type" -ln "u_LightPitch_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_LightPitch" -ln "u_LightPitch" -nn "Light pitch (deg)" 
		-ct "HW_shader_parameter" -dv 40 -min -90 -max 90 -at "float";
	addAttr -is true -ci true -h true -sn "u_BaseColorTexture_Name" -ln "u_BaseColorTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_BaseColorTexture_Type" -ln "u_BaseColorTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_BaseColorTexture" -ln "u_BaseColorTexture" 
		-nn "Base color map (sRGB)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_BaseColorTextureR" -ln "u_BaseColorTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseColorTexture";
	addAttr -is true -ci true -sn "u_BaseColorTextureG" -ln "u_BaseColorTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseColorTexture";
	addAttr -is true -ci true -sn "u_BaseColorTextureB" -ln "u_BaseColorTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseColorTexture";
	addAttr -is true -ci true -h true -sn "u_BaseColorFactor_Name" -ln "u_BaseColorFactor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_BaseColorFactor_Type" -ln "u_BaseColorFactor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_BaseColorFactor" -ln "u_BaseColorFactor" -nn "Base color factor" 
		-ct "HW_shader_parameter" -at "compound" -nc 2;
	addAttr -is true -ci true -uac -sn "u_BaseColorFactorRGB" -ln "u_BaseColorFactorRGB" 
		-ct "HW_shader_parameter" -at "float3" -p "u_BaseColorFactor" -nc 3;
	addAttr -is true -ci true -sn "u_BaseColorFactorR" -ln "u_BaseColorFactorR" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_BaseColorFactorRGB";
	addAttr -is true -ci true -sn "u_BaseColorFactorG" -ln "u_BaseColorFactorG" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_BaseColorFactorRGB";
	addAttr -is true -ci true -sn "u_BaseColorFactorB" -ln "u_BaseColorFactorB" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_BaseColorFactorRGB";
	addAttr -is true -ci true -sn "u_BaseColorFactorA" -ln "u_BaseColorFactorA" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -smn 0 -smx 1 -at "float" -p "u_BaseColorFactor";
	addAttr -is true -ci true -h true -sn "u_MetallicTexture_Name" -ln "u_MetallicTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_MetallicTexture_Type" -ln "u_MetallicTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_MetallicTexture" -ln "u_MetallicTexture" -nn "Metallic map (B,LIN)" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_MetallicTextureR" -ln "u_MetallicTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_MetallicTexture";
	addAttr -is true -ci true -sn "u_MetallicTextureG" -ln "u_MetallicTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_MetallicTexture";
	addAttr -is true -ci true -sn "u_MetallicTextureB" -ln "u_MetallicTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_MetallicTexture";
	addAttr -is true -ci true -h true -sn "u_MetallicStrength_Name" -ln "u_MetallicStrength_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_MetallicStrength_Type" -ln "u_MetallicStrength_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_MetallicStrength" -ln "u_MetallicStrength" -nn "Metallic strength" 
		-ct "HW_shader_parameter" -dv 0.5 -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_RoughnessTexture_Name" -ln "u_RoughnessTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_RoughnessTexture_Type" -ln "u_RoughnessTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_RoughnessTexture" -ln "u_RoughnessTexture" 
		-nn "Roughness map (G,LIN)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_RoughnessTextureR" -ln "u_RoughnessTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_RoughnessTexture";
	addAttr -is true -ci true -sn "u_RoughnessTextureG" -ln "u_RoughnessTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_RoughnessTexture";
	addAttr -is true -ci true -sn "u_RoughnessTextureB" -ln "u_RoughnessTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_RoughnessTexture";
	addAttr -is true -ci true -h true -sn "u_RoughnessStrength_Name" -ln "u_RoughnessStrength_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_RoughnessStrength_Type" -ln "u_RoughnessStrength_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_RoughnessStrength" -ln "u_RoughnessStrength" -nn "Roughness strength" 
		-ct "HW_shader_parameter" -dv 0.5 -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_OcclusionTexture_Name" -ln "u_OcclusionTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_OcclusionTexture_Type" -ln "u_OcclusionTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_OcclusionTexture" -ln "u_OcclusionTexture" 
		-nn "Occlusion map (R,LIN)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_OcclusionTextureR" -ln "u_OcclusionTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_OcclusionTexture";
	addAttr -is true -ci true -sn "u_OcclusionTextureG" -ln "u_OcclusionTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_OcclusionTexture";
	addAttr -is true -ci true -sn "u_OcclusionTextureB" -ln "u_OcclusionTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_OcclusionTexture";
	addAttr -is true -ci true -h true -sn "u_OcclusionStrength_Name" -ln "u_OcclusionStrength_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_OcclusionStrength_Type" -ln "u_OcclusionStrength_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_OcclusionStrength" -ln "u_OcclusionStrength" -nn "Occlusion strength" 
		-ct "HW_shader_parameter" -dv 1 -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_NormalTexture_Name" -ln "u_NormalTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_NormalTexture_Type" -ln "u_NormalTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_NormalTexture" -ln "u_NormalTexture" -nn "Normal map (LIN)" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_NormalTextureR" -ln "u_NormalTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_NormalTexture";
	addAttr -is true -ci true -sn "u_NormalTextureG" -ln "u_NormalTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_NormalTexture";
	addAttr -is true -ci true -sn "u_NormalTextureB" -ln "u_NormalTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_NormalTexture";
	addAttr -is true -ci true -h true -sn "u_NormalScale_Name" -ln "u_NormalScale_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_NormalScale_Type" -ln "u_NormalScale_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_NormalScale" -ln "u_NormalScale" -nn "Normal scale" 
		-ct "HW_shader_parameter" -dv 1 -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_EmissiveTexture_Name" -ln "u_EmissiveTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_EmissiveTexture_Type" -ln "u_EmissiveTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_EmissiveTexture" -ln "u_EmissiveTexture" -nn "Emissive map (sRGB)" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_EmissiveTextureR" -ln "u_EmissiveTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_EmissiveTexture";
	addAttr -is true -ci true -sn "u_EmissiveTextureG" -ln "u_EmissiveTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_EmissiveTexture";
	addAttr -is true -ci true -sn "u_EmissiveTextureB" -ln "u_EmissiveTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_EmissiveTexture";
	addAttr -is true -ci true -h true -sn "u_EmissiveColor_Name" -ln "u_EmissiveColor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_EmissiveColor_Type" -ln "u_EmissiveColor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_EmissiveColor" -ln "u_EmissiveColor" -nn "Emissive color factor" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_EmissiveColorR" -ln "u_EmissiveColorR" -ct "HW_shader_parameter" 
		-min 0 -max 1 -at "float" -p "u_EmissiveColor";
	addAttr -is true -ci true -sn "u_EmissiveColorG" -ln "u_EmissiveColorG" -ct "HW_shader_parameter" 
		-min 0 -max 1 -at "float" -p "u_EmissiveColor";
	addAttr -is true -ci true -sn "u_EmissiveColorB" -ln "u_EmissiveColorB" -ct "HW_shader_parameter" 
		-min 0 -max 1 -at "float" -p "u_EmissiveColor";
	addAttr -is true -ci true -h true -sn "u_DiffuseEnvTexture_Name" -ln "u_DiffuseEnvTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_DiffuseEnvTexture_Type" -ln "u_DiffuseEnvTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_DiffuseEnvTexture" -ln "u_DiffuseEnvTexture" 
		-nn "Diffuse env map (LIN)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_DiffuseEnvTextureR" -ln "u_DiffuseEnvTextureR" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_DiffuseEnvTexture";
	addAttr -is true -ci true -sn "u_DiffuseEnvTextureG" -ln "u_DiffuseEnvTextureG" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_DiffuseEnvTexture";
	addAttr -is true -ci true -sn "u_DiffuseEnvTextureB" -ln "u_DiffuseEnvTextureB" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_DiffuseEnvTexture";
	addAttr -is true -ci true -h true -sn "u_SpecularEnvTexture_Name" -ln "u_SpecularEnvTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_SpecularEnvTexture_Type" -ln "u_SpecularEnvTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_SpecularEnvTexture" -ln "u_SpecularEnvTexture" 
		-nn "Specular env map (LIN)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_SpecularEnvTextureR" -ln "u_SpecularEnvTextureR" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_SpecularEnvTexture";
	addAttr -is true -ci true -sn "u_SpecularEnvTextureG" -ln "u_SpecularEnvTextureG" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_SpecularEnvTexture";
	addAttr -is true -ci true -sn "u_SpecularEnvTextureB" -ln "u_SpecularEnvTextureB" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_SpecularEnvTexture";
	addAttr -is true -ci true -h true -sn "u_brdfTexture_Name" -ln "u_brdfTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_brdfTexture_Type" -ln "u_brdfTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_brdfTexture" -ln "u_brdfTexture" -nn "BRDF LUT (sRGB)" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_brdfTextureR" -ln "u_brdfTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_brdfTexture";
	addAttr -is true -ci true -sn "u_brdfTextureG" -ln "u_brdfTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_brdfTexture";
	addAttr -is true -ci true -sn "u_brdfTextureB" -ln "u_brdfTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_brdfTexture";
	addAttr -is true -ci true -h true -sn "u_UseMeshTangents_Name" -ln "u_UseMeshTangents_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_UseMeshTangents_Type" -ln "u_UseMeshTangents_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_UseMeshTangents" -ln "u_UseMeshTangents" -nn "Use mesh tangents?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_ScaleDiffBaseMR_Name" -ln "u_ScaleDiffBaseMR_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_ScaleDiffBaseMR_Type" -ln "u_ScaleDiffBaseMR_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMR" -ln "u_ScaleDiffBaseMR" -nn "Scale Diff Base MR" 
		-ct "HW_shader_parameter" -at "compound" -nc 2;
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRXYZ" -ln "u_ScaleDiffBaseMRXYZ" 
		-ct "HW_shader_parameter" -at "float3" -p "u_ScaleDiffBaseMR" -nc 3;
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRX" -ln "u_ScaleDiffBaseMRX" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleDiffBaseMRXYZ";
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRY" -ln "u_ScaleDiffBaseMRY" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleDiffBaseMRXYZ";
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRZ" -ln "u_ScaleDiffBaseMRZ" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleDiffBaseMRXYZ";
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRW" -ln "u_ScaleDiffBaseMRW" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleDiffBaseMR";
	addAttr -is true -ci true -h true -sn "u_ScaleFGDSpec_Name" -ln "u_ScaleFGDSpec_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_ScaleFGDSpec_Type" -ln "u_ScaleFGDSpec_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_ScaleFGDSpec" -ln "u_ScaleFGDSpec" -nn "Scale FGD Spec" 
		-ct "HW_shader_parameter" -at "compound" -nc 2;
	addAttr -is true -ci true -sn "u_ScaleFGDSpecXYZ" -ln "u_ScaleFGDSpecXYZ" -ct "HW_shader_parameter" 
		-at "float3" -p "u_ScaleFGDSpec" -nc 3;
	addAttr -is true -ci true -sn "u_ScaleFGDSpecX" -ln "u_ScaleFGDSpecX" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleFGDSpecXYZ";
	addAttr -is true -ci true -sn "u_ScaleFGDSpecY" -ln "u_ScaleFGDSpecY" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleFGDSpecXYZ";
	addAttr -is true -ci true -sn "u_ScaleFGDSpecZ" -ln "u_ScaleFGDSpecZ" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleFGDSpecXYZ";
	addAttr -is true -ci true -sn "u_ScaleFGDSpecW" -ln "u_ScaleFGDSpecW" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleFGDSpec";
	addAttr -is true -ci true -h true -sn "u_ScaleIBL_Occl_Name" -ln "u_ScaleIBL_Occl_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_ScaleIBL_Occl_Type" -ln "u_ScaleIBL_Occl_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_ScaleIBL_Occl" -ln "u_ScaleIBL_Occl" -nn "Scale IBL AO(w)" 
		-ct "HW_shader_parameter" -at "compound" -nc 2;
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclXYZ" -ln "u_ScaleIBL_OcclXYZ" -ct "HW_shader_parameter" 
		-at "float3" -p "u_ScaleIBL_Occl" -nc 3;
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclX" -ln "u_ScaleIBL_OcclX" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_ScaleIBL_OcclXYZ";
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclY" -ln "u_ScaleIBL_OcclY" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_ScaleIBL_OcclXYZ";
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclZ" -ln "u_ScaleIBL_OcclZ" -ct "HW_shader_parameter" 
		-min 0 -max 1 -at "float" -p "u_ScaleIBL_OcclXYZ";
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclW" -ln "u_ScaleIBL_OcclW" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_ScaleIBL_Occl";
	addAttr -ci true -sn "Position" -ln "Position" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "Position_Name" -ln "Position_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "Position";
	addAttr -is true -ci true -h true -sn "Position_Source" -ln "Position_Source" -ct "HW_shader_parameter" 
		-dt "string" -p "Position";
	addAttr -is true -ci true -sn "Position_DefaultTexture" -ln "Position_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "Position";
	addAttr -ci true -sn "Normal" -ln "Normal" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "Normal_Name" -ln "Normal_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "Normal";
	addAttr -is true -ci true -h true -sn "Normal_Source" -ln "Normal_Source" -ct "HW_shader_parameter" 
		-dt "string" -p "Normal";
	addAttr -is true -ci true -sn "Normal_DefaultTexture" -ln "Normal_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "Normal";
	addAttr -ci true -sn "Tangent" -ln "Tangent" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "Tangent_Name" -ln "Tangent_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "Tangent";
	addAttr -is true -ci true -h true -sn "Tangent_Source" -ln "Tangent_Source" -ct "HW_shader_parameter" 
		-dt "string" -p "Tangent";
	addAttr -is true -ci true -sn "Tangent_DefaultTexture" -ln "Tangent_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "Tangent";
	addAttr -ci true -sn "Binormal" -ln "Binormal" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "Binormal_Name" -ln "Binormal_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "Binormal";
	addAttr -is true -ci true -h true -sn "Binormal_Source" -ln "Binormal_Source" -ct "HW_shader_parameter" 
		-dt "string" -p "Binormal";
	addAttr -is true -ci true -sn "Binormal_DefaultTexture" -ln "Binormal_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "Binormal";
	addAttr -ci true -sn "TexCoord0" -ln "TexCoord0" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "TexCoord0_Name" -ln "TexCoord0_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "TexCoord0";
	addAttr -is true -ci true -h true -sn "TexCoord0_Source" -ln "TexCoord0_Source" 
		-ct "HW_shader_parameter" -dt "string" -p "TexCoord0";
	addAttr -is true -ci true -sn "TexCoord0_DefaultTexture" -ln "TexCoord0_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "TexCoord0";
	addAttr -is true -ci true -h true -sn "u_IsDoubleSided_Name" -ln "u_IsDoubleSided_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsDoubleSided_Type" -ln "u_IsDoubleSided_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsDoubleSided" -ln "u_IsDoubleSided" -nn "Double sided material?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_RoughnessOffset_Name" -ln "u_RoughnessOffset_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_RoughnessOffset_Type" -ln "u_RoughnessOffset_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_RoughnessOffset" -ln "u_RoughnessOffset" -nn "Roughness offset" 
		-ct "HW_shader_parameter" -min 0 -max 12 -smn 0 -smx 12 -at "long";
	addAttr -is true -ci true -h true -sn "u_BurleyFactor_Name" -ln "u_BurleyFactor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_BurleyFactor_Type" -ln "u_BurleyFactor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_BurleyFactor" -ln "u_BurleyFactor" -nn "Burley factor" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_UndoEdgeStretch_Name" -ln "u_UndoEdgeStretch_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_UndoEdgeStretch_Type" -ln "u_UndoEdgeStretch_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_UndoEdgeStretch" -ln "u_UndoEdgeStretch" -nn "Undo edge stretch?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsEmissiveInsRGB_Name" -ln "u_IsEmissiveInsRGB_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsEmissiveInsRGB_Type" -ln "u_IsEmissiveInsRGB_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsEmissiveInsRGB" -ln "u_IsEmissiveInsRGB" -nn "sRGB emissive?" 
		-ct "HW_shader_parameter" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_EnvRotationAngle_Name" -ln "u_EnvRotationAngle_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_EnvRotationAngle_Type" -ln "u_EnvRotationAngle_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_EnvRotationAngle" -ln "u_EnvRotationAngle" -nn "Environment Rotation" 
		-ct "HW_shader_parameter" -min 0 -max 360 -smn 0 -smx 360 -at "float";
	addAttr -is true -ci true -h true -sn "u_FlipEnvMapZ_Name" -ln "u_FlipEnvMapZ_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_FlipEnvMapZ_Type" -ln "u_FlipEnvMapZ_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_FlipEnvMapZ" -ln "u_FlipEnvMapZ" -nn "Flip environment Z?" 
		-ct "HW_shader_parameter" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsEnvMapInsRGB_Name" -ln "u_IsEnvMapInsRGB_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsEnvMapInsRGB_Type" -ln "u_IsEnvMapInsRGB_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsEnvMapInsRGB" -ln "u_IsEnvMapInsRGB" -nn "sRGB environment?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsEnvMapInRGBM_Name" -ln "u_IsEnvMapInRGBM_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsEnvMapInRGBM_Type" -ln "u_IsEnvMapInRGBM_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsEnvMapInRGBM" -ln "u_IsEnvMapInRGBM" -nn "RGBM environment?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsBRDFsSRGB_Name" -ln "u_IsBRDFsSRGB_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsBRDFsSRGB_Type" -ln "u_IsBRDFsSRGB_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsBRDFsSRGB" -ln "u_IsBRDFsSRGB" -nn "sRGB BRDF table?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsBaseColorInsRGB_Name" -ln "u_IsBaseColorInsRGB_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsBaseColorInsRGB_Type" -ln "u_IsBaseColorInsRGB_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsBaseColorInsRGB" -ln "u_IsBaseColorInsRGB" -nn "sRGB basecolor?" 
		-ct "HW_shader_parameter" -dv 1 -min 0 -max 1 -at "bool";
	setAttr ".vpar" -type "stringArray" 5 "Position" "Normal" "Tangent" "Binormal" "TexCoord0"  ;
	setAttr ".upar" -type "stringArray" 34 "u_LightColor" "u_LightIntensity" "u_LightRotation" "u_LightPitch" "u_BaseColorTexture" "u_BaseColorFactor" "u_MetallicTexture" "u_MetallicStrength" "u_RoughnessTexture" "u_RoughnessStrength" "u_OcclusionTexture" "u_OcclusionStrength" "u_NormalTexture" "u_NormalScale" "u_EmissiveTexture" "u_EmissiveColor" "u_DiffuseEnvTexture" "u_SpecularEnvTexture" "u_brdfTexture" "u_IsDoubleSided" "u_UseMeshTangents" "u_RoughnessOffset" "u_ScaleDiffBaseMR" "u_BurleyFactor" "u_ScaleFGDSpec" "u_UndoEdgeStretch" "u_ScaleIBL_Occl" "u_IsEmissiveInsRGB" "u_EnvRotationAngle" "u_FlipEnvMapZ" "u_IsEnvMapInsRGB" "u_IsEnvMapInRGBM" "u_IsBRDFsSRGB" "u_IsBaseColorInsRGB"  ;
	setAttr ".s" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/shaders/glTF_PBR.ogsfx";
	setAttr ".t" -type "string" "Solid";
	setAttr ".u_LightColor_Name" -type "string" "u_LightColor";
	setAttr ".u_LightColor_Type" -type "string" "color3x1";
	setAttr ".u_LightColor" -type "float3" 1 1 1 ;
	setAttr ".u_LightIntensity_Name" -type "string" "u_LightIntensity";
	setAttr ".u_LightIntensity_Type" -type "string" "float";
	setAttr ".u_LightIntensity" 1;
	setAttr ".u_LightRotation_Name" -type "string" "u_LightRotation";
	setAttr ".u_LightRotation_Type" -type "string" "float";
	setAttr ".u_LightRotation" 75;
	setAttr ".u_LightPitch_Name" -type "string" "u_LightPitch";
	setAttr ".u_LightPitch_Type" -type "string" "float";
	setAttr ".u_LightPitch" 40;
	setAttr ".u_BaseColorTexture_Name" -type "string" "u_BaseColorTexture";
	setAttr ".u_BaseColorTexture_Type" -type "string" "texture";
	setAttr ".u_BaseColorTexture" -type "float3" 0 0 0 ;
	setAttr ".u_BaseColorFactor_Name" -type "string" "u_BaseColorFactor";
	setAttr ".u_BaseColorFactor_Type" -type "string" "color4x1";
	setAttr ".u_BaseColorFactorRGB" -type "float3" 1 1 1 ;
	setAttr ".u_BaseColorFactorA" 1;
	setAttr ".u_MetallicTexture_Name" -type "string" "u_MetallicTexture";
	setAttr ".u_MetallicTexture_Type" -type "string" "texture";
	setAttr ".u_MetallicTexture" -type "float3" 0 0 0 ;
	setAttr ".u_MetallicStrength_Name" -type "string" "u_MetallicStrength";
	setAttr ".u_MetallicStrength_Type" -type "string" "float";
	setAttr ".u_MetallicStrength" 1;
	setAttr ".u_RoughnessTexture_Name" -type "string" "u_RoughnessTexture";
	setAttr ".u_RoughnessTexture_Type" -type "string" "texture";
	setAttr ".u_RoughnessTexture" -type "float3" 0 0 0 ;
	setAttr ".u_RoughnessStrength_Name" -type "string" "u_RoughnessStrength";
	setAttr ".u_RoughnessStrength_Type" -type "string" "float";
	setAttr ".u_RoughnessStrength" 0;
	setAttr ".u_OcclusionTexture_Name" -type "string" "u_OcclusionTexture";
	setAttr ".u_OcclusionTexture_Type" -type "string" "texture";
	setAttr ".u_OcclusionTexture" -type "float3" 0 0 0 ;
	setAttr ".u_OcclusionStrength_Name" -type "string" "u_OcclusionStrength";
	setAttr ".u_OcclusionStrength_Type" -type "string" "float";
	setAttr ".u_OcclusionStrength" 1;
	setAttr ".u_NormalTexture_Name" -type "string" "u_NormalTexture";
	setAttr ".u_NormalTexture_Type" -type "string" "texture";
	setAttr ".u_NormalTexture" -type "float3" 0 0 0 ;
	setAttr ".u_NormalScale_Name" -type "string" "u_NormalScale";
	setAttr ".u_NormalScale_Type" -type "string" "float";
	setAttr ".u_NormalScale" 1;
	setAttr ".u_EmissiveTexture_Name" -type "string" "u_EmissiveTexture";
	setAttr ".u_EmissiveTexture_Type" -type "string" "texture";
	setAttr ".u_EmissiveTexture" -type "float3" 0 0 0 ;
	setAttr ".u_EmissiveColor_Name" -type "string" "u_EmissiveColor";
	setAttr ".u_EmissiveColor_Type" -type "string" "color3x1";
	setAttr ".u_EmissiveColor" -type "float3" 0 0 0 ;
	setAttr ".u_DiffuseEnvTexture_Name" -type "string" "u_DiffuseEnvTexture";
	setAttr ".u_DiffuseEnvTexture_Type" -type "string" "texture";
	setAttr ".u_DiffuseEnvTexture" -type "float3" 0 0 0 ;
	setAttr ".u_SpecularEnvTexture_Name" -type "string" "u_SpecularEnvTexture";
	setAttr ".u_SpecularEnvTexture_Type" -type "string" "texture";
	setAttr ".u_SpecularEnvTexture" -type "float3" 0 0 0 ;
	setAttr ".u_brdfTexture_Name" -type "string" "u_brdfTexture";
	setAttr ".u_brdfTexture_Type" -type "string" "texture";
	setAttr ".u_brdfTexture" -type "float3" 0 0 0 ;
	setAttr ".u_UseMeshTangents_Name" -type "string" "u_UseMeshTangents";
	setAttr ".u_UseMeshTangents_Type" -type "string" "bool";
	setAttr ".u_UseMeshTangents" yes;
	setAttr ".u_ScaleDiffBaseMR_Name" -type "string" "u_ScaleDiffBaseMR";
	setAttr ".u_ScaleDiffBaseMR_Type" -type "string" "float4x1";
	setAttr ".u_ScaleDiffBaseMRXYZ" -type "float3" 0 0 0 ;
	setAttr ".u_ScaleDiffBaseMRW" 0;
	setAttr ".u_ScaleFGDSpec_Name" -type "string" "u_ScaleFGDSpec";
	setAttr ".u_ScaleFGDSpec_Type" -type "string" "float4x1";
	setAttr ".u_ScaleFGDSpecXYZ" -type "float3" 0 0 0 ;
	setAttr ".u_ScaleFGDSpecW" 0;
	setAttr ".u_ScaleIBL_Occl_Name" -type "string" "u_ScaleIBL_Occl";
	setAttr ".u_ScaleIBL_Occl_Type" -type "string" "float4x1";
	setAttr ".u_ScaleIBL_OcclXYZ" -type "float3" 1 1 0 ;
	setAttr ".u_ScaleIBL_OcclW" 1;
	setAttr ".Position_Name" -type "string" "Position";
	setAttr ".Position_Source" -type "string" "position";
	setAttr ".Normal_Name" -type "string" "Normal";
	setAttr ".Normal_Source" -type "string" "normal";
	setAttr ".Tangent_Name" -type "string" "Tangent";
	setAttr ".Tangent_Source" -type "string" "tangent:map1";
	setAttr ".Binormal_Name" -type "string" "Binormal";
	setAttr ".Binormal_Source" -type "string" "binormal:map1";
	setAttr ".TexCoord0_Name" -type "string" "TexCoord0";
	setAttr ".TexCoord0_Source" -type "string" "uv:map1";
	setAttr ".u_IsDoubleSided_Name" -type "string" "u_IsDoubleSided";
	setAttr ".u_IsDoubleSided_Type" -type "string" "bool";
	setAttr ".u_IsDoubleSided" no;
	setAttr ".u_RoughnessOffset_Name" -type "string" "u_RoughnessOffset";
	setAttr ".u_RoughnessOffset_Type" -type "string" "int";
	setAttr ".u_RoughnessOffset" 0;
	setAttr ".u_BurleyFactor_Name" -type "string" "u_BurleyFactor";
	setAttr ".u_BurleyFactor_Type" -type "string" "float";
	setAttr ".u_BurleyFactor" 0;
	setAttr ".u_UndoEdgeStretch_Name" -type "string" "u_UndoEdgeStretch";
	setAttr ".u_UndoEdgeStretch_Type" -type "string" "bool";
	setAttr ".u_UndoEdgeStretch" no;
	setAttr ".u_IsEmissiveInsRGB_Name" -type "string" "u_IsEmissiveInsRGB";
	setAttr ".u_IsEmissiveInsRGB_Type" -type "string" "bool";
	setAttr ".u_IsEmissiveInsRGB" yes;
	setAttr ".u_EnvRotationAngle_Name" -type "string" "u_EnvRotationAngle";
	setAttr ".u_EnvRotationAngle_Type" -type "string" "float";
	setAttr ".u_EnvRotationAngle" 0;
	setAttr ".u_FlipEnvMapZ_Name" -type "string" "u_FlipEnvMapZ";
	setAttr ".u_FlipEnvMapZ_Type" -type "string" "bool";
	setAttr ".u_FlipEnvMapZ" yes;
	setAttr ".u_IsEnvMapInsRGB_Name" -type "string" "u_IsEnvMapInsRGB";
	setAttr ".u_IsEnvMapInsRGB_Type" -type "string" "bool";
	setAttr ".u_IsEnvMapInsRGB" no;
	setAttr ".u_IsEnvMapInRGBM_Name" -type "string" "u_IsEnvMapInRGBM";
	setAttr ".u_IsEnvMapInRGBM_Type" -type "string" "bool";
	setAttr ".u_IsEnvMapInRGBM" no;
	setAttr ".u_IsBRDFsSRGB_Name" -type "string" "u_IsBRDFsSRGB";
	setAttr ".u_IsBRDFsSRGB_Type" -type "string" "bool";
	setAttr ".u_IsBRDFsSRGB" no;
	setAttr ".u_IsBaseColorInsRGB_Name" -type "string" "u_IsBaseColorInsRGB";
	setAttr ".u_IsBaseColorInsRGB_Type" -type "string" "bool";
	setAttr ".u_IsBaseColorInsRGB" yes;
createNode shadingEngine -n "GLSLShader1SG";
	rename -uid "4EE0CA71-4E0B-7B0C-254F-6095031017AA";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
	rename -uid "706C3E98-416F-F2DF-2500-1A92DBD78272";
createNode file -n "normal_map_file";
	rename -uid "5ABB11F6-4D95-8A68-EBDF-2193D9A2BCB4";
	setAttr ".ail" yes;
	setAttr ".ftn" -type "string" "C:/dev/glTF/Maya2glTF/maya//images/cube_flat-on-soft_normal.png";
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture1";
	rename -uid "5B9C4307-43A2-503B-5D24-1CB25BA4B9D8";
createNode file -n "file2";
	rename -uid "982B60E8-49EF-950C-22D8-46B961EC0928";
	setAttr ".ftn" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/images/damaged_helmet_diffuse_env.dds";
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture2";
	rename -uid "2AB7DD0A-4CA8-E0E9-ED17-60B9E2F22150";
createNode file -n "file3";
	rename -uid "6C3DF0C1-4D69-E81A-D4AA-81877FA5B85F";
	setAttr ".ftn" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/images/damaged_helmet_specular_env.dds";
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture3";
	rename -uid "67527172-413A-2B90-71F7-9C8B572E6A03";
createNode file -n "file4";
	rename -uid "33523EDA-497D-CAB9-C036-DB995B883EA2";
	setAttr ".ftn" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/images/brdfLUT.dds";
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture4";
	rename -uid "F68A3134-4D04-8867-6E4C-DD981877D25B";
createNode bump2d -n "bump2d1";
	rename -uid "0E43EF60-49DF-DBF7-CE83-8AA3C49273DA";
	setAttr ".bi" 1;
	setAttr ".vc1" -type "float3" 0 5.9999998e-05 0 ;
	setAttr ".vc2" -type "float3" 9.9999997e-06 9.9999997e-06 0 ;
createNode GLSLShader -n "PBR_Shader_no_normal_map";
	rename -uid "94301892-47FC-D9FE-9EB9-2289BD4C7887";
	addAttr -ci true -sn "Light_0_use_implicit_lighting" -ln "Light_0_use_implicit_lighting" 
		-dv 1 -min 0 -max 1 -at "bool";
	addAttr -s false -ci true -sn "Light_0_connected_light" -ln "Light_0_connected_light" 
		-at "message";
	addAttr -ci true -sn "Light_1_use_implicit_lighting" -ln "Light_1_use_implicit_lighting" 
		-dv 1 -min 0 -max 1 -at "bool";
	addAttr -s false -ci true -sn "Light_1_connected_light" -ln "Light_1_connected_light" 
		-at "message";
	addAttr -ci true -sn "Light_2_use_implicit_lighting" -ln "Light_2_use_implicit_lighting" 
		-dv 1 -min 0 -max 1 -at "bool";
	addAttr -s false -ci true -sn "Light_2_connected_light" -ln "Light_2_connected_light" 
		-at "message";
	addAttr -s false -is true -ci true -k true -sn "te" -ln "techniqueEnum" -nn "Technique" 
		-min 0 -max 1 -en "Solid:Transparent" -at "enum";
	addAttr -is true -ci true -h true -sn "u_LightColor_Name" -ln "u_LightColor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_LightColor_Type" -ln "u_LightColor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_LightColor" -ln "u_LightColor" -nn "Light Color" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_LightColorR" -ln "u_LightColorR" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_LightColor";
	addAttr -is true -ci true -sn "u_LightColorG" -ln "u_LightColorG" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_LightColor";
	addAttr -is true -ci true -sn "u_LightColorB" -ln "u_LightColorB" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_LightColor";
	addAttr -is true -ci true -h true -sn "u_LightIntensity_Name" -ln "u_LightIntensity_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_LightIntensity_Type" -ln "u_LightIntensity_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_LightIntensity" -ln "u_LightIntensity" -nn "Light Intensity" 
		-ct "HW_shader_parameter" -dv 1 -min 0 -max 10 -smn 0 -smx 10 -at "float";
	addAttr -is true -ci true -h true -sn "u_LightRotation_Name" -ln "u_LightRotation_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_LightRotation_Type" -ln "u_LightRotation_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_LightRotation" -ln "u_LightRotation" -nn "Light rotation (deg)" 
		-ct "HW_shader_parameter" -dv 75 -min 0 -max 360 -at "float";
	addAttr -is true -ci true -h true -sn "u_LightPitch_Name" -ln "u_LightPitch_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_LightPitch_Type" -ln "u_LightPitch_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_LightPitch" -ln "u_LightPitch" -nn "Light pitch (deg)" 
		-ct "HW_shader_parameter" -dv 40 -min -90 -max 90 -at "float";
	addAttr -is true -ci true -h true -sn "u_BaseColorTexture_Name" -ln "u_BaseColorTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_BaseColorTexture_Type" -ln "u_BaseColorTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_BaseColorTexture" -ln "u_BaseColorTexture" 
		-nn "Base color map (sRGB)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_BaseColorTextureR" -ln "u_BaseColorTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseColorTexture";
	addAttr -is true -ci true -sn "u_BaseColorTextureG" -ln "u_BaseColorTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseColorTexture";
	addAttr -is true -ci true -sn "u_BaseColorTextureB" -ln "u_BaseColorTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseColorTexture";
	addAttr -is true -ci true -h true -sn "u_BaseColorFactor_Name" -ln "u_BaseColorFactor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_BaseColorFactor_Type" -ln "u_BaseColorFactor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_BaseColorFactor" -ln "u_BaseColorFactor" -nn "Base color factor" 
		-ct "HW_shader_parameter" -at "compound" -nc 2;
	addAttr -is true -ci true -uac -sn "u_BaseColorFactorRGB" -ln "u_BaseColorFactorRGB" 
		-ct "HW_shader_parameter" -at "float3" -p "u_BaseColorFactor" -nc 3;
	addAttr -is true -ci true -sn "u_BaseColorFactorR" -ln "u_BaseColorFactorR" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_BaseColorFactorRGB";
	addAttr -is true -ci true -sn "u_BaseColorFactorG" -ln "u_BaseColorFactorG" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_BaseColorFactorRGB";
	addAttr -is true -ci true -sn "u_BaseColorFactorB" -ln "u_BaseColorFactorB" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_BaseColorFactorRGB";
	addAttr -is true -ci true -sn "u_BaseColorFactorA" -ln "u_BaseColorFactorA" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -smn 0 -smx 1 -at "float" -p "u_BaseColorFactor";
	addAttr -is true -ci true -h true -sn "u_MetallicTexture_Name" -ln "u_MetallicTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_MetallicTexture_Type" -ln "u_MetallicTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_MetallicTexture" -ln "u_MetallicTexture" -nn "Metallic map (B,LIN)" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_MetallicTextureR" -ln "u_MetallicTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_MetallicTexture";
	addAttr -is true -ci true -sn "u_MetallicTextureG" -ln "u_MetallicTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_MetallicTexture";
	addAttr -is true -ci true -sn "u_MetallicTextureB" -ln "u_MetallicTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_MetallicTexture";
	addAttr -is true -ci true -h true -sn "u_MetallicStrength_Name" -ln "u_MetallicStrength_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_MetallicStrength_Type" -ln "u_MetallicStrength_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_MetallicStrength" -ln "u_MetallicStrength" -nn "Metallic strength" 
		-ct "HW_shader_parameter" -dv 0.5 -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_RoughnessTexture_Name" -ln "u_RoughnessTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_RoughnessTexture_Type" -ln "u_RoughnessTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_RoughnessTexture" -ln "u_RoughnessTexture" 
		-nn "Roughness map (G,LIN)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_RoughnessTextureR" -ln "u_RoughnessTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_RoughnessTexture";
	addAttr -is true -ci true -sn "u_RoughnessTextureG" -ln "u_RoughnessTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_RoughnessTexture";
	addAttr -is true -ci true -sn "u_RoughnessTextureB" -ln "u_RoughnessTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_RoughnessTexture";
	addAttr -is true -ci true -h true -sn "u_RoughnessStrength_Name" -ln "u_RoughnessStrength_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_RoughnessStrength_Type" -ln "u_RoughnessStrength_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_RoughnessStrength" -ln "u_RoughnessStrength" -nn "Roughness strength" 
		-ct "HW_shader_parameter" -dv 0.5 -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_OcclusionTexture_Name" -ln "u_OcclusionTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_OcclusionTexture_Type" -ln "u_OcclusionTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_OcclusionTexture" -ln "u_OcclusionTexture" 
		-nn "Occlusion map (R,LIN)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_OcclusionTextureR" -ln "u_OcclusionTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_OcclusionTexture";
	addAttr -is true -ci true -sn "u_OcclusionTextureG" -ln "u_OcclusionTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_OcclusionTexture";
	addAttr -is true -ci true -sn "u_OcclusionTextureB" -ln "u_OcclusionTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_OcclusionTexture";
	addAttr -is true -ci true -h true -sn "u_OcclusionStrength_Name" -ln "u_OcclusionStrength_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_OcclusionStrength_Type" -ln "u_OcclusionStrength_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_OcclusionStrength" -ln "u_OcclusionStrength" -nn "Occlusion strength" 
		-ct "HW_shader_parameter" -dv 1 -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_NormalTexture_Name" -ln "u_NormalTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_NormalTexture_Type" -ln "u_NormalTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_NormalTexture" -ln "u_NormalTexture" -nn "Normal map (LIN)" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_NormalTextureR" -ln "u_NormalTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_NormalTexture";
	addAttr -is true -ci true -sn "u_NormalTextureG" -ln "u_NormalTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_NormalTexture";
	addAttr -is true -ci true -sn "u_NormalTextureB" -ln "u_NormalTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_NormalTexture";
	addAttr -is true -ci true -h true -sn "u_NormalScale_Name" -ln "u_NormalScale_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_NormalScale_Type" -ln "u_NormalScale_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_NormalScale" -ln "u_NormalScale" -nn "Normal scale" 
		-ct "HW_shader_parameter" -dv 1 -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_EmissiveTexture_Name" -ln "u_EmissiveTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_EmissiveTexture_Type" -ln "u_EmissiveTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_EmissiveTexture" -ln "u_EmissiveTexture" -nn "Emissive map (sRGB)" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_EmissiveTextureR" -ln "u_EmissiveTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_EmissiveTexture";
	addAttr -is true -ci true -sn "u_EmissiveTextureG" -ln "u_EmissiveTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_EmissiveTexture";
	addAttr -is true -ci true -sn "u_EmissiveTextureB" -ln "u_EmissiveTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_EmissiveTexture";
	addAttr -is true -ci true -h true -sn "u_EmissiveColor_Name" -ln "u_EmissiveColor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_EmissiveColor_Type" -ln "u_EmissiveColor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_EmissiveColor" -ln "u_EmissiveColor" -nn "Emissive color factor" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_EmissiveColorR" -ln "u_EmissiveColorR" -ct "HW_shader_parameter" 
		-min 0 -max 1 -at "float" -p "u_EmissiveColor";
	addAttr -is true -ci true -sn "u_EmissiveColorG" -ln "u_EmissiveColorG" -ct "HW_shader_parameter" 
		-min 0 -max 1 -at "float" -p "u_EmissiveColor";
	addAttr -is true -ci true -sn "u_EmissiveColorB" -ln "u_EmissiveColorB" -ct "HW_shader_parameter" 
		-min 0 -max 1 -at "float" -p "u_EmissiveColor";
	addAttr -is true -ci true -h true -sn "u_DiffuseEnvTexture_Name" -ln "u_DiffuseEnvTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_DiffuseEnvTexture_Type" -ln "u_DiffuseEnvTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_DiffuseEnvTexture" -ln "u_DiffuseEnvTexture" 
		-nn "Diffuse env map (LIN)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_DiffuseEnvTextureR" -ln "u_DiffuseEnvTextureR" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_DiffuseEnvTexture";
	addAttr -is true -ci true -sn "u_DiffuseEnvTextureG" -ln "u_DiffuseEnvTextureG" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_DiffuseEnvTexture";
	addAttr -is true -ci true -sn "u_DiffuseEnvTextureB" -ln "u_DiffuseEnvTextureB" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_DiffuseEnvTexture";
	addAttr -is true -ci true -h true -sn "u_SpecularEnvTexture_Name" -ln "u_SpecularEnvTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_SpecularEnvTexture_Type" -ln "u_SpecularEnvTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_SpecularEnvTexture" -ln "u_SpecularEnvTexture" 
		-nn "Specular env map (LIN)" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_SpecularEnvTextureR" -ln "u_SpecularEnvTextureR" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_SpecularEnvTexture";
	addAttr -is true -ci true -sn "u_SpecularEnvTextureG" -ln "u_SpecularEnvTextureG" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_SpecularEnvTexture";
	addAttr -is true -ci true -sn "u_SpecularEnvTextureB" -ln "u_SpecularEnvTextureB" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float" -p "u_SpecularEnvTexture";
	addAttr -is true -ci true -h true -sn "u_brdfTexture_Name" -ln "u_brdfTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_brdfTexture_Type" -ln "u_brdfTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_brdfTexture" -ln "u_brdfTexture" -nn "BRDF LUT (sRGB)" 
		-ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_brdfTextureR" -ln "u_brdfTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_brdfTexture";
	addAttr -is true -ci true -sn "u_brdfTextureG" -ln "u_brdfTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_brdfTexture";
	addAttr -is true -ci true -sn "u_brdfTextureB" -ln "u_brdfTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_brdfTexture";
	addAttr -is true -ci true -h true -sn "u_UseMeshTangents_Name" -ln "u_UseMeshTangents_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_UseMeshTangents_Type" -ln "u_UseMeshTangents_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_UseMeshTangents" -ln "u_UseMeshTangents" -nn "Use mesh tangents?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_ScaleDiffBaseMR_Name" -ln "u_ScaleDiffBaseMR_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_ScaleDiffBaseMR_Type" -ln "u_ScaleDiffBaseMR_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMR" -ln "u_ScaleDiffBaseMR" -nn "Scale Diff Base MR" 
		-ct "HW_shader_parameter" -at "compound" -nc 2;
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRXYZ" -ln "u_ScaleDiffBaseMRXYZ" 
		-ct "HW_shader_parameter" -at "float3" -p "u_ScaleDiffBaseMR" -nc 3;
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRX" -ln "u_ScaleDiffBaseMRX" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleDiffBaseMRXYZ";
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRY" -ln "u_ScaleDiffBaseMRY" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleDiffBaseMRXYZ";
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRZ" -ln "u_ScaleDiffBaseMRZ" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleDiffBaseMRXYZ";
	addAttr -is true -ci true -sn "u_ScaleDiffBaseMRW" -ln "u_ScaleDiffBaseMRW" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleDiffBaseMR";
	addAttr -is true -ci true -h true -sn "u_ScaleFGDSpec_Name" -ln "u_ScaleFGDSpec_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_ScaleFGDSpec_Type" -ln "u_ScaleFGDSpec_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_ScaleFGDSpec" -ln "u_ScaleFGDSpec" -nn "Scale FGD Spec" 
		-ct "HW_shader_parameter" -at "compound" -nc 2;
	addAttr -is true -ci true -sn "u_ScaleFGDSpecXYZ" -ln "u_ScaleFGDSpecXYZ" -ct "HW_shader_parameter" 
		-at "float3" -p "u_ScaleFGDSpec" -nc 3;
	addAttr -is true -ci true -sn "u_ScaleFGDSpecX" -ln "u_ScaleFGDSpecX" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleFGDSpecXYZ";
	addAttr -is true -ci true -sn "u_ScaleFGDSpecY" -ln "u_ScaleFGDSpecY" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleFGDSpecXYZ";
	addAttr -is true -ci true -sn "u_ScaleFGDSpecZ" -ln "u_ScaleFGDSpecZ" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleFGDSpecXYZ";
	addAttr -is true -ci true -sn "u_ScaleFGDSpecW" -ln "u_ScaleFGDSpecW" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_ScaleFGDSpec";
	addAttr -is true -ci true -h true -sn "u_ScaleIBL_Occl_Name" -ln "u_ScaleIBL_Occl_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_ScaleIBL_Occl_Type" -ln "u_ScaleIBL_Occl_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_ScaleIBL_Occl" -ln "u_ScaleIBL_Occl" -nn "Scale IBL AO(w)" 
		-ct "HW_shader_parameter" -at "compound" -nc 2;
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclXYZ" -ln "u_ScaleIBL_OcclXYZ" -ct "HW_shader_parameter" 
		-at "float3" -p "u_ScaleIBL_Occl" -nc 3;
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclX" -ln "u_ScaleIBL_OcclX" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_ScaleIBL_OcclXYZ";
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclY" -ln "u_ScaleIBL_OcclY" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_ScaleIBL_OcclXYZ";
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclZ" -ln "u_ScaleIBL_OcclZ" -ct "HW_shader_parameter" 
		-min 0 -max 1 -at "float" -p "u_ScaleIBL_OcclXYZ";
	addAttr -is true -ci true -sn "u_ScaleIBL_OcclW" -ln "u_ScaleIBL_OcclW" -ct "HW_shader_parameter" 
		-dv 1 -min 0 -max 1 -at "float" -p "u_ScaleIBL_Occl";
	addAttr -ci true -sn "Position" -ln "Position" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "Position_Name" -ln "Position_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "Position";
	addAttr -is true -ci true -h true -sn "Position_Source" -ln "Position_Source" -ct "HW_shader_parameter" 
		-dt "string" -p "Position";
	addAttr -is true -ci true -sn "Position_DefaultTexture" -ln "Position_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "Position";
	addAttr -ci true -sn "Normal" -ln "Normal" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "Normal_Name" -ln "Normal_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "Normal";
	addAttr -is true -ci true -h true -sn "Normal_Source" -ln "Normal_Source" -ct "HW_shader_parameter" 
		-dt "string" -p "Normal";
	addAttr -is true -ci true -sn "Normal_DefaultTexture" -ln "Normal_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "Normal";
	addAttr -ci true -sn "Tangent" -ln "Tangent" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "Tangent_Name" -ln "Tangent_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "Tangent";
	addAttr -is true -ci true -h true -sn "Tangent_Source" -ln "Tangent_Source" -ct "HW_shader_parameter" 
		-dt "string" -p "Tangent";
	addAttr -is true -ci true -sn "Tangent_DefaultTexture" -ln "Tangent_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "Tangent";
	addAttr -ci true -sn "Binormal" -ln "Binormal" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "Binormal_Name" -ln "Binormal_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "Binormal";
	addAttr -is true -ci true -h true -sn "Binormal_Source" -ln "Binormal_Source" -ct "HW_shader_parameter" 
		-dt "string" -p "Binormal";
	addAttr -is true -ci true -sn "Binormal_DefaultTexture" -ln "Binormal_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "Binormal";
	addAttr -ci true -sn "TexCoord0" -ln "TexCoord0" -at "compound" -nc 3;
	addAttr -is true -ci true -h true -sn "TexCoord0_Name" -ln "TexCoord0_Name" -ct "HW_shader_parameter" 
		-dt "string" -p "TexCoord0";
	addAttr -is true -ci true -h true -sn "TexCoord0_Source" -ln "TexCoord0_Source" 
		-ct "HW_shader_parameter" -dt "string" -p "TexCoord0";
	addAttr -is true -ci true -sn "TexCoord0_DefaultTexture" -ln "TexCoord0_DefaultTexture" 
		-ct "HW_shader_parameter" -dt "string" -p "TexCoord0";
	addAttr -is true -ci true -h true -sn "u_IsDoubleSided_Name" -ln "u_IsDoubleSided_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsDoubleSided_Type" -ln "u_IsDoubleSided_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsDoubleSided" -ln "u_IsDoubleSided" -nn "Double sided material?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_RoughnessOffset_Name" -ln "u_RoughnessOffset_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_RoughnessOffset_Type" -ln "u_RoughnessOffset_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_RoughnessOffset" -ln "u_RoughnessOffset" -nn "Roughness offset" 
		-ct "HW_shader_parameter" -min 0 -max 12 -smn 0 -smx 12 -at "long";
	addAttr -is true -ci true -h true -sn "u_BurleyFactor_Name" -ln "u_BurleyFactor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_BurleyFactor_Type" -ln "u_BurleyFactor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_BurleyFactor" -ln "u_BurleyFactor" -nn "Burley factor" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float";
	addAttr -is true -ci true -h true -sn "u_UndoEdgeStretch_Name" -ln "u_UndoEdgeStretch_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_UndoEdgeStretch_Type" -ln "u_UndoEdgeStretch_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_UndoEdgeStretch" -ln "u_UndoEdgeStretch" -nn "Undo edge stretch?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsEmissiveInsRGB_Name" -ln "u_IsEmissiveInsRGB_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsEmissiveInsRGB_Type" -ln "u_IsEmissiveInsRGB_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsEmissiveInsRGB" -ln "u_IsEmissiveInsRGB" -nn "sRGB emissive?" 
		-ct "HW_shader_parameter" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_EnvRotationAngle_Name" -ln "u_EnvRotationAngle_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_EnvRotationAngle_Type" -ln "u_EnvRotationAngle_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_EnvRotationAngle" -ln "u_EnvRotationAngle" -nn "Environment Rotation" 
		-ct "HW_shader_parameter" -min 0 -max 360 -smn 0 -smx 360 -at "float";
	addAttr -is true -ci true -h true -sn "u_FlipEnvMapZ_Name" -ln "u_FlipEnvMapZ_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_FlipEnvMapZ_Type" -ln "u_FlipEnvMapZ_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_FlipEnvMapZ" -ln "u_FlipEnvMapZ" -nn "Flip environment Z?" 
		-ct "HW_shader_parameter" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsEnvMapInsRGB_Name" -ln "u_IsEnvMapInsRGB_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsEnvMapInsRGB_Type" -ln "u_IsEnvMapInsRGB_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsEnvMapInsRGB" -ln "u_IsEnvMapInsRGB" -nn "sRGB environment?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsEnvMapInRGBM_Name" -ln "u_IsEnvMapInRGBM_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsEnvMapInRGBM_Type" -ln "u_IsEnvMapInRGBM_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsEnvMapInRGBM" -ln "u_IsEnvMapInRGBM" -nn "RGBM environment?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsBRDFsSRGB_Name" -ln "u_IsBRDFsSRGB_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsBRDFsSRGB_Type" -ln "u_IsBRDFsSRGB_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsBRDFsSRGB" -ln "u_IsBRDFsSRGB" -nn "sRGB BRDF table?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_IsBaseColorInsRGB_Name" -ln "u_IsBaseColorInsRGB_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsBaseColorInsRGB_Type" -ln "u_IsBaseColorInsRGB_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsBaseColorInsRGB" -ln "u_IsBaseColorInsRGB" -nn "sRGB basecolor?" 
		-ct "HW_shader_parameter" -dv 1 -min 0 -max 1 -at "bool";
	setAttr ".vpar" -type "stringArray" 5 "Position" "Normal" "Tangent" "Binormal" "TexCoord0"  ;
	setAttr ".upar" -type "stringArray" 34 "u_LightColor" "u_LightIntensity" "u_LightRotation" "u_LightPitch" "u_BaseColorTexture" "u_BaseColorFactor" "u_MetallicTexture" "u_MetallicStrength" "u_RoughnessTexture" "u_RoughnessStrength" "u_OcclusionTexture" "u_OcclusionStrength" "u_NormalTexture" "u_NormalScale" "u_EmissiveTexture" "u_EmissiveColor" "u_DiffuseEnvTexture" "u_SpecularEnvTexture" "u_brdfTexture" "u_IsDoubleSided" "u_UseMeshTangents" "u_RoughnessOffset" "u_ScaleDiffBaseMR" "u_BurleyFactor" "u_ScaleFGDSpec" "u_UndoEdgeStretch" "u_ScaleIBL_Occl" "u_IsEmissiveInsRGB" "u_EnvRotationAngle" "u_FlipEnvMapZ" "u_IsEnvMapInsRGB" "u_IsEnvMapInRGBM" "u_IsBRDFsSRGB" "u_IsBaseColorInsRGB"  ;
	setAttr ".s" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/shaders/glTF_PBR.ogsfx";
	setAttr ".t" -type "string" "Solid";
	setAttr ".u_LightColor_Name" -type "string" "u_LightColor";
	setAttr ".u_LightColor_Type" -type "string" "color3x1";
	setAttr ".u_LightColor" -type "float3" 1 1 1 ;
	setAttr ".u_LightIntensity_Name" -type "string" "u_LightIntensity";
	setAttr ".u_LightIntensity_Type" -type "string" "float";
	setAttr ".u_LightIntensity" 1;
	setAttr ".u_LightRotation_Name" -type "string" "u_LightRotation";
	setAttr ".u_LightRotation_Type" -type "string" "float";
	setAttr ".u_LightRotation" 75;
	setAttr ".u_LightPitch_Name" -type "string" "u_LightPitch";
	setAttr ".u_LightPitch_Type" -type "string" "float";
	setAttr ".u_LightPitch" 40;
	setAttr ".u_BaseColorTexture_Name" -type "string" "u_BaseColorTexture";
	setAttr ".u_BaseColorTexture_Type" -type "string" "texture";
	setAttr ".u_BaseColorTexture" -type "float3" 0 0 0 ;
	setAttr ".u_BaseColorFactor_Name" -type "string" "u_BaseColorFactor";
	setAttr ".u_BaseColorFactor_Type" -type "string" "color4x1";
	setAttr ".u_BaseColorFactorRGB" -type "float3" 1 1 1 ;
	setAttr ".u_BaseColorFactorA" 1;
	setAttr ".u_MetallicTexture_Name" -type "string" "u_MetallicTexture";
	setAttr ".u_MetallicTexture_Type" -type "string" "texture";
	setAttr ".u_MetallicTexture" -type "float3" 0 0 0 ;
	setAttr ".u_MetallicStrength_Name" -type "string" "u_MetallicStrength";
	setAttr ".u_MetallicStrength_Type" -type "string" "float";
	setAttr ".u_MetallicStrength" 1;
	setAttr ".u_RoughnessTexture_Name" -type "string" "u_RoughnessTexture";
	setAttr ".u_RoughnessTexture_Type" -type "string" "texture";
	setAttr ".u_RoughnessTexture" -type "float3" 0 0 0 ;
	setAttr ".u_RoughnessStrength_Name" -type "string" "u_RoughnessStrength";
	setAttr ".u_RoughnessStrength_Type" -type "string" "float";
	setAttr ".u_RoughnessStrength" 0;
	setAttr ".u_OcclusionTexture_Name" -type "string" "u_OcclusionTexture";
	setAttr ".u_OcclusionTexture_Type" -type "string" "texture";
	setAttr ".u_OcclusionTexture" -type "float3" 0 0 0 ;
	setAttr ".u_OcclusionStrength_Name" -type "string" "u_OcclusionStrength";
	setAttr ".u_OcclusionStrength_Type" -type "string" "float";
	setAttr ".u_OcclusionStrength" 1;
	setAttr ".u_NormalTexture_Name" -type "string" "u_NormalTexture";
	setAttr ".u_NormalTexture_Type" -type "string" "texture";
	setAttr ".u_NormalTexture" -type "float3" 0 0 0 ;
	setAttr ".u_NormalScale_Name" -type "string" "u_NormalScale";
	setAttr ".u_NormalScale_Type" -type "string" "float";
	setAttr ".u_NormalScale" 1;
	setAttr ".u_EmissiveTexture_Name" -type "string" "u_EmissiveTexture";
	setAttr ".u_EmissiveTexture_Type" -type "string" "texture";
	setAttr ".u_EmissiveTexture" -type "float3" 0 0 0 ;
	setAttr ".u_EmissiveColor_Name" -type "string" "u_EmissiveColor";
	setAttr ".u_EmissiveColor_Type" -type "string" "color3x1";
	setAttr ".u_EmissiveColor" -type "float3" 0 0 0 ;
	setAttr ".u_DiffuseEnvTexture_Name" -type "string" "u_DiffuseEnvTexture";
	setAttr ".u_DiffuseEnvTexture_Type" -type "string" "texture";
	setAttr ".u_DiffuseEnvTexture" -type "float3" 0 0 0 ;
	setAttr ".u_SpecularEnvTexture_Name" -type "string" "u_SpecularEnvTexture";
	setAttr ".u_SpecularEnvTexture_Type" -type "string" "texture";
	setAttr ".u_SpecularEnvTexture" -type "float3" 0 0 0 ;
	setAttr ".u_brdfTexture_Name" -type "string" "u_brdfTexture";
	setAttr ".u_brdfTexture_Type" -type "string" "texture";
	setAttr ".u_brdfTexture" -type "float3" 0 0 0 ;
	setAttr ".u_UseMeshTangents_Name" -type "string" "u_UseMeshTangents";
	setAttr ".u_UseMeshTangents_Type" -type "string" "bool";
	setAttr ".u_UseMeshTangents" no;
	setAttr ".u_ScaleDiffBaseMR_Name" -type "string" "u_ScaleDiffBaseMR";
	setAttr ".u_ScaleDiffBaseMR_Type" -type "string" "float4x1";
	setAttr ".u_ScaleDiffBaseMRXYZ" -type "float3" 0 0 0 ;
	setAttr ".u_ScaleDiffBaseMRW" 0;
	setAttr ".u_ScaleFGDSpec_Name" -type "string" "u_ScaleFGDSpec";
	setAttr ".u_ScaleFGDSpec_Type" -type "string" "float4x1";
	setAttr ".u_ScaleFGDSpecXYZ" -type "float3" 0 0 0 ;
	setAttr ".u_ScaleFGDSpecW" 0;
	setAttr ".u_ScaleIBL_Occl_Name" -type "string" "u_ScaleIBL_Occl";
	setAttr ".u_ScaleIBL_Occl_Type" -type "string" "float4x1";
	setAttr ".u_ScaleIBL_OcclXYZ" -type "float3" 1 1 0 ;
	setAttr ".u_ScaleIBL_OcclW" 1;
	setAttr ".Position_Name" -type "string" "Position";
	setAttr ".Position_Source" -type "string" "position";
	setAttr ".Normal_Name" -type "string" "Normal";
	setAttr ".Normal_Source" -type "string" "normal";
	setAttr ".Tangent_Name" -type "string" "Tangent";
	setAttr ".Tangent_Source" -type "string" "tangent:map1";
	setAttr ".Binormal_Name" -type "string" "Binormal";
	setAttr ".Binormal_Source" -type "string" "binormal:map1";
	setAttr ".TexCoord0_Name" -type "string" "TexCoord0";
	setAttr ".TexCoord0_Source" -type "string" "uv:map1";
	setAttr ".u_IsDoubleSided_Name" -type "string" "u_IsDoubleSided";
	setAttr ".u_IsDoubleSided_Type" -type "string" "bool";
	setAttr ".u_IsDoubleSided" no;
	setAttr ".u_RoughnessOffset_Name" -type "string" "u_RoughnessOffset";
	setAttr ".u_RoughnessOffset_Type" -type "string" "int";
	setAttr ".u_RoughnessOffset" 0;
	setAttr ".u_BurleyFactor_Name" -type "string" "u_BurleyFactor";
	setAttr ".u_BurleyFactor_Type" -type "string" "float";
	setAttr ".u_BurleyFactor" 0;
	setAttr ".u_UndoEdgeStretch_Name" -type "string" "u_UndoEdgeStretch";
	setAttr ".u_UndoEdgeStretch_Type" -type "string" "bool";
	setAttr ".u_UndoEdgeStretch" no;
	setAttr ".u_IsEmissiveInsRGB_Name" -type "string" "u_IsEmissiveInsRGB";
	setAttr ".u_IsEmissiveInsRGB_Type" -type "string" "bool";
	setAttr ".u_IsEmissiveInsRGB" yes;
	setAttr ".u_EnvRotationAngle_Name" -type "string" "u_EnvRotationAngle";
	setAttr ".u_EnvRotationAngle_Type" -type "string" "float";
	setAttr ".u_EnvRotationAngle" 0;
	setAttr ".u_FlipEnvMapZ_Name" -type "string" "u_FlipEnvMapZ";
	setAttr ".u_FlipEnvMapZ_Type" -type "string" "bool";
	setAttr ".u_FlipEnvMapZ" yes;
	setAttr ".u_IsEnvMapInsRGB_Name" -type "string" "u_IsEnvMapInsRGB";
	setAttr ".u_IsEnvMapInsRGB_Type" -type "string" "bool";
	setAttr ".u_IsEnvMapInsRGB" no;
	setAttr ".u_IsEnvMapInRGBM_Name" -type "string" "u_IsEnvMapInRGBM";
	setAttr ".u_IsEnvMapInRGBM_Type" -type "string" "bool";
	setAttr ".u_IsEnvMapInRGBM" no;
	setAttr ".u_IsBRDFsSRGB_Name" -type "string" "u_IsBRDFsSRGB";
	setAttr ".u_IsBRDFsSRGB_Type" -type "string" "bool";
	setAttr ".u_IsBRDFsSRGB" no;
	setAttr ".u_IsBaseColorInsRGB_Name" -type "string" "u_IsBaseColorInsRGB";
	setAttr ".u_IsBaseColorInsRGB_Type" -type "string" "bool";
	setAttr ".u_IsBaseColorInsRGB" yes;
createNode shadingEngine -n "GLSLShader2SG";
	rename -uid "F6CBDDE3-43A1-B911-B13D-BAB99FED35DC";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo3";
	rename -uid "4C9D9C12-4E25-EAD6-EACF-F582748844C7";
createNode script -n "uiConfigurationScriptNode";
	rename -uid "95CE6C44-4E28-FFFA-77BA-BA8A03B7C49D";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $nodeEditorPanelVisible = stringArrayContains(\"nodeEditorPanel1\", `getPanel -vis`);\n\tint    $nodeEditorWorkspaceControlOpen = (`workspaceControl -exists nodeEditorPanel1Window` && `workspaceControl -q -visible nodeEditorPanel1Window`);\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\n\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n"
		+ "            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 663\n            -height 1054\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n"
		+ "            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n"
		+ "            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 663\n            -height 505\n"
		+ "            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n"
		+ "            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n"
		+ "            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n"
		+ "            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 663\n            -height 1054\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"camera1\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n"
		+ "            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n"
		+ "            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n"
		+ "            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1333\n            -height 1054\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"ToggledOutliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"ToggledOutliner\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n"
		+ "            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -isSet 0\n            -isSetMember 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            -renderFilterIndex 0\n            -selectionOrder \"chronological\" \n"
		+ "            -expandAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n"
		+ "            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n"
		+ "            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n"
		+ "                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 1\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n"
		+ "                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 1\n                -snapTime \"integer\" \n"
		+ "                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -showCurveNames 0\n                -showActiveCurveNames 0\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                -valueLinesToggle 1\n                -outliner \"graphEditor1OutlineEd\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 1\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n"
		+ "                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n"
		+ "                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"timeEditorPanel\" (localizedPanelLabel(\"Time Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Time Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -frameRange 0 122 \n                -initialized 1\n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n"
		+ "                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif ($nodeEditorPanelVisible || $nodeEditorWorkspaceControlOpen) {\n"
		+ "\t\tif (\"\" == $panelName) {\n\t\t\tif ($useSceneConfig) {\n\t\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -copyConnectionsOnPaste 0\n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n"
		+ "                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -editorMode \"default\" \n                $editorName;\n\t\t\t}\n\t\t} else {\n\t\t\t$label = `panel -q -label $panelName`;\n\t\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -copyConnectionsOnPaste 0\n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n"
		+ "                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -editorMode \"default\" \n                $editorName;\n\t\t\tif (!$useSceneConfig) {\n\t\t\t\tpanel -e -l $label $panelName;\n\t\t\t}\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Editor\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"shapePanel\" (localizedPanelLabel(\"Shape Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tshapePanel -edit -l (localizedPanelLabel(\"Shape Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"posePanel\" (localizedPanelLabel(\"Pose Editor\")) `;\n\tif (\"\" != $panelName) {\n"
		+ "\t\t$label = `panel -q -label $panelName`;\n\t\tposePanel -edit -l (localizedPanelLabel(\"Pose Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"profilerPanel\" (localizedPanelLabel(\"Profiler Tool\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"contentBrowserPanel\" (localizedPanelLabel(\"Content Browser\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Content Browser\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"Stereo\" (localizedPanelLabel(\"Stereo\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels  $panelName;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -editorChanged \"updateModelPanelBar\" \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -holdOuts 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n"
		+ "                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 32768\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -depthOfFieldPreview 1\n                -maxConstantTransparency 1\n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n"
		+ "                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -controllers 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n"
		+ "                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -captureSequenceNumber -1\n                -width 0\n                -height 0\n                -sceneRenderFilter 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                -useCustomBackground 1\n                $editorName;\n            stereoCameraView -e -viewSelected 0 $editorName;\n            stereoCameraView -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n"
		+ "            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n"
		+ "            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n"
		+ "            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1\n            -height 1\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" != $panelName) {\n"
		+ "\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n"
		+ "            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n"
		+ "            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 0\n            -height 0\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n"
		+ "            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n"
		+ "            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n"
		+ "            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 0\n            -height 0\n"
		+ "            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n"
		+ "            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n"
		+ "            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n"
		+ "            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 0\n            -height 0\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-userCreated false\n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -camera \\\"camera1\\\" \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 1\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1333\\n    -height 1054\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -camera \\\"camera1\\\" \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 1\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1333\\n    -height 1054\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 1 -size 10 -divisions 4 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "08561F58-4853-A05E-496B-949BFCA8EE79";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
createNode phong -n "Material";
	rename -uid "A3225620-426C-0834-4BF4-06A429CEB74C";
	setAttr ".c" -type "float3" 0.80000001 0.80000001 0.80000001 ;
	setAttr ".sc" -type "float3" 0.25 0.25 0.25 ;
	setAttr ".rfl" 0;
	setAttr ".rc" -type "float3" 1 1 1 ;
	setAttr ".cp" 9.6078433990478516;
createNode shadingEngine -n "CubeSG";
	rename -uid "00FB02CC-4DA8-0AAC-A0F0-A29259A97C4E";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo4";
	rename -uid "71748155-4101-A371-7D57-D38F82638587";
createNode lambert -n "lambert2";
	rename -uid "776AA4A6-4247-D1FA-12B2-2DA815FEABD9";
	setAttr ".c" -type "float3" 0.51632047 0.51632047 0.51632047 ;
createNode shadingEngine -n "lambert2SG";
	rename -uid "448C0155-40A6-A2A4-3247-30A316E0F3AE";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo5";
	rename -uid "E5C82F35-416A-E38A-7E9F-328C08C6EA4B";
createNode phong -n "GLSL_PBR_Shader1";
	rename -uid "695840ED-42E2-827F-2930-0DA54F0C0E58";
	setAttr ".dc" 1;
	setAttr ".ambc" -type "float3" 0.40000001 0.40000001 0.40000001 ;
	setAttr ".sc" -type "float3" 0.30000001 0.30000001 0.30000001 ;
	setAttr ".rfl" 0;
createNode shadingEngine -n "SoftCubeSG";
	rename -uid "60048E74-4C30-E2E9-9DBB-36B4DCFBE56C";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo6";
	rename -uid "9F38497B-441C-EC7D-BA75-82AAAE52D677";
createNode skinCluster -n "skinCluster1";
	rename -uid "E13215D9-4254-B433-C5F3-C788017F3A98";
	setAttr -s 8 ".wl";
	setAttr ".wl[0:7].w"
		1 0 1
		1 0 1
		1 0 1
		1 0 1
		1 0 1
		1 0 1
		1 0 1
		1 0 1;
	setAttr ".pm[0]" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1;
	setAttr ".gm" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1;
	setAttr ".dpf[0]"  4;
	setAttr ".mmi" yes;
	setAttr ".ucm" yes;
createNode tweak -n "tweak1";
	rename -uid "F54D644C-4F0A-CAED-B9C0-CDB880CED095";
createNode objectSet -n "skinCluster1Set";
	rename -uid "523B2503-4E19-7EF4-03DD-ED8FE00D506B";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "skinCluster1GroupId";
	rename -uid "686A9291-4838-6D08-99B5-479E7CABC25B";
	setAttr ".ihi" 0;
createNode groupParts -n "skinCluster1GroupParts";
	rename -uid "77FD0A2D-4060-65F0-E1F6-9FA153CB00C9";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode objectSet -n "tweakSet1";
	rename -uid "71A46D69-44D5-E1B8-CDC0-4D883CC6B48F";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "groupId2";
	rename -uid "322E1589-4C76-EA71-8967-9EB7951B9EDA";
	setAttr ".ihi" 0;
createNode groupParts -n "groupParts2";
	rename -uid "34FDE041-446E-36E3-3995-10919C629335";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode dagPose -n "bindPose1";
	rename -uid "6600796C-4823-8652-47BD-2DADF3B4AD8B";
	setAttr ".xm[0]" -type "matrix" "xform" 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 yes;
	setAttr ".bp" yes;
createNode nodeGraphEditorInfo -n "hyperShadePrimaryNodeEditorSavedTabsInfo";
	rename -uid "B663DDA4-4D43-D00E-59A7-D49FD6F18540";
	setAttr ".tgi[0].tn" -type "string" "Untitled_1";
	setAttr ".tgi[0].vl" -type "double2" -113.09523360123728 -278.57141750199503 ;
	setAttr ".tgi[0].vh" -type "double2" 114.28570974440824 278.57141750199503 ;
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 0;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
	setAttr ".etmr" no;
	setAttr ".tmr" 4096;
	setAttr ".fprt" yes;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 8 ".st";
	setAttr -cb on ".an";
	setAttr -cb on ".pt";
select -ne :renderGlobalsList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultShaderList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 10 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 5 ".u";
select -ne :defaultRenderingList1;
select -ne :defaultTextureList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 4 ".tx";
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
	setAttr -cb on ".an";
	setAttr -cb on ".il";
	setAttr -cb on ".vo";
	setAttr -cb on ".eo";
	setAttr -cb on ".fo";
	setAttr -cb on ".epo";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".mwc";
	setAttr -cb on ".an";
	setAttr -cb on ".il";
	setAttr -cb on ".vo";
	setAttr -cb on ".eo";
	setAttr -cb on ".fo";
	setAttr -cb on ".epo";
	setAttr ".ro" yes;
select -ne :defaultResolution;
	setAttr ".w" 1280;
	setAttr ".h" 720;
	setAttr ".pa" 1;
select -ne :hardwareRenderGlobals;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".ctrs" 256;
	setAttr -av ".btrs" 512;
	setAttr -k off ".fbfm";
	setAttr -k off -cb on ".ehql";
	setAttr -k off -cb on ".eams";
	setAttr -k off -cb on ".eeaa";
	setAttr -k off -cb on ".engm";
	setAttr -k off -cb on ".mes";
	setAttr -k off -cb on ".emb";
	setAttr -av -k off -cb on ".mbbf";
	setAttr -k off -cb on ".mbs";
	setAttr -k off -cb on ".trm";
	setAttr -k off -cb on ".tshc";
	setAttr -k off ".enpt";
	setAttr -k off -cb on ".clmt";
	setAttr -k off -cb on ".tcov";
	setAttr -k off -cb on ".lith";
	setAttr -k off -cb on ".sobc";
	setAttr -k off -cb on ".cuth";
	setAttr -k off -cb on ".hgcd";
	setAttr -k off -cb on ".hgci";
	setAttr -k off -cb on ".mgcs";
	setAttr -k off -cb on ".twa";
	setAttr -k off -cb on ".twz";
	setAttr -k on ".hwcc";
	setAttr -k on ".hwdp";
	setAttr -k on ".hwql";
	setAttr -k on ".hwfr";
connectAttr "skinCluster1GroupId.id" "SoftCubeShape.iog.og[0].gid";
connectAttr "skinCluster1Set.mwc" "SoftCubeShape.iog.og[0].gco";
connectAttr "groupId2.id" "SoftCubeShape.iog.og[1].gid";
connectAttr "tweakSet1.mwc" "SoftCubeShape.iog.og[1].gco";
connectAttr "skinCluster1.og[0]" "SoftCubeShape.i";
connectAttr "tweak1.vl[0].vt[0]" "SoftCubeShape.twl";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "surfaceSamplingEnvelopeShaderSG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "GLSLShader1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "GLSLShader2SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "CubeSG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "lambert2SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "SoftCubeSG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "surfaceSamplingEnvelopeShaderSG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "GLSLShader1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "GLSLShader2SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "CubeSG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "lambert2SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "SoftCubeSG.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "surfaceSamplingEnvelopeShader.oc" "surfaceSamplingEnvelopeShaderSG.ss"
		;
connectAttr "surfaceSamplingEnvelopeShaderSG.msg" "materialInfo1.sg";
connectAttr "surfaceSamplingEnvelopeShader.msg" "materialInfo1.m";
connectAttr "normal_map_file.oc" "GLSL_PBR_Shader.u_NormalTexture";
connectAttr "file2.oc" "GLSL_PBR_Shader.u_DiffuseEnvTexture";
connectAttr "file3.oc" "GLSL_PBR_Shader.u_SpecularEnvTexture";
connectAttr "file4.oc" "GLSL_PBR_Shader.u_brdfTexture";
connectAttr "GLSL_PBR_Shader.oc" "GLSLShader1SG.ss";
connectAttr "SoftCubeShape.iog" "GLSLShader1SG.dsm" -na;
connectAttr "GLSLShader1SG.msg" "materialInfo2.sg";
connectAttr "GLSL_PBR_Shader.msg" "materialInfo2.m";
connectAttr "GLSL_PBR_Shader.msg" "materialInfo2.t" -na;
connectAttr ":defaultColorMgtGlobals.cme" "normal_map_file.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "normal_map_file.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "normal_map_file.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "normal_map_file.ws";
connectAttr "place2dTexture1.c" "normal_map_file.c";
connectAttr "place2dTexture1.tf" "normal_map_file.tf";
connectAttr "place2dTexture1.rf" "normal_map_file.rf";
connectAttr "place2dTexture1.mu" "normal_map_file.mu";
connectAttr "place2dTexture1.mv" "normal_map_file.mv";
connectAttr "place2dTexture1.s" "normal_map_file.s";
connectAttr "place2dTexture1.wu" "normal_map_file.wu";
connectAttr "place2dTexture1.wv" "normal_map_file.wv";
connectAttr "place2dTexture1.re" "normal_map_file.re";
connectAttr "place2dTexture1.of" "normal_map_file.of";
connectAttr "place2dTexture1.r" "normal_map_file.ro";
connectAttr "place2dTexture1.n" "normal_map_file.n";
connectAttr "place2dTexture1.vt1" "normal_map_file.vt1";
connectAttr "place2dTexture1.vt2" "normal_map_file.vt2";
connectAttr "place2dTexture1.vt3" "normal_map_file.vt3";
connectAttr "place2dTexture1.vc1" "normal_map_file.vc1";
connectAttr "place2dTexture1.o" "normal_map_file.uv";
connectAttr "place2dTexture1.ofs" "normal_map_file.fs";
connectAttr ":defaultColorMgtGlobals.cme" "file2.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "file2.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "file2.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "file2.ws";
connectAttr "place2dTexture2.c" "file2.c";
connectAttr "place2dTexture2.tf" "file2.tf";
connectAttr "place2dTexture2.rf" "file2.rf";
connectAttr "place2dTexture2.mu" "file2.mu";
connectAttr "place2dTexture2.mv" "file2.mv";
connectAttr "place2dTexture2.s" "file2.s";
connectAttr "place2dTexture2.wu" "file2.wu";
connectAttr "place2dTexture2.wv" "file2.wv";
connectAttr "place2dTexture2.re" "file2.re";
connectAttr "place2dTexture2.of" "file2.of";
connectAttr "place2dTexture2.r" "file2.ro";
connectAttr "place2dTexture2.n" "file2.n";
connectAttr "place2dTexture2.vt1" "file2.vt1";
connectAttr "place2dTexture2.vt2" "file2.vt2";
connectAttr "place2dTexture2.vt3" "file2.vt3";
connectAttr "place2dTexture2.vc1" "file2.vc1";
connectAttr "place2dTexture2.o" "file2.uv";
connectAttr "place2dTexture2.ofs" "file2.fs";
connectAttr ":defaultColorMgtGlobals.cme" "file3.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "file3.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "file3.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "file3.ws";
connectAttr "place2dTexture3.c" "file3.c";
connectAttr "place2dTexture3.tf" "file3.tf";
connectAttr "place2dTexture3.rf" "file3.rf";
connectAttr "place2dTexture3.mu" "file3.mu";
connectAttr "place2dTexture3.mv" "file3.mv";
connectAttr "place2dTexture3.s" "file3.s";
connectAttr "place2dTexture3.wu" "file3.wu";
connectAttr "place2dTexture3.wv" "file3.wv";
connectAttr "place2dTexture3.re" "file3.re";
connectAttr "place2dTexture3.of" "file3.of";
connectAttr "place2dTexture3.r" "file3.ro";
connectAttr "place2dTexture3.n" "file3.n";
connectAttr "place2dTexture3.vt1" "file3.vt1";
connectAttr "place2dTexture3.vt2" "file3.vt2";
connectAttr "place2dTexture3.vt3" "file3.vt3";
connectAttr "place2dTexture3.vc1" "file3.vc1";
connectAttr "place2dTexture3.o" "file3.uv";
connectAttr "place2dTexture3.ofs" "file3.fs";
connectAttr ":defaultColorMgtGlobals.cme" "file4.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "file4.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "file4.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "file4.ws";
connectAttr "place2dTexture4.c" "file4.c";
connectAttr "place2dTexture4.tf" "file4.tf";
connectAttr "place2dTexture4.rf" "file4.rf";
connectAttr "place2dTexture4.mu" "file4.mu";
connectAttr "place2dTexture4.mv" "file4.mv";
connectAttr "place2dTexture4.s" "file4.s";
connectAttr "place2dTexture4.wu" "file4.wu";
connectAttr "place2dTexture4.wv" "file4.wv";
connectAttr "place2dTexture4.re" "file4.re";
connectAttr "place2dTexture4.of" "file4.of";
connectAttr "place2dTexture4.r" "file4.ro";
connectAttr "place2dTexture4.n" "file4.n";
connectAttr "place2dTexture4.vt1" "file4.vt1";
connectAttr "place2dTexture4.vt2" "file4.vt2";
connectAttr "place2dTexture4.vt3" "file4.vt3";
connectAttr "place2dTexture4.vc1" "file4.vc1";
connectAttr "place2dTexture4.o" "file4.uv";
connectAttr "place2dTexture4.ofs" "file4.fs";
connectAttr "normal_map_file.oa" "bump2d1.bv";
connectAttr "file2.oc" "PBR_Shader_no_normal_map.u_DiffuseEnvTexture";
connectAttr "file3.oc" "PBR_Shader_no_normal_map.u_SpecularEnvTexture";
connectAttr "file4.oc" "PBR_Shader_no_normal_map.u_brdfTexture";
connectAttr "PBR_Shader_no_normal_map.oc" "GLSLShader2SG.ss";
connectAttr "GLSLShader2SG.msg" "materialInfo3.sg";
connectAttr "PBR_Shader_no_normal_map.msg" "materialInfo3.m";
connectAttr "Material.oc" "CubeSG.ss";
connectAttr "CubeSG.msg" "materialInfo4.sg";
connectAttr "Material.msg" "materialInfo4.m";
connectAttr "lambert2.oc" "lambert2SG.ss";
connectAttr "lambert2SG.msg" "materialInfo5.sg";
connectAttr "lambert2.msg" "materialInfo5.m";
connectAttr "GLSL_PBR_Shader1.oc" "SoftCubeSG.ss";
connectAttr "SoftCubeSG.msg" "materialInfo6.sg";
connectAttr "GLSL_PBR_Shader1.msg" "materialInfo6.m";
connectAttr "skinCluster1GroupParts.og" "skinCluster1.ip[0].ig";
connectAttr "skinCluster1GroupId.id" "skinCluster1.ip[0].gi";
connectAttr "bindPose1.msg" "skinCluster1.bp";
connectAttr "joint1.wm" "skinCluster1.ma[0]";
connectAttr "joint1.liw" "skinCluster1.lw[0]";
connectAttr "joint1.obcc" "skinCluster1.ifcl[0]";
connectAttr "groupParts2.og" "tweak1.ip[0].ig";
connectAttr "groupId2.id" "tweak1.ip[0].gi";
connectAttr "skinCluster1GroupId.msg" "skinCluster1Set.gn" -na;
connectAttr "SoftCubeShape.iog.og[0]" "skinCluster1Set.dsm" -na;
connectAttr "skinCluster1.msg" "skinCluster1Set.ub[0]";
connectAttr "tweak1.og[0]" "skinCluster1GroupParts.ig";
connectAttr "skinCluster1GroupId.id" "skinCluster1GroupParts.gi";
connectAttr "groupId2.msg" "tweakSet1.gn" -na;
connectAttr "SoftCubeShape.iog.og[1]" "tweakSet1.dsm" -na;
connectAttr "tweak1.msg" "tweakSet1.ub[0]";
connectAttr "SoftCubeShapeOrig.w" "groupParts2.ig";
connectAttr "groupId2.id" "groupParts2.gi";
connectAttr "joint1.msg" "bindPose1.m[0]";
connectAttr "bindPose1.w" "bindPose1.p[0]";
connectAttr "joint1.bps" "bindPose1.wm[0]";
connectAttr "surfaceSamplingEnvelopeShaderSG.pa" ":renderPartition.st" -na;
connectAttr "GLSLShader1SG.pa" ":renderPartition.st" -na;
connectAttr "GLSLShader2SG.pa" ":renderPartition.st" -na;
connectAttr "CubeSG.pa" ":renderPartition.st" -na;
connectAttr "lambert2SG.pa" ":renderPartition.st" -na;
connectAttr "SoftCubeSG.pa" ":renderPartition.st" -na;
connectAttr "surfaceSamplingEnvelopeShader.msg" ":defaultShaderList1.s" -na;
connectAttr "GLSL_PBR_Shader.msg" ":defaultShaderList1.s" -na;
connectAttr "PBR_Shader_no_normal_map.msg" ":defaultShaderList1.s" -na;
connectAttr "Material.msg" ":defaultShaderList1.s" -na;
connectAttr "lambert2.msg" ":defaultShaderList1.s" -na;
connectAttr "GLSL_PBR_Shader1.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture2.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture3.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture4.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "bump2d1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "normal_map_file.msg" ":defaultTextureList1.tx" -na;
connectAttr "file2.msg" ":defaultTextureList1.tx" -na;
connectAttr "file3.msg" ":defaultTextureList1.tx" -na;
connectAttr "file4.msg" ":defaultTextureList1.tx" -na;
// End of CubeNormalBakingRigTest.ma
