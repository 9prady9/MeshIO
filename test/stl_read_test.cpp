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

template<typename T>
void writeMesh(vector< Mesh<T> > &objs) {
    ofstream fNormals("normals.txt"); //TODO check file variable convention
    ofstream fPositions("positions.txt"); //TODO same as above

    if(fNormals.is_open() && fPositions.is_open()) {
        for(unsigned i = 0; i < objs.size(); ++i) {
            fNormals << "object " << i+1;
            fPositions << "object " << i+1;
            for(unsigned j = 0; j < objs[i].mNormals.size(); ++j) {
                fNormals << "\n" << objs[i].mNormals[j].x << " "
                    << objs[i].mNormals[j].y << " "
                    << objs[i].mNormals[j].z;
            }
            for(unsigned j = 0; j < objs[i].mPositions.size(); ++j) {
                fPositions << "\n" << objs[i].mPositions[j].x << " "
                    << objs[i].mPositions[j].y << " "
                    << objs[i].mPositions[j].z << " "
                    << objs[i].mPositions[j].w;
            }
        }
        fNormals.close();
        fPositions.close();
    }
}

int main()
{
    typedef float T;
    vector< Mesh<T> > objs;
    readSTL(objs, "../resources/sample_binary.stl");

    writeMesh<T>(objs);

    // Clear
    for(unsigned i = 0; i < objs.size(); ++i)
        objs[i].Clear();

    return 0;
}
