//Maya ASCII 2018ff07 scene
//Name: ComplexTraxAnim1.ma
//Last modified: Sun, Feb 03, 2019 11:57:22 AM
//Codeset: 1252
requires maya "2018ff07";
requires -nodeType "aiOptions" -nodeType "aiAOVDriver" -nodeType "aiAOVFilter" "mtoa" "2.1.0.1";
requires "stereoCamera" "10.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2018";
fileInfo "version" "2018";
fileInfo "cutIdentifier" "201711281015-8e846c9074";
fileInfo "osv" "Microsoft Windows 8 Business Edition, 64-bit  (Build 9200)\n";
createNode transform -s -n "persp";
	rename -uid "811D66CC-428E-11CE-4D28-B5BB1C7CB028";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -13.122390860867784 3.2238160445829411 3.8124069696161076 ;
	setAttr ".r" -type "double3" -0.93835272960183613 -73.799999999999301 0 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "F0656A63-4F39-C37B-DF60-A8944B9E2774";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 13.666809519018694;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" 0 3 0 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
	setAttr ".ai_translator" -type "string" "perspective";
createNode transform -s -n "top";
	rename -uid "47775968-481D-959C-DEC2-C4912A1B5C1A";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 1000.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "EB095155-4DB1-0744-A568-14BA62C44391";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -s -n "front";
	rename -uid "D2B058DF-4F52-A165-3820-02ACBF177175";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 2.5 1000.1031246826499 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "C0076C6D-486D-29FF-8F70-71ABAEEFAFEB";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1031246826499;
	setAttr ".ow" 11.922400202201116;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".tp" -type "double3" 0 2.5 0 ;
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -s -n "side";
	rename -uid "16C0B8E8-4BA7-F9BB-4576-23BDBB79EA1F";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "38CC8E14-4B71-AE99-14B3-67A7483C201E";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -n "character";
	rename -uid "308473CD-49C6-7C12-3686-70A190B85479";
	setAttr ".t" -type "double3" 0 2.5 0 ;
	setAttr -l on ".tx";
	setAttr -l on ".ty";
	setAttr -l on ".tz";
	setAttr -l on ".rx";
	setAttr -l on ".ry";
	setAttr -l on ".rz";
	setAttr -l on ".sx";
	setAttr -l on ".sy";
	setAttr -l on ".sz";
	setAttr ".rp" -type "double3" 0 -2.5 0 ;
	setAttr ".sp" -type "double3" 0 -2.5 0 ;
createNode mesh -n "characterShape" -p "character";
	rename -uid "58FFE630-426C-2EEC-EB41-73B726FBAFC3";
	setAttr -k off ".v";
	setAttr -s 6 ".iog[0].og";
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
	setAttr ".ai_translator" -type "string" "polymesh";
createNode mesh -n "characterShapeOrig" -p "character";
	rename -uid "BB1EBB54-47C9-CA20-0ED8-C4BDF9550EE1";
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
	setAttr ".ai_translator" -type "string" "polymesh";
createNode transform -n "target1";
	rename -uid "1862B60C-4CCB-46C8-6EE3-E1A3BB6F4E93";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1.5 2.5 0 ;
	setAttr ".rp" -type "double3" 0 -2.5 0 ;
	setAttr ".sp" -type "double3" 0 -2.5 0 ;
createNode mesh -n "target1Shape" -p "target1";
	rename -uid "4BEAC819-49DA-ADB7-DC45-B9B58D389E94";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.5 0.3750000074505806 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 38 ".uvst[0].uvsp[0:37]" -type "float2" 0.375 0 0.625 0 0.375
		 0.050000001 0.625 0.050000001 0.375 0.1 0.625 0.1 0.375 0.15000001 0.625 0.15000001
		 0.375 0.2 0.625 0.2 0.375 0.25 0.625 0.25 0.375 0.5 0.625 0.5 0.375 0.55000001 0.625
		 0.55000001 0.375 0.60000002 0.625 0.60000002 0.375 0.65000004 0.625 0.65000004 0.375
		 0.70000005 0.625 0.70000005 0.375 0.75000006 0.625 0.75000006 0.375 1 0.625 1 0.875
		 0 0.875 0.050000001 0.875 0.1 0.875 0.15000001 0.875 0.2 0.875 0.25 0.125 0 0.125
		 0.050000001 0.125 0.1 0.125 0.15000001 0.125 0.2 0.125 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 8 ".pt[8:15]" -type "float3"  -0.25000018 -2.0861626e-07 
		0.25000018 0.25000018 -2.0861626e-07 0.25000018 -0.25000018 1.7881393e-07 0.25000018 
		0.25000018 1.7881393e-07 0.25000018 -0.25000018 1.7881393e-07 -0.25000018 0.25000018 
		1.7881393e-07 -0.25000018 -0.25000018 -2.0861626e-07 -0.25000018 0.25000018 -2.0861626e-07 
		-0.25000018;
	setAttr -s 24 ".vt[0:23]"  -0.5 -2.5 0.5 0.5 -2.5 0.5 -0.5 -1.5 0.5
		 0.5 -1.5 0.5 -0.5 -0.5 0.5 0.5 -0.5 0.5 -0.5 0.5 0.5 0.5 0.5 0.5 -0.5 1.5 0.5 0.5 1.5 0.5
		 -0.5 2.5 0.5 0.5 2.5 0.5 -0.5 2.5 -0.5 0.5 2.5 -0.5 -0.5 1.5 -0.5 0.5 1.5 -0.5 -0.5 0.5 -0.5
		 0.5 0.5 -0.5 -0.5 -0.5 -0.5 0.5 -0.5 -0.5 -0.5 -1.5 -0.5 0.5 -1.5 -0.5 -0.5 -2.5 -0.5
		 0.5 -2.5 -0.5;
	setAttr -s 44 ".ed[0:43]"  0 1 0 2 3 1 4 5 1 6 7 1 8 9 1 10 11 0 12 13 0
		 14 15 1 16 17 1 18 19 1 20 21 1 22 23 0 0 2 0 1 3 0 2 4 0 3 5 0 4 6 0 5 7 0 6 8 0
		 7 9 0 8 10 0 9 11 0 10 12 0 11 13 0 12 14 0 13 15 0 14 16 0 15 17 0 16 18 0 17 19 0
		 18 20 0 19 21 0 20 22 0 21 23 0 22 0 0 23 1 0 21 3 1 19 5 1 17 7 1 15 9 1 20 2 1
		 18 4 1 16 6 1 14 8 1;
	setAttr -s 22 -ch 88 ".fc[0:21]" -type "polyFaces" 
		f 4 0 13 -2 -13
		mu 0 4 0 1 3 2
		f 4 1 15 -3 -15
		mu 0 4 2 3 5 4
		f 4 2 17 -4 -17
		mu 0 4 4 5 7 6
		f 4 3 19 -5 -19
		mu 0 4 6 7 9 8
		f 4 4 21 -6 -21
		mu 0 4 8 9 11 10
		f 4 5 23 -7 -23
		mu 0 4 10 11 13 12
		f 4 6 25 -8 -25
		mu 0 4 12 13 15 14
		f 4 7 27 -9 -27
		mu 0 4 14 15 17 16
		f 4 8 29 -10 -29
		mu 0 4 16 17 19 18
		f 4 9 31 -11 -31
		mu 0 4 18 19 21 20
		f 4 10 33 -12 -33
		mu 0 4 20 21 23 22
		f 4 11 35 -1 -35
		mu 0 4 22 23 25 24
		f 4 -36 -34 36 -14
		mu 0 4 1 26 27 3
		f 4 -37 -32 37 -16
		mu 0 4 3 27 28 5
		f 4 -38 -30 38 -18
		mu 0 4 5 28 29 7
		f 4 -39 -28 39 -20
		mu 0 4 7 29 30 9
		f 4 -40 -26 -24 -22
		mu 0 4 9 30 31 11
		f 4 34 12 -41 32
		mu 0 4 32 0 2 33
		f 4 40 14 -42 30
		mu 0 4 33 2 4 34
		f 4 41 16 -43 28
		mu 0 4 34 4 6 35
		f 4 42 18 -44 26
		mu 0 4 35 6 8 36
		f 4 43 20 22 24
		mu 0 4 36 8 10 37;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".ai_translator" -type "string" "polymesh";
createNode transform -n "target2";
	rename -uid "6461DEC0-45A5-45D4-85F3-3AB9838E5E98";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 3 2.5 0 ;
	setAttr ".rp" -type "double3" 0 -2.5 0 ;
	setAttr ".sp" -type "double3" 0 -2.5 0 ;
createNode mesh -n "targetShape2" -p "target2";
	rename -uid "1E5E3C1A-457B-D780-7DFF-F28CCD21310E";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.5 0.37500001490116119 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 38 ".uvst[0].uvsp[0:37]" -type "float2" 0.375 0 0.625 0 0.375
		 0.050000001 0.625 0.050000001 0.375 0.1 0.625 0.1 0.375 0.15000001 0.625 0.15000001
		 0.375 0.2 0.625 0.2 0.375 0.25 0.625 0.25 0.375 0.5 0.625 0.5 0.375 0.55000001 0.625
		 0.55000001 0.375 0.60000002 0.625 0.60000002 0.375 0.65000004 0.625 0.65000004 0.375
		 0.70000005 0.625 0.70000005 0.375 0.75000006 0.625 0.75000006 0.375 1 0.625 1 0.875
		 0 0.875 0.050000001 0.875 0.1 0.875 0.15000001 0.875 0.2 0.875 0.25 0.125 0 0.125
		 0.050000001 0.125 0.1 0.125 0.15000001 0.125 0.2 0.125 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 8 ".pt";
	setAttr ".pt[6]" -type "float3" -0.25 0 0.25 ;
	setAttr ".pt[7]" -type "float3" 0.25 0 0.25 ;
	setAttr ".pt[8]" -type "float3" -0.25 0 0.25 ;
	setAttr ".pt[9]" -type "float3" 0.25 0 0.25 ;
	setAttr ".pt[14]" -type "float3" -0.25 0 -0.25 ;
	setAttr ".pt[15]" -type "float3" 0.25 0 -0.25 ;
	setAttr ".pt[16]" -type "float3" -0.25 0 -0.25 ;
	setAttr ".pt[17]" -type "float3" 0.25 0 -0.25 ;
	setAttr -s 24 ".vt[0:23]"  -0.5 -2.5 0.5 0.5 -2.5 0.5 -0.5 -1.5 0.5
		 0.5 -1.5 0.5 -0.5 -0.5 0.5 0.5 -0.5 0.5 -0.5 0.5 0.5 0.5 0.5 0.5 -0.5 1.5 0.5 0.5 1.5 0.5
		 -0.5 2.5 0.5 0.5 2.5 0.5 -0.5 2.5 -0.5 0.5 2.5 -0.5 -0.5 1.5 -0.5 0.5 1.5 -0.5 -0.5 0.5 -0.5
		 0.5 0.5 -0.5 -0.5 -0.5 -0.5 0.5 -0.5 -0.5 -0.5 -1.5 -0.5 0.5 -1.5 -0.5 -0.5 -2.5 -0.5
		 0.5 -2.5 -0.5;
	setAttr -s 44 ".ed[0:43]"  0 1 0 2 3 1 4 5 1 6 7 1 8 9 1 10 11 0 12 13 0
		 14 15 1 16 17 1 18 19 1 20 21 1 22 23 0 0 2 0 1 3 0 2 4 0 3 5 0 4 6 0 5 7 0 6 8 0
		 7 9 0 8 10 0 9 11 0 10 12 0 11 13 0 12 14 0 13 15 0 14 16 0 15 17 0 16 18 0 17 19 0
		 18 20 0 19 21 0 20 22 0 21 23 0 22 0 0 23 1 0 21 3 1 19 5 1 17 7 1 15 9 1 20 2 1
		 18 4 1 16 6 1 14 8 1;
	setAttr -s 22 -ch 88 ".fc[0:21]" -type "polyFaces" 
		f 4 0 13 -2 -13
		mu 0 4 0 1 3 2
		f 4 1 15 -3 -15
		mu 0 4 2 3 5 4
		f 4 2 17 -4 -17
		mu 0 4 4 5 7 6
		f 4 3 19 -5 -19
		mu 0 4 6 7 9 8
		f 4 4 21 -6 -21
		mu 0 4 8 9 11 10
		f 4 5 23 -7 -23
		mu 0 4 10 11 13 12
		f 4 6 25 -8 -25
		mu 0 4 12 13 15 14
		f 4 7 27 -9 -27
		mu 0 4 14 15 17 16
		f 4 8 29 -10 -29
		mu 0 4 16 17 19 18
		f 4 9 31 -11 -31
		mu 0 4 18 19 21 20
		f 4 10 33 -12 -33
		mu 0 4 20 21 23 22
		f 4 11 35 -1 -35
		mu 0 4 22 23 25 24
		f 4 -36 -34 36 -14
		mu 0 4 1 26 27 3
		f 4 -37 -32 37 -16
		mu 0 4 3 27 28 5
		f 4 -38 -30 38 -18
		mu 0 4 5 28 29 7
		f 4 -39 -28 39 -20
		mu 0 4 7 29 30 9
		f 4 -40 -26 -24 -22
		mu 0 4 9 30 31 11
		f 4 34 12 -41 32
		mu 0 4 32 0 2 33
		f 4 40 14 -42 30
		mu 0 4 33 2 4 34
		f 4 41 16 -43 28
		mu 0 4 34 4 6 35
		f 4 42 18 -44 26
		mu 0 4 35 6 8 36
		f 4 43 20 22 24
		mu 0 4 36 8 10 37;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".ai_translator" -type "string" "polymesh";
