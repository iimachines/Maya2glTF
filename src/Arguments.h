#pragma once

class Arguments
{
public:
	Arguments(const MArgList& args, const MSyntax& syntax);
	~Arguments();

	static MSyntax createSyntax();

	MString sceneName;
	MString outputFolder;
	MSelectionList selection;
	bool glb = false;
	
	/** Create a default material for primitives that don't have shading in Maya? */
	bool defaultMaterial = false;

	/** Assign a color with a different hue to each material, for debugging purposes */
	bool colorizeMaterials = false;

	/** If non-null, dump the Maya intermediate objects to the stream */
	std::ostream* dumpMaya;
	
	/** If non-null, dump the GLTF JSON to the stream */
	std::ostream* dumpGLTF;

	bool separate = false;

private:
	static std::ostream* getOutputStream(const MArgDatabase& adb, const char* arg, std::ofstream& fileOutputStream);

	std::ofstream m_mayaOutputStream;
	std::ofstream m_gltfOutputStream;
};

