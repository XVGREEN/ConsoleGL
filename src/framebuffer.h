#ifndef FRAMEBUFFER
#define FRAMEBUFFER
#include <algorithm>
namespace consoleGl{
struct frame_buffer {
    bool* data;
    int height, width;

    frame_buffer(int w, int h) : width(w), height(h) {
        data = new bool[w * h](); // Inicializa com "false"
    }

    int size() const { return height * width; }

    void set_pixel(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height)
            data[y * width + x] = true; // Ativa o pixel
    }

    ~frame_buffer() {
        delete[] data;
    }

   void print() const {
        for(int i=0;i<width;i++)std::cout<<"-";
        std::cout<<"\n";
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                std::cout << (data[y * width + x] ? "#" : ".");
            }
            std::cout << "\n";
        }

    }
  
    void clear() {
    	 std::fill(data, data + width * height, false);
     }
    	
    
};
};
#endif
