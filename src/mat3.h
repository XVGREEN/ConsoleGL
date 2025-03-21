#ifndef MAT3
#define MAT3
namespace consoleGl{
class mat3 {
public:
    float m[3][3];

    mat3() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] = 0.0f;
    }

    mat3(float values[3][3]) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] = values[i][j];
    }

vec2 operator*(const  vec2& vec) const {
    vec2  result;
    result.x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z;
    result.y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z;
    result.z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z;
    return result;
}

    mat3 operator+(const mat3& other) const {
        mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[i][j] + other.m[i][j];
        return result;
    }

    mat3 operator-(const mat3& other) const {
        mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[i][j] - other.m[i][j];
        return result;
    }

    mat3 operator*(const mat3& other) const {
        mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[i][0] * other.m[0][j] + m[i][1] * other.m[1][j] + m[i][2] * other.m[2][j];
        return result;
    }

    mat3 operator*(float scalar) const {
        mat3 result;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                result.m[i][j] = m[i][j] * scalar;
        return result;
    }

    mat3 transpose() const {
        mat3 result;
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

    mat3 inverse() const {
        float det = determinant();
        if (det == 0)
            throw std::runtime_error("Matriz não é invertível, determinante é 0.");

        mat3 result;
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

  
    static mat3 translate(float tx, float ty) {
        mat3 result;
        result.m[0][2] = tx;
        result.m[1][2] = ty;
        return result;
    }

    static mat3 rotate(float angle) {
        mat3 result;
        result.m[0][0] = cos(angle);
        result.m[0][1] = -sin(angle);
        result.m[1][0] = sin(angle);
        result.m[1][1] = cos(angle);
        result.m[2][2] = 1.0f;
        return result;
    }

    static mat3 scale(float sx, float sy) {
        mat3 result;
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        return result;
    }


    mat3 operator*(const float v[3]) const {
        float result[3];
        for (int i = 0; i < 3; ++i) {
            result[i] = m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2];
        }

        mat3 resultMat;
        resultMat.m[0][0] = result[0];
        resultMat.m[1][0] = result[1];
        resultMat.m[2][0] = result[2];
        
        return resultMat;
    }
};
}
#endif
