#ifndef UTIL
#define UTIL
#define PI 3.141592653589793
#include <termios.h>
#include <fcntl.h>
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


   
   char getKey() {
       struct termios oldt, newt;
       int ch = 0; // Alterado para int
       int oldf;
   
       tcgetattr(STDIN_FILENO, &oldt);
       newt = oldt;
       newt.c_lflag &= ~(ICANON | ECHO);
       tcsetattr(STDIN_FILENO, TCSANOW, &newt);
   
       oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
       fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
   
       ch = getchar(); // getchar() retorna um int
   
       tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
       fcntl(STDIN_FILENO, F_SETFL, oldf);
   
       return (ch != EOF) ? (char)ch : 0;
   }
	
}
#endif
