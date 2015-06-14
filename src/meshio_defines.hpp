/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of stl reader whose distribution is governed by
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
};

template<typename T>
struct Vec2 {
    T x;
    T y;
};

template<typename T>
struct Mesh {
    std::vector< Vec4<T> >       mPositions;
    std::vector< Vec3<float> >   mNormals;
    std::vector< Vec2<float> >   mTexcoords;
    std::vector< Vec4<float> >   mColors;
    std::vector< unsigned int>   mIndices;

    void Resize(unsigned int pSize) {
        mPositions.resize(3*pSize);
        mNormals.resize(pSize);
        mTexcoords.resize(pSize);
        mColors.resize(pSize);
        mIndices.resize(3*pSize);
    }

    void Clear() {
        mPositions.clear();
        mNormals.clear();
        mTexcoords.clear();
        mColors.clear();
        mIndices.clear();
    }
};

}

#endif // __MESHIO_DEFINES_HPP__
