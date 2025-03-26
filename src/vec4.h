#pragma once
namespace consoleGl {

struct Vec4 {
    float x, y, z, w;

    // Constructors
    Vec4() : x(0), y(0), z(0), w(0) {}
    explicit Vec4(float v) : x(v), y(v), z(v), w(v) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    
    // Arithmetic operations
    Vec4 operator+(const Vec4& other) const {
        return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vec4 operator-(const Vec4& other) const {
        return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vec4 operator*(float scalar) const {
        return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Vec4 operator/(float scalar) const {
        return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    // Vector operations
    float dot(const Vec4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    Vec4 normalized() const {
        float len = length();
        return len > 0 ? (*this) / len : Vec4(0);
    } 
    Vec3 xyz (){
    	return Vec3 (x,y,z);
    }

    // Utility
    void print() const {
        std::cout << "Vec4(" << x << ", " << y << ", " << z << ", " << w << ")\n";
    }

    // Constants
    static Vec4 zero() { return Vec4(0, 0, 0, 0); }
    static Vec4 one() { return Vec4(1, 1, 1, 1); }
    static Vec4 unitX() { return Vec4(1, 0, 0, 0); }
    static Vec4 unitY() { return Vec4(0, 1, 0, 0); }
    static Vec4 unitZ() { return Vec4(0, 0, 1, 0); }
    static Vec4 unitW() { return Vec4(0, 0, 0, 1); }
};

} // namespace consoleGl
