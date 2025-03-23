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
     std::function<bool(int, int,float t)> shader1 = [=](int x, int y,float t) -> bool {
      consoleGl:: vec2 coord(x,y);
      auto uv= (coord*2.0-resolution)/resolution.y;
        if (uv.y>=sin(4*uv.x+t*3.0)*0.2) return true; 
        return false;             
     };
     std::function<bool(int, int,float t)> shader2 = [=](int x, int y,float t) -> bool {
     	    consoleGl:: vec2 coord(x,y);
     	      auto uv= (coord*2.0-resolution)/resolution.y;
     	     if (abs(uv.x*uv.x+uv.y*uv.y-sin(t*2.0))<=0.1) return true;
                 return false;
     };
     

      
     
       auto start_time = std::chrono::high_resolution_clock::now();
      while (true){
        auto now = std::chrono::high_resolution_clock::now();
         std::chrono::duration<double> elapsed = now - start_time;
         auto time = elapsed.count();
         if(time>=30)break;
         if(time<=15){
         applyFragment(frame,shader2,time);
         }else {
         	applyFragment(frame,shader1,time);
         }
         frame.print();
         consoleGl::delay(4);
         frame.clear();	
         
      }
   
   
  
 
	return 0;
}
