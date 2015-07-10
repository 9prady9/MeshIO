/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

/**
 * Write mtl file, courtesy obj_writer.cc of tinyobjloader.
 */
template<typename T>
bool WriteMtl(const char* pMtlFileName,
              const std::vector<tinyobj::material_t> &pMaterials)
{
    std::ofstream ofs(pMtlFileName, std::ios::out);

    if (!ofs.is_open()) {
        std::stringstream strErr;
        strErr << "Cannot open file (" << pMtlFileName << ")" << std::endl;
        std::cerr << strErr.str() << std::endl;
        return false;
    }

    for (unsigned i = 0; i < pMaterials.size(); ++i) {
        tinyobj::material_t mtl = pMaterials[i];
        ofs << "newmtl " << mtl.name.c_str() << std::endl;
        ofs << "Ka " << mtl.ambient[0] << " " << mtl.ambient[1]
            << " " << mtl.ambient[2] << std::endl;
        ofs << "Kd " << mtl.diffuse[0] << " " << mtl.diffuse[1]
            << " " << mtl.diffuse[2] << std::endl;
        ofs << "Ks " << mtl.specular[0] << " " << mtl.specular[1]
            << " " << mtl.specular[2] << std::endl;
        // TODO "Kt or Ft?"
        ofs << "Kt " << mtl.transmittance[0] << " " << mtl.transmittance[1]
            << " " << mtl.transmittance[2] << std::endl;
        ofs << "illum " << mtl.illum << std::endl;
        ofs << "d " << mtl.dissolve << std::endl;
        ofs << "Ke " << mtl.emission[0] << " " << mtl.emission[1]
            << " " << mtl.emission[2] << std::endl;
        ofs << "Ns " << mtl.shininess << std::endl;
        ofs << "Ni " << mtl.ior << std::endl;

        ofs << "map_Ka " << mtl.ambient_texname.c_str() << std::endl;
        ofs << "map_Kd " << mtl.diffuse_texname.c_str() << std::endl;
        ofs << "map_Ks " << mtl.specular_texname.c_str() << std::endl;
        ofs << "map_Ns " << mtl.specular_highlight_texname.c_str() << std::endl;
        ofs << "map_d " << mtl.alpha_texname.c_str() << std::endl;
        // TODO check for map_bump
        ofs << "bump " << mtl.bump_texname.c_str() << std::endl;
        ofs << "disp " << mtl.displacement_texname.c_str() << std::endl;
    }

    ofs.close();

    return true;
}

/**
 * Write OBJ file, courtesy obj_writer.cc of tinyobjloader.
 */
template<typename T>
bool write(const char* pFileName, const OBJData<T> &pObjects)
{
    std::string fileName(pFileName);
    std::string mtlFileName = GetFileBaseName(fileName) + ".mtl";

    std::ofstream ofs(pFileName, std::ios::out);

    if (!ofs.is_open()) {
        std::stringstream strErr;
        strErr << "Cannot open file (" << pFileName << ")" << std::endl;
        std::cerr << strErr.str() << std::endl;
        return false;
    }

    ofs << "mtllib " << mtlFileName.c_str() << std::endl;

    unsigned v_offset = 0;
    unsigned vn_offset = 0;
    unsigned vt_offset = 0;
    int prev_material_id = -1;

    for (auto obj_shape = pObjects.mOBJAttributes.begin();
         obj_shape != pObjects.mOBJAttributes.end(); ++obj_shape) {

        bool has_vn = false;
        bool has_vt = false;

        if (obj_shape->mOBJName.empty()) {
            ofs << "g Unknown" << std::endl;
        } else {
            ofs << "g " << obj_shape->mOBJName.c_str() << std::endl;
        }

        // face vertices
        for (auto face_indices = obj_shape->mTriVertexIndices.begin();
             face_indices != obj_shape->mTriVertexIndices.end();
             ++face_indices) {
            for (auto face_index = face_indices->Begin();
                 face_index != face_indices->End(); ++face_index) {
                ofs << "v " << obj_shape->mPositions[*face_index].X()
                    << " " << obj_shape->mPositions[*face_index].Y()
                    << " " << obj_shape->mPositions[*face_index].Z()
                    << std::endl;
            }
        }

        // face normals
        if (obj_shape->mNormals.size()) {
            has_vn = true;
            for (auto face_indices = obj_shape->mTriVertexIndices.begin();
                 face_indices != obj_shape->mTriVertexIndices.end();
                 ++face_indices) {
                for (auto face_index = face_indices->Begin();
                     face_index != face_indices->End(); ++face_index) {
                    ofs << "vn " << obj_shape->mNormals[*face_index].X()
                        << " " << obj_shape->mNormals[*face_index].Y()
                        << " " << obj_shape->mNormals[*face_index].Z()
                        << std::endl;
                }
            }
        }

        // face texture coordinates
        if (obj_shape->mTexturePositions.size()) {
            has_vt = true;
            for (auto face_indices = obj_shape->mTriVertexIndices.begin();
                 face_indices != obj_shape->mTriVertexIndices.end();
                 ++face_indices) {
                for (auto face_index = face_indices->Begin();
                     face_index != face_indices->End(); ++face_index) {
                    ofs << "vt "
                        << obj_shape->mTexturePositions[*face_index].X()
                        << " " << obj_shape->mTexturePositions[*face_index].Y()
                        << std::endl;
                }
            }
        }

        // face
        unsigned k = 0;
        for (auto face_indices = obj_shape->mTriVertexIndices.begin();
             face_indices != obj_shape->mTriVertexIndices.end();
             ++face_indices, ++k) {
            unsigned v0 = (3*k + 0) + 1 + v_offset;
            unsigned v1 = (3*k + 1) + 1 + v_offset;
            unsigned v2 = (3*k + 2) + 1 + v_offset;

            unsigned vt0 = (3*k + 0) + 1 + vt_offset;
            unsigned vt1 = (3*k + 1) + 1 + vt_offset;
            unsigned vt2 = (3*k + 2) + 1 + vt_offset;

            int material_id = obj_shape->mMaterialIDs[k];
            if (material_id != prev_material_id) {
                std::string material_name =
                    pObjects.mOBJMaterials[material_id].name;
                ofs << "usemtl " << material_name.c_str() << std::endl;
                prev_material_id = material_id;
            }

            if (has_vn && has_vt) {
                ofs << "f " << v0 << "/" << vt0 << "/" << v0
                    << " " << v1 << "/" << vt1 << "/" << v1
                    << " " << v2 << "/" << vt2 << "/" << v2 << std::endl;
            } else if (has_vn && !has_vt) {
                ofs << "f " << v0 << "//" << v0
                    << " " << v1 << "//" << v1
                    << " " << v2 << "//" << v2 << std::endl;
            } else if (!has_vn && has_vt) {
                ofs << "f " << v0 << "/" << vt0
                    << " " << v1 << "/" << vt1
                    << " " << v2 << "/" << vt2 << std::endl;
            } else {
                ofs << "f " << v0 << " " << v1 << " " << v2 << std::endl;
            }
        }

        v_offset += obj_shape->mTriVertexIndices.size();
        vt_offset += obj_shape->mTexturePositions.size() / 2;

    }

    ofs.close();

    // material file
    bool write_mtl_ret = WriteMtl<T>(mtlFileName.c_str(), pObjects.mOBJMaterials);

    return write_mtl_ret;
}

