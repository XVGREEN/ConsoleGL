#ifndef UTIL
#define UTIL

namespace consoleGl{

    struct color {
        float r, g, b;
    
       
        color(float r = 0, float g = 0, float b = 0) : r(r), g(g), b(b) {}
    
       
        color operator+(const color& other) const {
            return color(r + other.r, g + other.g, b + other.b);
        }
    
        
        color operator-(const color& other) const {
            return color(r - other.r, g - other.g, b - other.b);
        }
    
       
        color operator*(float scalar) const {
            return color(r * scalar, g * scalar, b * scalar);
        }
    };
    
	template<class T>
	T lerp (T a, T b,float t){
		return a+(b-a)*t;
	}
	
}
#endif
