#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <functional>
#include <chrono>
#include <thread>
#include "src/consolegl.h"

void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
int main (){ 
   int fc=0;
   const int fpp=20;  
   consoleGl:: vec2 resolution(70,60);
   consoleGl::frame_buffer frame(resolution.x,resolution.y);
     bool running  = 1;
   //shader functions (^.^)
      consoleGl::frag_shader  shader1 = [](int x, int y,std::vector<float> uniforms ) -> int {
      consoleGl:: vec2 coord(x,y);
      using namespace consoleGl::shader;
      using namespace consoleGl;
      consoleGl::vec2 resolution(uniforms[0],uniforms[1]);
      float t= uniforms[2];
      auto uv= (coord*2.0-resolution)/resolution.x;
      auto uv0 = mat3::rotate(t*PI)*uv;
      auto uv2 = uv+ vec2(1.6*sin(t));
      float d1= (sdBox(uv0*0.6,vec2(0.2)));
      float d2 = sdCircle((uv+uv2)*7.0,0.3);
      float d = smoothMin(d1,d2,0.6);
         if (abs(d)<=0.039) return 10;
         return 0;
      
       };
       
    

    
   
      auto start_time = std::chrono::high_resolution_clock::now();
      
      while (running){
         auto now = std::chrono::high_resolution_clock::now();
         std::chrono::duration<double> elapsed = now - start_time;
         auto time =(float) elapsed.count();
         consoleGl::shader_uniforms uniforms ={resolution.x,resolution.y,time};
         if(fc>=500)break;
         applyFragment(frame,shader1,uniforms);   
         if(fc%fpp){
        	 frame.print();
         }
         fc++;
         
         delay(35);
         frame.clear();	
         
      }
   
   
  
 
	return 0;
}