createNode transform -n "target3";
	rename -uid "C30B2E7D-489D-A02B-AEC9-4989C22B2313";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 4.5 2.5 0 ;
	setAttr ".rp" -type "double3" 0 -2.5 0 ;
	setAttr ".sp" -type "double3" 0 -2.5 0 ;
createNode mesh -n "targetShape3" -p "target3";
	rename -uid "CFD8C8AE-41E1-3E62-8406-9ABE42EACB8A";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.5 0.37500001862645149 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 38 ".uvst[0].uvsp[0:37]" -type "float2" 0.375 0 0.625 0 0.375
		 0.050000001 0.625 0.050000001 0.375 0.1 0.625 0.1 0.375 0.15000001 0.625 0.15000001
		 0.375 0.2 0.625 0.2 0.375 0.25 0.625 0.25 0.375 0.5 0.625 0.5 0.375 0.55000001 0.625
		 0.55000001 0.375 0.60000002 0.625 0.60000002 0.375 0.65000004 0.625 0.65000004 0.375
		 0.70000005 0.625 0.70000005 0.375 0.75000006 0.625 0.75000006 0.375 1 0.625 1 0.875
		 0 0.875 0.050000001 0.875 0.1 0.875 0.15000001 0.875 0.2 0.875 0.25 0.125 0 0.125
		 0.050000001 0.125 0.1 0.125 0.15000001 0.125 0.2 0.125 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 8 ".pt";
	setAttr ".pt[4]" -type "float3" -0.25 0 0.25 ;
	setAttr ".pt[5]" -type "float3" 0.25 0 0.25 ;
	setAttr ".pt[6]" -type "float3" -0.25 0 0.25 ;
	setAttr ".pt[7]" -type "float3" 0.25 0 0.25 ;
	setAttr ".pt[16]" -type "float3" -0.25 0 -0.25 ;
	setAttr ".pt[17]" -type "float3" 0.25 0 -0.25 ;
	setAttr ".pt[18]" -type "float3" -0.25 0 -0.25 ;
	setAttr ".pt[19]" -type "float3" 0.25 0 -0.25 ;
	setAttr -s 24 ".vt[0:23]"  -0.5 -2.5 0.5 0.5 -2.5 0.5 -0.5 -1.5 0.5
		 0.5 -1.5 0.5 -0.5 -0.5 0.5 0.5 -0.5 0.5 -0.5 0.5 0.5 0.5 0.5 0.5 -0.5 1.5 0.5 0.5 1.5 0.5
		 -0.5 2.5 0.5 0.5 2.5 0.5 -0.5 2.5 -0.5 0.5 2.5 -0.5 -0.5 1.5 -0.5 0.5 1.5 -0.5 -0.5 0.5 -0.5
		 0.5 0.5 -0.5 -0.5 -0.5 -0.5 0.5 -0.5 -0.5 -0.5 -1.5 -0.5 0.5 -1.5 -0.5 -0.5 -2.5 -0.5
		 0.5 -2.5 -0.5;
	setAttr -s 44 ".ed[0:43]"  0 1 0 2 3 1 4 5 1 6 7 1 8 9 1 10 11 0 12 13 0
		 14 15 1 16 17 1 18 19 1 20 21 1 22 23 0 0 2 0 1 3 0 2 4 0 3 5 0 4 6 0 5 7 0 6 8 0
		 7 9 0 8 10 0 9 11 0 10 12 0 11 13 0 12 14 0 13 15 0 14 16 0 15 17 0 16 18 0 17 19 0
		 18 20 0 19 21 0 20 22 0 21 23 0 22 0 0 23 1 0 21 3 1 19 5 1 17 7 1 15 9 1 20 2 1
		 18 4 1 16 6 1 14 8 1;
	setAttr -s 22 -ch 88 ".fc[0:21]" -type "polyFaces" 
		f 4 0 13 -2 -13
		mu 0 4 0 1 3 2
		f 4 1 15 -3 -15
		mu 0 4 2 3 5 4
		f 4 2 17 -4 -17
		mu 0 4 4 5 7 6
		f 4 3 19 -5 -19
		mu 0 4 6 7 9 8
		f 4 4 21 -6 -21
		mu 0 4 8 9 11 10
		f 4 5 23 -7 -23
		mu 0 4 10 11 13 12
		f 4 6 25 -8 -25
		mu 0 4 12 13 15 14
		f 4 7 27 -9 -27
		mu 0 4 14 15 17 16
		f 4 8 29 -10 -29
		mu 0 4 16 17 19 18
		f 4 9 31 -11 -31
		mu 0 4 18 19 21 20
		f 4 10 33 -12 -33
		mu 0 4 20 21 23 22
		f 4 11 35 -1 -35
		mu 0 4 22 23 25 24
		f 4 -36 -34 36 -14
		mu 0 4 1 26 27 3
		f 4 -37 -32 37 -16
		mu 0 4 3 27 28 5
		f 4 -38 -30 38 -18
		mu 0 4 5 28 29 7
		f 4 -39 -28 39 -20
		mu 0 4 7 29 30 9
		f 4 -40 -26 -24 -22
		mu 0 4 9 30 31 11
		f 4 34 12 -41 32
		mu 0 4 32 0 2 33
		f 4 40 14 -42 30
		mu 0 4 33 2 4 34
		f 4 41 16 -43 28
		mu 0 4 34 4 6 35
		f 4 42 18 -44 26
		mu 0 4 35 6 8 36
		f 4 43 20 22 24
		mu 0 4 36 8 10 37;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
	setAttr ".bck" 1;
	setAttr ".vbc" no;
	setAttr ".ai_translator" -type "string" "polymesh";
createNode joint -n "joint1";
	rename -uid "657D87BB-4410-833E-2100-56AF3A81B2C2";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	setAttr ".uoc" 1;
	setAttr ".t" -type "double3" 0 0.5 0 ;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 0 0 89.999999999999986 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 2.2204460492503131e-16 1 0 0 -1 2.2204460492503131e-16 0 0
		 0 0 1 0 0 0.5 0 1;
	setAttr ".radi" 2;
createNode joint -n "joint2" -p "joint1";
	rename -uid "784BD652-41D6-1FB4-BD6A-D5AC3B351063";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	addAttr -ci true -k true -sn "blendCharacterset" -ln "blendCharacterset" -dv 1 -smn 
		0 -smx 1 -at "double";
	addAttr -ci true -k true -sn "blendPairBlend1" -ln "blendPairBlend1" -dv 1 -smn 
		0 -smx 1 -at "double";
	setAttr ".uoc" 1;
	setAttr ".oc" 1;
	setAttr ".t" -type "double3" 1 2.2204460492503131e-16 0 ;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 2.2204460492503131e-16 1 0 0 -1 2.2204460492503131e-16 0 0
		 0 0 1 0 0 1.5 0 1;
	setAttr ".radi" 2;
	setAttr -k on ".blendCharacterset" 0;
	setAttr -k on ".blendPairBlend1" 0;
createNode joint -n "joint3" -p "joint2";
	rename -uid "2F5193C2-4CEE-967B-98EE-52B8453B373D";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	addAttr -ci true -k true -sn "blendCharacterset" -ln "blendCharacterset" -dv 1 -smn 
		0 -smx 1 -at "double";
	addAttr -ci true -k true -sn "blendPairBlend2" -ln "blendPairBlend2" -dv 1 -smn 
		0 -smx 1 -at "double";
	setAttr ".uoc" 1;
	setAttr ".oc" 2;
	setAttr ".t" -type "double3" 1 2.2204460492503131e-16 0 ;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 2.2204460492503131e-16 1 0 0 -1 2.2204460492503131e-16 0 0
		 0 0 1 0 0 2.5 0 1;
	setAttr ".radi" 2;
	setAttr -k on ".blendCharacterset" 0;
	setAttr -k on ".blendPairBlend2" 0;
createNode joint -n "joint4" -p "joint3";
	rename -uid "8A97BC9F-4A21-300B-0B62-42B95BB71110";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	addAttr -ci true -k true -sn "blendCharacterset" -ln "blendCharacterset" -dv 1 -smn 
		0 -smx 1 -at "double";
	addAttr -ci true -k true -sn "blendPairBlend3" -ln "blendPairBlend3" -dv 1 -smn 
		0 -smx 1 -at "double";
	setAttr ".uoc" 1;
	setAttr ".oc" 3;
	setAttr ".t" -type "double3" 1 2.2204460492503131e-16 0 ;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 2.2204460492503131e-16 1 0 0 -1 2.2204460492503131e-16 0 0
		 0 0 1 0 0 3.5 0 1;
	setAttr ".radi" 2;
	setAttr -k on ".blendCharacterset" 0;
	setAttr -k on ".blendPairBlend3" 0;
createNode joint -n "joint5" -p "joint4";
	rename -uid "7D29A041-4D85-902A-A5FF-08A5F7504E91";
	addAttr -ci true -sn "liw" -ln "lockInfluenceWeights" -min 0 -max 1 -at "bool";
	addAttr -ci true -k true -sn "blendCharacterset" -ln "blendCharacterset" -dv 1 -smn 
		0 -smx 1 -at "double";
	addAttr -ci true -k true -sn "blendPairBlend4" -ln "blendPairBlend4" -dv 1 -smn 
		0 -smx 1 -at "double";
	setAttr ".uoc" 1;
	setAttr ".oc" 4;
	setAttr ".t" -type "double3" 1 2.2204460492503131e-16 0 ;
	setAttr ".mnrl" -type "double3" -360 -360 -360 ;
	setAttr ".mxrl" -type "double3" 360 360 360 ;
	setAttr ".jo" -type "double3" 0 0 -89.999999999999986 ;
	setAttr ".ssc" no;
	setAttr ".bps" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 4.5 0 1;
	setAttr ".radi" 2;
	setAttr -k on ".blendCharacterset" 0;
	setAttr -k on ".blendPairBlend4" 0;
createNode transform -n "camera1";
	rename -uid "AA87BE12-4806-9E8C-F282-EAA69257F4DE";
	setAttr ".t" -type "double3" 5.6982398551890014 9.3670995521943432 7.9975475430593601 ;
	setAttr ".r" -type "double3" -35 25 0 ;
createNode camera -n "cameraShape1" -p "camera1";
	rename -uid "E96011B2-4807-1D43-BE7B-D6A251FB6D04";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".cap" -type "double2" 1.4173 0.9449 ;
	setAttr ".ff" 0;
	setAttr ".coi" 11.930576417602257;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "camera1";
	setAttr ".den" -type "string" "camera1_depth";
	setAttr ".man" -type "string" "camera1_mask";
	setAttr ".tp" -type "double3" 3.077683537175254 0.5 0 ;
	setAttr ".dr" yes;
	setAttr ".ai_translator" -type "string" "perspective";
createNode lightLinker -s -n "lightLinker1";
	rename -uid "77747829-413C-0556-7449-4E81CF1F02BF";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "51359F71-4B18-4661-FA35-34A02DCF1785";
	setAttr ".bsdt[0].bscd" -type "Int32Array" 1 0 ;
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "4C2C33C6-4876-C240-A190-EE98F29E2903";
createNode displayLayerManager -n "layerManager";
	rename -uid "56677627-4BC9-4C65-217B-B4B039A310D9";
