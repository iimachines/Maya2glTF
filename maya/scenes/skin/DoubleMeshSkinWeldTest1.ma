//Maya ASCII 2018 scene
//Name: DoubleMeshSkinWeldTest1.ma
//Last modified: Fri, Mar 16, 2018 08:32:46 PM
//Codeset: 1252
requires maya "2018";
requires "stereoCamera" "10.0";
requires "stereoCamera" "10.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2018";
fileInfo "version" "2018";
fileInfo "cutIdentifier" "201706261615-f9658c4cfc";
fileInfo "osv" "Microsoft Windows 8 Business Edition, 64-bit  (Build 9200)\n";
createNode transform -s -n "persp";
	rename -uid "DDE980E5-41DB-F102-AA3E-1D9878B2ADEF";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -0.02667633843383399 4.2268684171717661 7.6756769863598322 ;
	setAttr ".r" -type "double3" -14.738352729612368 -0.19999999999979387 8.5415807238037448e-16 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "F21D88BF-4355-5C8D-C41F-05B5C4B08622";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 7.9022251227507265;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" 0 2.2165000000000004 0.0335 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "242DD70A-4917-9D04-9466-BC8FD9F79142";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 1000.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "A187C64E-42F5-C640-B6DC-55A9F1AC5F16";
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
	rename -uid "FC607962-4170-B05F-5796-4EAA8A5FC84F";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 3 1000.104499539923 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "C76E3A00-4AF8-8472-A83B-47AC3B0E5D31";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.104499539923;
	setAttr ".ow" 15.482036214052229;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".tp" -type "double3" 0 3 0 ;
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	rename -uid "4A01B99E-4B22-BB0D-8C2C-4EB309078DB4";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "95EE3903-4164-AB02-362C-18B55EB39C3C";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "tri1";
	rename -uid "3966D4D7-4628-ACF9-2FEB-378DCB874F61";
	setAttr ".t" -type "double3" 0 1 0 ;
	setAttr -l on ".tx";
	setAttr -l on ".ty";
	setAttr -l on ".tz";
	setAttr -l on ".rx";
	setAttr -l on ".ry";
	setAttr -l on ".rz";
	setAttr -l on ".sx";
	setAttr -l on ".sy";
	setAttr -l on ".sz";
createNode mesh -n "triShape1" -p "tri1";
	rename -uid "CFC299B4-40C4-13E5-C9E1-DBB318292A86";
	setAttr -k off ".v";
	setAttr -s 4 ".iog[0].og";
	setAttr -av ".iog[0].og[0].gco";
	setAttr -av ".iog[0].og[1].gco";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.5 0.125 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".vcs" 2;
createNode mesh -n "triShape1Orig1" -p "tri1";
	rename -uid "6D7D9E02-45C9-92ED-3EF4-8496EC1FBA92";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 3 ".uvst[0].uvsp[0:2]" -type "float2" 0.5 0 0.375 0.25
		 0.625 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 3 ".vt[0:2]"  0 -1 0.5 -0.5 1 0.5 0.5 1 0.5;
	setAttr -s 3 ".ed[0:2]"  1 2 0 0 1 0 0 2 0;
	setAttr -ch 3 ".fc[0]" -type "polyFaces" 
		f 3 2 -1 -2
		mu 0 3 0 2 1;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".vcs" 2;
createNode transform -n "tri2";
	rename -uid "428E277D-4B2F-D9B5-99CF-0E89DA6EBF46";
	setAttr ".t" -type "double3" 0 3 0 ;
	setAttr -l on ".tx";
	setAttr -l on ".ty";
	setAttr -l on ".tz";
	setAttr -l on ".rx";
	setAttr -l on ".ry";
	setAttr -l on ".rz";
	setAttr -l on ".sx";
	setAttr -l on ".sy";
	setAttr -l on ".sz";
createNode mesh -n "triShape2" -p "tri2";
	rename -uid "25A2E7F8-4195-39D5-2DE4-3C8C0EDA9504";
	setAttr -k off ".v";
	setAttr -s 2 ".iog";
	setAttr -s 4 ".iog[0].og";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.5 0.125 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".vcs" 2;
createNode mesh -n "triShape2Orig2" -p "tri2";
	rename -uid "96EE8EA3-4C66-7284-2FB2-B1962A5E7F31";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 3 ".uvst[0].uvsp[0:2]" -type "float2" 0.375 0 0.625 0 0.5
		 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 3 ".vt[0:2]"  -0.5 -1 0.5 0.5 -1 0.5 0 1 0.5;
	setAttr -s 3 ".ed[0:2]"  0 1 0 0 2 0 1 2 0;
	setAttr -ch 3 ".fc[0]" -type "polyFaces" 
		f 3 2 -2 0
		mu 0 3 1 2 0;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".vcs" 2;
createNode joint -n "joint1";
	rename -uid "7ED63555-420F-3F3D-2136-72A89B138E86";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".uoc" 1;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 0 0 89.999999999999986 ;
	setAttr ".bps" -type "matrix" 2.2204460492503131e-16 1 0 0 -1 2.2204460492503131e-16 0 0
		 0 0 1 0 0 0 0 1;
	setAttr ".radi" 0.5;
createNode joint -n "joint2" -p "joint1";
	rename -uid "153C6B7D-4985-8DB6-0A6C-ABA88C57A56B";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".uoc" 1;
	setAttr ".oc" 1;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".bps" -type "matrix" 2.2204460492503131e-16 1.0000000000000002 0 0 -1.0000000000000002 2.2204460492503131e-16 0 0
		 0 0 1 0 0 1 0 1;
	setAttr ".radi" 0.5;
createNode joint -n "joint3" -p "joint2";
	rename -uid "72083376-4570-8D24-C3F7-2C8A3B65D02C";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".uoc" 1;
	setAttr ".oc" 2;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".bps" -type "matrix" 2.2204460492503131e-16 1.0000000000000002 0 0 -1.0000000000000002 2.2204460492503131e-16 0 0
		 0 0 1 0 0 2 0 1;
	setAttr ".radi" 0.5;
createNode joint -n "joint4" -p "joint3";
	rename -uid "0FC1DC8C-445D-F574-6A79-E2B9ED536E01";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".uoc" 1;
	setAttr ".oc" 3;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".bps" -type "matrix" 2.2204460492503131e-16 1.0000000000000002 0 0 -1.0000000000000002 2.2204460492503131e-16 0 0
		 0 0 1 0 0 3 0 1;
	setAttr ".radi" 0.5;
createNode joint -n "joint5" -p "joint4";
	rename -uid "0AA1F921-4F97-D247-5907-1E9643130B01";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".uoc" 1;
	setAttr ".oc" 4;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 0 0 -89.999999999999986 ;
	setAttr ".bps" -type "matrix" 1.0000000000000002 4.9303806576313238e-32 0 0 -4.9303806576313238e-32 1.0000000000000002 0 0
		 0 0 1 0 0 4 0 1;
	setAttr ".radi" 0.5;
createNode transform -n "cube3";
	rename -uid "47DCC292-4CC6-672E-F6B3-C2A5B88F1A66";
	setAttr ".t" -type "double3" 0 2 0 ;
	setAttr -l on ".tx";
	setAttr -l on ".ty";
	setAttr -l on ".tz";
	setAttr -l on ".rx";
	setAttr -l on ".ry";
	setAttr -l on ".rz";
	setAttr -l on ".sx";
	setAttr -l on ".sy";
	setAttr -l on ".sz";
createNode mesh -n "cubeShape3" -p "cube3";
	rename -uid "356F8090-4E66-82F5-DA0F-3290A0AA8AD7";
	setAttr -k off ".v";
	setAttr -s 4 ".iog[0].og";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".vcs" 2;
