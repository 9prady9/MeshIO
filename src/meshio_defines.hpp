/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of stl reader whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef __OUTPUT_FORMAT_HPP__
#define __OUTPUT_FORMAT_HPP__

#include <vector>

using namespace std;

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

template<class T>
struct Mesh {
    vector< Vec4<T> >		mPositions;
    vector< Vec3<float> >	mNormals;
    vector< Vec2<float> >	mTexcoords;
    vector< Vec4<float> >	mColors;
    vector< unsigned int>	mIndices;
};

}

#endif // __OUTPUT_FORMAT_HPP__
