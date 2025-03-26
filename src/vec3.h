#pragma once

namespace consoleGl {
struct Vec3 {
    float x, y, z;

    // Constructors
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float v) : x(v), y(v), z(v) {}
    Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}

    // Vector operations
    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator/(float scalar) const {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    // Dot product
    float dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vec3 cross(const Vec3& other) const {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Length/magnitude
    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    // Normalization
    Vec3 normal() const {
        float len = length();
        return len > 0 ? (*this) / len : Vec3(0);
    }

    friend float dot(Vec3 a, Vec3 b){
    	return a.dot(b);
    }
    friend float length(Vec3 a){
    	return a.length();
    }
    friend Vec3 normalize (Vec3 a) {
    	return a.normal();
    }
    friend Vec3 abs (Vec3 vec){
        return Vec3 (abs(vec.x),abs(vec.y),abs(vec.z));
    }

    // Print utility
    void print() const {
        std::cout << "Vec3(" << x << ", " << y << ", " << z << ")\n";
    }

    // Static constants
    static Vec3 zero() { return Vec3(0, 0, 0); }
    static Vec3 one() { return Vec3(1, 1, 1); }
    static Vec3 right() { return Vec3(1, 0, 0); }
    static Vec3 up() { return Vec3(0, 1, 0); }
    static Vec3 forward() { return Vec3(0, 0, 1); }
};
} // namespace consoleGl