createNode mesh -n "cubeShape3Orig3" -p "cube3";
	rename -uid "C7CFE1CB-4387-F365-B5CD-D6A749945FCF";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "E07E60F5-4E72-A55C-73B5-66B7341532EE";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "71054B34-4FF5-D7DE-19D0-689B19EF7059";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "3BF60E4A-4A2B-002F-404F-F5AF73DFBF85";
createNode displayLayerManager -n "layerManager";
	rename -uid "01C88B0E-40F2-20CC-0D80-419DCF0A7869";
createNode displayLayer -n "defaultLayer";
	rename -uid "8A2609F5-4BA4-3390-FEC8-7CACD700422B";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "C7D8D95A-43DB-6928-3DFF-C7AA86B5B915";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "7B4B4B3E-4067-5379-7D47-838C914EF973";
	setAttr ".g" yes;
createNode dagPose -n "bindPose1";
	rename -uid "7343CDA4-4880-AB7D-E3C1-D7BB402E40AB";
	setAttr -s 5 ".wm";
	setAttr -s 6 ".xm";
	setAttr ".xm[0]" -type "matrix" "xform" 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 1 0 0 0.70710678118654746 0.70710678118654757 1 1 1 yes;
	setAttr ".xm[1]" -type "matrix" "xform" 1 1 1 0 0 0 0 0.99999999999999978 2.2204460492503121e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 yes;
	setAttr ".xm[2]" -type "matrix" "xform" 1 1 1 0 0 0 0 0.99999999999999978 2.2204460492503121e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 yes;
	setAttr ".xm[3]" -type "matrix" "xform" 1 1 1 0 0 0 0 0.99999999999999956 2.2204460492503111e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 yes;
	setAttr ".xm[4]" -type "matrix" "xform" 1 1 1 0 0 0 0 0.99999999999999978 2.2204460492503121e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 -0.70710678118654746 0.70710678118654768 1
		 1 1 yes;
	setAttr ".xm[5]" -type "matrix" "xform" 1 1 1 0 0 0 0 1 2.2204460492503121e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 -0.70710678118654746 0.70710678118654768 1
		 1 1 yes;
	setAttr -s 5 ".m";
	setAttr -s 5 ".p";
	setAttr -s 6 ".g[3:5]" yes no no;
	setAttr ".bp" yes;
createNode skinCluster -n "skinCluster2";
	rename -uid "ABE68579-4F06-BDBB-8A28-AEB5366589FE";
	setAttr -s 12 ".wl";
	setAttr ".wl[0:11].w"
		2 1 0.5 2 0.5
		2 1 0.5 2 0.5
		2 3 0.5 4 0.5
		2 3 0.5 4 0.5
		2 3 0.5 4 0.5
		2 3 0.5 4 0.5
		2 3 0.5 4 0.5
		2 3 0.5 4 0.5
		2 2 0.5 3 0.5
		2 2 0.5 3 0.5
		2 1 0.5 2 0.5
		2 1 0.5 2 0.5;
	setAttr -s 5 ".pm";
	setAttr ".pm[0]" -type "matrix" 2.2204460492503121e-16 -0.99999999999999978 0 0 0.99999999999999978 2.2204460492503121e-16 0 0
		 0 0 1 0 0 0 0 1;
	setAttr ".pm[1]" -type "matrix" 2.2204460492503121e-16 -0.99999999999999978 0 0 0.99999999999999978 2.2204460492503121e-16 0 0
		 0 0 1 0 -0.99999999999999978 -2.2204460492503121e-16 0 1;
	setAttr ".pm[2]" -type "matrix" 2.2204460492503121e-16 -0.99999999999999978 0 0 0.99999999999999978 2.2204460492503121e-16 0 0
		 0 0 1 0 -1.9999999999999996 -4.4408920985006242e-16 0 1;
	setAttr ".pm[3]" -type "matrix" 2.2204460492503121e-16 -0.99999999999999978 0 0 0.99999999999999978 2.2204460492503121e-16 0 0
		 0 0 1 0 -2.9999999999999996 -6.6613381477509363e-16 0 1;
	setAttr ".pm[4]" -type "matrix" 0.99999999999999956 0 0 0 0 0.99999999999999956 0 0
		 0 0 1 0 0 -3.9999999999999982 0 1;
	setAttr ".gm" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 3 0 1;
	setAttr -s 4 ".ma";
	setAttr -s 5 ".dpf[0:4]"  4 4 4 4 4;
	setAttr -s 4 ".lw";
	setAttr -s 4 ".lw";
	setAttr ".mmi" yes;
	setAttr ".ucm" yes;
	setAttr -s 4 ".ifcl";
	setAttr -s 4 ".ifcl";
createNode tweak -n "tweak2";
	rename -uid "8D288178-4101-B391-5E6A-70A3EE6F83C4";
	setAttr -s 3 ".vl[0].vt[0:2]" -type "float3"  0 0 -0.5 0 0 -0.5 
		0 0 -0.5;
createNode objectSet -n "skinCluster2Set";
	rename -uid "D0F565FD-4604-A606-91C1-D28EEF91A995";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "skinCluster2GroupId";
	rename -uid "B20DFFBE-4876-9FEE-1099-C9B63701A900";
	setAttr ".ihi" 0;
createNode groupParts -n "skinCluster2GroupParts";
	rename -uid "9E81CE9E-47AA-4724-0274-B2A452E577B3";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[0:2]";
	setAttr ".irc" -type "componentList" 1 "vtx[3:11]";
createNode objectSet -n "tweakSet2";
	rename -uid "956F99E6-4432-B9D6-42ED-F79836F7E8F0";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "groupId4";
	rename -uid "5A7BE6A4-44FB-ECC7-6864-74AB1BE77F85";
	setAttr ".ihi" 0;
createNode groupParts -n "groupParts4";
	rename -uid "6584208F-4B36-6F18-6FDD-23AF15575FF8";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode animCurveTA -n "joint5_rotateZ";
	rename -uid "EB462DF0-49BA-5EF5-38EF-09AD32A66C86";
	setAttr ".tan" 18;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "joint1_rotateZ";
	rename -uid "F50215B0-40EE-93F4-7BB0-6A9F71BD1C72";
	setAttr ".tan" 18;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "joint2_rotateZ";
	rename -uid "485B86CE-48AB-8DED-DA9F-B08F7A060315";
	setAttr ".tan" 18;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "joint3_rotateZ";
	rename -uid "694C92ED-42D0-737A-C37A-CF9B08EB5DE4";
	setAttr ".tan" 18;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTA -n "joint4_rotateZ";
	rename -uid "A9447B54-4B2B-6B21-0EC8-F7BF828A4D29";
	setAttr ".tan" 18;
	setAttr ".ktv[0]"  1 0;
