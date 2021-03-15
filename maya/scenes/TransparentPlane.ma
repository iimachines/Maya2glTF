//Maya ASCII 2018 scene
//Name: TransparentPlane.ma
//Last modified: Tue, Jan 19, 2021 04:52:38 PM
//Codeset: 1252
requires maya "2018";
requires "stereoCamera" "10.0";
requires -nodeType "GLSLShader" "glslShader" "1.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2018";
fileInfo "version" "2018";
fileInfo "cutIdentifier" "201706261615-f9658c4cfc";
fileInfo "osv" "Microsoft Windows 8 Business Edition, 64-bit  (Build 9200)\n";
createNode transform -s -n "persp";
	rename -uid "360F5835-4139-9365-AAFF-02AB19EF919E";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0.35321359710095723 4.5280936890117749 0.0086323543790088886 ;
	setAttr ".r" -type "double3" -85.538352729390411 88.599999999946647 -1.3017892475530087e-13 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "05AB706C-4518-1283-AAFB-ECAB48484932";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 4.5418571993400469;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "863558FF-475A-4195-9DDD-F8A8F7188BCA";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 1000.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "446A3D25-419F-EBF9-AECA-3881D0244067";
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
	rename -uid "216D5DA2-4F74-4A44-C02B-529B2A1A6951";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 1000.1 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "C5A3BE7A-4767-9EE2-1FE5-728A803109B8";
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
	rename -uid "DBBFE8AF-4174-6939-9B8A-A2B8F742D22F";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "0EF9BF9F-4CBB-B991-D098-C595E1CBA99A";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "pPlane1";
	rename -uid "9A24BC92-47B1-B18F-855B-77A459EBD00A";
	setAttr ".t" -type "double3" 0 1.1507095739190747 0 ;
createNode mesh -n "pPlaneShape1" -p "pPlane1";
	rename -uid "74777387-4F94-22BE-2396-D98486CBC746";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "pPlane2";
	rename -uid "28A3433C-4844-DC8A-5A43-E3B1625674DE";
createNode mesh -n "pPlaneShape2" -p "pPlane2";
	rename -uid "DD373A8E-42F5-8A06-7366-9ABA5F63B7DB";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "4C5789B6-4827-133D-CFFC-85BF446DCB31";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "0541DD01-498D-FEA8-F59B-23B32FD4F4D0";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "2AF316A0-41D6-E083-3619-E7B42DDB67B2";
createNode displayLayerManager -n "layerManager";
	rename -uid "92330A00-46CE-D18E-BB93-1C9FD9D89477";
createNode displayLayer -n "defaultLayer";
	rename -uid "876AB58F-4E11-0E9D-0BBB-2B87CDF462F7";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "AEEBC73D-4D20-56D9-254B-2494EC773B32";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "174EA174-4BD4-C9E8-ACF2-B4B6434FA1FA";
	setAttr ".g" yes;
createNode polyPlane -n "polyPlane1";
	rename -uid "42494A45-454D-0494-C6DA-BF90C79F64F4";
	setAttr ".cuv" 2;
createNode script -n "maya2glTF_scriptNode";
	rename -uid "ABCBC469-46AA-BC3D-5118-378B04A27DB7";
	addAttr -ci true -sn "outputFolder" -ln "outputFolder" -dt "string";
	addAttr -ci true -sn "sceneName" -ln "sceneName" -dt "string";
	addAttr -ci true -sn "copyright" -ln "copyright" -dt "string";
	addAttr -ci true -sn "scale" -ln "scale" -at "float";
	addAttr -ci true -sn "flags" -ln "flags" -dt "string";
	addAttr -ci true -sn "char" -ln "char" -dt "string";
	addAttr -ci true -sn "anim" -ln "anim" -at "long";
	addAttr -ci true -sn "clip" -ln "clip" -dt "string";
	addAttr -ci true -sn "selOnly" -ln "selOnly" -at "long";
	addAttr -ci true -sn "visOnly" -ln "visOnly" -at "long";
	setAttr ".st" 2;
	setAttr ".outputFolder" -type "string" "C:/dev/glTF/Maya2glTF/maya/scenes/export/";
	setAttr ".sceneName" -type "string" "TransparentPlane";
	setAttr ".copyright" -type "string" "(C)2021 bugfa";
	setAttr ".scale" 1;
	setAttr ".flags" -type "string" "";
	setAttr ".char" -type "string" "";
	setAttr ".anim" 1;
	setAttr ".clip" -type "string" "clip";
	setAttr ".selOnly" 1;
	setAttr ".visOnly" 1;
