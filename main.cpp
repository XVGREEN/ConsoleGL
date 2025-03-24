#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <functional>
#include <chrono>
#include "src/consolegl.h"


void delay(int k) {
    for (int i = 0; i < k * 10000; i++)
        for (int j = 0; j < k * 100; j++);
}
int main (){   
   consoleGl:: vec2 resolution(70,60);
   consoleGl::frame_buffer frame(resolution.x,resolution.y);
    
   //shader functions (^.^)
      consoleGl::frag_shader  shader1 = [](int x, int y,std::vector<float> uniforms ) -> int {
      consoleGl:: vec2 coord(x,y);
      using namespace consoleGl::shader;
      using namespace consoleGl;
      consoleGl::vec2 resolution(uniforms[0],uniforms[1]);
      float t= uniforms[2];
      auto uv= (coord*2.0-resolution)/resolution.x;
      auto uv0 = mat3::rotate(t*PI)*uv;
      auto uv2 = uv+ vec2(1.5*sin(t));
      float d1= (sdBox(uv0*0.6,vec2(0.2)));
      float d2 = sdCircle((uv+uv2)*8.0,0.3);
      float d = smoothMin(d1,d2,0.5);
         if (abs(d)<=0.035) return 9;
         return 1;
      
       };
       
       consoleGl::shader_uniforms uniforms ={resolution.x,resolution.y,0.5};
       applyFragment (frame,shader1,uniforms);
       frame.print();

    
     

      
     
      auto start_time = std::chrono::high_resolution_clock::now();
      while (true){
        auto now = std::chrono::high_resolution_clock::now();
         std::chrono::duration<double> elapsed = now - start_time;
         auto time =(float) elapsed.count();
         consoleGl::shader_uniforms uniforms ={resolution.x,resolution.y,time};
         if(time>=15)break;
         applyFragment(frame,shader1,uniforms);
          
         frame.print();
         consoleGl::delay(5);
         frame.clear();	
         
      }
   
   
  
 
	return 0;
}
