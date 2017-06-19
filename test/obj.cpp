/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#include "testHelpers.hpp"
#include <meshio/obj.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace meshio;

TEST(OBJ, READ_OBJ)
{
    // Reference OBJData object
    obj::OBJData<float> refOBJData;
    initializeReferenceOBJObject(refOBJData);

    obj::OBJData<float> objData;
    obj::read<float>(objData, TEST_DIR "/cube_tri.obj", nullptr);

    EXPECT_TRUE(objData == refOBJData);

    refOBJData.clear();
    objData.clear();
}

TEST(OBJ, WRITE_OBJ)
{
    // Reference OBJData object
    obj::OBJData<float> refOBJData;
    initializeReferenceOBJObject(refOBJData);
    obj::write<float>(TEST_DIR "/cube_tri_write_ref.obj", refOBJData);

    obj::OBJData<float> objData;
    obj::read<float>(objData, TEST_DIR "/cube_tri.obj", nullptr);
    obj::write<float>(TEST_DIR "/cube_tri_write.obj", objData);

    // TODO: File comparison
    EXPECT_TRUE(true); // place holder

    refOBJData.clear();
    objData.clear();
}
