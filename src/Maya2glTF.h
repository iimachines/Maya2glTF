#pragma once

class Maya2glTF : public MPxCommand
{
public:
	Maya2glTF();
	~Maya2glTF();

	static void* creator();

	MStatus doIt(const MArgList& args) override;

	bool isUndoable() const override;
};

