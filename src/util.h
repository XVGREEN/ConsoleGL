#ifndef UTIL
#define UTIL
#define PI 3.141592653589793
namespace consoleGl{
  
    struct Color {
        float r, g, b;
    
       
       Color   (float r = 0, float g = 0, float b = 0) : r(r), g(g), b(b) {}
    
       
        Color operator+(const Color& other) const {
            return Color(r + other.r, g + other.g, b + other.b);
        }
    
        
        Color operator-(const Color& other) const {
            return Color(r - other.r, g - other.g, b - other.b);
        }
    
       
        Color operator*(float scalar) const {
            return Color(r * scalar, g * scalar, b * scalar);
        }
    };

     void delay(int milliseconds) {           
          std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
            
      }
       
	template<class T>
	T lerp (T a, T b,float t){
		return a+(b-a)*t;
	}
	
}
#endif
