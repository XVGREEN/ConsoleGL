#include "src/consolegl.h"
#include "shaders/cube.h"

int main() {
   int fc = 0;
    const int fpp = 1;
    consoleGl::Vec2 resolution(80, 80);
    consoleGl::FrameBuffer frame(resolution.x, resolution.y);
    bool running = true;
    auto start_time = std::chrono::high_resolution_clock::now();

    
    while (running) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - start_time;
        auto time = (float)elapsed.count();
        
        consoleGl::ShaderUniforms uniforms = {resolution.x, resolution.y, time};
        
        if (fc >= 1000) break;
        
        applyFragment(frame, cubeShader, uniforms);
        
        if (fc % fpp == 0) {
            frame.print();
        }
        
        fc++;
        consoleGl::delay(16);
        frame.clear();
    }

    return 0;
}
       
    

    
 
