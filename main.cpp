#include "src/consolegl.h"

int main() {
   int fc = 0;
    const int fpp = 1;
    consoleGl::Vec2 resolution(70, 60);
    consoleGl::FrameBuffer frame(resolution.x, resolution.y);
    bool running = true;
    
    // Shader function
    consoleGl::FragShader shader1 = [](int x, int y, std::vector<float> uniforms) -> int {
        consoleGl::Vec2 coord(x, y);
        using namespace consoleGl::shader;
        using namespace consoleGl;
        
        consoleGl::Vec2 resolution(uniforms[0], uniforms[1]);
        float t = uniforms[2];
        
        auto uv = (coord * 2.0f - resolution) / resolution.x;
        auto uv0 = Mat2::rotate(t * PI) * uv;
        auto uv2 = uv + Vec2(1.6f * sin(t));
        float d1 = sdBox(uv0 * 0.6f, Vec2(0.2f));
        float d2 = sdCircle((uv + uv2) * 7.0f, 0.3f);
        float d = smoothMin(d1, d2, 0.6f);
        
        if (abs(d) <= 0.039f) return 10;
        return 0;
    };

    auto start_time = std::chrono::high_resolution_clock::now();
    while (running) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - start_time;
        auto time = (float)elapsed.count();
        
        consoleGl::ShaderUniforms uniforms = {resolution.x, resolution.y, time};
        
        if (fc >= 500) break;
        
        applyFragment(frame, shader1, uniforms);
        
        if (fc % fpp == 0) {
            frame.print();
        }
        
        fc++;
        consoleGl::delay(35);
        frame.clear();
    }

    return 0;
}
       
    

    
 
