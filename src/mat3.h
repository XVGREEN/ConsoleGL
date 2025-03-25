#pragma once
#include <cmath>
#include <stdexcept>

namespace consoleGl {
class Mat3 {
public:
    float m[3][3];

    Mat3() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] = 0.0f;
    }

    Mat3(float values[3][3]) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] = values[i][j];
    }

    Vec3 operator*(const Vec3& vec) const {
        Vec3 result;
        result.x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z;
        result.y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z;
        result.z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z;
        return result;
    }

    Mat3 operator+(const Mat3& other) const {
        Mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[i][j] + other.m[i][j];
        return result;
    }

    Mat3 operator-(const Mat3& other) const {
        Mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[i][j] - other.m[i][j];
        return result;
    }

    Mat3 operator*(const Mat3& other) const {
        Mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[i][0] * other.m[0][j] + m[i][1] * other.m[1][j] + m[i][2] * other.m[2][j];
        return result;
    }

    Mat3 operator*(float scalar) const {
        Mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[i][j] * scalar;
        return result;
    }

    Mat3 transpose() const {
        Mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[j][i];
        return result;
    }

    float determinant() const {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
               m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
               m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    Mat3 inverse() const {
        float det = determinant();
        if (det == 0)
            throw std::runtime_error("Matrix is not invertible, determinant is 0.");

        Mat3 result;
        float invDet = 1.0f / det;

        result.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
        result.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invDet;
        result.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;

        result.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invDet;
        result.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
        result.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invDet;

        result.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet;
        result.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invDet;
        result.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet;

        return result;
    }

    static Mat3 translate(float tx, float ty) {
        Mat3 result;
        result.m[0][0] = 1.0f;
        result.m[1][1] = 1.0f;
        result.m[2][2] = 1.0f;
        result.m[0][2] = tx;
        result.m[1][2] = ty;
        return result;
    }

    static Mat3 rotate(float angle) {
        Mat3 result;
        float c = cos(angle);
        float s = sin(angle);
        result.m[0][0] = c;
        result.m[0][1] = -s;
        result.m[1][0] = s;
        result.m[1][1] = c;
        result.m[2][2] = 1.0f;
        return result;
    }

    static Mat3 scale(float sx, float sy) {
        Mat3 result;
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = 1.0f;
        return result;
    }
};
}

