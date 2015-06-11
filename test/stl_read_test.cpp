/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of stl reader whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#include "../src/stl.hpp"
#include <vector>

using namespace std;
using namespace meshio;
using namespace stl;

int main()
{
    vector< Mesh<float> > objs;
    readSTL<float>(objs, "stl file full path");
    return 0;
}
