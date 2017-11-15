#pragma once

namespace Maya
{
	MMatrix getMatrix(const MPlug& plug);
	MMatrix getMatrix(const MFnDependencyNode& node, const char* plugName);
	MTransformationMatrix getTransformation(const MDagPath& path);

	// Return a string with all non-alpha-numeric characters replaced with an underscore.
	std::string simpleName(const MString& name);
}
