#include <cmath>
#pragma once
namespace consoleGl {
    struct Vec2 {  
        float x;
        float y;
        
        Vec2(): x(0), y(0) {}
        Vec2(float v): x(v), y(v) {}
        Vec2(float X, float Y): x(X), y(Y) {}
        Vec2(const Vec2& other) {
            x = other.x;
            y = other.y;
        }
        
        void print() {
            std::cout << "x:" << x << std::endl;
            std::cout << "y:" << y << std::endl;
        }
        
        Vec2 operator+(const Vec2& other) const {
            return Vec2(x + other.x, y + other.y);
        }
        
        Vec2 operator-(const Vec2& other) const {
            return Vec2(x - other.x, y - other.y);
        }
        
        Vec2 operator*(float scale) const {
            return Vec2(x * scale, y * scale);
        }
        
        Vec2 operator/(float scale) const {
            return Vec2(x / scale, y / scale);
        }
        
        float length() const {
            return sqrt(x * x + y * y);
        }
        
         Vec2 normal() {
            float l = length();
            return Vec2(x / l, y / l);
        }
        
        friend float dot(Vec2 a, Vec2 b) {
            return a.x * b.x + a.y * b.y;
        }
        friend float length(Vec2 vec){
        	return vec.length();
        }
        friend Vec2 normalize(Vec2 vec){
        	return vec.normal();
        }
        
    };
}
