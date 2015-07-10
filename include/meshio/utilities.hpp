/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef MESHIO_UTILITIES_HPP_
#define MESHIO_UTILITIES_HPP_

#include <string>
#include <cmath>

namespace meshio
{

/**
 * Extracts filename from path.
 */
static inline std::string GetFileBaseName(const std::string& pFileName)
{
    if (pFileName.find_last_of(".") != std::string::npos)
        return pFileName.substr(0, pFileName.find_last_of("."));
    return "";
}

template<typename T = float>
static inline bool isEqual(const T pA, const T pB, const T pTolerance = 1e-6)
{
    if (std::abs(pA - pB) <= pTolerance)
        return true;
    else
        return false;
}
}

#endif // MESHIO_UTILITIES_HPP_