createNode character -n "character1";
	rename -uid "8F6F61B3-4317-DD50-CA7A-5F94DD72C52D";
	addAttr -ci true -h true -sn "aal" -ln "attributeAliasList" -dt "attributeAlias";
	setAttr -s 30 ".dnsm";
	setAttr -s 15 ".lv[2:15]"  2.2204460492503121e-16 0.99999999999999978 
		0 2.2204460492503121e-16 0.99999999999999978 0 2.2204460492503121e-16 0.99999999999999978 
		0 2.2204460492503121e-16 0.99999999999999978 0 0 0;
	setAttr -s 15 ".lv";
	setAttr -s 15 ".av";
	setAttr -s 15 ".av";
	setAttr ".am" -type "characterMapping" 30 "joint5.rotateZ" 2 1 "joint5.rotateY" 
		2 2 "joint5.rotateX" 2 3 "joint5.translateZ" 1 1 "joint5.translateY" 
		1 2 "joint5.translateX" 1 3 "joint4.rotateZ" 2 4 "joint4.rotateY" 
		2 5 "joint4.rotateX" 2 6 "joint4.translateZ" 1 4 "joint4.translateY" 
		1 5 "joint4.translateX" 1 6 "joint3.rotateZ" 2 7 "joint3.rotateY" 
		2 8 "joint3.rotateX" 2 9 "joint3.translateZ" 1 7 "joint3.translateY" 
		1 8 "joint3.translateX" 1 9 "joint2.rotateZ" 2 10 "joint2.rotateY" 
		2 11 "joint2.rotateX" 2 12 "joint2.translateZ" 1 10 "joint2.translateY" 
		1 11 "joint2.translateX" 1 12 "joint1.rotateZ" 2 13 "joint1.rotateY" 
		2 14 "joint1.rotateX" 2 15 "joint1.translateZ" 1 13 "joint1.translateY" 
		1 14 "joint1.translateX" 1 15  ;
	setAttr ".cim" -type "Int32Array" 30 0 1 2 3 4 5
		 6 7 8 9 10 11 12 13 14 15 16 17
		 18 19 20 21 22 23 24 25 26 27 28 29 ;
	setAttr ".tcs" 10;
	setAttr ".tce" 10;
	setAttr ".aal" -type "attributeAlias" {"joint2_rotateZ","angularValues[10]","joint2_rotateY"
		,"angularValues[11]","joint2_rotateX","angularValues[12]","joint1_rotateZ","angularValues[13]"
		,"joint1_rotateY","angularValues[14]","joint1_rotateX","angularValues[15]","joint5_rotateZ"
		,"angularValues[1]","joint5_rotateY","angularValues[2]","joint5_rotateX","angularValues[3]"
		,"joint4_rotateZ","angularValues[4]","joint4_rotateY","angularValues[5]","joint4_rotateX"
		,"angularValues[6]","joint3_rotateZ","angularValues[7]","joint3_rotateY","angularValues[8]"
		,"joint3_rotateX","angularValues[9]","joint2_translateZ","linearValues[10]","joint2_translateY"
		,"linearValues[11]","joint2_translateX","linearValues[12]","joint1_translateZ","linearValues[13]"
		,"joint1_translateY","linearValues[14]","joint1_translateX","linearValues[15]","joint5_translateZ"
		,"linearValues[1]","joint5_translateY","linearValues[2]","joint5_translateX","linearValues[3]"
		,"joint4_translateZ","linearValues[4]","joint4_translateY","linearValues[5]","joint4_translateX"
		,"linearValues[6]","joint3_translateZ","linearValues[7]","joint3_translateY","linearValues[8]"
		,"joint3_translateX","linearValues[9]"} ;
createNode clipScheduler -n "character1Scheduler1";
	rename -uid "9F6105F9-451D-9353-34C0-F28C511F3BBF";
	setAttr -s 2 ".cl";
	setAttr -s 2 ".st";
	setAttr -s 2 ".st";
	setAttr -s 2 ".ss";
	setAttr -s 2 ".ss";
	setAttr -s 2 ".se";
	setAttr -s 2 ".se";
	setAttr -s 2 ".sc";
	setAttr -s 2 ".sc";
	setAttr -s 2 ".h";
	setAttr -s 2 ".h";
	setAttr -s 2 ".w";
	setAttr -s 2 ".w";
	setAttr -s 2 ".ws";
	setAttr -s 2 ".ws";
	setAttr -s 2 ".cb";
	setAttr -s 2 ".cb";
	setAttr -s 2 ".ca";
	setAttr -s 2 ".ca";
	setAttr -s 2 ".ea";
	setAttr -s 2 ".ea";
	setAttr -s 2 ".tr[0:1]"  1 1;
	setAttr ".nt" 1;
createNode clipLibrary -n "character1Clips1";
	rename -uid "1B5FC997-4B86-AD1E-43A4-74B88C027C30";
	setAttr -s 2 ".cel";
	setAttr -s 5 ".cel[0].cev";
	setAttr -s 5 ".cel[1].cev";
	setAttr -s 2 ".sc";
	setAttr -s 2 ".cl";
createNode animClip -n "NEUTRALSource";
	rename -uid "6265904D-4A14-7F54-70FC-B591E9CBDBF0";
	setAttr ".ihi" 0;
	setAttr ".se" 1;
	setAttr ".ci" no;
createNode animClip -n "NEUTRAL";
	rename -uid "47C3AC07-4D7C-0D4E-ABFB-E2854068BAFF";
	setAttr -s 30 ".ac[0:29]" yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 1;
createNode animCurveTA -n "character1_joint5_rotateZ";
	rename -uid "21AEB727-4D64-2CD6-2BDA-C4960B0B4739";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  10 36;
	setAttr ".kix[0]"  4.125;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  4.125;
	setAttr ".koy[0]"  0;
createNode animCurveTA -n "character1_joint4_rotateZ";
	rename -uid "F5F4BCEE-474C-40EC-1A72-47A80D2FCE91";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  10 36;
	setAttr ".kix[0]"  4.125;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  4.125;
	setAttr ".koy[0]"  0;
createNode animCurveTA -n "character1_joint3_rotateZ";
	rename -uid "3E2A2CA2-451A-0445-DF0E-0D8949806D60";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  10 36;
	setAttr ".kix[0]"  4.125;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  4.125;
	setAttr ".koy[0]"  0;
createNode animCurveTA -n "character1_joint2_rotateZ";
	rename -uid "4304D02C-47FC-E6AB-D07E-11A4AD5E61C6";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  10 36;
	setAttr ".kix[0]"  4.125;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  4.125;
	setAttr ".koy[0]"  0;
createNode animCurveTA -n "character1_joint1_rotateZ";
	rename -uid "776CE520-4F24-4890-81A8-5E94899ABE96";
	setAttr ".tan" 1;
	setAttr ".ktv[0]"  10 36;
	setAttr ".kix[0]"  4.125;
	setAttr ".kiy[0]"  0;
	setAttr ".kox[0]"  4.125;
	setAttr ".koy[0]"  0;
createNode animClip -n "TWISTSource";
	rename -uid "B2F4792A-46C8-67AC-AE56-4EB0E9719D26";
	setAttr ".ihi" 0;
	setAttr ".ss" 10;
	setAttr ".se" 11;
	setAttr ".ci" no;
createNode animClip -n "TWIST";
	rename -uid "74A2C558-4260-6CEA-0BD5-E48A49CA4B05";
	setAttr -s 30 ".ac[0:29]" yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".sf" 2;
	setAttr ".ss" 10;
	setAttr ".se" 11;
