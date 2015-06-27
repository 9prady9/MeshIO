/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#include <gtest/gtest.h>
#include <meshio/stl.hpp>
#include <vector>

using namespace std;
using namespace meshio;

#include "initialize_reference_objs.inl"

TEST(STL, READ_BINARY)
{
    /* Reference STLData object */
    vector< STLData<float> > referenceObjs;
    initializeReferenceSTLObj(referenceObjs);

    /* Read stl file using library function */
    vector< STLData<float> > objs;
    stl::read<float>(objs, TEST_DIR "/cube_binary.stl");

    EXPECT_TRUE((objs[0] == referenceObjs[0]) == true);

    referenceObjs.clear();
    objs.clear();
}

TEST(STL, READ_ASCII)
{
    /* Reference STLData object */
    vector< STLData<float> > referenceObjs;
    initializeReferenceSTLObj(referenceObjs);

    vector< STLData<float> > objs;
    stl::read<float>(objs, TEST_DIR "/cube_ascii.stl");

    EXPECT_TRUE((objs[0] == referenceObjs[0]) == true);

    referenceObjs.clear();
    objs.clear();
}

TEST(STL, WRITE_ASCII)
{
    /* Reference STLData object */
    vector< STLData<float> > referenceObjs;
    initializeReferenceSTLObj(referenceObjs);

    vector< STLData<float> > objs;
    stl::read<float>(objs, TEST_DIR "/cube_ascii.stl");
    stl::write(objs, TEST_DIR "/cube_ascii2ascii.stl");

    referenceObjs.clear();
    objs.clear();
}
