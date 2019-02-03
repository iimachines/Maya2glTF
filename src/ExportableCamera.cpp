#include "externals.h"
#include "ExportableCamera.h"
#include "ExportableResources.h"
#include "Arguments.h"
#include "ExportableScene.h"
#include "ExportableNode.h"
#include "DagHelper.h"
#include "MayaException.h"

ExportableCamera::ExportableCamera(
    ExportableScene& scene,
    ExportableNode& node,
    const MDagPath& shapeDagPath)
    : ExportableObject(shapeDagPath.node())
{
    MStatus status;

    // NOTE: We leave the aspect ratio undefined, so GLTF adapts to the viewport
    // https://github.com/KhronosGroup/glTF/issues/1292

#if 0
    auto aspectRatio = 1.0f;

    // Determine aspect ratio from resolution.
    MSelectionList sl;
    sl.add(":defaultResolution");

    MObject defaultResolutionNode;
    status = sl.getDependNode(0, defaultResolutionNode);

    if (status)
    {
        float width;
        float height;
        const auto hasWidth = DagHelper::getPlugValue(defaultResolutionNode, "width", width);
        const auto hasHeight = DagHelper::getPlugValue(defaultResolutionNode, "height", height);

        if (hasWidth && hasHeight)
        {
            aspectRatio = width / height;
        }
    }
#endif

    auto& resources = scene.resources();
    auto& args = resources.arguments();

    const auto cameraNode = shapeDagPath.node();

    MFnCamera camera(shapeDagPath, &status);
    THROW_ON_FAILURE(status);

    auto perspectiveCamera = std::make_unique< GLTF::CameraPerspective>();
    perspectiveCamera->yfov = float(camera.verticalFieldOfView(&status));
    THROW_ON_FAILURE(status);

    perspectiveCamera->aspectRatio = 0; // 0 = undefined, adapt to viewport at runtime
    THROW_ON_FAILURE(status);

    perspectiveCamera->znear = float(camera.nearClippingPlane(&status)) * args.globalScaleFactor;
    THROW_ON_FAILURE(status);

    perspectiveCamera->zfar = float(camera.farClippingPlane(&status)) * args.globalScaleFactor;
    THROW_ON_FAILURE(status);

#if 0
    auto mayaMatrix = camera.projectionMatrix(&status);
    THROW_ON_FAILURE(status);

    cout << prefix << name() << " properties:" << endl;

    cout << "aspect ratio:  " << perspectiveCamera->aspectRatio << endl;
    cout << "field of view: " << perspectiveCamera->yfov << endl;

    cout << "Maya projection matrix:" << mayaMatrix << endl;

    // For testing, also print GLTF projection matrix
    float a = perspectiveCamera->aspectRatio;
    float y = perspectiveCamera->yfov;
    float n = perspectiveCamera->znear;
    float f = perspectiveCamera->zfar;
    float t = tanf(0.5f * y);

    float m[4][4] = {
        {1 / (a*t), 0, 0, 0},
        {0, 1 / t, 0, 0},
        {0,0, (f + n) / (n - f), 2 * f*n / (n - f)},
        {0,0,-1,0 }
    };

    const auto gltfMatrix = MFloatMatrix(m).transpose();
    cout << "gltF projection matrix:" << gltfMatrix << endl;
#endif

    glCamera = move(perspectiveCamera);
}

ExportableCamera::~ExportableCamera() = default;

void ExportableCamera::attachToNode(GLTF::Node& node) const
{
    node.camera = glCamera.get();
}

