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
	bool dumpMaya = false;
	bool dumpGLTF = false;
	bool separate = false;
};

