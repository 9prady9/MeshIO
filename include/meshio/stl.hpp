/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef MESHIO_STL_HPP_
#define MESHIO_STL_HPP_

#include "meshio_defines.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>

namespace meshio
{
namespace stl
{

template<typename T=float>
bool read(std::vector< STLData<T> > &pObjects, const char* pFileName);

template<typename T=float>
bool write(const char* pFileName, const STLFormat pFormat,
           const std::vector< STLData<T> > &pObjects);

#include "stl.inl"

}
}

#endif // MESHIO_STL_HPP_