createNode GLSLShader -n "GLSLShader1";
	rename -uid "9544B0B8-47CE-F3D3-BCCB-A6A3FA6AD51F";
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
	addAttr -is true -ci true -h true -sn "u_IsDoubleSided_Name" -ln "u_IsDoubleSided_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_IsDoubleSided_Type" -ln "u_IsDoubleSided_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_IsDoubleSided" -ln "u_IsDoubleSided" -nn "Double sided material?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_UseMeshTangents_Name" -ln "u_UseMeshTangents_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_UseMeshTangents_Type" -ln "u_UseMeshTangents_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_UseMeshTangents" -ln "u_UseMeshTangents" -nn "Use mesh tangents?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
	addAttr -is true -ci true -h true -sn "u_RoughnessOffset_Name" -ln "u_RoughnessOffset_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_RoughnessOffset_Type" -ln "u_RoughnessOffset_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_RoughnessOffset" -ln "u_RoughnessOffset" -nn "Roughness offset" 
		-ct "HW_shader_parameter" -min 0 -max 12 -smn 0 -smx 12 -at "long";
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
	addAttr -is true -ci true -h true -sn "u_BurleyFactor_Name" -ln "u_BurleyFactor_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_BurleyFactor_Type" -ln "u_BurleyFactor_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_BurleyFactor" -ln "u_BurleyFactor" -nn "Burley factor" 
		-ct "HW_shader_parameter" -smn 0 -smx 1 -at "float";
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
	addAttr -is true -ci true -h true -sn "u_UndoEdgeStretch_Name" -ln "u_UndoEdgeStretch_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_UndoEdgeStretch_Type" -ln "u_UndoEdgeStretch_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -sn "u_UndoEdgeStretch" -ln "u_UndoEdgeStretch" -nn "Undo edge stretch?" 
		-ct "HW_shader_parameter" -min 0 -max 1 -at "bool";
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
	addAttr -s false -is true -ci true -k true -sn "te" -ln "techniqueEnum" -nn "Technique" 
		-min 0 -max 1 -en "Solid:Transparent" -at "enum";
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
	addAttr -is true -ci true -h true -sn "u_BaseAlphaTexture_Name" -ln "u_BaseAlphaTexture_Name" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -h true -sn "u_BaseAlphaTexture_Type" -ln "u_BaseAlphaTexture_Type" 
		-ct "HW_shader_parameter" -dt "string";
	addAttr -is true -ci true -uac -sn "u_BaseAlphaTexture" -ln "u_BaseAlphaTexture" 
		-nn "Base alpha map" -ct "HW_shader_parameter" -at "float3" -nc 3;
	addAttr -is true -ci true -sn "u_BaseAlphaTextureR" -ln "u_BaseAlphaTextureR" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseAlphaTexture";
	addAttr -is true -ci true -sn "u_BaseAlphaTextureG" -ln "u_BaseAlphaTextureG" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseAlphaTexture";
	addAttr -is true -ci true -sn "u_BaseAlphaTextureB" -ln "u_BaseAlphaTextureB" -ct "HW_shader_parameter" 
		-smn 0 -smx 1 -at "float" -p "u_BaseAlphaTexture";
	setAttr ".vpar" -type "stringArray" 5 "Position" "Normal" "Tangent" "Binormal" "TexCoord0"  ;
	setAttr ".upar" -type "stringArray" 35 "u_LightColor" "u_LightIntensity" "u_LightRotation" "u_LightPitch" "u_BaseColorTexture" "u_BaseAlphaTexture" "u_BaseColorFactor" "u_MetallicTexture" "u_MetallicStrength" "u_RoughnessTexture" "u_RoughnessStrength" "u_OcclusionTexture" "u_OcclusionStrength" "u_NormalTexture" "u_NormalScale" "u_EmissiveTexture" "u_EmissiveColor" "u_DiffuseEnvTexture" "u_SpecularEnvTexture" "u_brdfTexture" "u_IsDoubleSided" "u_UseMeshTangents" "u_RoughnessOffset" "u_ScaleDiffBaseMR" "u_BurleyFactor" "u_ScaleFGDSpec" "u_UndoEdgeStretch" "u_ScaleIBL_Occl" "u_IsEmissiveInsRGB" "u_EnvRotationAngle" "u_FlipEnvMapZ" "u_IsEnvMapInsRGB" "u_IsEnvMapInRGBM" "u_IsBRDFsSRGB" "u_IsBaseColorInsRGB"  ;
	setAttr ".s" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/shaders/glTF_PBR.ogsfx";
	setAttr ".t" -type "string" "Transparent";
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
	setAttr ".u_MetallicStrength" 0.5;
	setAttr ".u_RoughnessTexture_Name" -type "string" "u_RoughnessTexture";
	setAttr ".u_RoughnessTexture_Type" -type "string" "texture";
	setAttr ".u_RoughnessTexture" -type "float3" 0 0 0 ;
	setAttr ".u_RoughnessStrength_Name" -type "string" "u_RoughnessStrength";
	setAttr ".u_RoughnessStrength_Type" -type "string" "float";
	setAttr ".u_RoughnessStrength" 0.5;
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
	setAttr ".u_IsDoubleSided_Name" -type "string" "u_IsDoubleSided";
	setAttr ".u_IsDoubleSided_Type" -type "string" "bool";
	setAttr ".u_IsDoubleSided" no;
	setAttr ".u_UseMeshTangents_Name" -type "string" "u_UseMeshTangents";
	setAttr ".u_UseMeshTangents_Type" -type "string" "bool";
	setAttr ".u_UseMeshTangents" no;
	setAttr ".u_RoughnessOffset_Name" -type "string" "u_RoughnessOffset";
	setAttr ".u_RoughnessOffset_Type" -type "string" "int";
	setAttr ".u_RoughnessOffset" 0;
	setAttr ".u_ScaleDiffBaseMR_Name" -type "string" "u_ScaleDiffBaseMR";
	setAttr ".u_ScaleDiffBaseMR_Type" -type "string" "float4x1";
	setAttr ".u_ScaleDiffBaseMRXYZ" -type "float3" 0 0 0 ;
	setAttr ".u_ScaleDiffBaseMRW" 0;
	setAttr ".u_BurleyFactor_Name" -type "string" "u_BurleyFactor";
	setAttr ".u_BurleyFactor_Type" -type "string" "float";
	setAttr ".u_BurleyFactor" 0;
	setAttr ".u_ScaleFGDSpec_Name" -type "string" "u_ScaleFGDSpec";
	setAttr ".u_ScaleFGDSpec_Type" -type "string" "float4x1";
	setAttr ".u_ScaleFGDSpecXYZ" -type "float3" 0 0 0 ;
	setAttr ".u_ScaleFGDSpecW" 0;
	setAttr ".u_UndoEdgeStretch_Name" -type "string" "u_UndoEdgeStretch";
	setAttr ".u_UndoEdgeStretch_Type" -type "string" "bool";
	setAttr ".u_UndoEdgeStretch" no;
	setAttr ".u_ScaleIBL_Occl_Name" -type "string" "u_ScaleIBL_Occl";
	setAttr ".u_ScaleIBL_Occl_Type" -type "string" "float4x1";
	setAttr ".u_ScaleIBL_OcclXYZ" -type "float3" 1 1 0 ;
	setAttr ".u_ScaleIBL_OcclW" 1;
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
	setAttr ".u_BaseAlphaTexture_Name" -type "string" "u_BaseAlphaTexture";
	setAttr ".u_BaseAlphaTexture_Type" -type "string" "texture";
	setAttr ".u_BaseAlphaTexture" -type "float3" 1 0 0 ;
