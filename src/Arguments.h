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
};

