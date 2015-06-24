/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef __STL_HPP__
#define __STL_HPP__

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include "meshio_defines.hpp"

namespace meshio
{
namespace stl
{

template<typename T=float>
bool read(std::vector< STLData<T> > &pObjects, const char* pFileName);

template<typename T=float>
bool write(const std::vector< STLData<T> > &pObjects, const char* pFileName,
           const STLFormat pFormat = STL_ASCII);

template<typename T>
bool computeVertexNormals(const std::vector< STLData<T> > &pObjects,
                          std::vector< std::vector< Vec3<float> > > &pNormals);

#include "stl.inl"

}
}

#endif // __STL_HPP__
