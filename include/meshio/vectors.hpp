/*
 * Copyright (c) 2015, Lakshman Anumolu, Pradeep Garigipati
 * All rights reserved.
 *
 * This file is part of MeshIO whose distribution is governed by
 * the BSD 2-Clause License contained in the accompanying LICENSE.txt
 * file.
 */

#ifndef MESHIO_VECTORS_HPP_
#define MESHIO_VECTORS_HPP_

#include <vector>

namespace meshio
{

template<class T>
class VecBase {
  public:
    typedef T *iterator;
    typedef const T *const_iterator;

    VecBase() {}
    ~VecBase() {}

    virtual unsigned Size() const = 0;
    virtual iterator Begin() = 0;
    virtual iterator End() = 0;
    virtual const_iterator Begin() const = 0;
    virtual const_iterator End() const = 0;
};

template<class T>
class Vec2 : public VecBase<T> {
  public:
    typedef T *iterator;
    typedef const T *const_iterator;

    Vec2(T pX, T pY) : elements{pX, pY} {}
    Vec2() : Vec2{0,0} {}
    ~Vec2() {}

    unsigned Size() const {
        return 2;
    }

    T& X() {
        return elements[0];
    }

    T& Y() {
        return elements[1];
    }

    iterator Begin() {
        return &elements[0];
    }

    iterator End() {
        return &elements[2];
    }

    const_iterator Begin() const {
        return &elements[0];
    }

    const_iterator End() const {
        return &elements[2];
    }

    Vec2& operator+=(const Vec2& other) {
        elements[0] += other.X();
        elements[1] += other.Y();
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        elements[0] -= other.X();
        elements[1] -= other.Y();
        return *this;
    }

    Vec2& operator*=(const T pDiv) {
        elements[0] *= pDiv;
        elements[0] *= pDiv;
        return *this;
    }

    Vec2& operator/=(const T pDiv) {
        T oneByPDiv = (T)1/pDiv;
        return operator*=(oneByPDiv);
    }

    bool operator==(const Vec2& other) {
        return ((elements[0] == other.X()) && (elements[1] == other.Y()));
    }

  private:
    T elements[2];
};

template<class T>
class Vec3 : public VecBase<T> {
  public:
    typedef T *iterator;
    typedef const T *const_iterator;

    Vec3(T pX, T pY, T pZ) : elements{pX, pY, pZ} {}
    Vec3() : Vec3{0,0,0} {}
    ~Vec3() {}

    unsigned Size() const {
        return 3;
    }

    void SetX(T pX) {
        elements[0] = pX;
    }

    void SetY(T pY) {
        elements[1] = pY;
    }

    void SetZ(T pZ) {
        elements[2] = pZ;
    }

    const T& X() const {
        return elements[0];
    }

    const T& Y() const {
        return elements[1];
    }

    const T& Z() const {
        return elements[2];
    }

    iterator Begin() {
        return &elements[0];
    }

    iterator End() {
        return &elements[3];
    }

    iterator PreviousToEnd() {
        return &elements[2];
    }

    const_iterator Begin() const {
        return &elements[0];
    }

    const_iterator End() const {
        return &elements[3];
    }

    const_iterator PreviousToEnd() const {
        return &elements[2];
    }

    Vec3& operator+=(const Vec3& other) {
        elements[0] += other.X();
        elements[1] += other.Y();
        elements[2] += other.Z();
        return *this;
    }

    Vec3& operator-=(const Vec3& other) {
        elements[0] -= other.X();
        elements[1] -= other.Y();
        elements[2] -= other.Z();
        return *this;
    }

    Vec3& operator*=(const T pDiv) {
        elements[0] *= pDiv;
        elements[1] *= pDiv;
        elements[2] *= pDiv;
        return *this;
    }

    Vec3& operator/=(const T pDiv) {
        T oneByPDiv = (T)1/pDiv;
        return operator*=(oneByPDiv);
    }

    bool operator==(const Vec3& other) {
        return ((elements[0] == other.X()) && (elements[1] == other.Y()) &&
                (elements[2] == other.Z()));
    }

  private:
    T elements[3];
};

template<class T>
class Vec4 : public VecBase<T> {
  public:
    typedef T *iterator;
    typedef const T *const_iterator;

    Vec4(T pX, T pY, T pZ, T pW) : elements{pX, pY, pZ, pW} {}
    Vec4() : Vec4{0,0,0,0} {}
    ~Vec4() {}

    unsigned Size() const {
        return 4;
    }

    void SetX(T pX) {
        elements[0] = pX;
    }

    void SetY(T pY) {
        elements[1] = pY;
    }

    void SetZ(T pZ) {
        elements[2] = pZ;
    }

    void SetW(T pW) {
        elements[3] = pW;
    }

    const T& X() const {
        return elements[0];
    }

    const T& Y() const {
        return elements[1];
    }

    const T& Z() const {
        return elements[2];
    }

    const T& W() const {
        return elements[3];
    }

    iterator Begin() {
        return &elements[0];
    }

    iterator End() {
        return &elements[4];
    }

    iterator PreviousToEnd() {
        return &elements[3];
    }

    const_iterator Begin() const {
        return &elements[0];
    }

    const_iterator End() const {
        return &elements[4];
    }

    const_iterator PreviousToEnd() const {
        return &elements[3];
    }

    Vec4& operator+=(const Vec4& other) {
        elements[0] += other.X();
        elements[1] += other.Y();
        elements[2] += other.Z();
        elements[3] += other.W();
        return *this;
    }

    Vec4& operator-=(const Vec4& other) {
        elements[0] -= other.X();
        elements[1] -= other.Y();
        elements[2] -= other.Z();
        elements[3] -= other.W();
        return *this;
    }

    Vec4& operator*=(const T pDiv) {
        elements[0] *= pDiv;
        elements[1] *= pDiv;
        elements[2] *= pDiv;
        elements[3] *= pDiv;
        return *this;
    }

    Vec4& operator/=(const T pDiv) {
        T oneByPDiv = (T)1/pDiv;
        return operator*=(oneByPDiv);
    }

    bool operator==(const Vec4& other) {
        return ((elements[0] == other.X()) && (elements[1] == other.Y()) &&
                (elements[2] == other.Z()) && (elements[3] == other.W()));
    }

  private:
    T elements[4];
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

#endif // MESHIO_VECTORS_HPP_
