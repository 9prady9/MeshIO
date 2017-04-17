/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#include "testHelpers.hpp"
#include <meshio/obj/obj.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace meshio;

TEST(OBJ, READ_OBJ)
{
    // Reference OBJData object
    obj::OBJData<float> refOBJData;
    initializeReferenceOBJObject(refOBJData);

    obj::OBJData<float> objData;
    obj::read<float>(objData, TEST_DIR "/obj/cube_tri.obj", nullptr);

    obj::write<float>(TEST_DIR "/obj/cube_tri_write.obj", objData);

    std::cout << "printing ref data" << std::endl;
    refOBJData.print();
    std::cout << "printing read data" << std::endl;
    objData.print();

    EXPECT_TRUE(objData == refOBJData);

    refOBJData.clear();
    objData.clear();
}

/*
TEST(OBJ, WRITE_OBJ)
{
    vector< STLData<float> > objs;
    stl::read<float>(objs, TEST_DIR "/cube_binary.stl");
    stl::write(TEST_DIR "/cube_binary2ascii.stl", meshio::STL_ASCII, objs);

    objs.clear();
}
*/