template<typename T>
bool read(OBJData<T> &pObjects, const char* pFileName,
          const char* pMatFileBasePath)
{
    for (unsigned i = 0; i < pObjects.mOBJAttributes.size(); ++i)
        pObjects.mOBJAttributes[i].clear();
    pObjects.mOBJAttributes.clear();
    pObjects.mOBJMaterials.clear();

    std::stringstream strErr;
    std::ifstream ifs(pFileName);
    if (!ifs) {
        strErr << "Cannot open file (" << pFileName << ")" << std::endl;
        std::cerr << strErr.str() << std::endl;
        return false;
    }

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string strErrObj;
    bool read_obj = tinyobj::LoadObj(shapes, materials, strErrObj, pFileName,
                                     pMatFileBasePath);

    if (!read_obj) return false;

    pObjects.mOBJAttributes.resize(shapes.size());
    for (unsigned object = 0; object < pObjects.mOBJAttributes.size();
         ++object) {

        assert(shapes[object].mesh.indices.size() % 3 == 0);
        pObjects.mOBJAttributes[object].mOBJName = shapes[object].name;
        for (unsigned idx = 0; idx < shapes[object].mesh.indices.size() / 3;
             ++idx) {
            Vec3<unsigned> indices;
            indices.SetX(shapes[object].mesh.indices[3 * idx + 0]);
            indices.SetY(shapes[object].mesh.indices[3 * idx + 1]);
            indices.SetZ(shapes[object].mesh.indices[3 * idx + 2]);
            pObjects.mOBJAttributes[object].mTriVertexIndices.push_back(
                    indices);
            pObjects.mOBJAttributes[object].mMaterialIDs.push_back(
                    shapes[object].mesh.material_ids[idx]);
        }

        assert(shapes[object].mesh.texcoords.size() % 2 == 0);
        for (unsigned idx = 0; idx < shapes[object].mesh.texcoords.size() / 2;
             ++idx) {
            Vec3<T> texture_position;
            texture_position.SetX(shapes[object].mesh.texcoords[2 * idx + 0]);
            texture_position.SetY(shapes[object].mesh.texcoords[2 * idx + 1]);
            pObjects.mOBJAttributes[object].mTexturePositions.push_back(
                    texture_position);
        }

        bool get_normals =
            static_cast<bool>(shapes[object].mesh.normals.size());

        assert(shapes[object].mesh.positions.size() % 3 == 0);
        if (get_normals) assert(shapes[object].mesh.positions.size() % 3 == 0);
        for (unsigned idx = 0; idx < shapes[object].mesh.positions.size() / 3;
             ++idx) {
            Vec4<T> position;
            position.SetX(shapes[object].mesh.positions[3 * idx + 0]);
            position.SetY(shapes[object].mesh.positions[3 * idx + 1]);
            position.SetZ(shapes[object].mesh.positions[3 * idx + 2]);
            pObjects.mOBJAttributes[object].mPositions.push_back(position);

            if (get_normals) {
                Vec3<T> normal;
                normal.SetX(shapes[object].mesh.normals[3 * idx + 0]);
                normal.SetY(shapes[object].mesh.normals[3 * idx + 1]);
                normal.SetZ(shapes[object].mesh.normals[3 * idx + 2]);
                pObjects.mOBJAttributes[object].mNormals.push_back(normal);
            }
        }

    }

    for (unsigned i = 0; i < materials.size(); ++i)
        pObjects.mOBJMaterials.push_back(std::move(materials[i]));
    materials.clear();

    return false;
}
