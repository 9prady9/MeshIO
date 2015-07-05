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
#include "vectors.hpp"

namespace meshio
{

enum STLFormat {
    STL_ASCII = 0,
    STL_BINARY = 1
};

template<class T>
class Mesh {
  public:
    std::vector< Vec4<T> >  mPositions;
    std::vector< Vec3<float> > mNormals;
    std::vector< Vec2<float> > mTexcoords;
    std::vector< Vec4<float> > mColors;
    std::vector< unsigned > mIndices;

    Mesh() {}

    ~Mesh() {
        this->clear();
    }

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

/* STLData class to store data from STL file */
template<class T>
class STLData {
  public:
    std::vector< Vec4<T> >      mPositions;
    std::vector< Vec3<float> >  mNormals;

    STLData() {}

    ~STLData() {
        this->clear();
    }

    void resize(unsigned pNumTriangles) {
        mPositions.resize(3*pNumTriangles);
        mNormals.resize(pNumTriangles);
    }

    void clear() {
        mPositions.clear();
        mNormals.clear();
    }

    bool operator==(const STLData<T>& pSTLObj) {
        if(this->mPositions.size() != pSTLObj.mPositions.size())
            return false;

        if(this->mNormals.size() != pSTLObj.mNormals.size())
            return false;

        for(unsigned i = 0; i < mPositions.size(); ++i)
            if(!(this->mPositions[i] == pSTLObj.mPositions[i]))
                return false;

        for(unsigned i = 0; i < mNormals.size(); ++i)
            if(!(this->mNormals[i] == pSTLObj.mNormals[i]))
                return false;

        return true;
    }
};

}

#endif // __MESHIO_DEFINES_HPP__
