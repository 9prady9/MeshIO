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

#include <cstdlib>
#include <vector>

namespace meshio
{

template<class T>
class Vec4 {
  public:
    typedef typename std::vector<T>::iterator viterator;
    typedef typename std::vector<T>::const_iterator const_viterator;

    Vec4(T pX, T pY, T pZ, T pW) : elems({pX, pY, pZ, pW}) {}
    Vec4() : Vec4(0, 0, 0, 0) { }
    ~Vec4() {}

    virtual std::size_t size() const { return 4; }
    virtual viterator end() { return elems.end(); }
    virtual const_viterator end() const { return elems.end(); }

    inline void setX(T value) { elems[0] = value; }
    inline void setY(T value) { elems[1] = value; }
    inline void setZ(T value) { elems[2] = value; }
    inline void setW(T value) { elems[3] = value; }

    inline T getX() const { return elems[0]; }
    inline T getY() const { return elems[1]; }
    inline T getZ() const { return elems[2]; }
    inline T getW() const { return elems[3]; }

    viterator begin() { return elems.begin(); }
    const_viterator begin() const { return elems.begin(); }

  private:
    std::vector<T> elems;
};

template<class T>
class Vec3 : public Vec4<T> {
  public:
    typedef typename std::vector<T>::iterator viterator;
    typedef typename std::vector<T>::const_iterator const_viterator;

    Vec3(T pX, T pY, T pZ) : Vec4<T>(pX, pY, pZ, 0) {}
    Vec3() : Vec4<T>(0, 0, 0, 0) {}
    ~Vec3() {}

    std::size_t size() const { return 3; }
    viterator end() { return Vec4<T>::end()--; }
    const_viterator end() const { return Vec4<T>::end()--; }
};

template<class T>
class Vec2 : public Vec4<T> {
  public:
    typedef typename std::vector<T>::iterator viterator;
    typedef typename std::vector<T>::const_iterator const_viterator;

    Vec2(T pX, T pY, T pZ) : Vec4<T>(pX, pY, 0, 0) {}
    Vec2() : Vec4<T>(0, 0, 0, 0) {}
    ~Vec2() {}

    std::size_t size() const { return 2; }
    viterator end() { return Vec4<T>::end()-2; }
    const_viterator end() const { return Vec4<T>::end()-2; }
};


////////////////////////// BINARY ARITHMETIC ////////////////////////

#define BIN_VEC_ARITH_DEFINITION(Op)                                \
template<typename T>                                                \
Vec2<T> operator Op(Vec2<T> const & lhs, Vec2<T> const & rhs)       \
{                                                                   \
    return Vec2<T>(lhs.getX() Op rhs.getX(),                        \
                   lhs.getY() Op rhs.getY());                       \
}                                                                   \
                                                                    \
template<typename T>                                                \
Vec3<T> operator Op(Vec3<T> const & lhs, Vec3<T> const & rhs)       \
{                                                                   \
    return Vec3<T>(lhs.getX() Op rhs.getX(),                        \
                   lhs.getY() Op rhs.getY(),                        \
                   lhs.getZ() Op rhs.getZ());                       \
}                                                                   \
                                                                    \
template<typename T>                                                \
Vec4<T> operator Op(Vec4<T> const & lhs, Vec4<T> const & rhs)       \
{                                                                   \
    return Vec4<T>(lhs.getX() Op rhs.getX(),                        \
                   lhs.getY() Op rhs.getY(),                        \
                   lhs.getZ() Op rhs.getZ(),                        \
                   lhs.getW() Op rhs.getW());                       \
}

BIN_VEC_ARITH_DEFINITION(+)
BIN_VEC_ARITH_DEFINITION(-)

#undef BIN_VEC_ARITH_DEFINITION

template<typename T>
Vec2<T> operator *(Vec2<T> const & lhs, T const rhs)
{
    return Vec2<T>(lhs.getX()*rhs, lhs.getY()*rhs);
}

template<typename T>
Vec3<T> operator *(Vec3<T> const & lhs, T const rhs)
{
    return Vec3<T>(lhs.getX()*rhs, lhs.getY()*rhs, lhs.getZ()*rhs);
}

template<typename T>
Vec4<T> operator *(Vec4<T> const & lhs, T const rhs)
{
    return Vec4<T>(lhs.getX()*rhs, lhs.getY()*rhs, lhs.getZ()*rhs, lhs.getW()*rhs);
}

template<typename T>
Vec2<T> operator *(T const lhs, Vec2<T> const & rhs)
{
    return operator*(rhs, lhs);
}

template<typename T>
Vec3<T> operator *(T const lhs, Vec3<T> const & rhs)
{
    return operator*(rhs, lhs);
}

template<typename T>
Vec4<T> operator *(T const lhs, Vec4<T> const & rhs)
{
    return operator*(rhs, lhs);
}

template<typename T>
bool operator==(Vec2<T> const & lhs, Vec2<T> const & rhs)
{
    return (lhs.getX()==rhs.getX() &&
            lhs.getY()==rhs.getY());
}

template<typename T>
bool operator==(Vec3<T> const & lhs, Vec3<T> const & rhs)
{
    return (lhs.getX()==rhs.getX() &&
            lhs.getY()==rhs.getY() &&
            lhs.getZ()==rhs.getZ());
}

template<typename T>
bool operator==(Vec4<T> const & lhs, Vec4<T> const & rhs)
{
    return (lhs.getX()==rhs.getX() &&
            lhs.getY()==rhs.getY() &&
            lhs.getZ()==rhs.getZ() &&
            lhs.getW()==rhs.getW());
}

////////////////////////// VECTOR ARITHMETIC ////////////////////////

/* Dot product of two vectors */
template<typename T>
T dot(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return lhs.getX()*rhs.getX() + lhs.getY()*rhs.getY();
}

/* Cross product of two vectors */
template<typename T>
Vec3<T> cross(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return Vec3<T>(0, 0, lhs.getX()*rhs.getY() - lhs.getY()*rhs.getX());
}

/* Dot product of two vectors */
template<typename T>
T dot(const Vec3<T> &lhs, const Vec3<T>& rhs) {
    return lhs.getX()*rhs.getX() + lhs.getY()*rhs.getY(), lhs.getZ()*rhs.getZ();
}

/* Cross product of three dimensional vectors */
template<typename T>
Vec3<T> cross(const Vec3<T> &lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs.getY()*rhs.getZ() - lhs.getZ()*rhs.getY(),
                lhs.getZ()*rhs.getX() - lhs.getX()*rhs.getZ(),
                lhs.getX()*rhs.getY() - lhs.getY()*rhs.getX());
}

}

#endif // MESHIO_VECTORS_HPP_
