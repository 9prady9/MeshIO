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
    T x, y;

    Vec2(T pX, T pY)
        : x(pX), y(pY) {
    }

    Vec2()
        : x(0), y(0) {
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& operator*=(const T pDiv) {
        x *= pDiv;
        y *= pDiv;
        return *this;
    }

    Vec2& operator/=(const T pDiv) {
        T oneByPDiv = (T)1/pDiv;
        return operator*=(oneByPDiv);
    }

    bool operator==(const Vec2& other) {
        return ((x == other.x) && (y == other.y));
    }
};

template<class T>
class Vec3 {
  public:
    T x,y,z;

    Vec3(T pX, T pY, T pZ)
        : x(pX), y(pY), z(pZ) {
    }

    Vec3()
        : x(0), y(0), z(0) {
    }

    Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
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
        return operator*=(oneByPDiv);
    }

    bool operator==(const Vec3& other) {
        return ((x == other.x) && (y == other.y) && (z == other.z));
    }
};

template<class T>
class Vec4 {
  public:
    T x,y,z,w;

    Vec4(T pX, T pY, T pZ, T pW)
        : x(pX), y(pY), z(pZ), w(pW) {
    }

    Vec4()
        : x(0), y(0), z(0), w(0) {
    }

    Vec4& operator+=(const Vec4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Vec4& operator-=(const Vec4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
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
        return operator*=(oneByPDiv);
    }

    bool operator==(const Vec4& other) {
        return ((x==other.x) && (y==other.y) && (z==other.z) && (w==other.w));
    }
};

/* Dot product of two vectors */
template<typename T>
T dot(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

/* Cross product of two vectors */
template<typename T>
Vec3<T> cross(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return Vec3<T>(0, 0, lhs.x*rhs.y - lhs.y*rhs.x);
}

/* Dot product of two vectors */
template<typename T>
T dot(const Vec3<T> &lhs, const Vec3<T>& rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y, lhs.z*rhs.z;
}

/* Cross product of three dimensional vectors */
template<typename T>
Vec3<T> cross(const Vec3<T> &lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs.y*rhs.z - lhs.z*rhs.y,
                lhs.z*rhs.x - lhs.x*rhs.z,
                lhs.x*rhs.y - lhs.y*rhs.x);
}

}

#endif // __VECTORS_HPP__
