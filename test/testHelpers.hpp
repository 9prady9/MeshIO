#include <meshio/stl.hpp>

#include <vector>

template <typename T>
void initializeReferenceSTLObj(std::vector< meshio::stl::Data<T> > &refObjs)
{
    for(unsigned i = 0; i < refObjs.size(); ++i)
        refObjs[i].clear();
    refObjs.clear();

    meshio::stl::Data<T> refObj;
    refObj.resize(12);
    refObj.mNormals[0] = meshio::Vec3<T>(0,0,-1);
    refObj.mPositions[0] = meshio::Vec4<T>(0, 0, 0, 1);
    refObj.mPositions[1] = meshio::Vec4<T>(1, 1, 0, 1);
    refObj.mPositions[2] = meshio::Vec4<T>(1, 0, 0, 1);
    refObj.mNormals[1] = meshio::Vec3<T>(0, 0, -1);
    refObj.mPositions[3] = meshio::Vec4<T>(0, 0, 0, 1);
    refObj.mPositions[4] = meshio::Vec4<T>(0, 1, 0, 1);
    refObj.mPositions[5] = meshio::Vec4<T>(1, 1, 0, 1);
    refObj.mNormals[2] = meshio::Vec3<T>(1, 0, 0);
    refObj.mPositions[6] = meshio::Vec4<T>(1, 0, 0, 1);
    refObj.mPositions[7] = meshio::Vec4<T>(1, 1, 1, 1);
    refObj.mPositions[8] = meshio::Vec4<T>(1, 0, 1, 1);
    refObj.mNormals[3] = meshio::Vec3<T>(1, 0, 0);
    refObj.mPositions[9] = meshio::Vec4<T>(1, 0, 0, 1);
    refObj.mPositions[10] = meshio::Vec4<T>(1,1,0,1);
    refObj.mPositions[11] = meshio::Vec4<T>(1,1,1,1);
    refObj.mNormals[4] = meshio::Vec3<T>(0, 0, 1);
    refObj.mPositions[12] = meshio::Vec4<T>(1,0,1,1);
    refObj.mPositions[13] = meshio::Vec4<T>(0,1,1,1);
    refObj.mPositions[14] = meshio::Vec4<T>(0,0,1,1);
    refObj.mNormals[5] = meshio::Vec3<T>(0, 0, 1);
    refObj.mPositions[15] = meshio::Vec4<T>(1,0,1,1);
    refObj.mPositions[16] = meshio::Vec4<T>(1,1,1,1);
    refObj.mPositions[17] = meshio::Vec4<T>(0,1,1,1);
    refObj.mNormals[6] = meshio::Vec3<T>(-1, 0, 0);
    refObj.mPositions[18] = meshio::Vec4<T>(0,0,0,1);
    refObj.mPositions[19] = meshio::Vec4<T>(0,1,1,1);
    refObj.mPositions[20] = meshio::Vec4<T>(0,1,0,1);
    refObj.mNormals[7] = meshio::Vec3<T>(-1, 0, 0);
    refObj.mPositions[21] = meshio::Vec4<T>(0,0,0,1);
    refObj.mPositions[22] = meshio::Vec4<T>(0,0,1,1);
    refObj.mPositions[23] = meshio::Vec4<T>(0,1,1,1);
    refObj.mNormals[8] = meshio::Vec3<T>(0, 1, 0);
    refObj.mPositions[24] = meshio::Vec4<T>(0,1,0,1);
    refObj.mPositions[25] = meshio::Vec4<T>(1,1,1,1);
    refObj.mPositions[26] = meshio::Vec4<T>(1,1,0,1);
    refObj.mNormals[9] = meshio::Vec3<T>(0, 1, 0);
    refObj.mPositions[27] = meshio::Vec4<T>(0,1,0,1);
    refObj.mPositions[28] = meshio::Vec4<T>(0,1,1,1);
    refObj.mPositions[29] = meshio::Vec4<T>(1,1,1,1);
    refObj.mNormals[10] = meshio::Vec3<T>(0, -1, 0);
    refObj.mPositions[30] = meshio::Vec4<T>(0,0,0,1);
    refObj.mPositions[31] = meshio::Vec4<T>(1,0,0,1);
    refObj.mPositions[32] = meshio::Vec4<T>(1,0,1,1);
    refObj.mNormals[11] = meshio::Vec3<T>(0, -1, 0);
    refObj.mPositions[33] = meshio::Vec4<T>(0,0,0,1);
    refObj.mPositions[34] = meshio::Vec4<T>(1,0,1,1);
    refObj.mPositions[35] = meshio::Vec4<T>(0,0,1,1);

    refObjs.push_back(refObj);
}
