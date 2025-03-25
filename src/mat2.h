#pragma once
namespace consoleGl {

class Mat2 {
public:
    float m[2][2];  // Row-major storage: m[row][column]

    // Constructors
    Mat2() {
        m[0][0] = m[1][1] = 1.0f;  // Identity matrix
        m[0][1] = m[1][0] = 0.0f;
    }

    explicit Mat2(float diagonal) {
        m[0][0] = m[1][1] = diagonal;
        m[0][1] = m[1][0] = 0.0f;
    }

    Mat2(float m00, float m01, 
         float m10, float m11) {
        m[0][0] = m00; m[0][1] = m01;
        m[1][0] = m10; m[1][1] = m11;
    }

    // Matrix-vector multiplication
    Vec2 operator*(const Vec2& vec) const {
        return Vec2(
            m[0][0] * vec.x + m[0][1] * vec.y,
            m[1][0] * vec.x + m[1][1] * vec.y
        );
    }

    // Matrix-matrix operations
    Mat2 operator+(const Mat2& other) const {
        return Mat2(
            m[0][0] + other.m[0][0], m[0][1] + other.m[0][1],
            m[1][0] + other.m[1][0], m[1][1] + other.m[1][1]
        );
    }

    Mat2 operator-(const Mat2& other) const {
        return Mat2(
            m[0][0] - other.m[0][0], m[0][1] - other.m[0][1],
            m[1][0] - other.m[1][0], m[1][1] - other.m[1][1]
        );
    }

    Mat2 operator*(const Mat2& other) const {
        return Mat2(
            m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0],
            m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1],
            m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0],
            m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1]
        );
    }

    Mat2 operator*(float scalar) const {
        return Mat2(
            m[0][0] * scalar, m[0][1] * scalar,
            m[1][0] * scalar, m[1][1] * scalar
        );
    }

    // Matrix operations
    Mat2 transpose() const {
        return Mat2(
            m[0][0], m[1][0],
            m[0][1], m[1][1]
        );
    }

    float determinant() const {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    Mat2 inverse() const {
        float det = determinant();
        if (det == 0.0f) {
            throw std::runtime_error("Matrix is not invertible");
        }
        
        float invDet = 1.0f / det;
        return Mat2(
             m[1][1] * invDet, -m[0][1] * invDet,
            -m[1][0] * invDet,  m[0][0] * invDet
        );
    }

    // Transformation generators
    static Mat2 identity() {
        return Mat2();
    }

    static Mat2 rotate(float angle) {
        float c = std::cos(angle);
        float s = std::sin(angle);
        return Mat2(
            c, -s,
            s,  c
        );
    }

    static Mat2 scale(float sx, float sy) {
        return Mat2(
            sx, 0.0f,
            0.0f, sy
        );
    }

    static Mat2 scale(float uniformScale) {
        return scale(uniformScale, uniformScale);
    }

    // For debugging
    void print() const {
        std::cout << "Mat2:\n";
        std::cout << m[0][0] << " " << m[0][1] << "\n";
        std::cout << m[1][0] << " " << m[1][1] << "\n";
    }
};

} // namespace consoleGl
