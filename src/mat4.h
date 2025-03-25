
#pragma once
namespace consoleGl {

struct Mat4 {
    // Column-major storage (compatible with OpenGL)
    union {
        float m[4][4];
        float elements[16];
    };

    // Constructors
    Mat4() { 
        for (int i = 0; i < 16; i++) elements[i] = 0.0f;
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f; // Identity matrix
    }

    explicit Mat4(float diagonal) {
        for (int i = 0; i < 16; i++) elements[i] = 0.0f;
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = diagonal;
    }

    

    // Matrix operations
    Mat4 operator*(const Mat4& other) const {
        Mat4 result;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result.m[row][col] = 
                    m[row][0] * other.m[0][col] +
                    m[row][1] * other.m[1][col] +
                    m[row][2] * other.m[2][col] +
                    m[row][3] * other.m[3][col];
            }
        }
        return result;
    }

    Vec4 operator*(const Vec4& vec) const {
        return Vec4(
            m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3] * vec.w,
            m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3] * vec.w,
            m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3] * vec.w,
            m[3][0] * vec.x + m[3][1] * vec.y + m[3][2] * vec.z + m[3][3] * vec.w
        );
    }

    // Transformation generators
    static Mat4 identity() { return Mat4(); }

    static Mat4 translate(float x, float y, float z) {
        Mat4 result;
        result.m[0][3] = x;
        result.m[1][3] = y;
        result.m[2][3] = z;
        return result;
    }

    static Mat4 scale(float x, float y, float z) {
        Mat4 result;
        result.m[0][0] = x;
        result.m[1][1] = y;
        result.m[2][2] = z;
        return result;
    }

    static Mat4 rotateX(float angle) {
        Mat4 result;
        float c = cos(angle);
        float s = sin(angle);
        result.m[1][1] = c;
        result.m[1][2] = -s;
        result.m[2][1] = s;
        result.m[2][2] = c;
        return result;
    }

    static Mat4 rotateY(float angle) {
        Mat4 result;
        float c = cos(angle);
        float s = sin(angle);
        result.m[0][0] = c;
        result.m[0][2] = s;
        result.m[2][0] = -s;
        result.m[2][2] = c;
        return result;
    }

    static Mat4 rotateZ(float angle) {
        Mat4 result;
        float c = cos(angle);
        float s = sin(angle);
        result.m[0][0] = c;
        result.m[0][1] = -s;
        result.m[1][0] = s;
        result.m[1][1] = c;
        return result;
    }

    // Projection matrices
    static Mat4 perspective(float fov, float aspect, float near, float far) {
        Mat4 result;
        float tanHalfFov = tan(fov / 2.0f);
        result.m[0][0] = 1.0f / (aspect * tanHalfFov);
        result.m[1][1] = 1.0f / tanHalfFov;
        result.m[2][2] = -(far + near) / (far - near);
        result.m[2][3] = -2.0f * far * near / (far - near);
        result.m[3][2] = -1.0f;
        result.m[3][3] = 0.0f;
        return result;
    }

    static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far) {
        Mat4 result;
        result.m[0][0] = 2.0f / (right - left);
        result.m[1][1] = 2.0f / (top - bottom);
        result.m[2][2] = -2.0f / (far - near);
        result.m[0][3] = -(right + left) / (right - left);
        result.m[1][3] = -(top + bottom) / (top - bottom);
        result.m[2][3] = -(far + near) / (far - near);
        return result;
    }

    // Utility
    void print() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << m[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

} // namespace consoleGl
