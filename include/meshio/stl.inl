/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

template<typename T=float>
Vec3<T> readNormal(const std::string& pLine)
{
    Vec3<T> N;
    float nx, ny, nz;
    std::stringstream lineSS(pLine);
    std::string facet, normal;

    lineSS >> facet >> normal >> nx >> ny >> nz;

    N.SetX(nx);
    N.SetY(ny);
    N.SetZ(nz);

    return N;
}

template<typename T>
Vec4<T> readVertex(const std::string& pLine)
{
    Vec4<T> V;
    float vx, vy, vz, vw;
    std::stringstream lineSS(pLine);
    std::string vertex;

    lineSS >> vertex >> vx >> vy >> vz;
    vw = static_cast<T>(1.0);

    V.SetX(vx);
    V.SetY(vy);
    V.SetZ(vz);
    V.SetW(vw);

    return V;
}

template<typename T = float>
bool readAsciiSTL(std::vector< STLData<T> > &pObjects, const char* pFileName)
{
    std::ifstream objFile(pFileName);
    std::string line;

    if (!objFile.is_open())
        return false;

    while (std::getline(objFile, line)) {
        std::stringstream lineSS(line);
        std::string keyWord;

        lineSS >> keyWord;

        if (keyWord == "solid") {
            STLData<T> currObj;
            bool isFacetRead = false;
            unsigned outerCount = 0;

            while (std::getline(objFile, line)) {
                std::stringstream ss(line);
                std::string key;

                ss >> key;
                if (key == "endsolid")
                    break;

                if (key == "facet") {
                    currObj.mNormals.push_back(readNormal(line));
                    isFacetRead = true;
                } else if (key == "outer") {
                    /* Check if already facet is being read
                       if true, that means another primitive is having the
                       same normal as it's predecessor. Therefore, duplicate
                       the normal
                     */
                    if (isFacetRead && outerCount > 1)
                        currObj.mNormals.push_back(currObj.mNormals.back());
                    /* No need to do anything else specific just
                    just proceed to next line to read vertices */
                    outerCount++;
                } else if (key == "endloop") {
                    /* Marks end of current primitive
                       we don't need to do anything specific
                       here */
                } else if (key == "endfacet") {
                    /* Marks end of current facet, hence reset readFacet flag */
                    isFacetRead = false;
                    outerCount = 0;
                }
                else if (key == "vertex") {
                    currObj.mPositions.push_back(readVertex<T>(line));
                }
            }
            pObjects.push_back(currObj);
        }
    }

    objFile.close();

    return true;
}

/*
 * Reads binary STL file assuming the format as described in
 * https://en.wikipedia.org/wiki/STL_(file_format). After the end of first
 * object, we assume that the next object's information starts with number of
 * triangles and the format continues.
 */
template<typename T = float>
bool readBinarySTL(std::vector< STLData<T> > &pObjects, const char* pFileName)
{
    uint32_t numTriangles;
    uint16_t attribByteCount;
    float value;
    std::vector<float> values;
    std::size_t sizeFloat = sizeof(float);
    std::size_t sizeUInt16 = sizeof(uint16_t);
    unsigned objectCount = 0;

    std::stringstream strErr;
    std::ifstream ifs(pFileName, std::ios::binary | std::ios::in);
    if (!ifs) {
        strErr << "Cannot open file (" << pFileName << ")" << std::endl;
        std::cerr << strErr.str() << std::endl;
        return false;
    }

    char header[80];
    ifs.read(&header[0], 80);

    ifs.read((char *)&numTriangles, sizeof(uint32_t));

    while (numTriangles) {
        STLData<T> stlObject;
        stlObject.resize(numTriangles);
        Vec4<T> position;
        Vec3<float> normal;

        // Default assignment
        position.SetW(static_cast<T>(1.));

        for (uint32_t facet = 0; facet < numTriangles; ++facet) {
            values.clear();
            for (short i = 0; i < 3; ++i) {
                ifs.read((char *)&value, sizeFloat);
                values.push_back(value);
            }
            normal.SetX(values[0]);
            normal.SetY(values[1]);
            normal.SetZ(values[2]);
            stlObject.mNormals[facet] = normal;

            for (short i = 0; i < 3; ++i) {
                values.clear();
                for (short j = 0; j < 3; ++j) {
                    ifs.read((char *)&value, sizeFloat);
                    values.push_back(value);
                }
                position.SetX(values[0]);
                position.SetY(values[1]);
                position.SetZ(values[2]);
                stlObject.mPositions[(3 * facet) + i] = position;
            }

            ifs.read((char *)&attribByteCount, sizeUInt16);
        }
        pObjects.push_back(stlObject);

        numTriangles = 0;
        ifs.read((char *)&numTriangles, sizeof(uint32_t));
    }

    ifs.close();

    return true;
}

