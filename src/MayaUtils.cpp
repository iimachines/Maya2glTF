#include "externals.h"
#include "MayaUtils.h"
#include "MayaException.h"

namespace utils
{
	MMatrix getMatrix(const MPlug& plug)
	{
		MStatus status;
		MObject matrixDataObject;
		THROW_ON_FAILURE(plug.getValue(matrixDataObject));
		const MMatrix& mayaMatrix = MFnMatrixData(matrixDataObject, &status).matrix();
		THROW_ON_FAILURE(status);
		return mayaMatrix;
	}

	MMatrix getMatrix(const MFnDependencyNode& node, const char* plugName)
	{
		MStatus status;
		MPlug plug = node.findPlug(plugName, &status);
		THROW_ON_FAILURE(status);
		return getMatrix(plug);
	}

	MTransformationMatrix getTransformation(const MDagPath& path)
	{
		MStatus status;

		MFnDagNode transFn(path);
		MPlug matrixPlugArray = transFn.findPlug("worldMatrix", &status);
		THROW_ON_FAILURE(status);

		matrixPlugArray.evaluateNumElements(&status);
		THROW_ON_FAILURE(status);

		MPlug matrixPlug = matrixPlugArray.elementByPhysicalIndex(0, &status);
		THROW_ON_FAILURE(status);

		MObject matrixO;
		THROW_ON_FAILURE(matrixPlug.getValue(matrixO));

		MFnMatrixData fnMat(matrixO, &status);
		THROW_ON_FAILURE(status);

		return fnMat.transformation();
	}

	MString simpleName(const MString& name)
	{
		std::string buffer(name.asChar());
		replace_if(buffer.begin(), buffer.end(), isalnum, '_');
		return MString(buffer.c_str());
	}
}
