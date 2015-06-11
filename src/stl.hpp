/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of stl reader whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef __STL_READER_HPP__
#define __STL_READER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "meshio_defines.hpp"

using namespace std;

namespace meshio
{
namespace stl
{

template<class T>
void readSTL(vector< <Mesh<T> > pObjects, string pFileName)
{
    cout << "Hello World!" << endl;
}

}
}

#endif // __STL_READER_HPP__
