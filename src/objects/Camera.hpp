#ifndef _CAMERA_
#define _CAMERA_
#include "../util/Matrix4x4.hpp"
#include "../util/VectorUtilities.hpp"
class Camera{
    private:
    Matrix4x4 cameraToWorld;
    public:
        Camera(Point3f eye,Point3f at,Point3f up);
        Matrix4x4 getCameraToWorld();
        Matrix4x4 getWorldToCamera();
};
#endif