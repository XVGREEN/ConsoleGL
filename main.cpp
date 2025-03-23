#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <functional>
#include <chrono>
#include "src/consolegl.h"
#define PI 3.141592653589793

void delay(int k) {
    for (int i = 0; i < k * 10000; i++)
        for (int j = 0; j < k * 100; j++);
}
int main (){   
   consoleGl:: vec2 resolution(70,50);
   consoleGl::frame_buffer frame(resolution.x,resolution.y); 
  // auto start_time = std::chrono::high_resolution_clock::now();

  	       
  

    std::function<bool(int, int,float t)> shader = [=](int x, int y,float t) -> bool {
      consoleGl:: vec2 coord(x,y);
      auto uv= (coord*2.0-resolution)/resolution.y;
        if (uv.y>=sin(4*uv.x+t)*0.2) return true; 
        return false;             
      };
      std::cout<<"whatatta\n";
       auto start_time = std::chrono::high_resolution_clock::now();
      while (true){
        auto now = std::chrono::high_resolution_clock::now();
         std::chrono::duration<double> elapsed = now - start_time;
         auto time = elapsed.count();
         if(time>=10)break;
         applyFragment(frame,shader,time);
         frame.print();
         deleay(5);
         frame.clear();	
         
      }
   
   
  
 
	return 0;
}
