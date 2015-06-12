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
#include "meshio_defines.hpp"

namespace meshio
{
namespace stl
{

template<class T>
bool readAsciiSTL(std::vector< Mesh<T> > &pObjects, const char* pFileName);

template<class T>
bool readBinarySTL(std::vector< Mesh<T> > &pObjects, const char* pFileName);

template<class T>
bool readSTL(std::vector< Mesh<T> > &pObjects, const char* pFileName)
{
    pObjects.clear();
    std::stringstream pStrErr;
    std::ifstream pIFS(pFileName);
    if(!pIFS) {
        pStrErr << "Cannot open file (" << pFileName << ")" << std::endl;
        return false;
    }

    int pBufferMaxSize = 80; // Only to read header
    char pBuffer[pBufferMaxSize];

    pIFS.getline(&pBuffer[0], pBufferMaxSize);
    std::string pLine(&pBuffer[0]);
    pIFS.close();

    if(pLine.substr(0,5) == "solid")
        readAsciiSTL<T>(pObjects, pFileName);
    else
        readBinarySTL<T>(pObjects, pFileName);

    return true;
}

template<class T>
bool readAsciiSTL(std::vector< Mesh<T> > &pObjects, const char* pFileName)
{
    std::cout << "Reading Ascii STL file" << std::endl;
    return true;
}

template<class T>
bool readBinarySTL(std::vector< Mesh<T> > &pObjects, const char* pFileName)
{
    std::cout << "Reading Binary STL file" << std::endl;
    return true;
}

}
}

#endif // __STL_HPP__