createNode file -n "file1";
	rename -uid "EFC7767B-4749-1642-F98D-BC9560EDF1C8";
	setAttr ".ftn" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/shaders//../images/damaged_helmet_diffuse_env.dds";
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture1";
	rename -uid "D4BE4B8D-4B95-3EF2-EE81-9298832FC1DD";
createNode file -n "file2";
	rename -uid "7FF67A47-4B72-E38F-9BAB-0D8B18312DB6";
	setAttr ".ftn" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/shaders//../images/damaged_helmet_specular_env.dds";
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture2";
	rename -uid "D899F264-4423-3FEE-5191-14B9EB2507F1";
createNode file -n "file3";
	rename -uid "2623324C-4236-7FF1-80E2-6BB08DF3C414";
	setAttr ".ftn" -type "string" "C:/dev/glTF/Maya2glTF/maya//renderData/shaders//../images/brdfLUT.dds";
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture3";
	rename -uid "65E42160-4B21-EADF-8311-C5BAE44BF486";
createNode shadingEngine -n "GLSLShader1SG";
	rename -uid "48996740-441A-3EB8-0B47-C7B34A616107";
	setAttr ".ihi" 0;
	setAttr -s 2 ".dsm";
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
	rename -uid "87CF0B68-4BFA-9C49-AE43-67B1CFE010F3";