createNode script -n "uiConfigurationScriptNode";
	rename -uid "A6C69AA2-41A9-2C6F-093B-168F74D8491E";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n"
		+ "            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 4 4 \n"
		+ "            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n"
		+ "            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1585\n            -height 508\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 0\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n"
		+ "            -grid 0\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 524\n            -height 508\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n"
		+ "\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n"
		+ "            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n"
		+ "            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 525\n            -height 508\n"
		+ "            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"perspective\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"perspective\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 0\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n"
		+ "            -backfaceCulling 0\n            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 0\n"
		+ "            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 0\n            -polymeshes 1\n            -subdivSurfaces 0\n            -planes 0\n            -lights 0\n            -cameras 0\n            -controlVertices 0\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 0\n            -ikHandles 0\n            -deformers 0\n            -dynamics 0\n            -particleInstancers 1\n            -fluids 0\n            -hairSystems 0\n            -follicles 0\n            -nCloths 0\n            -nParticles 1\n            -nRigids 0\n            -dynamicConstraints 0\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 0\n"
		+ "            -handles 0\n            -pivots 0\n            -textures 0\n            -strokes 0\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 0\n            -height 0\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"ToggledOutliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"ToggledOutliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n"
		+ "            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n"
		+ "            -isSet 0\n            -isSetMember 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            -renderFilterIndex 0\n            -selectionOrder \"chronological\" \n            -expandAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" != $panelName) {\n"
		+ "\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n"
		+ "            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -isSet 0\n            -isSetMember 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n"
		+ "            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            -renderFilterIndex 0\n            -selectionOrder \"chronological\" \n            -expandAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n"
		+ "                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 1\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n"
		+ "                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 1\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n"
		+ "                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -showCurveNames 0\n                -showActiveCurveNames 0\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 1\n                -classicMode 1\n                -valueLinesToggle 1\n                -outliner \"graphEditor1OutlineEd\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 1\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n"
		+ "                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n"
		+ "                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"timeEditorPanel\" (localizedPanelLabel(\"Time Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Time Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 1\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n"
		+ "                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"shapePanel\" (localizedPanelLabel(\"Shape Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tshapePanel -edit -l (localizedPanelLabel(\"Shape Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"posePanel\" (localizedPanelLabel(\"Pose Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tposePanel -edit -l (localizedPanelLabel(\"Pose Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"profilerPanel\" (localizedPanelLabel(\"Profiler Tool\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"contentBrowserPanel\" (localizedPanelLabel(\"Content Browser\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Content Browser\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"Stereo\" (localizedPanelLabel(\"Stereo\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels  $panelName;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -editorChanged \"updateModelPanelBar\" \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -holdOuts 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n"
		+ "                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 32768\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -depthOfFieldPreview 1\n                -maxConstantTransparency 1\n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n"
		+ "                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -controllers 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n"
		+ "                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -captureSequenceNumber -1\n                -width 0\n                -height 0\n                -sceneRenderFilter 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                -useCustomBackground 1\n                $editorName;\n            stereoCameraView -e -viewSelected 0 $editorName;\n            stereoCameraView -e \n                -pluginObjects \"gpuCacheDisplayFilter\" 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n"
		+ "            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 4 4 \n            -bumpResolution 4 4 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n"
		+ "            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1585\n            -height 1060\n"
		+ "            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -highlightConnections 0\n                -copyConnectionsOnPaste 0\n                -connectionStyle \"bezier\" \n"
		+ "                -connectionMinSegment 0.03\n                -connectionOffset 0.03\n                -connectionRoundness 0.8\n                -connectionTension -100\n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -activeTab 0\n                -editorMode \"default\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n"
		+ "        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-userCreated false\n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 1\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 4 4 \\n    -bumpResolution 4 4 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1585\\n    -height 1060\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 1\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 4 4 \\n    -bumpResolution 4 4 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1585\\n    -height 1060\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 1 -size 10 -divisions 4 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"1 -0.019419 1.088376 4.466232 0.095292 1.011479 -0.228114 0.000400 0.999866 -0.016369 0.000000 0.000000 0.000000 27.216112 18.924645 0 0 1\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "CFCA14B7-4C5A-978C-7A25-3B97EE7B9502";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
createNode skinCluster -n "skinCluster1";
	rename -uid "185F464A-4F44-7B0B-2178-68B9CDBF364F";
	setAttr -s 12 ".wl";
	setAttr ".wl[0:11].w"
		2 0 0.89999999999999991 1 0.10000000000000006
		2 1 0.5 2 0.5
		2 1 0.5 2 0.5
		2 1 0.5 2 0.5
		2 1 0.5 2 0.5
		2 1 0.5 2 0.5
		2 1 0.5 2 0.5
		2 1 0.5 2 0.5
		2 0 0.5 1 0.5
		2 0 0.5 1 0.5
		2 0 0.89999999999999991 1 0.10000000000000006
		2 0 0.89999999999999991 1 0.10000000000000006;
	setAttr -s 5 ".pm";
	setAttr ".pm[0]" -type "matrix" 2.2204460492503121e-16 -0.99999999999999978 0 0 0.99999999999999978 2.2204460492503121e-16 0 0
		 0 0 1 0 0 0 0 1;
	setAttr ".pm[1]" -type "matrix" 2.2204460492503121e-16 -0.99999999999999978 0 0 0.99999999999999978 2.2204460492503121e-16 0 0
		 0 0 1 0 -0.99999999999999978 -2.2204460492503121e-16 0 1;
	setAttr ".pm[2]" -type "matrix" 2.2204460492503121e-16 -0.99999999999999978 0 0 0.99999999999999978 2.2204460492503121e-16 0 0
		 0 0 1 0 -1.9999999999999996 -4.4408920985006242e-16 0 1;
	setAttr ".pm[3]" -type "matrix" 2.2204460492503121e-16 -0.99999999999999978 0 0 0.99999999999999978 2.2204460492503121e-16 0 0
		 0 0 1 0 -2.9999999999999996 -6.6613381477509363e-16 0 1;
	setAttr ".pm[4]" -type "matrix" 0.99999999999999956 0 0 0 0 0.99999999999999956 0 0
		 0 0 1 0 0 -3.9999999999999982 0 1;
	setAttr ".gm" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr -s 3 ".ma";
	setAttr -s 5 ".dpf[0:4]"  4 4 4 4 4;
	setAttr -s 3 ".lw";
	setAttr -s 3 ".lw";
	setAttr ".mmi" yes;
	setAttr ".ucm" yes;
	setAttr -s 3 ".ifcl";
	setAttr -s 3 ".ifcl";
createNode groupParts -n "skinCluster1GroupParts";
	rename -uid "B0292E27-4871-0E13-ED20-A4A03484A35A";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[0:2]";
	setAttr ".irc" -type "componentList" 1 "vtx[3:11]";
createNode groupId -n "skinCluster1GroupId";
	rename -uid "9E546784-4BC7-139E-EC81-F48189F6F28E";
	setAttr ".ihi" 0;
createNode objectSet -n "skinCluster1Set";
	rename -uid "0468DE4B-4FE0-8C1C-8CE7-3B8E69D4B2EF";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode tweak -n "tweak1";
	rename -uid "05F7719C-4938-F8F0-9718-78955320BA9B";
	setAttr -s 3 ".vl[0].vt[0:2]" -type "float3"  0 0 -0.5 0 0 -0.5 
		0 0 -0.5;
createNode groupParts -n "groupParts2";
	rename -uid "2753CDB3-466C-A929-90AB-8DB3BA7E49F4";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode groupId -n "groupId2";
	rename -uid "9BCA8C57-4F5F-F57E-6A1E-E5A43C5BBDC3";
	setAttr ".ihi" 0;
createNode objectSet -n "tweakSet1";
	rename -uid "282EE377-4818-35B4-E086-B89D17409DE6";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode phong -n "phong1";
	rename -uid "A6EC3C54-4F3F-9855-1285-5E93496228C6";
	setAttr ".c" -type "float3" 0 1 0 ;
createNode shadingEngine -n "phong1SG";
	rename -uid "EE9C6877-44D8-12A0-E051-3BA6CB848F1F";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
	rename -uid "0213192C-407B-2F6F-DA87-7B9F2B579394";
createNode phong -n "phong2";
	rename -uid "B2D5B810-4A6B-C560-E722-0BA459DB24DE";
	setAttr ".c" -type "float3" 1 0 0 ;
createNode shadingEngine -n "phong2SG";
	rename -uid "CD81862A-4106-FF53-6A54-3083A1A058FB";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
	rename -uid "60987E05-40F0-2F73-6CDB-63B79CA96B7D";
createNode polyCube -n "polyCube1";
	rename -uid "A19873D3-49A3-0E4C-85AD-B790F79E5CC3";
	setAttr ".h" 4;
	setAttr ".sh" 8;
	setAttr ".cuv" 4;
createNode skinCluster -n "skinCluster3";
	rename -uid "578255EF-40C6-8B13-7853-FC9680DD9772";
	setAttr -s 36 ".wl";
	setAttr ".wl[0:35].w"
		5 0 0.88719718376608336 1 0.098577464862898215 2 0.010953051651433145 
		3 0.0024576099273298738 4 0.0008146897922553573
		5 0 0.88719718376608336 1 0.098577464862898215 2 0.010953051651433145 
		3 0.0024576099273298738 4 0.0008146897922553573
		5 0 0.6736151714395251 1 0.29938452063978926 2 0.022268270130232259 
		3 0.0036961051930838192 4 0.0010359325973695131
		5 0 0.6736151714395251 1 0.29938452063978926 2 0.022268270130232259 
		3 0.0036961051930838192 4 0.0010359325973695131
		5 0 0.47031669695848682 1 0.47031669695848671 2 0.052257410773165279 
		3 0.0058063789747961423 4 0.0013028163350650617
		5 0 0.47031669695848682 1 0.47031669695848671 2 0.052257410773165279 
		3 0.0058063789747961423 4 0.0013028163350650617
		5 0 0.23058870583529861 1 0.51882458812942234 2 0.23058870583529911 
		3 0.017151226053865241 4 0.0028467741461148037
		5 0 0.23058870583529861 1 0.51882458812942234 2 0.23058870583529911 
		3 0.017151226053865241 4 0.0028467741461148037
		5 0 0.049723756906077332 1 0.44751381215469621 2 0.44751381215469599 
		3 0.049723756906077485 4 0.0055248618784530463
		5 0 0.049723756906077332 1 0.44751381215469621 2 0.44751381215469599 
		3 0.049723756906077485 4 0.0055248618784530463
		5 0 0.016909347111319858 1 0.22733677782996684 2 0.51150775011742577 
		3 0.22733677782996764 4 0.016909347111319903
		5 0 0.016909347111319858 1 0.22733677782996684 2 0.51150775011742577 
		3 0.22733677782996764 4 0.016909347111319903
		5 0 0.005524861878453041 1 0.049723756906077297 2 0.44751381215469621 
		3 0.44751381215469599 4 0.049723756906077485
		5 0 0.005524861878453041 1 0.049723756906077297 2 0.44751381215469621 
		3 0.44751381215469599 4 0.049723756906077485
		5 0 0.0028467741461148011 1 0.017151226053865189 2 0.23058870583529834 
		3 0.51882458812942223 4 0.23058870583529942
		5 0 0.0028467741461148011 1 0.017151226053865189 2 0.23058870583529834 
		3 0.51882458812942223 4 0.23058870583529942
		5 0 0.0013028163350650615 1 0.0058063789747961345 2 0.052257410773165078 
		3 0.47031669695848682 4 0.47031669695848682
		5 0 0.0013028163350650615 1 0.0058063789747961345 2 0.052257410773165078 
		3 0.47031669695848682 4 0.47031669695848682
		5 0 0.0013028163350650615 1 0.0058063789747961345 2 0.052257410773165078 
		3 0.47031669695848682 4 0.47031669695848682
		5 0 0.0013028163350650615 1 0.0058063789747961345 2 0.052257410773165078 
		3 0.47031669695848682 4 0.47031669695848682
		5 0 0.0028467741461148011 1 0.017151226053865189 2 0.23058870583529834 
		3 0.51882458812942223 4 0.23058870583529942
		5 0 0.0028467741461148011 1 0.017151226053865189 2 0.23058870583529834 
		3 0.51882458812942223 4 0.23058870583529942
		5 0 0.005524861878453041 1 0.049723756906077297 2 0.44751381215469621 
		3 0.44751381215469599 4 0.049723756906077485
		5 0 0.005524861878453041 1 0.049723756906077297 2 0.44751381215469621 
		3 0.44751381215469599 4 0.049723756906077485
		5 0 0.016909347111319858 1 0.22733677782996684 2 0.51150775011742577 
		3 0.22733677782996764 4 0.016909347111319903
		5 0 0.016909347111319858 1 0.22733677782996684 2 0.51150775011742577 
		3 0.22733677782996764 4 0.016909347111319903
		5 0 0.049723756906077332 1 0.44751381215469621 2 0.44751381215469599 
		3 0.049723756906077485 4 0.0055248618784530463
		5 0 0.049723756906077332 1 0.44751381215469621 2 0.44751381215469599 
		3 0.049723756906077485 4 0.0055248618784530463
		5 0 0.23058870583529861 1 0.51882458812942234 2 0.23058870583529911 
		3 0.017151226053865241 4 0.0028467741461148037
		5 0 0.23058870583529861 1 0.51882458812942234 2 0.23058870583529911 
		3 0.017151226053865241 4 0.0028467741461148037
		5 0 0.47031669695848682 1 0.47031669695848671 2 0.052257410773165279 
		3 0.0058063789747961423 4 0.0013028163350650617
		5 0 0.47031669695848682 1 0.47031669695848671 2 0.052257410773165279 
		3 0.0058063789747961423 4 0.0013028163350650617
		5 0 0.6736151714395251 1 0.29938452063978926 2 0.022268270130232259 
		3 0.0036961051930838192 4 0.0010359325973695131
		5 0 0.6736151714395251 1 0.29938452063978926 2 0.022268270130232259 
		3 0.0036961051930838192 4 0.0010359325973695131
		5 0 0.88719718376608336 1 0.098577464862898215 2 0.010953051651433145 
		3 0.0024576099273298738 4 0.0008146897922553573
		5 0 0.88719718376608336 1 0.098577464862898215 2 0.010953051651433145 
		3 0.0024576099273298738 4 0.0008146897922553573;
	setAttr -s 5 ".pm";
	setAttr ".pm[0]" -type "matrix" 2.2204460492503131e-16 -1 0 -0 1 2.2204460492503131e-16 -0 0
		 0 -0 1 -0 -0 0 -0 1;
	setAttr ".pm[1]" -type "matrix" 2.2204460492503131e-16 -1 0 -0 1 2.2204460492503131e-16 -0 0
		 0 -0 1 -0 -0.99999999999999978 -2.2204460492503121e-16 -0 1;
	setAttr ".pm[2]" -type "matrix" 2.2204460492503131e-16 -1 0 -0 1 2.2204460492503131e-16 -0 0
		 0 -0 1 -0 -1.9999999999999996 -4.4408920985006242e-16 -0 1;
	setAttr ".pm[3]" -type "matrix" 2.2204460492503131e-16 -1 0 -0 1 2.2204460492503131e-16 -0 0
		 0 -0 1 -0 -2.9999999999999991 -6.6613381477509353e-16 -0 1;
	setAttr ".pm[4]" -type "matrix" 1 -0 0 -0 -0 1 -0 0 0 -0 1 -0 -1.9721522630525295e-31 -3.9999999999999991 -0 1;
	setAttr ".gm" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 2 0 1;
	setAttr -s 5 ".ma";
	setAttr -s 5 ".dpf[0:4]"  4 4 4 4 4;
	setAttr -s 5 ".lw";
	setAttr -s 5 ".lw";
	setAttr ".mmi" yes;
	setAttr ".mi" 5;
	setAttr ".ucm" yes;
	setAttr -s 5 ".ifcl";
	setAttr -s 5 ".ifcl";
createNode tweak -n "tweak3";
	rename -uid "1DF6E673-456B-2E31-1B02-64B04CB5857A";
createNode objectSet -n "skinCluster3Set";
	rename -uid "28E5E5FE-4469-C1E2-785F-1096600FDCEB";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "skinCluster3GroupId";
	rename -uid "645974D4-4DBE-1138-D50F-EEA64F637EE2";
	setAttr ".ihi" 0;
createNode groupParts -n "skinCluster3GroupParts";
	rename -uid "C53CF2DB-49A2-5374-1E06-ECA4B2CF04F5";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode objectSet -n "tweakSet3";
	rename -uid "08D7AEF3-453B-E547-AD61-2E8616C2FED3";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "groupId6";
	rename -uid "84D2E547-48BA-1D87-C952-3093C7147923";
	setAttr ".ihi" 0;
createNode groupParts -n "groupParts6";
	rename -uid "005823B1-4383-9487-CDB8-7E9654F49C70";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode nodeGraphEditorInfo -n "MayaNodeEditorSavedTabsInfo";
	rename -uid "281A8010-4D06-06B3-AE90-BC9BAD81B3F3";
	setAttr ".tgi[0].tn" -type "string" "Untitled_1";
	setAttr ".tgi[0].vl" -type "double2" -763.52820405209354 -691.01914058402315 ;
	setAttr ".tgi[0].vh" -type "double2" 940.96143589354176 715.01900598591715 ;
	setAttr -s 19 ".tgi[0].ni";
	setAttr ".tgi[0].ni[0].x" -157.14285278320313;
	setAttr ".tgi[0].ni[0].y" 352.85714721679688;
	setAttr ".tgi[0].ni[0].nvs" 18304;
	setAttr ".tgi[0].ni[1].x" 150;
	setAttr ".tgi[0].ni[1].y" 350;
	setAttr ".tgi[0].ni[1].nvs" 18305;
	setAttr ".tgi[0].ni[2].x" 764.28570556640625;
	setAttr ".tgi[0].ni[2].y" 285.71429443359375;
	setAttr ".tgi[0].ni[2].nvs" 18304;
	setAttr ".tgi[0].ni[3].x" -771.4285888671875;
	setAttr ".tgi[0].ni[3].y" -134.28572082519531;
	setAttr ".tgi[0].ni[3].nvs" 18304;
	setAttr ".tgi[0].ni[4].x" -771.4285888671875;
	setAttr ".tgi[0].ni[4].y" -32.857143402099609;
	setAttr ".tgi[0].ni[4].nvs" 18304;
	setAttr ".tgi[0].ni[5].x" 150;
	setAttr ".tgi[0].ni[5].y" 471.42855834960938;
	setAttr ".tgi[0].ni[5].nvs" 18304;
	setAttr ".tgi[0].ni[6].x" -771.4285888671875;
	setAttr ".tgi[0].ni[6].y" 170;
	setAttr ".tgi[0].ni[6].nvs" 18304;
	setAttr ".tgi[0].ni[7].x" 150;
	setAttr ".tgi[0].ni[7].y" -55.714286804199219;
	setAttr ".tgi[0].ni[7].nvs" 18304;
	setAttr ".tgi[0].ni[8].x" -157.14285278320313;
	setAttr ".tgi[0].ni[8].y" 251.42857360839844;
	setAttr ".tgi[0].ni[8].nvs" 18304;
	setAttr ".tgi[0].ni[9].x" 511.42855834960938;
	setAttr ".tgi[0].ni[9].y" -197.14285278320313;
	setAttr ".tgi[0].ni[9].nvs" 18304;
	setAttr ".tgi[0].ni[10].x" -157.14285278320313;
	setAttr ".tgi[0].ni[10].y" 150;
	setAttr ".tgi[0].ni[10].nvs" 18304;
	setAttr ".tgi[0].ni[11].x" 457.14285278320313;
	setAttr ".tgi[0].ni[11].y" 280;
	setAttr ".tgi[0].ni[11].nvs" 18304;
	setAttr ".tgi[0].ni[12].x" -771.4285888671875;
	setAttr ".tgi[0].ni[12].y" 68.571426391601563;
	setAttr ".tgi[0].ni[12].nvs" 18304;
	setAttr ".tgi[0].ni[13].x" 457.14285278320313;
	setAttr ".tgi[0].ni[13].y" -264.28570556640625;
	setAttr ".tgi[0].ni[13].nvs" 18304;
	setAttr ".tgi[0].ni[14].x" 764.28570556640625;
	setAttr ".tgi[0].ni[14].y" -264.28570556640625;
	setAttr ".tgi[0].ni[14].nvs" 18304;
	setAttr ".tgi[0].ni[15].x" -157.14285278320313;
	setAttr ".tgi[0].ni[15].y" 48.571430206298828;
	setAttr ".tgi[0].ni[15].nvs" 18304;
	setAttr ".tgi[0].ni[16].x" -464.28570556640625;
	setAttr ".tgi[0].ni[16].y" -52.857143402099609;
	setAttr ".tgi[0].ni[16].nvs" 18304;
	setAttr ".tgi[0].ni[17].x" 457.14285278320313;
	setAttr ".tgi[0].ni[17].y" -38.571430206298828;
	setAttr ".tgi[0].ni[17].nvs" 18304;
	setAttr ".tgi[0].ni[18].x" -157.14285278320313;
	setAttr ".tgi[0].ni[18].y" -110;
	setAttr ".tgi[0].ni[18].nvs" 18304;
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 1;
	setAttr ".unw" 1;
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
	setAttr -s 4 ".st";
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
	setAttr -s 6 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :lambert1;
	setAttr ".it" -type "float3" 0.47872341 0.47872341 0.47872341 ;
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
	setAttr -k on ".nds";
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
	setAttr ".btrs" 512;
	setAttr -k off ".fbfm";
	setAttr -k off -cb on ".ehql";
	setAttr -k off -cb on ".eams";
	setAttr -k off ".eeaa";
	setAttr -k off ".engm";
	setAttr -k off ".mes";
	setAttr -k off ".emb";
	setAttr -av -k off ".mbbf";
	setAttr -k off ".mbs";
	setAttr -k off ".trm";
	setAttr -k off -cb on ".tshc";
	setAttr -k off ".enpt";
	setAttr -k off ".clmt";
	setAttr -k off -cb on ".tcov";
	setAttr -k off -cb on ".lith";
	setAttr -k off -cb on ".sobc";
	setAttr -k off -cb on ".cuth";
	setAttr -k off -cb on ".hgcd";
	setAttr -k off -cb on ".hgci";
	setAttr -k off -cb on ".mgcs";
	setAttr -k off ".twa";
	setAttr -k off ".twz";
	setAttr -k on ".hwcc";
	setAttr -k on ".hwdp";
	setAttr -k on ".hwql";
select -ne :characterPartition;
connectAttr "skinCluster1Set.mwc" "triShape1.iog.og[0].gco";
connectAttr "skinCluster1GroupId.id" "triShape1.iog.og[0].gid";
connectAttr "tweakSet1.mwc" "triShape1.iog.og[1].gco";
connectAttr "groupId2.id" "triShape1.iog.og[1].gid";
connectAttr "skinCluster1.og[0]" "triShape1.i";
connectAttr "tweak1.vl[0].vt[2]" "triShape1.twl";
connectAttr "skinCluster2GroupId.id" "triShape2.iog.og[0].gid";
connectAttr "skinCluster2Set.mwc" "triShape2.iog.og[0].gco";
connectAttr "groupId4.id" "triShape2.iog.og[1].gid";
connectAttr "tweakSet2.mwc" "triShape2.iog.og[1].gco";
connectAttr "skinCluster2.og[0]" "triShape2.i";
connectAttr "tweak2.vl[0].vt[2]" "triShape2.twl";
connectAttr "character1.av[13]" "joint1.rz";
connectAttr "character1.av[14]" "joint1.ry";
connectAttr "character1.av[15]" "joint1.rx";
connectAttr "character1.lv[13]" "joint1.tz";
connectAttr "character1.lv[14]" "joint1.ty";
connectAttr "character1.lv[15]" "joint1.tx";
connectAttr "joint1.s" "joint2.is";
connectAttr "character1.av[10]" "joint2.rz";
connectAttr "character1.av[11]" "joint2.ry";
connectAttr "character1.av[12]" "joint2.rx";
connectAttr "character1.lv[10]" "joint2.tz";
connectAttr "character1.lv[11]" "joint2.ty";
connectAttr "character1.lv[12]" "joint2.tx";
connectAttr "joint2.s" "joint3.is";
connectAttr "character1.av[7]" "joint3.rz";
connectAttr "character1.av[8]" "joint3.ry";
connectAttr "character1.av[9]" "joint3.rx";
connectAttr "character1.lv[7]" "joint3.tz";
connectAttr "character1.lv[8]" "joint3.ty";
connectAttr "character1.lv[9]" "joint3.tx";
connectAttr "joint3.s" "joint4.is";
connectAttr "character1.av[4]" "joint4.rz";
connectAttr "character1.av[5]" "joint4.ry";
connectAttr "character1.av[6]" "joint4.rx";
connectAttr "character1.lv[4]" "joint4.tz";
connectAttr "character1.lv[5]" "joint4.ty";
connectAttr "character1.lv[6]" "joint4.tx";
connectAttr "joint4.s" "joint5.is";
connectAttr "character1.av[1]" "joint5.rz";
connectAttr "character1.av[2]" "joint5.ry";
connectAttr "character1.av[3]" "joint5.rx";
connectAttr "character1.lv[1]" "joint5.tz";
connectAttr "character1.lv[2]" "joint5.ty";
connectAttr "character1.lv[3]" "joint5.tx";
connectAttr "skinCluster3GroupId.id" "cubeShape3.iog.og[0].gid";
connectAttr "skinCluster3Set.mwc" "cubeShape3.iog.og[0].gco";
connectAttr "groupId6.id" "cubeShape3.iog.og[1].gid";
connectAttr "tweakSet3.mwc" "cubeShape3.iog.og[1].gco";
connectAttr "skinCluster3.og[0]" "cubeShape3.i";
connectAttr "tweak3.vl[0].vt[0]" "cubeShape3.twl";
connectAttr "polyCube1.out" "cubeShape3Orig3.i";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "phong1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "phong2SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "phong1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "phong2SG.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "joint1.msg" "bindPose1.m[0]";
connectAttr "joint2.msg" "bindPose1.m[1]";
connectAttr "joint3.msg" "bindPose1.m[2]";
connectAttr "joint4.msg" "bindPose1.m[3]";
connectAttr "joint5.msg" "bindPose1.m[5]";
connectAttr "bindPose1.w" "bindPose1.p[0]";
connectAttr "bindPose1.m[0]" "bindPose1.p[1]";
connectAttr "bindPose1.m[1]" "bindPose1.p[2]";
connectAttr "bindPose1.m[2]" "bindPose1.p[3]";
connectAttr "bindPose1.m[3]" "bindPose1.p[5]";
connectAttr "joint1.bps" "bindPose1.wm[0]";
connectAttr "joint2.bps" "bindPose1.wm[1]";
connectAttr "joint3.bps" "bindPose1.wm[2]";
connectAttr "joint4.bps" "bindPose1.wm[3]";
connectAttr "joint5.bps" "bindPose1.wm[5]";
connectAttr "skinCluster2GroupParts.og" "skinCluster2.ip[0].ig";
connectAttr "skinCluster2GroupId.id" "skinCluster2.ip[0].gi";
connectAttr "joint2.wm" "skinCluster2.ma[1]";
connectAttr "joint3.wm" "skinCluster2.ma[2]";
connectAttr "joint4.wm" "skinCluster2.ma[3]";
connectAttr "joint5.wm" "skinCluster2.ma[4]";
connectAttr "joint2.liw" "skinCluster2.lw[1]";
connectAttr "joint3.liw" "skinCluster2.lw[2]";
connectAttr "joint4.liw" "skinCluster2.lw[3]";
connectAttr "joint5.liw" "skinCluster2.lw[4]";
connectAttr "joint2.obcc" "skinCluster2.ifcl[1]";
connectAttr "joint3.obcc" "skinCluster2.ifcl[2]";
connectAttr "joint4.obcc" "skinCluster2.ifcl[3]";
connectAttr "joint5.obcc" "skinCluster2.ifcl[4]";
connectAttr "bindPose1.msg" "skinCluster2.bp";
connectAttr "groupParts4.og" "tweak2.ip[0].ig";
connectAttr "groupId4.id" "tweak2.ip[0].gi";
connectAttr "skinCluster2GroupId.msg" "skinCluster2Set.gn" -na;
connectAttr "triShape2.iog.og[0]" "skinCluster2Set.dsm" -na;
connectAttr "skinCluster2.msg" "skinCluster2Set.ub[0]";
connectAttr "tweak2.og[0]" "skinCluster2GroupParts.ig";
connectAttr "skinCluster2GroupId.id" "skinCluster2GroupParts.gi";
connectAttr "groupId4.msg" "tweakSet2.gn" -na;
connectAttr "triShape2.iog.og[1]" "tweakSet2.dsm" -na;
connectAttr "tweak2.msg" "tweakSet2.ub[0]";
connectAttr "triShape2Orig2.w" "groupParts4.ig";
connectAttr "groupId4.id" "groupParts4.gi";
connectAttr "joint5.rz" "character1.dnsm[0]";
connectAttr "joint5.ry" "character1.dnsm[1]";
connectAttr "joint5.rx" "character1.dnsm[2]";
connectAttr "joint5.tz" "character1.dnsm[3]";
connectAttr "joint5.ty" "character1.dnsm[4]";
connectAttr "joint5.tx" "character1.dnsm[5]";
connectAttr "joint4.rz" "character1.dnsm[6]";
connectAttr "joint4.ry" "character1.dnsm[7]";
connectAttr "joint4.rx" "character1.dnsm[8]";
connectAttr "joint4.tz" "character1.dnsm[9]";
connectAttr "joint4.ty" "character1.dnsm[10]";
connectAttr "joint4.tx" "character1.dnsm[11]";
connectAttr "joint3.rz" "character1.dnsm[12]";
connectAttr "joint3.ry" "character1.dnsm[13]";
connectAttr "joint3.rx" "character1.dnsm[14]";
connectAttr "joint3.tz" "character1.dnsm[15]";
connectAttr "joint3.ty" "character1.dnsm[16]";
connectAttr "joint3.tx" "character1.dnsm[17]";
connectAttr "joint2.rz" "character1.dnsm[18]";
connectAttr "joint2.ry" "character1.dnsm[19]";
connectAttr "joint2.rx" "character1.dnsm[20]";
connectAttr "joint2.tz" "character1.dnsm[21]";
connectAttr "joint2.ty" "character1.dnsm[22]";
connectAttr "joint2.tx" "character1.dnsm[23]";
connectAttr "joint1.rz" "character1.dnsm[24]";
connectAttr "joint1.ry" "character1.dnsm[25]";
connectAttr "joint1.rx" "character1.dnsm[26]";
connectAttr "joint1.tz" "character1.dnsm[27]";
connectAttr "joint1.ty" "character1.dnsm[28]";
connectAttr "joint1.tx" "character1.dnsm[29]";
connectAttr "character1Scheduler1.ce" "character1.cer";
connectAttr "character1Clips1.cf" "character1Scheduler1.cfr";
connectAttr "character1Clips1.cl[0]" "character1Scheduler1.cl[0]";
connectAttr "character1Clips1.cl[1]" "character1Scheduler1.cl[1]";
connectAttr "NEUTRAL.sf" "character1Scheduler1.st[0]";
connectAttr "TWIST.sf" "character1Scheduler1.st[1]";
connectAttr "NEUTRAL.ss" "character1Scheduler1.ss[0]";
connectAttr "TWIST.ss" "character1Scheduler1.ss[1]";
connectAttr "NEUTRAL.se" "character1Scheduler1.se[0]";
connectAttr "TWIST.se" "character1Scheduler1.se[1]";
connectAttr "NEUTRAL.w" "character1Scheduler1.w[0]";
connectAttr "TWIST.w" "character1Scheduler1.w[1]";
connectAttr "NEUTRAL.ws" "character1Scheduler1.ws[0]";
connectAttr "TWIST.ws" "character1Scheduler1.ws[1]";
connectAttr "NEUTRAL.ea" "character1Scheduler1.ea[0]";
connectAttr "TWIST.ea" "character1Scheduler1.ea[1]";
connectAttr "NEUTRAL.cb" "character1Scheduler1.cb[0]";
connectAttr "TWIST.cb" "character1Scheduler1.cb[1]";
connectAttr "NEUTRAL.ca" "character1Scheduler1.ca[0]";
connectAttr "TWIST.ca" "character1Scheduler1.ca[1]";
connectAttr "NEUTRAL.sc" "character1Scheduler1.sc[0]";
connectAttr "TWIST.sc" "character1Scheduler1.sc[1]";
connectAttr "NEUTRAL.h" "character1Scheduler1.h[0]";
connectAttr "TWIST.h" "character1Scheduler1.h[1]";
connectAttr "character1.am" "character1Clips1.cd[0].cm";
connectAttr "character1.cim" "character1Clips1.cd[0].cim";
connectAttr "joint5_rotateZ.a" "character1Clips1.cel[0].cev[0].cevr";
connectAttr "joint4_rotateZ.a" "character1Clips1.cel[0].cev[6].cevr";
connectAttr "joint3_rotateZ.a" "character1Clips1.cel[0].cev[12].cevr";
connectAttr "joint2_rotateZ.a" "character1Clips1.cel[0].cev[18].cevr";
connectAttr "joint1_rotateZ.a" "character1Clips1.cel[0].cev[24].cevr";
connectAttr "character1_joint5_rotateZ.a" "character1Clips1.cel[1].cev[0].cevr";
connectAttr "character1_joint4_rotateZ.a" "character1Clips1.cel[1].cev[6].cevr";
connectAttr "character1_joint3_rotateZ.a" "character1Clips1.cel[1].cev[12].cevr"
		;
connectAttr "character1_joint2_rotateZ.a" "character1Clips1.cel[1].cev[18].cevr"
		;
connectAttr "character1_joint1_rotateZ.a" "character1Clips1.cel[1].cev[24].cevr"
		;
connectAttr "NEUTRALSource.cl" "character1Clips1.sc[0]";
connectAttr "TWISTSource.cl" "character1Clips1.sc[1]";
connectAttr "NEUTRALSource.cl" "NEUTRAL.cl";
connectAttr "TWISTSource.cl" "TWIST.cl";
connectAttr "skinCluster1GroupParts.og" "skinCluster1.ip[0].ig";
connectAttr "skinCluster1GroupId.id" "skinCluster1.ip[0].gi";
connectAttr "bindPose1.msg" "skinCluster1.bp";
connectAttr "joint1.wm" "skinCluster1.ma[0]";
connectAttr "joint2.wm" "skinCluster1.ma[1]";
connectAttr "joint3.wm" "skinCluster1.ma[2]";
connectAttr "joint1.liw" "skinCluster1.lw[0]";
connectAttr "joint2.liw" "skinCluster1.lw[1]";
connectAttr "joint3.liw" "skinCluster1.lw[2]";
connectAttr "joint1.obcc" "skinCluster1.ifcl[0]";
connectAttr "joint2.obcc" "skinCluster1.ifcl[1]";
connectAttr "joint3.obcc" "skinCluster1.ifcl[2]";
connectAttr "tweak1.og[0]" "skinCluster1GroupParts.ig";
connectAttr "skinCluster1GroupId.id" "skinCluster1GroupParts.gi";
connectAttr "skinCluster1GroupId.msg" "skinCluster1Set.gn" -na;
connectAttr "triShape1.iog.og[0]" "skinCluster1Set.dsm" -na;
connectAttr "skinCluster1.msg" "skinCluster1Set.ub[0]";
connectAttr "groupParts2.og" "tweak1.ip[0].ig";
connectAttr "groupId2.id" "tweak1.ip[0].gi";
connectAttr "triShape1Orig1.w" "groupParts2.ig";
connectAttr "groupId2.id" "groupParts2.gi";
connectAttr "groupId2.msg" "tweakSet1.gn" -na;
connectAttr "triShape1.iog.og[1]" "tweakSet1.dsm" -na;
connectAttr "tweak1.msg" "tweakSet1.ub[0]";
connectAttr "phong1.oc" "phong1SG.ss";
connectAttr "triShape1.iog" "phong1SG.dsm" -na;
connectAttr "phong1SG.msg" "materialInfo1.sg";
connectAttr "phong1.msg" "materialInfo1.m";
connectAttr "phong2.oc" "phong2SG.ss";
connectAttr "triShape2.iog" "phong2SG.dsm" -na;
connectAttr "phong2SG.msg" "materialInfo2.sg";
connectAttr "phong2.msg" "materialInfo2.m";
connectAttr "skinCluster3GroupParts.og" "skinCluster3.ip[0].ig";
connectAttr "skinCluster3GroupId.id" "skinCluster3.ip[0].gi";
connectAttr "joint1.wm" "skinCluster3.ma[0]";
connectAttr "joint2.wm" "skinCluster3.ma[1]";
connectAttr "joint3.wm" "skinCluster3.ma[2]";
connectAttr "joint4.wm" "skinCluster3.ma[3]";
connectAttr "joint5.wm" "skinCluster3.ma[4]";
connectAttr "joint1.liw" "skinCluster3.lw[0]";
connectAttr "joint2.liw" "skinCluster3.lw[1]";
connectAttr "joint3.liw" "skinCluster3.lw[2]";
connectAttr "joint4.liw" "skinCluster3.lw[3]";
connectAttr "joint5.liw" "skinCluster3.lw[4]";
connectAttr "joint1.obcc" "skinCluster3.ifcl[0]";
connectAttr "joint2.obcc" "skinCluster3.ifcl[1]";
connectAttr "joint3.obcc" "skinCluster3.ifcl[2]";
connectAttr "joint4.obcc" "skinCluster3.ifcl[3]";
connectAttr "joint5.obcc" "skinCluster3.ifcl[4]";
connectAttr "bindPose1.msg" "skinCluster3.bp";
connectAttr "groupParts6.og" "tweak3.ip[0].ig";
connectAttr "groupId6.id" "tweak3.ip[0].gi";
connectAttr "skinCluster3GroupId.msg" "skinCluster3Set.gn" -na;
connectAttr "cubeShape3.iog.og[0]" "skinCluster3Set.dsm" -na;
connectAttr "skinCluster3.msg" "skinCluster3Set.ub[0]";
connectAttr "tweak3.og[0]" "skinCluster3GroupParts.ig";
connectAttr "skinCluster3GroupId.id" "skinCluster3GroupParts.gi";
connectAttr "groupId6.msg" "tweakSet3.gn" -na;
connectAttr "cubeShape3.iog.og[1]" "tweakSet3.dsm" -na;
connectAttr "tweak3.msg" "tweakSet3.ub[0]";
connectAttr "cubeShape3Orig3.w" "groupParts6.ig";
connectAttr "groupId6.id" "groupParts6.gi";
connectAttr "skinCluster2Set.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[0].dn";
connectAttr "triShape2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[1].dn";
connectAttr "phong2SG.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[2].dn";
connectAttr "joint4.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[3].dn";
connectAttr "joint3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[4].dn";
connectAttr "cube3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[5].dn";
connectAttr "joint2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[6].dn";
connectAttr "cubeShape3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[7].dn";
connectAttr "tweak2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[8].dn";
connectAttr "triShape2Orig2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[9].dn";
connectAttr "skinCluster2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[10].dn";
connectAttr "tweakSet2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[11].dn";
connectAttr "joint5.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[12].dn";
connectAttr "polyCube1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[13].dn";
connectAttr "cubeShape3Orig3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[14].dn"
		;
connectAttr "tweak3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[15].dn";
connectAttr "skinCluster3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[16].dn";
connectAttr "tweakSet3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[17].dn";
connectAttr "skinCluster3Set.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[18].dn"
		;
connectAttr "phong1SG.pa" ":renderPartition.st" -na;
connectAttr "phong2SG.pa" ":renderPartition.st" -na;
connectAttr "phong1.msg" ":defaultShaderList1.s" -na;
connectAttr "phong2.msg" ":defaultShaderList1.s" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "cubeShape3.iog" ":initialShadingGroup.dsm" -na;
connectAttr "character1.pa" ":characterPartition.st" -na;
// End of DoubleMeshSkinWeldTest1.ma
