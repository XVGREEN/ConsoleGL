#pragma once
namespace consoleGl{
typedef  std::function<int(int, int,std::vector<float>)> FragShader;
typedef  std::vector<float> ShaderUniforms;

void applyFragment(FrameBuffer &fb, std::function<bool(int,int,float t)>func,float time) {
    for (int i = 0; i < fb.size(); i++) { 
        int x = i % fb.width;
        int y = i / fb.width;  
        fb.data[i] = func(x, y,time);  
    }
}

void applyFragment(FrameBuffer &fb,  FragShader  shade,const std::vector<float>& uniforms) {
    for (int i = 0; i < fb.size(); i++) {
        int x = i % fb.width;
        int y = i / fb.width;
        fb.data[i] = shade(x, y, uniforms);
    }
}
 /*this namespace contains all shade4 functions*/
 namespace shader {
    
     float fract(float x) {
         return x - std::floor(x);
     }
 
     Vec2 fract(const Vec2& vec) {
         return Vec2(fract(vec.x), fract(vec.y));
     }
 
     float sdCircle(const Vec2& p, float r) {
         return p.length() - r;
     }
 
     float sdBox(const Vec2& p, const Vec2& size) {
         Vec2 d(std::fabs(p.x) - size.x, std::fabs(p.y) - size.y);
         return std::max(d.x, 0.0f) + std::max(d.y, 0.0f) + std::min(std::max(d.x, d.y), 0.0f);
     }
     float sdStar(consoleGl::Vec2 p, int n, float r, float rf) {
     
         float angle = atan2(p.y, p.x); 
         float radius = r * (1.0f + rf * cos(n * angle));  
         float dist = p.length() - radius;  
     
         return dist;
     }
      float sdBall(consoleGl::Vec3 p, float r) {
          return p.length() - r;
      }
     
     float smoothMin(float a, float b) {
         return (a + b - std::abs(a - b)) * 0.5f;
     }
     
 
     float smoothMin(float a, float b, float k) {
         float h = std::exp(-k * a) + std::exp(-k * b);
         return -std::log(h) / k;
     }
     float sdCube(Vec3 p, Vec3 size) {
         Vec3 d = abs(p) - size;  
         return fmax(d.x, fmax(d.y, d.z)); 
     }
     
 };
	
};