template<typename T = float>
bool writeAsciiSTL(const char* pFileName, const std::vector< STLData<T> > &pObjects)
{
    typedef typename std::vector< STLData<T> >::const_iterator CSTLIter;
    typedef typename std::vector< Vec3<float> >::const_iterator CVec3Iter;
    typedef typename std::vector< Vec4<T> >::const_iterator CVec4Iter;

    std::ofstream objFile(pFileName);

    if (!objFile.is_open())
        return false;

    for (CSTLIter obj = pObjects.begin(); obj != pObjects.end(); ++obj) {
        objFile << "solid " << std::endl;

        CVec4Iter v = obj->mPositions.begin();
        for (CVec3Iter f = obj->mNormals.begin(); f != obj->mNormals.end();
             ++f) {
            objFile << "facet normal " << std::scientific << f->X() << " "
                    << f->Y() << " " << f->Z() << std::endl;
            objFile << "outer loop" << std::endl;
            objFile << "vertex " << std::scientific << v->X() << " "
                    << v->Y() << " " << v->Z() << std::endl;
            ++v;
            objFile << "vertex " << std::scientific << v->X() << " "
                    << v->Y() << " " << v->Z() << std::endl;
            ++v;
            objFile << "vertex " << std::scientific << v->X() << " "
                    << v->Y() << " " << v->Z() << std::endl;
            ++v;
            objFile << "endloop" << std::endl;
            objFile << "endfacet" << std::endl;
        }

        objFile << "endsolid" << std::endl;
    }

    objFile.close();

    return true;
}

template<typename T = float>
bool writeBinarySTL(const char* pFileName, const std::vector< STLData<T> > &pObjects)
{
    uint32_t numTriangles;
    uint16_t attribByteCount = 0;
    std::size_t sizeFloat = sizeof(float);
    std::size_t sizeUInt16 = sizeof(uint16_t);
    unsigned objectCount = pObjects.size();

    std::stringstream strErr;
    std::ofstream ofs(pFileName, std::ios::binary | std::ios::out);
    if (!ofs) {
        strErr << "Cannot open file (" << pFileName << ")" << std::endl;
        std::cerr << strErr.str() << std::endl;
        return false;
    }

    std::string headerStr = "<<<<<<<<<<<<<<<<<<<<<<";
    headerStr = headerStr + "Binary STL file written using MeshIO";
    headerStr = headerStr + ">>>>>>>>>>>>>>>>>>>>>>";
    const char *header = headerStr.c_str();
    ofs.write(header, 80);

    for (unsigned object = 0; object < objectCount; ++object) {
        numTriangles = pObjects[object].mNormals.size();
        ofs.write(reinterpret_cast<char *>(&(numTriangles)), sizeof(uint32_t));

        for (unsigned facet = 0; facet < numTriangles; ++facet) {
            Vec3<float> normal = pObjects[object].mNormals[facet];
            ofs.write(reinterpret_cast<char *>(
                            const_cast<float *>(&(normal.X()))), sizeFloat);
            ofs.write(reinterpret_cast<char *>(
                            const_cast<float *>(&(normal.Y()))), sizeFloat);
            ofs.write(reinterpret_cast<char *>(
                            const_cast<float *>(&(normal.Z()))), sizeFloat);
            for (short i = 0; i < 3; ++i) {
                Vec4<T> position = pObjects[object].mPositions[3 * facet + i];
                ofs.write(reinterpret_cast<char *>(
                            const_cast<float *>(&(position.X()))), sizeFloat);
                ofs.write(reinterpret_cast<char *>(
                            const_cast<float *>(&(position.Y()))), sizeFloat);
                ofs.write(reinterpret_cast<char *>(
                            const_cast<float *>(&(position.Z()))), sizeFloat);
            }
            ofs.write(reinterpret_cast<char *>(
                            &(attribByteCount)), sizeUInt16);
        }
    }

    ofs.close();

    return true;
}


template<typename T>
bool read(std::vector< STLData<T> > &pObjects, const char* pFileName)
{
    for (unsigned int i = 0; i < pObjects.size(); ++i)
        pObjects[i].clear();
    pObjects.clear();

    std::stringstream strErr;
    std::ifstream ifs(pFileName);
    if (!ifs) {
        strErr << "Cannot open file (" << pFileName << ")" << std::endl;
        std::cerr << strErr.str() << std::endl;
        return false;
    }

    const int bufferMaxSize = 80; // Only to read header
    char buffer[bufferMaxSize];

    ifs.getline(&buffer[0], bufferMaxSize);
    std::string line(&buffer[0]);
    ifs.close();

    if (line.substr(0, 5) == "solid")
        return readAsciiSTL<T>(pObjects, pFileName);
    else
        return readBinarySTL<T>(pObjects, pFileName);
}

/*
 * Writes STL files in a specified format
 * "ascii" or "binary"
 */
template<typename T>
bool write(const char* pFileName, const STLFormat pFormat,
    const std::vector< STLData<T> > &pObjects)
{
    switch (pFormat) {
    case STL_ASCII: return writeAsciiSTL(pFileName, pObjects);
    case STL_BINARY: return writeBinarySTL(pFileName, pObjects);
        default: return false;
    }
}
