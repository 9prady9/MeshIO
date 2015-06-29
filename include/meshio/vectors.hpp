/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef __VECTORS_HPP__
#define __VECTORS_HPP__

#include <vector>

namespace meshio
{

template<class T>
class Vec2 {
  public:
    T x,y;

    Vec2(T pX, T pY) {
        x = pX;
        y = pY;
    }

    Vec2(T pX) {
        Vec2(pX, 0);
    }

    Vec2() {
        Vec2(0, 0);
    }

    Vec2(const Vec2& pVec2) {
        *this = pVec2;
    }

    ~Vec2() {}

    void operator=(const Vec2& pVec2) {
        x = pVec2.x;
        y = pVec2.y;
    }

    Vec2& operator+=(const Vec2& pVec2) {
        x += pVec2.x;
        y += pVec2.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& pVec2) {
        x -= pVec2.x;
        y -= pVec2.y;
        return *this;
    }

    Vec2& operator*=(const T pDiv) {
        x *= pDiv;
        y *= pDiv;
        return *this;
    }

    Vec2& operator/=(const T pDiv) {
        T oneByPDiv = (T)1/pDiv;
        x *= oneByPDiv;
        y *= oneByPDiv;
        return *this;
    }

    bool operator==(const Vec2& pVec2) {
        return ((x == pVec2.x) && (y == pVec2.y));
    }

    /* Dot product of two vectors */
    Vec2 operator&(const Vec2& pVec2) {
        return Vec2(this->x*pVec2.x, this->y*pVec2.y);
    }

    /* Cross product of two vectors */
    Vec2 operator^(const Vec2& pVec2) {
        return Vec3(0, 0, this->x*pVec2.y-this->y*pVec2.x);
    }
};

template<class T>
class Vec3 {
  public:
    T x,y,z;

    Vec3(T pX, T pY, T pZ) {
        x = pX;
        y = pY;
        z = pZ;
    }

    Vec3(T pX, T pY) {
        Vec3(pX, pY, 0);
    }

    Vec3(T pX) {
        Vec3(pX, 0, 0);
    }

    Vec3() {
        Vec3(0, 0, 0);
    }

    Vec3(const Vec3& pVec3) {
        *this = pVec3;
    }

    ~Vec3() {}

    void operator=(const Vec3& pVec3) {
        x = pVec3.x;
        y = pVec3.y;
        z = pVec3.z;
    }

    Vec3& operator+=(const Vec3& pVec3) {
        x += pVec3.x;
        y += pVec3.y;
        z += pVec3.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& pVec3) {
        x -= pVec3.x;
        y -= pVec3.y;
        z -= pVec3.z;
        return *this;
    }

    Vec3& operator*=(const T pDiv) {
        x *= pDiv;
        y *= pDiv;
        z *= pDiv;
        return *this;
    }

    Vec3& operator/=(const T pDiv) {
        T oneByPDiv = (T)1/pDiv;
        x *= oneByPDiv;
        y *= oneByPDiv;
        z *= oneByPDiv;
        return *this;
    }

    bool operator==(const Vec3& pVec3) {
        return ((x == pVec3.x) && (y == pVec3.y) && (z == pVec3.z));
    }

    /* Dot product of two vectors */
    Vec3 operator&(const Vec3& pVec3) {
        return Vec3(this->x*pVec3.x, this->y*pVec3.y, this->z*pVec3.z);
    }

    /* Cross product of two vectors */
    Vec3 operator^(const Vec3& pVec3) {
        return Vec3(this->y*pVec3.z-this->z*pVec3.y,
                    this->z*pVec3.x-this->x*pVec3.z,
                    this->x*pVec3.y-this->y*pVec3.x);
    }
};

template<class T>
class Vec4 {
  public:
    T x,y,z,w;

    Vec4(T pX, T pY, T pZ, T pW) {
        x = pX;
        y = pY;
        z = pZ;
        w = pW;
    }

    Vec4(T pX, T pY, T pZ) {
        Vec4(pX, pY, pZ, 0);
    }

    Vec4(T pX, T pY) {
        Vec4(pX, pY, 0, 0);
    }

    Vec4(T pX) {
        Vec4(pX, 0, 0, 0);
    }

    Vec4() {
        Vec4(0, 0, 0, 0);
    }

    Vec4(const Vec4& pVec4) {
        *this = pVec4;
    }

    ~Vec4() {}

    void operator=(const Vec4& pVec4) {
        x = pVec4.x;
        y = pVec4.y;
        z = pVec4.z;
        w = pVec4.w;
    }

    Vec4& operator+=(const Vec4& pVec4) {
        x += pVec4.x;
        y += pVec4.y;
        z += pVec4.z;
        w += pVec4.w;
        return *this;
    }

    Vec4& operator-=(const Vec4& pVec4) {
        x -= pVec4.x;
        y -= pVec4.y;
        z -= pVec4.z;
        w -= pVec4.w;
        return *this;
    }

    Vec4& operator*=(const T pDiv) {
        x *= pDiv;
        y *= pDiv;
        z *= pDiv;
        w *= pDiv;
        return *this;
    }

    Vec4& operator/=(const T pDiv) {
        T oneByPDiv = (T)1/pDiv;
        x *= oneByPDiv;
        y *= oneByPDiv;
        z *= oneByPDiv;
        w *= oneByPDiv;
        return *this;
    }

    bool operator==(const Vec4& pVec4) {
        return ((x == pVec4.x) && (y == pVec4.y) && (z == pVec4.z) &&
                (w == pVec4.w));
    }
};


}

#endif // __VECTORS_HPP__
