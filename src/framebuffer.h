#ifndef FRAMEBUFFER
#define FRAMEBUFFER
#include <algorithm>
namespace consoleGl{
struct FrameBuffer{
    int * data;
    int height, width;
   const std::string  values =" .,:;+*?%S#@";
    FrameBuffer(int w, int h) : width(w), height(h) {
        data = new int [w * h](); // Inicializa com "false"
        
    }

    int size() const { return height * width; }

    void setPixel(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height)
            data[y * width + x] = true; // Ativa o pixel
    }

    ~FrameBuffer() {
        delete[] data;
    }

    void print() const {
        std::string output;
        output.reserve(width * height + height); 
    
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                output += values[data[y * width + x]];
            }
            output += '\n';  
        }
    
        std::cout << output; 
    }
  
    void clear() {
    	 std::fill(data, data + width * height, false);
     }
    	
    
};
};
#endif
