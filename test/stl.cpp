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
#include <testHelpers.hpp>

using namespace std;
using namespace meshio;

TEST(STL, INVALID_FILE)
{
    vector< stl::Data<float> > objs;
    EXPECT_FALSE(stl::read<float>(objs, "/home/nonexistant/cube.stl"));
}

TEST(STL, READ_BINARY)
{
    /* Reference stl::Data object */
    vector< stl::Data<float> > referenceObjs;
    initializeReferenceSTLObj(referenceObjs);

    /* Read stl file using library function */
    vector< stl::Data<float> > objs;
    stl::read<float>(objs, TEST_DIR "/cube_binary.stl");

    EXPECT_TRUE(objs[0] == referenceObjs[0]);

    referenceObjs.clear();
    objs.clear();
}

TEST(STL, READ_ASCII)
{
    /* Reference stl::Data object */
    vector< stl::Data<float> > referenceObjs;
    initializeReferenceSTLObj(referenceObjs);

    vector< stl::Data<float> > objs;
    stl::read<float>(objs, TEST_DIR "/cube_ascii.stl");

    EXPECT_TRUE(objs[0] == referenceObjs[0]);

    referenceObjs.clear();
    objs.clear();
}

TEST(STL, WRITE_INVALID_FORMAT)
{
    vector< stl::Data<float> > objs;
    EXPECT_FALSE(stl::write("/home/nonexistant/wrongformat.stl",
                stl::Format::Binary, objs));
}


TEST(STL, WRITE_TO_INVALID_BINARY_FILE)
{
    vector< stl::Data<float> > objs;
    EXPECT_FALSE(stl::write("/home/nonexistatnt/binary.stl",
                stl::Format::Binary, objs));
}


TEST(STL, WRITE_TO_INVALID_ASCII_FILENAME)
{
    vector< stl::Data<float> > objs;
    EXPECT_FALSE(stl::write("/home/nonexistatnt/ascii.stl",
                stl::Format::Ascii, objs));
}

TEST(STL, WRITE_BINARY)
{
    vector< stl::Data<float> > objs;
    stl::read<float>(objs, TEST_DIR "/cube_ascii.stl");
    stl::write(TEST_DIR "/cube_ascii2binary.stl", stl::Format::Binary, objs);
    objs.clear();
}

TEST(STL, WRITE_ASCII)
{
    vector< stl::Data<float> > objs;
    stl::read<float>(objs, TEST_DIR "/cube_binary.stl");
    stl::write(TEST_DIR "/cube_binary2ascii.stl", stl::Format::Ascii, objs);

    objs.clear();
}

TEST(STL, CROSS_CHECK)
{
    vector< stl::Data<float> > binReadObjs;
    stl::read<float>(binReadObjs, TEST_DIR "/cube_binary.stl");

    vector< stl::Data<float> > asciiReadObjs;
    stl::read<float>(asciiReadObjs, TEST_DIR "/cube_ascii.stl");

    EXPECT_TRUE(binReadObjs[0] == asciiReadObjs[0]);
}
