
#include <meshio/meshio_defines.hpp>
#include <meshio/obj/obj.hpp>

#include <vector>

template <typename T>
void initializeReferenceSTLObj(std::vector< meshio::STLData<T> > &refObjs)
{
    for(unsigned i = 0; i < refObjs.size(); ++i)
        refObjs[i].clear();
    refObjs.clear();

    meshio::STLData<T> refObj;
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

template <typename T>
void initializeReferenceOBJObject(meshio::obj::OBJData<T> &refObjects)
{
    refObjects.clear();

    meshio::obj::OBJAttribute<T> objAttribute;
    meshio::Vec4<T> position;
    meshio::Vec3<unsigned> indices;

    position = meshio::Vec4<T>(0,0,0,1);
    objAttribute.mPositions.push_back(position);
    position = meshio::Vec4<T>(1,0,0,1);
    objAttribute.mPositions.push_back(position);
    position = meshio::Vec4<T>(1,1,0,1);
    objAttribute.mPositions.push_back(position);
    position = meshio::Vec4<T>(0,1,0,1);
    objAttribute.mPositions.push_back(position);
    position = meshio::Vec4<T>(0,0,1,1);
    objAttribute.mPositions.push_back(position);
    position = meshio::Vec4<T>(1,0,1,1);
    objAttribute.mPositions.push_back(position);
    position = meshio::Vec4<T>(1,1,1,1);
    objAttribute.mPositions.push_back(position);
    position = meshio::Vec4<T>(0,1,1,1);
    objAttribute.mPositions.push_back(position);

    indices = meshio::Vec3<unsigned>(1,3,2);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(1,4,3);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(2,3,6);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(3,7,6);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(6,7,5);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(5,7,8);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(5,8,4);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(5,4,1);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(1,6,5);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(1,2,6);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(4,8,7);
    objAttribute.mTriVertexIndices.push_back(indices);
    indices = meshio::Vec3<unsigned>(4,7,3);
    objAttribute.mTriVertexIndices.push_back(indices);

    refObjects.mOBJAttributes.push_back(objAttribute);
}
