/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef __MESHIO_DEFINES_HPP__
#define __MESHIO_DEFINES_HPP__

#include <vector>

namespace meshio
{

enum STLFormat {
    STL_ASCII = 0,
    STL_BINARY = 1
};

template<typename T>
struct Vec4 {
    T x;
    T y;
    T z;
    T w;

    Vec4(T pX, T pY, T pZ, T pW) {
        x = pX;
        y = pY;
        z = pZ;
        w = pW;
    }

    Vec4(T pX, T pY, T pZ) {
        Vec4(pX, pY, pZ, (T)0);
    }

    Vec4(T pX, T pY) {
        Vec4(pX, pY, (T)0, (T)0);
    }

    Vec4(T pX) {
        Vec4(pX, (T)0, (T)0, (T)0);
    }

    Vec4() {
        Vec4((T)0, (T)0, (T)0, (T)0);
    }

    bool equal(Vec4& pVec4) {
        return (pVec4.x == x && pVec4.y == y && pVec4.z == z &&
                pVec4.w == w);
    }
};

template<typename T>
struct Vec3 {
    T x;
    T y;
    T z;

    Vec3(T pX, T pY, T pZ) {
        x = pX;
        y = pY;
        z = pZ;
    }

    Vec3(T pX, T pY) {
        Vec3(pX, pY, (T)0);
    }

    Vec3(T pX) {
        Vec3(pX, (T)0, (T)0);
    }

    Vec3() {
        Vec3((T)0, (T)0, (T)0);
    }

    bool equal(Vec3& pVec3) {
        return (pVec3.x == x && pVec3.y == y && pVec3.z == z);
    }

    struct Vec3& operator+=(const struct Vec3& pVec3) {
        x += pVec3.x;
        y += pVec3.y;
        z += pVec3.z;
        return *this;
    }

    struct Vec3& operator/=(const int pDiv) {
        x /= pDiv;
        y /= pDiv;
        z /= pDiv;
        return *this;
    }
};

template<typename T>
struct Vec2 {
    T x;
    T y;
};

template<class T>
class Mesh {
  public:
    std::vector< Vec4<T> >  mPositions;
    std::vector< Vec3<float> > mNormals;
    std::vector< Vec2<float> > mTexcoords;
    std::vector< Vec4<float> > mColors;
    std::vector< unsigned > mIndices;

    void resize(unsigned pSize) {
        mPositions.resize(pSize);
        mNormals.resize(pSize);
        mTexcoords.resize(pSize);
        mColors.resize(pSize);
    }

    void resizeIndices(unsigned pSize) {
        mIndices.resize(pSize);
    }

    void clear() {
        mPositions.clear();
        mNormals.clear();
        mTexcoords.clear();
        mColors.clear();
        mIndices.clear();
    }
};

/*
 * struct to store data from STL file
 */
template<typename T>
struct STLData {
    std::vector< Vec4<T> >      mPositions;
    std::vector< Vec3<float> >  mNormals;

    void resize(unsigned pNumTriangles) {
        mPositions.resize(3*pNumTriangles);
        mNormals.resize(pNumTriangles);
    }

    void clear() {
        mPositions.clear();
        mNormals.clear();
    }

    bool equal(STLData<T>& pSTLObj) {
        if(mPositions.size() != pSTLObj.mPositions.size())
            return false;
        if(mNormals.size() != pSTLObj.mNormals.size())
            return false;
        for(unsigned i = 0; i < mPositions.size(); ++i)
            if(!mPositions[i].equal(pSTLObj.mPositions[i]))
                return false;
        for(unsigned i = 0; i < mNormals.size(); ++i)
            if(!mNormals[i].equal(pSTLObj.mNormals[i]))
                return false;
        return true;
    }
};

}

#endif // __MESHIO_DEFINES_HPP__
