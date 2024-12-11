#pragma once
#include <numbers>
#include <cmath>
#include <cassert>

class Vector3 {
public:
    float x, y, z;

    float Length(const Vector3& v) { return (float)std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

    // 正規化
    Vector3 Normalize(const Vector3& v) {
        float len = Length(v);
        Vector3 result = v;
        if (len != 0) {
            result /= len;
        }
        return result;
    }

    // コンストラクタ
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // 加算演算子オーバーロード
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }

    // 減算演算子オーバーロード
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }

    // スカラー乗算演算子オーバーロード
    Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }

    // ベクトル同士の乗算演算子オーバーロード（各成分の積）
    Vector3 operator*(const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }

    // スカラー除算演算子オーバーロード
    Vector3 operator/(float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }

    // 代入演算子オーバーロード
    Vector3& operator=(const Vector3& v) {
        if (this != &v) {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        return *this;
    }

    // 等価比較演算子オーバーロード
    bool operator==(const Vector3& v) const { return x == v.x && y == v.y && z == v.z; }

    // 非等価比較演算子オーバーロード
    bool operator!=(const Vector3& v) const { return !(*this == v); }

    // += 演算子オーバーロード
    Vector3& operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // -= 演算子オーバーロード
    Vector3& operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // *= 演算子オーバーロード（スカラー）
    Vector3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // *= 演算子オーバーロード（ベクトル同士）
    Vector3& operator*=(const Vector3& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    // /= 演算子オーバーロード
    Vector3& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // 内積
    float Dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }

    // 外積
    Vector3 Cross(const Vector3& other) const { return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
};

// スカラーと Vector3 の掛け算演算子オーバーロード
inline Vector3 operator*(float scalar, const Vector3& v) { return Vector3(v.x * scalar, v.y * scalar, v.z * scalar); }