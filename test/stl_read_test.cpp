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
using namespace stl;

TEST(MeshIO, Read_BinarySTL)
{
    // FIXME
    /*
    The tests still need to be fixed. This message for Laxman to get to know how to
    write unit tests using google test.
    */

    /* Read stl file using library function */
    vector< STLData<float> > objs;
    readSTL<float>(objs, TEST_DIR "/binary.stl");

    /* read gold data using regular file reading */

    /* Now write another helper function that helps you compare two
       objects that has same type of data.

       For example, iIn our case we can handle simple objects like square with
       hard coded data and much bigger objects can be compared
       by cross checking data read from different formats or something
       like that.
    */

    /* use the boolean returned by the comparison helper functon
    to find check for expected result which is TRUE because the
    results should match for our test to pass. This can be done
    using Google Test macros such as EXPECT_EQ (Check Below)
    */

    EXPECT_TRUE(true == true/* Ideally you should your comparison function called here*/);
}
