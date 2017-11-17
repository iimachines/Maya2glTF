#pragma once

namespace utils
{
	MMatrix getMatrix(const MPlug& plug);
	MMatrix getMatrix(const MFnDependencyNode& node, const char* plugName);

	MTransformationMatrix getTransformation(const MDagPath& path);

	// Return a string with all non-alpha-numeric characters replaced with an underscore.
	MString simpleName(const MString& name);
}
