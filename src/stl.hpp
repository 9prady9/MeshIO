/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of stl reader whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef __STL_HPP__
#define __STL_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include "meshio_defines.hpp"

namespace meshio
{
namespace stl
{

template<typename T>
bool readAsciiSTL(std::vector< Mesh<T> > &pObjects, const char* pFileName);

template<typename T>
bool readBinarySTL(std::vector< Mesh<T> > &pObjects, const char* pFileName);

template<typename T=float>
bool readSTL(std::vector< Mesh<T> > &pObjects, const char* pFileName)
{
    for(unsigned int i = 0; i < pObjects.size(); ++i)
        pObjects[i].Clear();

    std::stringstream pStrErr;
    std::ifstream pIFS(pFileName);
    if(!pIFS) {
        pStrErr << "Cannot open file (" << pFileName << ")" << std::endl;
        std::cout << pStrErr.str() << std::endl;
        return false;
    }

    int pBufferMaxSize = 80; // Only to read header
    char pBuffer[pBufferMaxSize];

    pIFS.getline(&pBuffer[0], pBufferMaxSize);
    std::string pLine(&pBuffer[0]);
    pIFS.close();

    if(pLine.substr(0,5) == "solid")
        return readAsciiSTL<T>(pObjects, pFileName);
    else
        return readBinarySTL<T>(pObjects, pFileName);
}

template<typename T=float>
bool readAsciiSTL(std::vector< Mesh<T> > &pObjects, const char* pFileName)
{
    std::cout << "Reading Ascii STL file" << std::endl;
    return true;
}

template<class T=float>
bool readBinarySTL(std::vector< Mesh<T> > &pObjects, const char* pFileName)
{
    typedef float T2;
    std::cout << "Reading Binary STL file" << std::endl;

    uint32_t pNumTriangles;
    uint16_t pAttribByteCount;
    T2 pValue;
    std::vector<T2> pValues;
    std::size_t pSizeT2 = sizeof(T2);
    std::size_t pSizeUInt16 = sizeof(uint16_t);
    unsigned pObjectCount = 0;

    std::stringstream pStrErr;
    std::ifstream pIFS(pFileName, std::ios::binary | std::ios::in);
    if(!pIFS) {
        pStrErr << "Cannot open file (" << pFileName << ")" << std::endl;
        std::cout << pStrErr.str() << std::endl;
        return false;
    }

    char pHeader[80];
    pIFS.read(&pHeader[0],80);

    pIFS.read((char *)&pNumTriangles, sizeof(uint32_t));

    while(pNumTriangles) {
        std::cout<<"\tReading " << pNumTriangles << " facets from object "
            << ++pObjectCount << std::endl;
        Mesh<T> pObject;
        pObject.Resize(pNumTriangles);
        Vec4<T> pPosition;
        Vec3<T> pNormal;

        // Default assignment
        pPosition.w = (T)1.;

        for(uint32_t facet = 0; facet < pNumTriangles; ++facet) {
            pValues.clear();
            for(short i = 0; i < 3; ++i) {
                pIFS.read((char *)&pValue, pSizeT2);
                pValues.push_back(pValue);
            }
            pNormal.x = pValues[0];
            pNormal.y = pValues[1];
            pNormal.z = pValues[2];
            pObject.mNormals[facet] = pNormal;

            for(short i = 0; i < 3; ++i) {
                pValues.clear();
                for(short j = 0; j < 3; ++j) {
                    pIFS.read((char *)&pValue, pSizeT2);
                    pValues.push_back(pValue);
                }
                pPosition.x = pValues[0];
                pPosition.y = pValues[1];
                pPosition.z = pValues[2];
                pObject.mPositions[(3*facet)+i] = pPosition;

                pObject.mIndices[(3*facet)+i] = (3*facet)+i;
            }

            pIFS.read((char *)&pAttribByteCount, pSizeUInt16);
        }
        pObjects.push_back(pObject);

        pNumTriangles = 0;
        pIFS.read((char *)&pNumTriangles, sizeof(uint32_t));
    }

    pIFS.close();

    return true;
}

}
}

#endif // __STL_HPP__