createNode file -n "pPlane1_BaseColorTexture";
	rename -uid "24585881-4720-FAA9-EE2F-128F584716DB";
	setAttr ".ail" yes;
	setAttr ".ag" 0.72727274894714355;
	setAttr ".ao" 0.36868685483932495;
	setAttr ".ftn" -type "string" "C:/dev/glTF/Maya2glTF/maya//images/blue_transparent_albedo.png";
	setAttr ".exp" -0.42929291725158691;
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture4";
	rename -uid "EA8807A9-44DC-772D-1B64-F39E37B1695B";
createNode polyPlane -n "polyPlane2";
	rename -uid "4D625063-4549-EA70-C7C0-CBA395ADE7F4";
	setAttr ".cuv" 2;
createNode script -n "uiConfigurationScriptNode";
	rename -uid "0FCAF390-470A-90A4-2A86-E591CF41703A";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n"
		+ "            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n"
		+ "            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n"
		+ "            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1\n            -height 1\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n"
		+ "            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1\n            -height 1\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n"
		+ "            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n"
		+ "            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1\n            -height 1\n"
		+ "            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 0\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n"
		+ "            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n"
		+ "            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n"
		+ "            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1529\n            -height 1060\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"ToggledOutliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"ToggledOutliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 1\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n"
		+ "            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n"
		+ "            -isSet 0\n            -isSetMember 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            -renderFilterIndex 0\n            -selectionOrder \"chronological\" \n            -expandAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" != $panelName) {\n"
		+ "\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n"
		+ "            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n"
		+ "            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n"
		+ "                -showPublishedAsConnected 0\n                -showParentContainers 1\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n"
		+ "                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 1\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n"
		+ "                -showUpstreamCurves 1\n                -showCurveNames 0\n                -showActiveCurveNames 0\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                -valueLinesToggle 1\n                -outliner \"graphEditor1OutlineEd\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n"
		+ "                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 1\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n"
		+ "                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n"
		+ "                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"timeEditorPanel\" (localizedPanelLabel(\"Time Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Time Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n"
		+ "            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n"
		+ "                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n"
		+ "\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n"
		+ "\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"shapePanel\" (localizedPanelLabel(\"Shape Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tshapePanel -edit -l (localizedPanelLabel(\"Shape Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"posePanel\" (localizedPanelLabel(\"Pose Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tposePanel -edit -l (localizedPanelLabel(\"Pose Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"profilerPanel\" (localizedPanelLabel(\"Profiler Tool\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"contentBrowserPanel\" (localizedPanelLabel(\"Content Browser\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Content Browser\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"Stereo\" (localizedPanelLabel(\"Stereo\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels  $panelName;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -editorChanged \"updateModelPanelBar\" \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -holdOuts 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n"
		+ "                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 32768\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -depthOfFieldPreview 1\n                -maxConstantTransparency 1\n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n"
		+ "                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -controllers 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n"
		+ "                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -captureSequenceNumber -1\n                -width 0\n                -height 0\n                -sceneRenderFilter 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                -useCustomBackground 1\n                $editorName;\n            stereoCameraView -e -viewSelected 0 $editorName;\n            stereoCameraView -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -highlightConnections 0\n                -copyConnectionsOnPaste 0\n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n"
		+ "                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -activeTab -1\n                -editorMode \"default\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-userCreated false\n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 0\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 0\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1529\\n    -height 1060\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 0\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 0\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1529\\n    -height 1060\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "B825F259-4E28-287D-8339-57B0A0209E53";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
createNode nodeGraphEditorInfo -n "hyperShadePrimaryNodeEditorSavedTabsInfo";
	rename -uid "057FC644-4ACC-AA7B-1913-2787BCAB9AFD";
	setAttr ".tgi[0].tn" -type "string" "Untitled_1";
	setAttr ".tgi[0].vl" -type "double2" -774.6972494477202 23.3643541616226 ;
	setAttr ".tgi[0].vh" -type "double2" -281.13184305558519 525.08038194371943 ;
	setAttr -s 10 ".tgi[0].ni";
	setAttr ".tgi[0].ni[0].x" -602.85711669921875;
	setAttr ".tgi[0].ni[0].y" -147.14285278320313;
	setAttr ".tgi[0].ni[0].nvs" 1923;
	setAttr ".tgi[0].ni[1].x" 370;
	setAttr ".tgi[0].ni[1].y" 660;
	setAttr ".tgi[0].ni[1].nvs" 1923;
	setAttr ".tgi[0].ni[2].x" -295.71429443359375;
	setAttr ".tgi[0].ni[2].y" 470;
	setAttr ".tgi[0].ni[2].nvs" 1923;
	setAttr ".tgi[0].ni[3].x" -602.85711669921875;
	setAttr ".tgi[0].ni[3].y" 28.571428298950195;
	setAttr ".tgi[0].ni[3].nvs" 1923;
	setAttr ".tgi[0].ni[4].x" -295.71429443359375;
	setAttr ".tgi[0].ni[4].y" 227.14285278320313;
	setAttr ".tgi[0].ni[4].nvs" 1923;
	setAttr ".tgi[0].ni[5].x" -602.85711669921875;
	setAttr ".tgi[0].ni[5].y" 412.85714721679688;
	setAttr ".tgi[0].ni[5].nvs" 1923;
	setAttr ".tgi[0].ni[6].x" -602.85711669921875;
	setAttr ".tgi[0].ni[6].y" 204.28572082519531;
	setAttr ".tgi[0].ni[6].nvs" 1923;
	setAttr ".tgi[0].ni[7].x" 61.428569793701172;
	setAttr ".tgi[0].ni[7].y" 682.85711669921875;
	setAttr ".tgi[0].ni[7].nvs" 1938;
	setAttr ".tgi[0].ni[8].x" -295.71429443359375;
	setAttr ".tgi[0].ni[8].y" -124.28571319580078;
	setAttr ".tgi[0].ni[8].nvs" 1923;
	setAttr ".tgi[0].ni[9].x" -295.71429443359375;
	setAttr ".tgi[0].ni[9].y" 51.428569793701172;
	setAttr ".tgi[0].ni[9].nvs" 1923;
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
	setAttr ".fprt" yes;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 3 ".st";
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
	setAttr -s 5 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 4 ".u";
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
connectAttr "polyPlane1.out" "pPlaneShape1.i";
connectAttr "polyPlane2.out" "pPlaneShape2.i";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "GLSLShader1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "GLSLShader1SG.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "file1.oc" "GLSLShader1.u_DiffuseEnvTexture";
connectAttr "file2.oc" "GLSLShader1.u_SpecularEnvTexture";
connectAttr "file3.oc" "GLSLShader1.u_brdfTexture";
connectAttr "pPlane1_BaseColorTexture.oc" "GLSLShader1.u_BaseColorTexture";
connectAttr "pPlane1_BaseColorTexture.oa" "GLSLShader1.u_BaseAlphaTextureR";
connectAttr ":defaultColorMgtGlobals.cme" "file1.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "file1.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "file1.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "file1.ws";
connectAttr "place2dTexture1.c" "file1.c";
connectAttr "place2dTexture1.tf" "file1.tf";
connectAttr "place2dTexture1.rf" "file1.rf";
connectAttr "place2dTexture1.mu" "file1.mu";
connectAttr "place2dTexture1.mv" "file1.mv";
connectAttr "place2dTexture1.s" "file1.s";
connectAttr "place2dTexture1.wu" "file1.wu";
connectAttr "place2dTexture1.wv" "file1.wv";
connectAttr "place2dTexture1.re" "file1.re";
connectAttr "place2dTexture1.r" "file1.ro";
connectAttr "place2dTexture1.of" "file1.of";
connectAttr "place2dTexture1.n" "file1.n";
connectAttr "place2dTexture1.vt1" "file1.vt1";
connectAttr "place2dTexture1.vt2" "file1.vt2";
connectAttr "place2dTexture1.vt3" "file1.vt3";
connectAttr "place2dTexture1.vc1" "file1.vc1";
connectAttr "place2dTexture1.o" "file1.uv";
connectAttr "place2dTexture1.ofs" "file1.fs";
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
connectAttr "place2dTexture2.r" "file2.ro";
connectAttr "place2dTexture2.of" "file2.of";
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
connectAttr "place2dTexture3.r" "file3.ro";
connectAttr "place2dTexture3.of" "file3.of";
connectAttr "place2dTexture3.n" "file3.n";
connectAttr "place2dTexture3.vt1" "file3.vt1";
connectAttr "place2dTexture3.vt2" "file3.vt2";
connectAttr "place2dTexture3.vt3" "file3.vt3";
connectAttr "place2dTexture3.vc1" "file3.vc1";
connectAttr "place2dTexture3.o" "file3.uv";
connectAttr "place2dTexture3.ofs" "file3.fs";
connectAttr "GLSLShader1.oc" "GLSLShader1SG.ss";
connectAttr "pPlaneShape1.iog" "GLSLShader1SG.dsm" -na;
connectAttr "GLSLShader1SG.msg" "materialInfo1.sg";
connectAttr "GLSLShader1.msg" "materialInfo1.m";
connectAttr ":defaultColorMgtGlobals.cme" "pPlane1_BaseColorTexture.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "pPlane1_BaseColorTexture.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "pPlane1_BaseColorTexture.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "pPlane1_BaseColorTexture.ws";
connectAttr "place2dTexture4.c" "pPlane1_BaseColorTexture.c";
connectAttr "place2dTexture4.tf" "pPlane1_BaseColorTexture.tf";
connectAttr "place2dTexture4.rf" "pPlane1_BaseColorTexture.rf";
connectAttr "place2dTexture4.mu" "pPlane1_BaseColorTexture.mu";
connectAttr "place2dTexture4.mv" "pPlane1_BaseColorTexture.mv";
connectAttr "place2dTexture4.s" "pPlane1_BaseColorTexture.s";
connectAttr "place2dTexture4.wu" "pPlane1_BaseColorTexture.wu";
connectAttr "place2dTexture4.wv" "pPlane1_BaseColorTexture.wv";
connectAttr "place2dTexture4.re" "pPlane1_BaseColorTexture.re";
connectAttr "place2dTexture4.of" "pPlane1_BaseColorTexture.of";
connectAttr "place2dTexture4.r" "pPlane1_BaseColorTexture.ro";
connectAttr "place2dTexture4.n" "pPlane1_BaseColorTexture.n";
connectAttr "place2dTexture4.vt1" "pPlane1_BaseColorTexture.vt1";
connectAttr "place2dTexture4.vt2" "pPlane1_BaseColorTexture.vt2";
connectAttr "place2dTexture4.vt3" "pPlane1_BaseColorTexture.vt3";
connectAttr "place2dTexture4.vc1" "pPlane1_BaseColorTexture.vc1";
connectAttr "place2dTexture4.o" "pPlane1_BaseColorTexture.uv";
connectAttr "place2dTexture4.ofs" "pPlane1_BaseColorTexture.fs";
connectAttr "place2dTexture3.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[0].dn"
		;
connectAttr "GLSLShader1SG.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[1].dn"
		;
connectAttr "pPlane1_BaseColorTexture.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[2].dn"
		;
connectAttr "place2dTexture1.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[3].dn"
		;
connectAttr "file2.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[4].dn"
		;
connectAttr "place2dTexture4.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[5].dn"
		;
connectAttr "place2dTexture2.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[6].dn"
		;
connectAttr "GLSLShader1.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[7].dn"
		;
connectAttr "file3.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[8].dn"
		;
connectAttr "file1.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[9].dn"
		;
connectAttr "GLSLShader1SG.pa" ":renderPartition.st" -na;
connectAttr "GLSLShader1.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture2.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture3.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture4.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "file2.msg" ":defaultTextureList1.tx" -na;
connectAttr "file3.msg" ":defaultTextureList1.tx" -na;
connectAttr "pPlane1_BaseColorTexture.msg" ":defaultTextureList1.tx" -na;
connectAttr "pPlaneShape2.iog" ":initialShadingGroup.dsm" -na;
// End of TransparentPlane.ma