createNode displayLayer -n "defaultLayer";
	rename -uid "B4A9A8EB-47B1-1301-5F6C-4687950E3E5E";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "DC6CCD6F-4AAC-BC15-FB5D-61B3FB1762FA";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "7F7C254D-4AA6-16A8-00D4-81B62C35963B";
	setAttr ".g" yes;
createNode polyCube -n "polyCube1";
	rename -uid "D0DF4715-481F-95AB-8AA0-D4BACE01D98F";
	setAttr ".h" 5;
	setAttr ".sh" 5;
	setAttr ".cuv" 4;
createNode script -n "uiConfigurationScriptNode";
	rename -uid "EC8E308D-42CF-689D-CAEA-FFB37284F009";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $nodeEditorPanelVisible = stringArrayContains(\"nodeEditorPanel1\", `getPanel -vis`);\n\tint    $nodeEditorWorkspaceControlOpen = (`workspaceControl -exists nodeEditorPanel1Window` && `workspaceControl -q -visible nodeEditorPanel1Window`);\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\n\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n"
		+ "            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 663\n            -height 1054\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n"
		+ "            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n"
		+ "            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 663\n            -height 505\n"
		+ "            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n"
		+ "            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n"
		+ "            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n"
		+ "            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 663\n            -height 1054\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"camera1\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n"
		+ "            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 1\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n"
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
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -displayValues 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -frameRange -62.790346 510.290346 \n                -initialized 1\n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n"
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
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -camera \\\"camera1\\\" \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 1\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1333\\n    -height 1054\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -camera \\\"camera1\\\" \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 1\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1333\\n    -height 1054\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 10 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "F73172AE-431E-C65E-2119-0FB6E7DEE1FC";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 300 -ast 1 -aet 300 ";
	setAttr ".st" 6;
createNode blendShape -n "blendShape1";
	rename -uid "7EA2D131-48BC-E4B5-E208-C78B9C20FC41";
	addAttr -ci true -h true -sn "aal" -ln "attributeAliasList" -dt "attributeAlias";
	setAttr -s 3 ".w";
	setAttr -s 3 ".w";
	setAttr -s 3 ".it[0].itg";
	setAttr ".mlid" 0;
	setAttr ".mlpr" 0;
	setAttr -s 3 ".pndr[0:2]"  0 0 0;
	setAttr ".tgdt[0].cid" -type "Int32Array" 3 0 1 2 ;
	setAttr ".aal" -type "attributeAlias" {"target3","weight[0]","target2","weight[1]"
		,"target1","weight[2]"} ;
createNode tweak -n "tweak1";
	rename -uid "E762CE4D-437D-702A-289A-2BBA7B4BA341";
createNode objectSet -n "blendShape1Set";
	rename -uid "B7DD1F34-4F1F-8478-43FF-BD803E76DCCA";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "blendShape1GroupId";
	rename -uid "5865CD67-4E00-8384-A5FC-E8B65FE5B181";
	setAttr ".ihi" 0;
createNode groupParts -n "blendShape1GroupParts";
	rename -uid "D97E1207-43B6-0354-7D60-BE8E9B8DC917";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode objectSet -n "tweakSet1";
	rename -uid "924ECB26-4516-F115-5E6F-BE8065F3E523";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "groupId2";
	rename -uid "63A278ED-457B-1811-E2EE-55A9845920A5";
	setAttr ".ihi" 0;
createNode groupParts -n "groupParts2";
	rename -uid "B7F679EA-4E96-5333-5BA3-27B09D94BD81";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode skinCluster -n "skinCluster1";
	rename -uid "5B876C25-4DF5-A02A-B1E3-3F8DB7F5D653";
	setAttr -s 24 ".wl";
	setAttr ".wl[0:23].w"
		5 0 0.91617671772720477 1 0.068145375698717703 2 0.0113108236756445 
		3 0.0031701616530353089 4 0.0011969212453977124
		5 0 0.91617671772720477 1 0.068145375698717703 2 0.0113108236756445 
		3 0.0031701616530353089 4 0.0011969212453977124
		5 0 0.67361517143952521 1 0.29938452063978915 2 0.022268270130232248 
		3 0.0036961051930838157 4 0.001035932597369512
		5 0 0.67361517143952521 1 0.29938452063978915 2 0.022268270130232248 
		3 0.0036961051930838157 4 0.001035932597369512
		5 0 0.23058870583529889 1 0.51882458812942223 2 0.23058870583529889 
		3 0.017151226053865203 4 0.0028467741461148002
		5 0 0.23058870583529889 1 0.51882458812942223 2 0.23058870583529889 
		3 0.017151226053865203 4 0.0028467741461148002
		5 0 0.016909347111319872 1 0.2273367778299672 2 0.51150775011742589 
		3 0.2273367778299672 4 0.016909347111319872
		5 0 0.016909347111319872 1 0.2273367778299672 2 0.51150775011742589 
		3 0.2273367778299672 4 0.016909347111319872
		5 0 0.0028467741461148002 1 0.017151226053865203 2 0.23058870583529889 
		3 0.51882458812942223 4 0.23058870583529889
		5 0 0.0028467741461148002 1 0.017151226053865203 2 0.23058870583529889 
		3 0.51882458812942223 4 0.23058870583529889
		5 0 0.0016554543598107491 1 0.005906497654139589 2 0.035585428015436037 
		3 0.47842630998530683 4 0.47842630998530683
		5 0 0.0016554543598107491 1 0.005906497654139589 2 0.035585428015436037 
		3 0.47842630998530683 4 0.47842630998530683
		5 0 0.0016554543598107491 1 0.005906497654139589 2 0.035585428015436037 
		3 0.47842630998530683 4 0.47842630998530683
		5 0 0.0016554543598107491 1 0.005906497654139589 2 0.035585428015436037 
		3 0.47842630998530683 4 0.47842630998530683
		5 0 0.0028467741461148002 1 0.017151226053865203 2 0.23058870583529889 
		3 0.51882458812942223 4 0.23058870583529889
		5 0 0.0028467741461148002 1 0.017151226053865203 2 0.23058870583529889 
		3 0.51882458812942223 4 0.23058870583529889
		5 0 0.016909347111319872 1 0.2273367778299672 2 0.51150775011742589 
		3 0.2273367778299672 4 0.016909347111319872
		5 0 0.016909347111319872 1 0.2273367778299672 2 0.51150775011742589 
		3 0.2273367778299672 4 0.016909347111319872
		5 0 0.23058870583529889 1 0.51882458812942223 2 0.23058870583529889 
		3 0.017151226053865203 4 0.0028467741461148002
		5 0 0.23058870583529889 1 0.51882458812942223 2 0.23058870583529889 
		3 0.017151226053865203 4 0.0028467741461148002
		5 0 0.67361517143952521 1 0.29938452063978915 2 0.022268270130232248 
		3 0.0036961051930838157 4 0.001035932597369512
		5 0 0.67361517143952521 1 0.29938452063978915 2 0.022268270130232248 
		3 0.0036961051930838157 4 0.001035932597369512
		5 0 0.91617671772720477 1 0.068145375698717703 2 0.0113108236756445 
		3 0.0031701616530353089 4 0.0011969212453977124
		5 0 0.91617671772720477 1 0.068145375698717703 2 0.0113108236756445 
		3 0.0031701616530353089 4 0.0011969212453977124;
	setAttr -s 5 ".pm";
	setAttr ".pm[0]" -type "matrix" 2.2204460492503131e-16 -1 0 0 1 2.2204460492503131e-16 0 0
		 0 0 1 0 -0.5 -1.1102230246251565e-16 0 1;
	setAttr ".pm[1]" -type "matrix" 2.2204460492503131e-16 -1 0 0 1 2.2204460492503131e-16 0 0
		 0 0 1 0 -1.5 -3.3306690738754696e-16 0 1;
	setAttr ".pm[2]" -type "matrix" 2.2204460492503131e-16 -1 0 0 1 2.2204460492503131e-16 0 0
		 0 0 1 0 -2.5 -5.5511151231257827e-16 0 1;
	setAttr ".pm[3]" -type "matrix" 2.2204460492503131e-16 -1 0 0 1 2.2204460492503131e-16 0 0
		 0 0 1 0 -3.5 -7.7715611723760958e-16 0 1;
	setAttr ".pm[4]" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 -4.5 0 1;
	setAttr ".gm" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 2.5 0 1;
	setAttr -s 5 ".ma";
	setAttr -s 5 ".dpf[0:4]"  4 4 4 4 4;
	setAttr -s 5 ".lw";
	setAttr -s 5 ".lw";
	setAttr ".mmi" yes;
	setAttr ".mi" 5;
	setAttr ".ucm" yes;
	setAttr -s 5 ".ifcl";
	setAttr -s 5 ".ifcl";
createNode objectSet -n "skinCluster1Set";
	rename -uid "B19A2755-4E89-3E02-AF2D-35BA9877E22A";
	setAttr ".ihi" 0;
	setAttr ".vo" yes;
createNode groupId -n "skinCluster1GroupId";
	rename -uid "3382336A-4CA2-4CAB-412B-ABB47B0895BB";
	setAttr ".ihi" 0;
createNode groupParts -n "skinCluster1GroupParts";
	rename -uid "F6D1B5BE-4870-ED8D-F5DD-C28DF96EBF49";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "vtx[*]";
createNode dagPose -n "bindPose1";
	rename -uid "FB088B59-4D36-2AB3-BDE7-DDAD5EA580F3";
	setAttr -s 5 ".wm";
	setAttr -s 5 ".xm";
	setAttr ".xm[0]" -type "matrix" "xform" 1 1 1 0 0 0 0 0 0.5 0 0 0 0 0 0 0 0
		 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0.70710678118654746 0.70710678118654757 1 1 1 yes;
	setAttr ".xm[1]" -type "matrix" "xform" 1 1 1 0 0 0 0 1 2.2204460492503131e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 yes;
	setAttr ".xm[2]" -type "matrix" "xform" 1 1 1 0 0 0 0 1 2.2204460492503131e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 yes;
	setAttr ".xm[3]" -type "matrix" "xform" 1 1 1 0 0 0 0 1 2.2204460492503131e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 1 1 yes;
	setAttr ".xm[4]" -type "matrix" "xform" 1 1 1 0 0 0 0 1 2.2204460492503131e-16
		 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 -0.70710678118654746 0.70710678118654757 1
		 1 1 yes;
	setAttr -s 5 ".m";
	setAttr -s 5 ".p";
	setAttr ".bp" yes;
createNode character -n "character_set";
	rename -uid "0E29FC62-4828-4A3E-A79A-B4A3D560A8FE";
	addAttr -ci true -h true -sn "aal" -ln "attributeAliasList" -dt "attributeAlias";
	setAttr -s 4 ".dnsm";
	setAttr -s 26 ".uv[1:26]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
		0 0 0 0 0 0;
	setAttr -s 3 ".uv";
	setAttr -s 14 ".lv[2:15]"  0.5 0 0 2.2204460492503131e-16 1 0 2.2204460492503131e-16 
		1 0 2.2204460492503131e-16 1 0 2.2204460492503131e-16 1;
	setAttr ".av[1]"  -36;
	setAttr ".am" -type "characterMapping" 4 "blendShape1.target3" 0 21 "blendShape1.target1" 
		0 22 "blendShape1.target2" 0 23 "joint1.rotateZ" 2 1  ;
	setAttr ".cim" -type "Int32Array" 4 0 1 2 3 ;
	setAttr ".tcs" 266;
	setAttr ".tce" 290;
	setAttr ".aal" -type "attributeAlias" {"joint3_rotateZ","angularValues[10]","joint2_rotateZ"
		,"angularValues[13]","joint1_rotateZ","angularValues[1]","joint5_rotateZ","angularValues[4]"
		,"joint4_rotateZ","angularValues[7]","blendShape1_target3","unitlessValues[21]","blendShape1_target1"
		,"unitlessValues[22]","blendShape1_target2","unitlessValues[23]"} ;
createNode trackInfoManager -n "trackInfoManager1";
	rename -uid "648FBF04-4D18-0C76-CD6D-41A1A9DD508F";
createNode animCurveTU -n "character_set_blendShape1_target3";
	rename -uid "48871E22-4A66-D0FE-E00D-DD9BA5245B73";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character_set_blendShape1_target1";
	rename -uid "99C882B2-4D26-A4FC-7708-EAA9A189FF09";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode animCurveTU -n "character_set_blendShape1_target2";
	rename -uid "4C681906-42D3-AE32-9E8A-0CB6A9228E30";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode clipScheduler -n "character_setScheduler1";
	rename -uid "1ADC1FB9-4CC6-507C-392F-0B811DD71345";
	setAttr -s 10 ".cl";
	setAttr -s 10 ".st";
	setAttr -s 10 ".ss";
	setAttr -s 10 ".se";
	setAttr -s 10 ".sc";
	setAttr -s 10 ".h";
	setAttr -s 10 ".w";
	setAttr -s 10 ".ws";
	setAttr -s 10 ".cb";
	setAttr -s 10 ".ca";
	setAttr -s 10 ".ea";
	setAttr -s 10 ".tr";
	setAttr ".tr[0]" 1;
	setAttr ".tr[1]" 1;
	setAttr ".tr[2]" 1;
	setAttr ".tr[3]" 1;
	setAttr ".tr[4]" 1;
	setAttr ".tr[8]" 1;
	setAttr ".tr[9]" 2;
	setAttr ".tr[10]" 2;
	setAttr ".tr[11]" 2;
	setAttr ".tr[12]" 1;
	setAttr ".nt" 9;
createNode clipLibrary -n "character_setClips1";
	rename -uid "F5C329E5-4C99-BBC5-FC7D-2AB615652AFC";
	setAttr -s 6 ".cel";
	setAttr -s 4 ".cel[0].cev";
	setAttr -s 3 ".cel[1].cev";
	setAttr -s 3 ".cel[2].cev";
	setAttr -s 3 ".cel[3].cev";
	setAttr -s 4 ".cel[4].cev";
	setAttr -s 4 ".cel[5].cev";
	setAttr -s 6 ".sc";
	setAttr -s 6 ".cl";
createNode animClip -n "setupSource";
	rename -uid "EBAACE3B-4F0F-1627-7D02-E283F1210B4A";
	setAttr ".ihi" 0;
	setAttr ".ss" 1;
	setAttr ".se" 1;
	setAttr ".ci" no;
createNode animClip -n "setup";
	rename -uid "3F8078E3-42F8-3965-FE31-8484475412D9";
	setAttr -s 43 ".ac";
	setAttr ".ac[0]" yes;
	setAttr ".ac[1]" yes;
	setAttr ".ac[2]" yes;
	setAttr ".ac[10]" yes;
	setAttr ".ac[11]" yes;
	setAttr ".ac[12]" yes;
	setAttr ".ac[13]" yes;
	setAttr ".ac[14]" yes;
	setAttr ".ac[15]" yes;
	setAttr ".ac[16]" yes;
	setAttr ".ac[17]" yes;
	setAttr ".ac[18]" yes;
	setAttr ".ac[19]" yes;
	setAttr ".ac[20]" yes;
	setAttr ".ac[21]" yes;
	setAttr ".ac[22]" yes;
	setAttr ".ac[23]" yes;
	setAttr ".ac[24]" yes;
	setAttr ".ac[25]" yes;
	setAttr ".ac[26]" yes;
	setAttr ".ac[27]" yes;
	setAttr ".ac[28]" yes;
	setAttr ".ac[29]" yes;
	setAttr ".ac[30]" yes;
	setAttr ".ac[31]" yes;
	setAttr ".ac[32]" yes;
	setAttr ".ac[33]" yes;
	setAttr ".ac[34]" yes;
	setAttr ".ac[35]" yes;
	setAttr ".ac[36]" yes;
	setAttr ".ac[37]" yes;
	setAttr ".ac[38]" yes;
	setAttr ".ac[39]" yes;
	setAttr ".ac[40]" yes;
	setAttr ".ac[41]" yes;
	setAttr ".ac[42]" yes;
	setAttr ".ac[43]" yes;
	setAttr ".ac[44]" yes;
	setAttr ".ac[45]" yes;
	setAttr ".ac[46]" yes;
	setAttr ".ac[47]" yes;
	setAttr ".ac[48]" yes;
	setAttr ".ac[49]" yes;
	setAttr ".sf" -10;
	setAttr ".ss" 1;
	setAttr ".se" 10;
createNode animCurveTU -n "character_set_blendShape1_target4";
	rename -uid "566769D6-439B-657C-802E-A1B3D4FC1E2A";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 0 20 0 30 0 40 0;
	setAttr -s 5 ".kit[0:4]"  1 18 18 18 18;
	setAttr -s 5 ".kot[0:4]"  1 18 18 18 18;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
createNode animCurveTU -n "character_set_blendShape1_target5";
	rename -uid "3C8E6EDB-44E9-EBE6-0E14-0AA7FBA4F69B";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 1 20 0 30 -1 40 0;
	setAttr -s 5 ".kit[0:4]"  1 18 18 18 18;
	setAttr -s 5 ".kot[0:4]"  1 18 18 18 18;
	setAttr -s 5 ".kix[0:4]"  1 1 0.38461538461538458 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 -0.92307692307692313 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 0.38461538461538458 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 -0.92307692307692313 0 0;
createNode animCurveTU -n "character_set_blendShape1_target6";
	rename -uid "382D076E-4D90-4606-38B3-2EA765E0AB63";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 0 20 0 30 0 40 0;
	setAttr -s 5 ".kit[0:4]"  1 18 18 18 18;
	setAttr -s 5 ".kot[0:4]"  1 18 18 18 18;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
createNode animClip -n "clip_target1Source";
	rename -uid "B7E2B415-45A3-5134-30C0-479D7BC92318";
	setAttr ".ihi" 0;
	setAttr ".ss" 30;
	setAttr ".se" 70;
	setAttr ".ci" no;
createNode animClip -n "clip_target1";
	rename -uid "C0D0F4FB-4237-B0F1-F1AA-72ACFB2A9F06";
	setAttr -s 43 ".ac";
	setAttr ".ac[0]" yes;
	setAttr ".ac[1]" yes;
	setAttr ".ac[2]" yes;
	setAttr ".ac[10]" yes;
	setAttr ".ac[11]" yes;
	setAttr ".ac[12]" yes;
	setAttr ".ac[13]" yes;
	setAttr ".ac[14]" yes;
	setAttr ".ac[15]" yes;
	setAttr ".ac[16]" yes;
	setAttr ".ac[17]" yes;
	setAttr ".ac[18]" yes;
	setAttr ".ac[19]" yes;
	setAttr ".ac[20]" yes;
	setAttr ".ac[21]" yes;
	setAttr ".ac[22]" yes;
	setAttr ".ac[23]" yes;
	setAttr ".ac[24]" yes;
	setAttr ".ac[25]" yes;
	setAttr ".ac[26]" yes;
	setAttr ".ac[27]" yes;
	setAttr ".ac[28]" yes;
	setAttr ".ac[29]" yes;
	setAttr ".ac[30]" yes;
	setAttr ".ac[31]" yes;
	setAttr ".ac[32]" yes;
	setAttr ".ac[33]" yes;
	setAttr ".ac[34]" yes;
	setAttr ".ac[35]" yes;
	setAttr ".ac[36]" yes;
	setAttr ".ac[37]" yes;
	setAttr ".ac[38]" yes;
	setAttr ".ac[39]" yes;
	setAttr ".ac[40]" yes;
	setAttr ".ac[41]" yes;
	setAttr ".ac[42]" yes;
	setAttr ".ac[43]" yes;
	setAttr ".ac[44]" yes;
	setAttr ".ac[45]" yes;
	setAttr ".ac[46]" yes;
	setAttr ".ac[47]" yes;
	setAttr ".ac[48]" yes;
	setAttr ".ac[49]" yes;
	setAttr ".sf" 1;
	setAttr ".ss" 1;
	setAttr ".se" 40;
createNode animCurveTU -n "character_set_blendShape1_target7";
	rename -uid "5F695200-4BED-AFC8-DEEA-619A7A7F75FE";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 0 20 0 30 0 40 0;
createNode animCurveTU -n "character_set_blendShape1_target8";
	rename -uid "B4EF06B7-42AF-9588-8C1D-D6BC641A3E4F";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 0 20 0 30 0 40 0;
createNode animCurveTU -n "character_set_blendShape1_target9";
	rename -uid "0DFFC0BC-45C3-4FA2-79E9-588D4BBAC9E0";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 1 20 0 30 -1 40 0;
createNode animClip -n "clip_target2Source";
	rename -uid "2E6AED3B-427D-590B-956D-49A9D1601F30";
	setAttr ".ihi" 0;
	setAttr ".ss" 1;
	setAttr ".se" 40;
	setAttr ".ci" no;
createNode animClip -n "clip_target2";
	rename -uid "A9AEA2A6-46D7-3120-E958-08976DA4E1B9";
	setAttr -s 43 ".ac";
	setAttr ".ac[0]" yes;
	setAttr ".ac[1]" yes;
	setAttr ".ac[2]" yes;
	setAttr ".ac[10]" yes;
	setAttr ".ac[11]" yes;
	setAttr ".ac[12]" yes;
	setAttr ".ac[13]" yes;
	setAttr ".ac[14]" yes;
	setAttr ".ac[15]" yes;
	setAttr ".ac[16]" yes;
	setAttr ".ac[17]" yes;
	setAttr ".ac[18]" yes;
	setAttr ".ac[19]" yes;
	setAttr ".ac[20]" yes;
	setAttr ".ac[21]" yes;
	setAttr ".ac[22]" yes;
	setAttr ".ac[23]" yes;
	setAttr ".ac[24]" yes;
	setAttr ".ac[25]" yes;
	setAttr ".ac[26]" yes;
	setAttr ".ac[27]" yes;
	setAttr ".ac[28]" yes;
	setAttr ".ac[29]" yes;
	setAttr ".ac[30]" yes;
	setAttr ".ac[31]" yes;
	setAttr ".ac[32]" yes;
	setAttr ".ac[33]" yes;
	setAttr ".ac[34]" yes;
	setAttr ".ac[35]" yes;
	setAttr ".ac[36]" yes;
	setAttr ".ac[37]" yes;
	setAttr ".ac[38]" yes;
	setAttr ".ac[39]" yes;
	setAttr ".ac[40]" yes;
	setAttr ".ac[41]" yes;
	setAttr ".ac[42]" yes;
	setAttr ".ac[43]" yes;
	setAttr ".ac[44]" yes;
	setAttr ".ac[45]" yes;
	setAttr ".ac[46]" yes;
	setAttr ".ac[47]" yes;
	setAttr ".ac[48]" yes;
	setAttr ".ac[49]" yes;
	setAttr ".sf" 50;
	setAttr ".ss" 1;
	setAttr ".se" 40;
createNode animCurveTU -n "character_set_blendShape1_target10";
	rename -uid "F33C57EF-4CC4-2388-EA6A-FD9B2ACF3162";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 1 20 0 30 -1 40 0;
createNode animCurveTU -n "character_set_blendShape1_target11";
	rename -uid "72BB84CE-4772-23B5-9425-248ADC7CF604";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 0 20 0 30 0 40 0;
createNode animCurveTU -n "character_set_blendShape1_target12";
	rename -uid "4F4815C8-496D-42B1-89FF-81801F11E2DD";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 10 0 20 0 30 0 40 0;
createNode animClip -n "clip_target3Source";
	rename -uid "23605AF3-421F-A095-2411-7A8F6C4601A4";
	setAttr ".ihi" 0;
	setAttr ".ss" 1;
	setAttr ".se" 40;
	setAttr ".ci" no;
createNode animClip -n "clip_target3";
	rename -uid "11715892-4C23-470E-6951-EE949CC80B4A";
	setAttr -s 43 ".ac";
	setAttr ".ac[0]" yes;
	setAttr ".ac[1]" yes;
	setAttr ".ac[2]" yes;
	setAttr ".ac[10]" yes;
	setAttr ".ac[11]" yes;
	setAttr ".ac[12]" yes;
	setAttr ".ac[13]" yes;
	setAttr ".ac[14]" yes;
	setAttr ".ac[15]" yes;
	setAttr ".ac[16]" yes;
	setAttr ".ac[17]" yes;
	setAttr ".ac[18]" yes;
	setAttr ".ac[19]" yes;
	setAttr ".ac[20]" yes;
	setAttr ".ac[21]" yes;
	setAttr ".ac[22]" yes;
	setAttr ".ac[23]" yes;
	setAttr ".ac[24]" yes;
	setAttr ".ac[25]" yes;
	setAttr ".ac[26]" yes;
	setAttr ".ac[27]" yes;
	setAttr ".ac[28]" yes;
	setAttr ".ac[29]" yes;
	setAttr ".ac[30]" yes;
	setAttr ".ac[31]" yes;
	setAttr ".ac[32]" yes;
	setAttr ".ac[33]" yes;
	setAttr ".ac[34]" yes;
	setAttr ".ac[35]" yes;
	setAttr ".ac[36]" yes;
	setAttr ".ac[37]" yes;
	setAttr ".ac[38]" yes;
	setAttr ".ac[39]" yes;
	setAttr ".ac[40]" yes;
	setAttr ".ac[41]" yes;
	setAttr ".ac[42]" yes;
	setAttr ".ac[43]" yes;
	setAttr ".ac[44]" yes;
	setAttr ".ac[45]" yes;
	setAttr ".ac[46]" yes;
	setAttr ".ac[47]" yes;
	setAttr ".ac[48]" yes;
	setAttr ".ac[49]" yes;
	setAttr ".sf" 100;
	setAttr ".ss" 1;
	setAttr ".se" 40;
createNode animCurveTU -n "character_set_blendShape1_target13";
	rename -uid "AFAA6C1E-464B-8E28-6B96-229F4ED92922";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 30 0 60 0 90 0 120 0;
createNode animCurveTU -n "character_set_blendShape1_target14";
	rename -uid "51A3C6C3-489B-1295-CF38-AABE19831B91";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 30 0 60 0 90 0 120 0;
createNode animCurveTU -n "character_set_blendShape1_target15";
	rename -uid "602AD4B2-4D87-9B63-5503-548193042D4A";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 30 0 60 0 90 0 120 0;
createNode animCurveTA -n "joint1_rotateX";
	rename -uid "1544E740-48B0-C740-BF03-AFB4527C58B7";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  1 0 30 0;
createNode animCurveTA -n "joint1_rotateZ";
	rename -uid "E11509F0-4319-357C-9C0D-408B176D467D";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  1 0 30 -20 60 0 90 20 120 0;
	setAttr -s 5 ".kbd[0:4]" yes no no no no;
createNode pairBlend -n "pairBlend1";
	rename -uid "219DE558-4FFD-558D-C1E8-BFB565460FBA";
	setAttr ".txm" 2;
	setAttr ".tym" 2;
	setAttr ".tzm" 2;
createNode animCurveTA -n "pairBlend1_inRotateZ1";
	rename -uid "5295F275-46CC-CDC6-FBBC-1EA226BB1711";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode pairBlend -n "pairBlend2";
	rename -uid "77C69CC4-4B81-39BC-DB72-D4B457032B93";
	setAttr ".txm" 2;
	setAttr ".tym" 2;
	setAttr ".tzm" 2;
createNode animCurveTA -n "pairBlend2_inRotateZ1";
	rename -uid "CD88EB99-4335-1844-FA5A-E893EB9FDCA3";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode pairBlend -n "pairBlend3";
	rename -uid "3974C23D-4987-CD9E-C9DB-4A82FC691F00";
	setAttr ".txm" 2;
	setAttr ".tym" 2;
	setAttr ".tzm" 2;
createNode animCurveTA -n "pairBlend3_inRotateZ1";
	rename -uid "887CF097-4A1D-8B90-26EC-BEA9F89A2820";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode pairBlend -n "pairBlend4";
	rename -uid "43BC8CFF-4CF0-AEA8-DB5F-BD8E7AD3EB52";
	setAttr ".txm" 2;
	setAttr ".tym" 2;
	setAttr ".tzm" 2;
createNode animCurveTA -n "pairBlend4_inRotateZ1";
	rename -uid "6B0CDDE7-4EA3-EDE0-2C29-32B051F0FA5B";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode pairBlend -n "pairBlend5";
	rename -uid "23D98614-46D5-4776-06DB-FBA27750A647";
	setAttr ".txm" 2;
	setAttr ".tym" 2;
	setAttr ".tzm" 2;
createNode animCurveTA -n "pairBlend5_inRotateZ1";
	rename -uid "53A726CA-495F-DFB3-E2E0-8CB6F7F2B1C2";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  1 -20 30 -20;
	setAttr -s 2 ".kbd[0:1]" yes no;
createNode pairBlend -n "pairBlend6";
	rename -uid "7AC2C5E0-401D-59FC-F602-97BBE802384D";
	setAttr ".txm" 2;
	setAttr ".tym" 2;
	setAttr ".tzm" 2;
createNode animCurveTA -n "pairBlend6_inRotateZ1";
	rename -uid "E00B7E83-4080-F437-BF6A-908686ECEEED";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  1 -20 30 -20;
	setAttr -s 2 ".kbd[0:1]" yes no;
createNode pairBlend -n "pairBlend7";
	rename -uid "A0A3AC7F-4D00-C33A-23F7-D0A3DB8CE76F";
	setAttr ".txm" 2;
	setAttr ".tym" 2;
	setAttr ".tzm" 2;
createNode animCurveTA -n "pairBlend7_inRotateZ1";
	rename -uid "2022A2F6-4224-9F9A-EE3C-D7B6D6957115";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  1 -20 30 -20;
	setAttr -s 2 ".kbd[0:1]" yes no;
createNode pairBlend -n "pairBlend8";
	rename -uid "B327F2CE-4471-975F-FC9E-C49F3872D5F0";
	setAttr ".txm" 2;
	setAttr ".tym" 2;
	setAttr ".tzm" 2;
createNode animCurveTA -n "pairBlend8_inRotateZ1";
	rename -uid "F3422A84-4415-94CF-5627-748E15FF87A7";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 -20;
	setAttr ".kbd[0]" yes;
createNode animClip -n "clip_joint_rot_zSource";
	rename -uid "02FAFC4D-4F1A-000D-FC11-F3B2AC35D778";
	setAttr ".ihi" 0;
	setAttr ".ss" 1;
	setAttr ".se" 120;
	setAttr ".ci" no;
createNode animClip -n "clip_joint_rot_z";
	rename -uid "1C3DFB98-4892-437E-84D1-A98EDD19EB55";
	setAttr -s 4 ".ac[0:3]" yes yes yes yes;
	setAttr ".sf" 150;
	setAttr ".sc" 0.25;
	setAttr ".ss" 1;
	setAttr ".se" 120;
createNode animClip -n "clip_target6";
	rename -uid "9C196431-44B3-090A-0729-588D774735BE";
	setAttr -s 64 ".ac[0:63]" yes yes yes no no no no no no no yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes no no no no no 
		no no no no no no no no no;
	setAttr ".sf" 234;
	setAttr ".sc" 0.5;
	setAttr ".ss" 1;
	setAttr ".se" 40;
createNode animClip -n "clip_target5";
	rename -uid "0BEBC150-40C1-503D-2DB7-CCA20EDFD6BF";
	setAttr -s 64 ".ac[0:63]" yes yes yes no no no no no no no yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes no no no no no 
		no no no no no no no no no;
	setAttr ".sf" 214;
	setAttr ".sc" 0.5;
	setAttr ".ss" 1;
	setAttr ".se" 40;
createNode animClip -n "clip_target4";
	rename -uid "9188E84A-4146-18BD-A31D-DA88E4B83759";
	setAttr -s 64 ".ac[0:63]" yes yes yes no no no no no no no yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes no no no no no 
		no no no no no no no no no;
	setAttr ".sf" 194;
	setAttr ".sc" 0.5;
	setAttr ".ss" 1;
	setAttr ".se" 40;
createNode animClip -n "clip_joint_rot_z_dup";
	rename -uid "FE940260-4519-8188-94EB-47A22344F6C3";
	setAttr -s 32 ".ac[0:31]" yes yes yes yes no no no no no no no no 
		no no no no no no no no no no no no no no no no no no no no;
	setAttr ".sf" 194;
	setAttr ".sc" 0.5;
	setAttr ".ss" 1;
	setAttr ".se" 120;
createNode animCurveTA -n "character_set_joint1_rotateZ";
	rename -uid "263F8935-4256-F56F-8376-AAA129624B78";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  1 0;
createNode script -n "maya2glTF_scriptNode";
	rename -uid "505B6A66-4A15-6774-6FF5-3D8433609167";
	addAttr -ci true -sn "outputFolder" -ln "outputFolder" -dt "string";
	addAttr -ci true -sn "sceneName" -ln "sceneName" -dt "string";
	addAttr -ci true -sn "copyright" -ln "copyright" -dt "string";
	addAttr -ci true -sn "scale" -ln "scale" -at "float";
	addAttr -ci true -sn "flags" -ln "flags" -dt "string";
	addAttr -ci true -sn "char" -ln "char" -dt "string";
	addAttr -ci true -sn "anim" -ln "anim" -at "long";
	addAttr -ci true -sn "clip" -ln "clip" -dt "string";
	setAttr ".st" 2;
	setAttr ".outputFolder" -type "string" "C:/dev/glTF/Maya2glTF/maya/scenes/complex/export/";
	setAttr ".sceneName" -type "string" "ComplexAnim1";
	setAttr ".copyright" -type "string" "(C)2018 bugfa";
	setAttr ".scale" 1;
	setAttr ".flags" -type "string" "";
	setAttr ".char" -type "string" "character_set";
	setAttr ".anim" 4;
	setAttr ".clip" -type "string" "clip";
createNode nodeGraphEditorInfo -n "MayaNodeEditorSavedTabsInfo";
	rename -uid "77BD6873-4C5E-87D9-4715-E9B0D7B9E858";
	setAttr ".tgi[0].tn" -type "string" "Untitled_1";
	setAttr ".tgi[0].vl" -type "double2" -1805.3523989203343 -2670.2379891323708 ;
	setAttr ".tgi[0].vh" -type "double2" 472.01911856890518 -1529.7618439746307 ;
	setAttr -s 47 ".tgi[0].ni";
	setAttr ".tgi[0].ni[0].x" -930;
	setAttr ".tgi[0].ni[0].y" -2508.571533203125;
	setAttr ".tgi[0].ni[0].nvs" 18304;
	setAttr ".tgi[0].ni[1].x" -930;
	setAttr ".tgi[0].ni[1].y" -3782.857177734375;
	setAttr ".tgi[0].ni[1].nvs" 18304;
	setAttr ".tgi[0].ni[2].x" -1544.2857666015625;
	setAttr ".tgi[0].ni[2].y" -1081.4285888671875;
	setAttr ".tgi[0].ni[2].nvs" 18304;
	setAttr ".tgi[0].ni[3].x" -4922.85693359375;
	setAttr ".tgi[0].ni[3].y" -944.28570556640625;
	setAttr ".tgi[0].ni[3].nvs" 18304;
	setAttr ".tgi[0].ni[4].x" -4922.85693359375;
	setAttr ".tgi[0].ni[4].y" -1248.5714111328125;
	setAttr ".tgi[0].ni[4].nvs" 18304;
	setAttr ".tgi[0].ni[5].x" -4615.71435546875;
	setAttr ".tgi[0].ni[5].y" -1350;
	setAttr ".tgi[0].ni[5].nvs" 18304;
	setAttr ".tgi[0].ni[6].x" -4922.85693359375;
	setAttr ".tgi[0].ni[6].y" -1552.857177734375;
	setAttr ".tgi[0].ni[6].nvs" 18304;
	setAttr ".tgi[0].ni[7].x" -255.71427917480469;
	setAttr ".tgi[0].ni[7].y" -1078.5714111328125;
	setAttr ".tgi[0].ni[7].nvs" 18306;
	setAttr ".tgi[0].ni[8].x" -2465.71435546875;
	setAttr ".tgi[0].ni[8].y" -1112.857177734375;
	setAttr ".tgi[0].ni[8].nvs" 18304;
	setAttr ".tgi[0].ni[9].x" -2772.857177734375;
	setAttr ".tgi[0].ni[9].y" -1132.857177734375;
	setAttr ".tgi[0].ni[9].nvs" 18304;
	setAttr ".tgi[0].ni[10].x" -4922.85693359375;
	setAttr ".tgi[0].ni[10].y" -1350;
	setAttr ".tgi[0].ni[10].nvs" 18304;
	setAttr ".tgi[0].ni[11].x" -562.85711669921875;
	setAttr ".tgi[0].ni[11].y" -2305.71435546875;
	setAttr ".tgi[0].ni[11].nvs" 18304;
	setAttr ".tgi[0].ni[12].x" -4922.85693359375;
	setAttr ".tgi[0].ni[12].y" -1147.142822265625;
	setAttr ".tgi[0].ni[12].nvs" 18304;
	setAttr ".tgi[0].ni[13].x" -930;
	setAttr ".tgi[0].ni[13].y" -3421.428466796875;
	setAttr ".tgi[0].ni[13].nvs" 18304;
	setAttr ".tgi[0].ni[14].x" -4922.85693359375;
	setAttr ".tgi[0].ni[14].y" -1045.7142333984375;
	setAttr ".tgi[0].ni[14].nvs" 18304;
	setAttr ".tgi[0].ni[15].x" -2158.571533203125;
	setAttr ".tgi[0].ni[15].y" -1010;
	setAttr ".tgi[0].ni[15].nvs" 18306;
	setAttr ".tgi[0].ni[16].x" -1237.142822265625;
	setAttr ".tgi[0].ni[16].y" -977.14288330078125;
	setAttr ".tgi[0].ni[16].nvs" 18306;
	setAttr ".tgi[0].ni[17].x" -930;
	setAttr ".tgi[0].ni[17].y" -2001.4285888671875;
	setAttr ".tgi[0].ni[17].nvs" 18304;
	setAttr ".tgi[0].ni[18].x" -562.85711669921875;
	setAttr ".tgi[0].ni[18].y" -981.4285888671875;
	setAttr ".tgi[0].ni[18].nvs" 18304;
	setAttr ".tgi[0].ni[19].x" -930;
	setAttr ".tgi[0].ni[19].y" -3015.71435546875;
	setAttr ".tgi[0].ni[19].nvs" 18304;
	setAttr ".tgi[0].ni[20].x" -4001.428466796875;
	setAttr ".tgi[0].ni[20].y" -1085.7142333984375;
	setAttr ".tgi[0].ni[20].nvs" 18306;
	setAttr ".tgi[0].ni[21].x" -4922.85693359375;
	setAttr ".tgi[0].ni[21].y" -1755.7142333984375;
	setAttr ".tgi[0].ni[21].nvs" 18304;
	setAttr ".tgi[0].ni[22].x" -930;
	setAttr ".tgi[0].ni[22].y" -1118.5714111328125;
	setAttr ".tgi[0].ni[22].nvs" 18304;
	setAttr ".tgi[0].ni[23].x" -3694.28564453125;
	setAttr ".tgi[0].ni[23].y" -1304.2857666015625;
	setAttr ".tgi[0].ni[23].nvs" 18304;
	setAttr ".tgi[0].ni[24].x" -930;
	setAttr ".tgi[0].ni[24].y" -2711.428466796875;
	setAttr ".tgi[0].ni[24].nvs" 18304;
	setAttr ".tgi[0].ni[25].x" -930;
	setAttr ".tgi[0].ni[25].y" -4550;
	setAttr ".tgi[0].ni[25].nvs" 18304;
	setAttr ".tgi[0].ni[26].x" -4308.5712890625;
	setAttr ".tgi[0].ni[26].y" -1170;
	setAttr ".tgi[0].ni[26].nvs" 18304;
	setAttr ".tgi[0].ni[27].x" -930;
	setAttr ".tgi[0].ni[27].y" -3985.71435546875;
	setAttr ".tgi[0].ni[27].nvs" 18304;
	setAttr ".tgi[0].ni[28].x" -255.71427917480469;
	setAttr ".tgi[0].ni[28].y" -977.14288330078125;
	setAttr ".tgi[0].ni[28].nvs" 18304;
	setAttr ".tgi[0].ni[29].x" -930;
	setAttr ".tgi[0].ni[29].y" -3218.571533203125;
	setAttr ".tgi[0].ni[29].nvs" 18304;
	setAttr ".tgi[0].ni[30].x" -562.85711669921875;
	setAttr ".tgi[0].ni[30].y" -1695.7142333984375;
	setAttr ".tgi[0].ni[30].nvs" 18304;
	setAttr ".tgi[0].ni[31].x" -4308.5712890625;
	setAttr ".tgi[0].ni[31].y" -1372.857177734375;
	setAttr ".tgi[0].ni[31].nvs" 18304;
	setAttr ".tgi[0].ni[32].x" -930;
	setAttr ".tgi[0].ni[32].y" -2407.142822265625;
	setAttr ".tgi[0].ni[32].nvs" 18304;
	setAttr ".tgi[0].ni[33].x" -4922.85693359375;
	setAttr ".tgi[0].ni[33].y" -1654.2857666015625;
	setAttr ".tgi[0].ni[33].nvs" 18304;
	setAttr ".tgi[0].ni[34].x" -930;
	setAttr ".tgi[0].ni[34].y" -2914.28564453125;
	setAttr ".tgi[0].ni[34].nvs" 18304;
	setAttr ".tgi[0].ni[35].x" -930;
	setAttr ".tgi[0].ni[35].y" -4955.71435546875;
	setAttr ".tgi[0].ni[35].nvs" 18304;
	setAttr ".tgi[0].ni[36].x" -930;
	setAttr ".tgi[0].ni[36].y" -4188.5712890625;
	setAttr ".tgi[0].ni[36].nvs" 18304;
	setAttr ".tgi[0].ni[37].x" -930;
	setAttr ".tgi[0].ni[37].y" -1900;
	setAttr ".tgi[0].ni[37].nvs" 18304;
	setAttr ".tgi[0].ni[38].x" -930;
	setAttr ".tgi[0].ni[38].y" -3320;
	setAttr ".tgi[0].ni[38].nvs" 18304;
	setAttr ".tgi[0].ni[39].x" -3080;
	setAttr ".tgi[0].ni[39].y" -1034.2857666015625;
	setAttr ".tgi[0].ni[39].nvs" 18306;
	setAttr ".tgi[0].ni[40].x" -562.85711669921875;
	setAttr ".tgi[0].ni[40].y" -1140;
	setAttr ".tgi[0].ni[40].nvs" 18304;
	setAttr ".tgi[0].ni[41].x" -1851.4285888671875;
	setAttr ".tgi[0].ni[41].y" -1101.4285888671875;
	setAttr ".tgi[0].ni[41].nvs" 18304;
	setAttr ".tgi[0].ni[42].x" -4922.85693359375;
	setAttr ".tgi[0].ni[42].y" -1451.4285888671875;
	setAttr ".tgi[0].ni[42].nvs" 18304;
	setAttr ".tgi[0].ni[43].x" -3387.142822265625;
	setAttr ".tgi[0].ni[43].y" -1265.7142333984375;
	setAttr ".tgi[0].ni[43].nvs" 18304;
	setAttr ".tgi[0].ni[44].x" -930;
	setAttr ".tgi[0].ni[44].y" -2204.28564453125;
	setAttr ".tgi[0].ni[44].nvs" 18304;
	setAttr ".tgi[0].ni[45].x" -930;
	setAttr ".tgi[0].ni[45].y" -1798.5714111328125;
	setAttr ".tgi[0].ni[45].nvs" 18304;
	setAttr ".tgi[0].ni[46].x" -1462.857177734375;
	setAttr ".tgi[0].ni[46].y" -2077.142822265625;
	setAttr ".tgi[0].ni[46].nvs" 18304;
createNode animCurveTU -n "character_set_blendShape1_target16";
	rename -uid "C3C536D2-484C-319F-0E38-52AFC830EE6D";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  266 0 290 0;
createNode animCurveTU -n "character_set_blendShape1_target17";
	rename -uid "6FBF34BE-48A7-3FC3-14CD-8AB5DF41AB09";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  266 0 290 0;
createNode animCurveTU -n "character_set_blendShape1_target18";
	rename -uid "3A4A9D12-48DD-9E04-E35C-908112F36AFE";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  266 0 290 0;
createNode animCurveTA -n "character_set_joint1_rotateZ1";
	rename -uid "F2965E60-4AA4-C281-9631-D88333C4CDDA";
	setAttr ".tan" 18;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  266 -36 290 -36;
createNode animClip -n "clip_rot_debugSource";
	rename -uid "93B69E61-4F1F-51B9-BB6B-2FA4C40F8CEE";
	setAttr ".ihi" 0;
	setAttr ".ss" 266;
	setAttr ".se" 290;
	setAttr ".ci" no;
createNode animClip -n "clip_rot_debug";
	rename -uid "67345CFC-4165-DF99-4C21-F8967FB1F59B";
	setAttr -s 4 ".ac[0:3]" yes yes yes yes;
	setAttr ".sf" 266;
	setAttr ".ss" 266;
	setAttr ".se" 290;
createNode nodeGraphEditorInfo -n "hyperShadePrimaryNodeEditorSavedTabsInfo";
	rename -uid "4B6899BB-4695-8F10-4DAD-1E98BB37C60B";
	setAttr ".tgi[0].tn" -type "string" "Untitled_1";
	setAttr ".tgi[0].vl" -type "double2" -113.09523360123728 -278.57141750199503 ;
	setAttr ".tgi[0].vh" -type "double2" 114.28570974440824 278.57141750199503 ;
createNode aiOptions -s -n "defaultArnoldRenderOptions";
	rename -uid "BBEB1C36-4C1F-22FA-F00D-4FADAE83DFC0";
	setAttr ".version" -type "string" "2.1.0.1";
createNode aiAOVFilter -s -n "defaultArnoldFilter";
	rename -uid "82978A8E-4CAB-58E6-F239-EAB87B6C1AB7";
	setAttr ".ai_translator" -type "string" "gaussian";
createNode aiAOVDriver -s -n "defaultArnoldDriver";
	rename -uid "2A207767-4CBF-3603-D360-1D8FCF6F819C";
	setAttr ".ai_translator" -type "string" "exr";
createNode aiAOVDriver -s -n "defaultArnoldDisplayDriver";
	rename -uid "DFAB2248-4B24-9B84-727D-7F874DFEACD1";
	setAttr ".output_mode" 0;
	setAttr ".ai_translator" -type "string" "maya";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 300;
	setAttr ".unw" 300;
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
	setAttr -s 2 ".st";
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
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 4 ".dsm";
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
select -ne :defaultRenderGlobals;
	setAttr -k on ".cch";
	setAttr -cb on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -k on ".macc";
	setAttr -k on ".macd";
	setAttr -k on ".macq";
	setAttr -cb on ".ifg";
	setAttr -k on ".clip";
	setAttr -k on ".edm";
	setAttr -k on ".edl";
	setAttr ".ren" -type "string" "arnold";
	setAttr -av -k on ".esr";
	setAttr -k on ".ors";
	setAttr -cb on ".sdf";
	setAttr ".outf" 51;
	setAttr -cb on ".imfkey" -type "string" "exr";
	setAttr -k on ".gama";
	setAttr -cb on ".ar";
	setAttr -av ".bfs";
	setAttr -k on ".be";
	setAttr -k on ".fec";
	setAttr -k on ".ofc";
	setAttr -cb on ".ofe";
	setAttr -cb on ".efe";
	setAttr -cb on ".umfn";
	setAttr -cb on ".ufe";
	setAttr -k on ".comp";
	setAttr -k on ".cth";
	setAttr -k on ".soll";
	setAttr -k on ".rd";
	setAttr -k on ".lp";
	setAttr -k on ".sp";
	setAttr -k on ".shs";
	setAttr -k on ".lpr";
	setAttr -cb on ".gv";
	setAttr -cb on ".sv";
	setAttr -k on ".mm";
	setAttr -k on ".npu";
	setAttr -k on ".itf";
	setAttr -k on ".shp";
	setAttr -cb on ".isp";
	setAttr -k on ".uf";
	setAttr -k on ".oi";
	setAttr -k on ".rut";
	setAttr -av -k on ".mbf";
	setAttr -k on ".afp";
	setAttr -k on ".pfb";
	setAttr -cb on ".pfrm";
	setAttr -cb on ".pfom";
	setAttr -av -k on ".bll";
	setAttr -k on ".bls";
	setAttr -k on ".smv";
	setAttr -k on ".ubc";
	setAttr -k on ".mbc";
	setAttr -k on ".udbx";
	setAttr -k on ".smc";
	setAttr -k on ".kmv";
	setAttr -cb on ".isl";
	setAttr -cb on ".ism";
	setAttr -cb on ".imb";
	setAttr -k on ".rlen";
	setAttr -av -k on ".frts";
	setAttr -k on ".tlwd";
	setAttr -k on ".tlht";
	setAttr -k on ".jfc";
	setAttr -cb on ".rsb";
	setAttr -k on ".ope";
	setAttr -k on ".oppf";
	setAttr -cb on ".hbl";
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
select -ne :characterPartition;
connectAttr "blendShape1GroupId.id" "characterShape.iog.og[0].gid";
connectAttr "blendShape1Set.mwc" "characterShape.iog.og[0].gco";
connectAttr "groupId2.id" "characterShape.iog.og[1].gid";
connectAttr "tweakSet1.mwc" "characterShape.iog.og[1].gco";
connectAttr "skinCluster1GroupId.id" "characterShape.iog.og[3].gid";
connectAttr "skinCluster1Set.mwc" "characterShape.iog.og[3].gco";
connectAttr "skinCluster1.og[0]" "characterShape.i";
connectAttr "tweak1.vl[0].vt[0]" "characterShape.twl";
connectAttr "polyCube1.out" "characterShapeOrig.i";
connectAttr "character_set.av[1]" "joint1.rz";
connectAttr "joint1_rotateX.o" "joint1.rx";
connectAttr "joint1.s" "joint2.is";
connectAttr "joint1.rz" "joint2.rz";
connectAttr "pairBlend7.ory" "joint2.ry";
connectAttr "pairBlend7.orx" "joint2.rx";
connectAttr "joint2.s" "joint3.is";
connectAttr "joint2.rz" "joint3.rz";
connectAttr "pairBlend6.ory" "joint3.ry";
connectAttr "pairBlend6.orx" "joint3.rx";
connectAttr "joint3.s" "joint4.is";
connectAttr "joint3.rz" "joint4.rz";
connectAttr "pairBlend5.ory" "joint4.ry";
connectAttr "pairBlend5.orx" "joint4.rx";
connectAttr "joint4.s" "joint5.is";
connectAttr "joint4.rz" "joint5.rz";
connectAttr "pairBlend8.ory" "joint5.ry";
connectAttr "pairBlend8.orx" "joint5.rx";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
connectAttr "blendShape1.mlpr" "shapeEditorManager.bspr[0]";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "blendShape1GroupParts.og" "blendShape1.ip[0].ig";
connectAttr "blendShape1GroupId.id" "blendShape1.ip[0].gi";
connectAttr "targetShape3.w" "blendShape1.it[0].itg[0].iti[6000].igt";
connectAttr "targetShape2.w" "blendShape1.it[0].itg[1].iti[6000].igt";
connectAttr "target1Shape.w" "blendShape1.it[0].itg[2].iti[6000].igt";
connectAttr "shapeEditorManager.obsv[0]" "blendShape1.tgdt[0].dpvs";
connectAttr "character_set.uv[21]" "blendShape1.w[0]";
connectAttr "character_set.uv[23]" "blendShape1.w[1]";
connectAttr "character_set.uv[22]" "blendShape1.w[2]";
connectAttr "groupParts2.og" "tweak1.ip[0].ig";
connectAttr "groupId2.id" "tweak1.ip[0].gi";
connectAttr "blendShape1GroupId.msg" "blendShape1Set.gn" -na;
connectAttr "characterShape.iog.og[0]" "blendShape1Set.dsm" -na;
connectAttr "blendShape1.msg" "blendShape1Set.ub[0]";
connectAttr "tweak1.og[0]" "blendShape1GroupParts.ig";
connectAttr "blendShape1GroupId.id" "blendShape1GroupParts.gi";
connectAttr "groupId2.msg" "tweakSet1.gn" -na;
connectAttr "characterShape.iog.og[1]" "tweakSet1.dsm" -na;
connectAttr "tweak1.msg" "tweakSet1.ub[0]";
connectAttr "characterShapeOrig.w" "groupParts2.ig";
connectAttr "groupId2.id" "groupParts2.gi";
connectAttr "skinCluster1GroupParts.og" "skinCluster1.ip[0].ig";
connectAttr "skinCluster1GroupId.id" "skinCluster1.ip[0].gi";
connectAttr "bindPose1.msg" "skinCluster1.bp";
connectAttr "joint1.wm" "skinCluster1.ma[0]";
connectAttr "joint2.wm" "skinCluster1.ma[1]";
connectAttr "joint3.wm" "skinCluster1.ma[2]";
connectAttr "joint4.wm" "skinCluster1.ma[3]";
connectAttr "joint5.wm" "skinCluster1.ma[4]";
connectAttr "joint1.liw" "skinCluster1.lw[0]";
connectAttr "joint2.liw" "skinCluster1.lw[1]";
connectAttr "joint3.liw" "skinCluster1.lw[2]";
connectAttr "joint4.liw" "skinCluster1.lw[3]";
connectAttr "joint5.liw" "skinCluster1.lw[4]";
connectAttr "joint1.obcc" "skinCluster1.ifcl[0]";
connectAttr "joint2.obcc" "skinCluster1.ifcl[1]";
connectAttr "joint3.obcc" "skinCluster1.ifcl[2]";
connectAttr "joint4.obcc" "skinCluster1.ifcl[3]";
connectAttr "joint5.obcc" "skinCluster1.ifcl[4]";
connectAttr "skinCluster1GroupId.msg" "skinCluster1Set.gn" -na;
connectAttr "characterShape.iog.og[3]" "skinCluster1Set.dsm" -na;
connectAttr "skinCluster1.msg" "skinCluster1Set.ub[0]";
connectAttr "blendShape1.og[0]" "skinCluster1GroupParts.ig";
connectAttr "skinCluster1GroupId.id" "skinCluster1GroupParts.gi";
connectAttr "joint1.msg" "bindPose1.m[0]";
connectAttr "joint2.msg" "bindPose1.m[1]";
connectAttr "joint3.msg" "bindPose1.m[2]";
connectAttr "joint4.msg" "bindPose1.m[3]";
connectAttr "joint5.msg" "bindPose1.m[4]";
connectAttr "bindPose1.w" "bindPose1.p[0]";
connectAttr "bindPose1.m[0]" "bindPose1.p[1]";
connectAttr "bindPose1.m[1]" "bindPose1.p[2]";
connectAttr "bindPose1.m[2]" "bindPose1.p[3]";
connectAttr "bindPose1.m[3]" "bindPose1.p[4]";
connectAttr "joint1.bps" "bindPose1.wm[0]";
connectAttr "joint2.bps" "bindPose1.wm[1]";
connectAttr "joint3.bps" "bindPose1.wm[2]";
connectAttr "joint4.bps" "bindPose1.wm[3]";
connectAttr "joint5.bps" "bindPose1.wm[4]";
connectAttr "blendShape1.w[0]" "character_set.dnsm[50]";
connectAttr "blendShape1.w[2]" "character_set.dnsm[51]";
connectAttr "blendShape1.w[1]" "character_set.dnsm[52]";
connectAttr "joint1.rz" "character_set.dnsm[53]";
connectAttr "character_setScheduler1.ce" "character_set.cer";
connectAttr "character_setClips1.cf" "character_setScheduler1.cfr";
connectAttr "character_setClips1.cl[0]" "character_setScheduler1.cl[0]";
connectAttr "character_setClips1.cl[1]" "character_setScheduler1.cl[1]";
connectAttr "character_setClips1.cl[2]" "character_setScheduler1.cl[2]";
connectAttr "character_setClips1.cl[3]" "character_setScheduler1.cl[3]";
connectAttr "character_setClips1.cl[4]" "character_setScheduler1.cl[4]";
connectAttr "character_setClips1.cl[4]" "character_setScheduler1.cl[8]";
connectAttr "character_setClips1.cl[1]" "character_setScheduler1.cl[9]";
connectAttr "character_setClips1.cl[2]" "character_setScheduler1.cl[10]";
connectAttr "character_setClips1.cl[3]" "character_setScheduler1.cl[11]";
connectAttr "character_setClips1.cl[5]" "character_setScheduler1.cl[12]";
connectAttr "setup.sf" "character_setScheduler1.st[0]";
connectAttr "clip_target1.sf" "character_setScheduler1.st[1]";
connectAttr "clip_target2.sf" "character_setScheduler1.st[2]";
connectAttr "clip_target3.sf" "character_setScheduler1.st[3]";
connectAttr "clip_joint_rot_z.sf" "character_setScheduler1.st[4]";
connectAttr "clip_joint_rot_z_dup.sf" "character_setScheduler1.st[8]";
connectAttr "clip_target4.sf" "character_setScheduler1.st[9]";
connectAttr "clip_target5.sf" "character_setScheduler1.st[10]";
connectAttr "clip_target6.sf" "character_setScheduler1.st[11]";
connectAttr "clip_rot_debug.sf" "character_setScheduler1.st[12]";
connectAttr "setup.ss" "character_setScheduler1.ss[0]";
connectAttr "clip_target1.ss" "character_setScheduler1.ss[1]";
connectAttr "clip_target2.ss" "character_setScheduler1.ss[2]";
connectAttr "clip_target3.ss" "character_setScheduler1.ss[3]";
connectAttr "clip_joint_rot_z.ss" "character_setScheduler1.ss[4]";
connectAttr "clip_joint_rot_z_dup.ss" "character_setScheduler1.ss[8]";
connectAttr "clip_target4.ss" "character_setScheduler1.ss[9]";
connectAttr "clip_target5.ss" "character_setScheduler1.ss[10]";
connectAttr "clip_target6.ss" "character_setScheduler1.ss[11]";
connectAttr "clip_rot_debug.ss" "character_setScheduler1.ss[12]";
connectAttr "setup.se" "character_setScheduler1.se[0]";
connectAttr "clip_target1.se" "character_setScheduler1.se[1]";
connectAttr "clip_target2.se" "character_setScheduler1.se[2]";
connectAttr "clip_target3.se" "character_setScheduler1.se[3]";
connectAttr "clip_joint_rot_z.se" "character_setScheduler1.se[4]";
connectAttr "clip_joint_rot_z_dup.se" "character_setScheduler1.se[8]";
connectAttr "clip_target4.se" "character_setScheduler1.se[9]";
connectAttr "clip_target5.se" "character_setScheduler1.se[10]";
connectAttr "clip_target6.se" "character_setScheduler1.se[11]";
connectAttr "clip_rot_debug.se" "character_setScheduler1.se[12]";
connectAttr "setup.w" "character_setScheduler1.w[0]";
connectAttr "clip_target1.w" "character_setScheduler1.w[1]";
connectAttr "clip_target2.w" "character_setScheduler1.w[2]";
connectAttr "clip_target3.w" "character_setScheduler1.w[3]";
connectAttr "clip_joint_rot_z.w" "character_setScheduler1.w[4]";
connectAttr "clip_joint_rot_z_dup.w" "character_setScheduler1.w[8]";
connectAttr "clip_target4.w" "character_setScheduler1.w[9]";
connectAttr "clip_target5.w" "character_setScheduler1.w[10]";
connectAttr "clip_target6.w" "character_setScheduler1.w[11]";
connectAttr "clip_rot_debug.w" "character_setScheduler1.w[12]";
connectAttr "setup.ws" "character_setScheduler1.ws[0]";
connectAttr "clip_target1.ws" "character_setScheduler1.ws[1]";
connectAttr "clip_target2.ws" "character_setScheduler1.ws[2]";
connectAttr "clip_target3.ws" "character_setScheduler1.ws[3]";
connectAttr "clip_joint_rot_z.ws" "character_setScheduler1.ws[4]";
connectAttr "clip_joint_rot_z_dup.ws" "character_setScheduler1.ws[8]";
connectAttr "clip_target4.ws" "character_setScheduler1.ws[9]";
connectAttr "clip_target5.ws" "character_setScheduler1.ws[10]";
connectAttr "clip_target6.ws" "character_setScheduler1.ws[11]";
connectAttr "clip_rot_debug.ws" "character_setScheduler1.ws[12]";
connectAttr "setup.ea" "character_setScheduler1.ea[0]";
connectAttr "clip_target1.ea" "character_setScheduler1.ea[1]";
connectAttr "clip_target2.ea" "character_setScheduler1.ea[2]";
connectAttr "clip_target3.ea" "character_setScheduler1.ea[3]";
connectAttr "clip_joint_rot_z.ea" "character_setScheduler1.ea[4]";
connectAttr "clip_joint_rot_z_dup.ea" "character_setScheduler1.ea[8]";
connectAttr "clip_target4.ea" "character_setScheduler1.ea[9]";
connectAttr "clip_target5.ea" "character_setScheduler1.ea[10]";
connectAttr "clip_target6.ea" "character_setScheduler1.ea[11]";
connectAttr "clip_rot_debug.ea" "character_setScheduler1.ea[12]";
connectAttr "setup.cb" "character_setScheduler1.cb[0]";
connectAttr "clip_target1.cb" "character_setScheduler1.cb[1]";
connectAttr "clip_target2.cb" "character_setScheduler1.cb[2]";
connectAttr "clip_target3.cb" "character_setScheduler1.cb[3]";
connectAttr "clip_joint_rot_z.cb" "character_setScheduler1.cb[4]";
connectAttr "clip_joint_rot_z_dup.cb" "character_setScheduler1.cb[8]";
connectAttr "clip_target4.cb" "character_setScheduler1.cb[9]";
connectAttr "clip_target5.cb" "character_setScheduler1.cb[10]";
connectAttr "clip_target6.cb" "character_setScheduler1.cb[11]";
connectAttr "clip_rot_debug.cb" "character_setScheduler1.cb[12]";
connectAttr "setup.ca" "character_setScheduler1.ca[0]";
connectAttr "clip_target1.ca" "character_setScheduler1.ca[1]";
connectAttr "clip_target2.ca" "character_setScheduler1.ca[2]";
connectAttr "clip_target3.ca" "character_setScheduler1.ca[3]";
connectAttr "clip_joint_rot_z.ca" "character_setScheduler1.ca[4]";
connectAttr "clip_joint_rot_z_dup.ca" "character_setScheduler1.ca[8]";
connectAttr "clip_target4.ca" "character_setScheduler1.ca[9]";
connectAttr "clip_target5.ca" "character_setScheduler1.ca[10]";
connectAttr "clip_target6.ca" "character_setScheduler1.ca[11]";
connectAttr "clip_rot_debug.ca" "character_setScheduler1.ca[12]";
connectAttr "setup.sc" "character_setScheduler1.sc[0]";
connectAttr "clip_target1.sc" "character_setScheduler1.sc[1]";
connectAttr "clip_target2.sc" "character_setScheduler1.sc[2]";
connectAttr "clip_target3.sc" "character_setScheduler1.sc[3]";
connectAttr "clip_joint_rot_z.sc" "character_setScheduler1.sc[4]";
connectAttr "clip_joint_rot_z_dup.sc" "character_setScheduler1.sc[8]";
connectAttr "clip_target4.sc" "character_setScheduler1.sc[9]";
connectAttr "clip_target5.sc" "character_setScheduler1.sc[10]";
connectAttr "clip_target6.sc" "character_setScheduler1.sc[11]";
connectAttr "clip_rot_debug.sc" "character_setScheduler1.sc[12]";
connectAttr "setup.h" "character_setScheduler1.h[0]";
connectAttr "clip_target1.h" "character_setScheduler1.h[1]";
connectAttr "clip_target2.h" "character_setScheduler1.h[2]";
connectAttr "clip_target3.h" "character_setScheduler1.h[3]";
connectAttr "clip_joint_rot_z.h" "character_setScheduler1.h[4]";
connectAttr "clip_joint_rot_z_dup.h" "character_setScheduler1.h[8]";
connectAttr "clip_target4.h" "character_setScheduler1.h[9]";
connectAttr "clip_target5.h" "character_setScheduler1.h[10]";
connectAttr "clip_target6.h" "character_setScheduler1.h[11]";
connectAttr "clip_rot_debug.h" "character_setScheduler1.h[12]";
connectAttr "character_set.am" "character_setClips1.cd[0].cm";
connectAttr "character_set.cim" "character_setClips1.cd[0].cim";
connectAttr "character_set_blendShape1_target3.a" "character_setClips1.cel[0].cev[0].cevr"
		;
connectAttr "character_set_blendShape1_target1.a" "character_setClips1.cel[0].cev[1].cevr"
		;
connectAttr "character_set_blendShape1_target2.a" "character_setClips1.cel[0].cev[2].cevr"
		;
connectAttr "character_set_joint1_rotateZ.a" "character_setClips1.cel[0].cev[3].cevr"
		;
connectAttr "character_set_blendShape1_target4.a" "character_setClips1.cel[1].cev[0].cevr"
		;
connectAttr "character_set_blendShape1_target5.a" "character_setClips1.cel[1].cev[1].cevr"
		;
connectAttr "character_set_blendShape1_target6.a" "character_setClips1.cel[1].cev[2].cevr"
		;
connectAttr "character_set_blendShape1_target7.a" "character_setClips1.cel[2].cev[0].cevr"
		;
connectAttr "character_set_blendShape1_target8.a" "character_setClips1.cel[2].cev[1].cevr"
		;
connectAttr "character_set_blendShape1_target9.a" "character_setClips1.cel[2].cev[2].cevr"
		;
connectAttr "character_set_blendShape1_target10.a" "character_setClips1.cel[3].cev[0].cevr"
		;
connectAttr "character_set_blendShape1_target11.a" "character_setClips1.cel[3].cev[1].cevr"
		;
connectAttr "character_set_blendShape1_target12.a" "character_setClips1.cel[3].cev[2].cevr"
		;
connectAttr "character_set_blendShape1_target13.a" "character_setClips1.cel[4].cev[0].cevr"
		;
connectAttr "character_set_blendShape1_target14.a" "character_setClips1.cel[4].cev[1].cevr"
		;
connectAttr "character_set_blendShape1_target15.a" "character_setClips1.cel[4].cev[2].cevr"
		;
connectAttr "joint1_rotateZ.a" "character_setClips1.cel[4].cev[3].cevr";
connectAttr "character_set_blendShape1_target16.a" "character_setClips1.cel[5].cev[0].cevr"
		;
connectAttr "character_set_blendShape1_target17.a" "character_setClips1.cel[5].cev[1].cevr"
		;
connectAttr "character_set_blendShape1_target18.a" "character_setClips1.cel[5].cev[2].cevr"
		;
connectAttr "character_set_joint1_rotateZ1.a" "character_setClips1.cel[5].cev[3].cevr"
		;
connectAttr "setupSource.cl" "character_setClips1.sc[0]";
connectAttr "clip_target1Source.cl" "character_setClips1.sc[1]";
connectAttr "clip_target2Source.cl" "character_setClips1.sc[2]";
connectAttr "clip_target3Source.cl" "character_setClips1.sc[3]";
connectAttr "clip_joint_rot_zSource.cl" "character_setClips1.sc[4]";
connectAttr "clip_rot_debugSource.cl" "character_setClips1.sc[5]";
connectAttr "setupSource.cl" "setup.cl";
connectAttr "clip_target1Source.cl" "clip_target1.cl";
connectAttr "clip_target2Source.cl" "clip_target2.cl";
connectAttr "clip_target3Source.cl" "clip_target3.cl";
connectAttr "joint1.rz" "pairBlend1.irz2";
connectAttr "joint2.blendCharacterset" "pairBlend1.w";
connectAttr "pairBlend1_inRotateZ1.o" "pairBlend1.irz1";
connectAttr "joint2.rz" "pairBlend2.irz2";
connectAttr "joint3.blendCharacterset" "pairBlend2.w";
connectAttr "pairBlend2_inRotateZ1.o" "pairBlend2.irz1";
connectAttr "joint3.rz" "pairBlend3.irz2";
connectAttr "joint4.blendCharacterset" "pairBlend3.w";
connectAttr "pairBlend3_inRotateZ1.o" "pairBlend3.irz1";
connectAttr "joint4.rz" "pairBlend4.irz2";
connectAttr "joint5.blendCharacterset" "pairBlend4.w";
connectAttr "pairBlend4_inRotateZ1.o" "pairBlend4.irz1";
connectAttr "pairBlend3.orx" "pairBlend5.irx2";
connectAttr "pairBlend3.ory" "pairBlend5.iry2";
connectAttr "joint3.rz" "pairBlend5.irz2";
connectAttr "joint4.blendPairBlend3" "pairBlend5.w";
connectAttr "pairBlend5_inRotateZ1.o" "pairBlend5.irz1";
connectAttr "pairBlend2.orx" "pairBlend6.irx2";
connectAttr "pairBlend2.ory" "pairBlend6.iry2";
connectAttr "joint2.rz" "pairBlend6.irz2";
connectAttr "joint3.blendPairBlend2" "pairBlend6.w";
connectAttr "pairBlend6_inRotateZ1.o" "pairBlend6.irz1";
connectAttr "pairBlend1.orx" "pairBlend7.irx2";
connectAttr "pairBlend1.ory" "pairBlend7.iry2";
connectAttr "joint1.rz" "pairBlend7.irz2";
connectAttr "joint2.blendPairBlend1" "pairBlend7.w";
connectAttr "pairBlend7_inRotateZ1.o" "pairBlend7.irz1";
connectAttr "pairBlend4.orx" "pairBlend8.irx2";
connectAttr "pairBlend4.ory" "pairBlend8.iry2";
connectAttr "joint4.rz" "pairBlend8.irz2";
connectAttr "joint5.blendPairBlend4" "pairBlend8.w";
connectAttr "pairBlend8_inRotateZ1.o" "pairBlend8.irz1";
connectAttr "clip_joint_rot_zSource.cl" "clip_joint_rot_z.cl";
connectAttr "clip_target3Source.cl" "clip_target6.cl";
connectAttr "clip_target2Source.cl" "clip_target5.cl";
connectAttr "clip_target1Source.cl" "clip_target4.cl";
connectAttr "clip_joint_rot_zSource.cl" "clip_joint_rot_z_dup.cl";
connectAttr "character_set_blendShape1_target7.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[0].dn"
		;
connectAttr "character_set_blendShape1_target3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[1].dn"
		;
connectAttr "pairBlend5.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[2].dn";
connectAttr "clip_joint_rot_z.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[3].dn"
		;
connectAttr "clip_target3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[4].dn";
connectAttr "character_setScheduler1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[5].dn"
		;
connectAttr "clip_target4.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[6].dn";
connectAttr "joint5.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[7].dn";
connectAttr "pairBlend6.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[8].dn";
connectAttr "pairBlend2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[9].dn";
connectAttr "clip_target1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[10].dn";
connectAttr "character_setClips1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[11].dn"
		;
connectAttr "clip_target6.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[12].dn";
connectAttr "character_set_blendShape1_target9.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[13].dn"
		;
connectAttr "clip_joint_rot_z_dup.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[14].dn"
		;
connectAttr "joint3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[15].dn";
connectAttr "joint4.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[16].dn";
connectAttr "character_set_blendShape1_target6.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[17].dn"
		;
connectAttr "skinCluster1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[18].dn";
connectAttr "character_set_blendShape1_target2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[19].dn"
		;
connectAttr "joint1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[20].dn";
connectAttr "setup.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[21].dn";
connectAttr "pairBlend4.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[22].dn";
connectAttr "pairBlend1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[23].dn";
connectAttr "character_set_blendShape1_target11.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[24].dn"
		;
connectAttr "character_set_blendShape1_target8.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[25].dn"
		;
connectAttr "joint1_rotateX.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[26].dn";
connectAttr "joint1_rotateZ.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[27].dn";
connectAttr "characterShape.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[28].dn";
connectAttr "character_set_blendShape1_target15.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[29].dn"
		;
connectAttr "bindPose1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[30].dn";
connectAttr "character_set.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[31].dn";
connectAttr "character_set_blendShape1_target5.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[32].dn"
		;
connectAttr "clip_target2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[33].dn";
connectAttr "character_set_joint1_rotateZ.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[34].dn"
		;
connectAttr "character_set_blendShape1_target4.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[35].dn"
		;
connectAttr "character_set_blendShape1_target13.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[36].dn"
		;
connectAttr "character_set_blendShape1_target12.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[37].dn"
		;
connectAttr "character_set_blendShape1_target1.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[38].dn"
		;
connectAttr "joint2.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[39].dn";
connectAttr "pairBlend8.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[40].dn";
connectAttr "pairBlend3.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[41].dn";
connectAttr "clip_target5.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[42].dn";
connectAttr "pairBlend7.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[43].dn";
connectAttr "character_set_blendShape1_target10.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[44].dn"
		;
connectAttr "character_set_blendShape1_target14.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[45].dn"
		;
connectAttr "maya2glTF_scriptNode.msg" "MayaNodeEditorSavedTabsInfo.tgi[0].ni[46].dn"
		;
connectAttr "clip_rot_debugSource.cl" "clip_rot_debug.cl";
connectAttr ":defaultArnoldDisplayDriver.msg" ":defaultArnoldRenderOptions.drivers"
		 -na;
connectAttr ":defaultArnoldFilter.msg" ":defaultArnoldRenderOptions.filt";
connectAttr ":defaultArnoldDriver.msg" ":defaultArnoldRenderOptions.drvr";
connectAttr "trackInfoManager1.msg" ":sequenceManager1.tim";
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "characterShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "target1Shape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "targetShape2.iog" ":initialShadingGroup.dsm" -na;
connectAttr "targetShape3.iog" ":initialShadingGroup.dsm" -na;
connectAttr "character_set.pa" ":characterPartition.st" -na;
// End of ComplexTraxAnim1.ma
