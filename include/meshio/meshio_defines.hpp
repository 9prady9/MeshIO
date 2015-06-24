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

template<typename T>
struct Vec4 {
    T x;
    T y;
    T z;
    T w;
};

template<typename T>
struct Vec3 {
    T x;
    T y;
    T z;
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
};

}

#endif // __MESHIO_DEFINES_HPP__
