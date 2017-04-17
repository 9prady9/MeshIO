/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef MESHIO_OBJ_OBJ_HPP_
#define MESHIO_OBJ_OBJ_HPP_

#define TINYOBJLOADER_IMPLEMENTATION

#include "../utilities.hpp"
#include "../meshio_defines.hpp"
#include "../../third_party/tiny_obj_loader.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace meshio
{
namespace obj
{

/* Datastructure to store Wavefront OBJ */
template<class T>
class OBJAttribute : public GeometryData<T> {
  public:
    std::string mOBJName;
    std::vector<int> mMaterialIDs;

    OBJAttribute() {}
    ~OBJAttribute() {}

    void resizeVertexAttributes(unsigned pNumTriangles) {
        this->mPositions.resize(pNumTriangles);
        this->mNormals.resize(pNumTriangles);
        this->mTexturePositions.resize(pNumTriangles);
        this->mColors.resize(pNumTriangles);
        this->mParameterSpaceVertices.resize(pNumTriangles);
    }

    void resizeIndices(unsigned pNumIndices) {
        this->mTriVertexIndices.resize(pNumIndices);
        this->mTriTextureIndices.resize(pNumIndices);
        this->mTriNormalIndices.resize(pNumIndices);
    }

    void clear() {
        GeometryData<T>::clear();
        mMaterialIDs.clear();
    }

    bool operator==(const OBJAttribute<T>& pOBJAttribute) const {
        if (dynamic_cast<GeometryData<T>&>(
                        const_cast<OBJAttribute<T>&>(*this)) ==
                dynamic_cast<GeometryData<T>&>(
                        const_cast<OBJAttribute<T>&>(pOBJAttribute))) {

            if (!mOBJName.compare(pOBJAttribute.mOBJName)) {
                // Checking equality for mMaterialIDs.
                if (mMaterialIDs.size() && pOBJAttribute.mMaterialIDs.size()) {
                    for (unsigned i = 0; i < mMaterialIDs.size(); ++i) {
                        if (!(mMaterialIDs[i] == pOBJAttribute.mMaterialIDs[i]))
                            return false;
                    }
                    return true;
                } else if (!mMaterialIDs.size() &&
                           !pOBJAttribute.mMaterialIDs.size()) {
                    return true;
                } else {
                    return false;
                }

            } else {
                return false;
            }

        } else {
            return false;
        }
    }

};

template<class T>
class OBJData {
  public:
    std::vector< OBJAttribute<T> > mOBJAttributes;
    std::vector<tinyobj::material_t> mOBJMaterials;

    OBJData() {}
    ~OBJData() {
        clear();
    }

    // TODO Delete this function
    void print() {
        for (unsigned i = 0; i < mOBJAttributes.size(); ++i) {
            OBJAttribute<T> &objAttribute = mOBJAttributes[i];
            std::cout << "Number of points = "
                << objAttribute.mPositions.size() << std::endl;
            for (unsigned j = 0; j < objAttribute.mPositions.size();
                 ++j) {
                std::cout << "v " << objAttribute.mPositions[j].getX() << " "
                    << objAttribute.mPositions[j].getY() << " "
                    << objAttribute.mPositions[j].getZ() << std::endl;
            }

            std::cout << "Number of indices = "
                << objAttribute.mTriVertexIndices.size() << std::endl;
            for (unsigned j = 0; j < objAttribute.mTriVertexIndices.size();
                 ++j) {
                std::cout << "f " << objAttribute.mTriVertexIndices[j].getX()
                    << " " << objAttribute.mTriVertexIndices[j].getY()
                    << " " << objAttribute.mTriVertexIndices[j].getZ()
                    << std::endl;
            }
        }
    }
    // End delete

    void clear() {
        for (unsigned i = 0; i < mOBJAttributes.size(); ++i)
            mOBJAttributes[i].clear();
        mOBJAttributes.clear();
        mOBJMaterials.clear();
    }

    bool isEqualOBJAttributes(const OBJData<T>& pOBJData) {
        return (mOBJAttributes == pOBJData.mOBJAttributes);
    }

    bool isEqualOBJMaterials(const OBJData<T>& pOBJData) {
        if (mOBJMaterials.size() && pOBJData.mOBJMaterials.size()) {
            for (unsigned i = 0; i < mOBJMaterials.size(); ++i) {

                if (!isEqual(mOBJMaterials[i].ambient[0],
                             pOBJData.mOBJMaterials[i].ambient[0]) ||
                    !isEqual(mOBJMaterials[i].ambient[1],
                             pOBJData.mOBJMaterials[i].ambient[1]) ||
                    !isEqual(mOBJMaterials[i].ambient[2],
                             pOBJData.mOBJMaterials[i].ambient[2]))
                    return false;

                if (!isEqual(mOBJMaterials[i].diffuse[0],
                             pOBJData.mOBJMaterials[i].diffuse[0]) ||
                    !isEqual(mOBJMaterials[i].diffuse[1],
                             pOBJData.mOBJMaterials[i].diffuse[1]) ||
                    !isEqual(mOBJMaterials[i].diffuse[2],
                             pOBJData.mOBJMaterials[i].diffuse[2]))
                    return false;

                if (!isEqual(mOBJMaterials[i].specular[0],
                             pOBJData.mOBJMaterials[i].specular[0]) ||
                    !isEqual(mOBJMaterials[i].specular[1],
                             pOBJData.mOBJMaterials[i].specular[1]) ||
                    !isEqual(mOBJMaterials[i].specular[2],
                             pOBJData.mOBJMaterials[i].specular[2]))
                    return false;

                if (!isEqual(mOBJMaterials[i].transmittance[0],
                             pOBJData.mOBJMaterials[i].transmittance[0]) ||
                    !isEqual(mOBJMaterials[i].transmittance[1],
                             pOBJData.mOBJMaterials[i].transmittance[1]) ||
                    !isEqual(mOBJMaterials[i].transmittance[2],
                             pOBJData.mOBJMaterials[i].transmittance[2]))
                    return false;

                if (!isEqual(mOBJMaterials[i].emission[0],
                             pOBJData.mOBJMaterials[i].emission[0]) ||
                    !isEqual(mOBJMaterials[i].emission[1],
                             pOBJData.mOBJMaterials[i].emission[1]) ||
                    !isEqual(mOBJMaterials[i].emission[2],
                             pOBJData.mOBJMaterials[i].emission[2]))
                    return false;

                if (!isEqual(mOBJMaterials[i].shininess,
                             pOBJData.mOBJMaterials[i].shininess))
                    return false;

                if (!isEqual(mOBJMaterials[i].ior,
                             pOBJData.mOBJMaterials[i].ior))
                    return false;

                if (!isEqual(mOBJMaterials[i].dissolve,
                             pOBJData.mOBJMaterials[i].dissolve))
                    return false;

                if (!(mOBJMaterials[i].illum ==
                      pOBJData.mOBJMaterials[i].illum))
                    return false;

                if (mOBJMaterials[i].ambient_texname.compare(
                                pOBJData.mOBJMaterials[i].ambient_texname))
                    return false;

                if (mOBJMaterials[i].diffuse_texname.compare(
                                pOBJData.mOBJMaterials[i].diffuse_texname))
                    return false;

                if (mOBJMaterials[i].specular_texname.compare(
                                pOBJData.mOBJMaterials[i].specular_texname))
                    return false;

                if (mOBJMaterials[i].specular_highlight_texname.compare(
                        pOBJData.mOBJMaterials[i].specular_highlight_texname))
                    return false;

                if (mOBJMaterials[i].bump_texname.compare(
                                pOBJData.mOBJMaterials[i].bump_texname))
                    return false;

                if (mOBJMaterials[i].displacement_texname.compare(
                                pOBJData.mOBJMaterials[i].displacement_texname))
                    return false;

                if (mOBJMaterials[i].alpha_texname.compare(
                                pOBJData.mOBJMaterials[i].alpha_texname))
                    return false;

            }
            return true;
        } else if (!mOBJMaterials.size() && !pOBJData.mOBJMaterials.size()) {
            return true;
        } else {
            return false;
        }
    }

    bool operator==(const OBJData<T>& pOBJData) {
        return (isEqualOBJAttributes(pOBJData) &&
                isEqualOBJMaterials(pOBJData));
    }
};

/*
 * Usage:
 * vector< obj::OBJData<float> > objs;
 * obj::read<float>(objs, obj_file_path, mtl_file_base_path or nullptr);
 */
template<typename T=float>
bool read(OBJData<T> &pObjects, const char* pFileName,
          const char* pMatFileBasePath);

template<typename T=float>
bool write(const char* pFileName, const OBJData<T> &pObjects);

#include "obj.inl"

}
}

#endif // MESHIO_OBJ_OBJ_HPP_
