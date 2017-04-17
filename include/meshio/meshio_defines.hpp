/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef MESHIO_MESHIO_DEFINES_HPP_
#define MESHIO_MESHIO_DEFINES_HPP_

#include "vectors.hpp"
#include <vector>

namespace meshio
{

enum STLFormat {
    STL_ASCII = 0,
    STL_BINARY = 1
};

/* Base class for various geometry definitions */
template<class T>
class GeometryData {
  public:
    std::vector< Vec4<T> >          mPositions;
    std::vector< Vec3<float> >      mNormals;
    std::vector< Vec3<T> >          mTexturePositions;
    std::vector< Vec3<T> >          mColors;
    std::vector< Vec3<T> >          mParameterSpaceVertices;
    std::vector< Vec3<unsigned> >   mTriVertexIndices;
    std::vector< Vec4<unsigned> >   mQuadVertexIndices;
    std::vector< Vec3<unsigned> >   mTriTextureIndices;
    std::vector< Vec4<unsigned> >   mQuadTextureIndices;
    std::vector< Vec3<unsigned> >   mTriNormalIndices;
    std::vector< Vec4<unsigned> >   mQuadNormalIndices;

    GeometryData() {}

    ~GeometryData() {
        this->clear();
    }

    virtual void clear() {
        mPositions.clear();
        mNormals.clear();
        mTexturePositions.clear();
        mColors.clear();
        mParameterSpaceVertices.clear();
        mTriVertexIndices.clear();
        mQuadVertexIndices.clear();
        mTriTextureIndices.clear();
        mQuadTextureIndices.clear();
        mTriNormalIndices.clear();
        mQuadNormalIndices.clear();
    }

    virtual bool operator==(const GeometryData<T>& pGeometryDataObj) {
        if (mPositions.size() != pGeometryDataObj.mPositions.size())
            return false;
        if (mNormals.size() != pGeometryDataObj.mNormals.size())
            return false;
        if (mTexturePositions.size()!=pGeometryDataObj.mTexturePositions.size())
            return false;
        if (mColors.size() != pGeometryDataObj.mColors.size())
            return false;
        if (mParameterSpaceVertices.size() !=
           pGeometryDataObj.mParameterSpaceVertices.size())
            return false;
        if (mPositions.size())
            for (unsigned i = 0; i < mPositions.size(); ++i)
                if (!(mPositions[i] == pGeometryDataObj.mPositions[i]))
                    return false;
        if (mNormals.size())
            for (unsigned i = 0; i < mNormals.size(); ++i)
                if (!(mNormals[i] == pGeometryDataObj.mNormals[i]))
                    return false;
        if (mTexturePositions.size())
            for (unsigned i = 0; i < mTexturePositions.size(); ++i)
                if (!(mTexturePositions[i] ==
                      pGeometryDataObj.mTexturePositions[i]))
                    return false;
        if (mColors.size())
            for (unsigned i = 0; i < mColors.size(); ++i)
                if (!(mColors[i] == pGeometryDataObj.mColors[i]))
                    return false;
        if (mParameterSpaceVertices.size())
            for (unsigned i = 0; i < mParameterSpaceVertices.size(); ++i)
                if (!(mParameterSpaceVertices[i] ==
                      pGeometryDataObj.mParameterSpaceVertices[i]))
                    return false;
        return true;
    }
};

/* STLData class to store data from STL file */
template<class T>
class STLData : public GeometryData<T> {
  public:
    STLData() {}
    ~STLData() {}

    void resize(unsigned pNumTriangles) {
        this->mPositions.resize(3*pNumTriangles);
        this->mNormals.resize(pNumTriangles);
    }
};

}

#endif // MESHIO_MESHIO_DEFINES_HPP_
