template<typename T>
void initializeReferenceSTLObj(vector< STLData<T> > &refObjs)
{
    for(unsigned i = 0; i < refObjs.size(); ++i)
        refObjs[i].clear();
    refObjs.clear();

    STLData<T> refObj;
    refObj.resize(12);
    refObj.mNormals[0] = Vec3<T>(0,0,-1);
    refObj.mPositions[0] = Vec4<T>(0,0,0,1);
    refObj.mPositions[1] = Vec4<T>(1,1,0,1);
    refObj.mPositions[2] = Vec4<T>(1,0,0,1);
    refObj.mNormals[1] = Vec3<T>(0,0,-1);
    refObj.mPositions[3] = Vec4<T>(0,0,0,1);
    refObj.mPositions[4] = Vec4<T>(0,1,0,1);
    refObj.mPositions[5] = Vec4<T>(1,1,0,1);
    refObj.mNormals[2] = Vec3<T>(1,0,0);
    refObj.mPositions[6] = Vec4<T>(1,0,0,1);
    refObj.mPositions[7] = Vec4<T>(1,1,1,1);
    refObj.mPositions[8] = Vec4<T>(1,0,1,1);
    refObj.mNormals[3] = Vec3<T>(1,0,0);
    refObj.mPositions[9] = Vec4<T>(1,0,0,1);
    refObj.mPositions[10] = Vec4<T>(1,1,0,1);
    refObj.mPositions[11] = Vec4<T>(1,1,1,1);
    refObj.mNormals[4] = Vec3<T>(0,0,1);
    refObj.mPositions[12] = Vec4<T>(1,0,1,1);
    refObj.mPositions[13] = Vec4<T>(0,1,1,1);
    refObj.mPositions[14] = Vec4<T>(0,0,1,1);
    refObj.mNormals[5] = Vec3<T>(0,0,1);
    refObj.mPositions[15] = Vec4<T>(1,0,1,1);
    refObj.mPositions[16] = Vec4<T>(1,1,1,1);
    refObj.mPositions[17] = Vec4<T>(0,1,1,1);
    refObj.mNormals[6] = Vec3<T>(-1,0,0);
    refObj.mPositions[18] = Vec4<T>(0,0,0,1);
    refObj.mPositions[19] = Vec4<T>(0,1,1,1);
    refObj.mPositions[20] = Vec4<T>(0,1,0,1);
    refObj.mNormals[7] = Vec3<T>(-1,0,0);
    refObj.mPositions[21] = Vec4<T>(0,0,0,1);
    refObj.mPositions[22] = Vec4<T>(0,0,1,1);
    refObj.mPositions[23] = Vec4<T>(0,1,1,1);
    refObj.mNormals[8] = Vec3<T>(0,1,0);
    refObj.mPositions[24] = Vec4<T>(0,1,0,1);
    refObj.mPositions[25] = Vec4<T>(1,1,1,1);
    refObj.mPositions[26] = Vec4<T>(1,1,0,1);
    refObj.mNormals[9] = Vec3<T>(0,1,0);
    refObj.mPositions[27] = Vec4<T>(0,1,0,1);
    refObj.mPositions[28] = Vec4<T>(0,1,1,1);
    refObj.mPositions[29] = Vec4<T>(1,1,1,1);
    refObj.mNormals[10] = Vec3<T>(0,-1,0);
    refObj.mPositions[30] = Vec4<T>(0,0,0,1);
    refObj.mPositions[31] = Vec4<T>(1,0,0,1);
    refObj.mPositions[32] = Vec4<T>(1,0,1,1);
    refObj.mNormals[11] = Vec3<T>(0,-1,0);
    refObj.mPositions[33] = Vec4<T>(0,0,0,1);
    refObj.mPositions[34] = Vec4<T>(1,0,1,1);
    refObj.mPositions[35] = Vec4<T>(0,0,1,1);

    refObjs.push_back(refObj);
}

