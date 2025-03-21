#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include "src/consolegl.h"
void wait(int k){
	for(int i =0;i<k*10000;i++);
}

int main (){
   consoleGl::frame_buffer frame(100,70);
   int frames =0;
   consoleGl::vec2 triangle[3] = { {-10, -10}, {0, 10}, {10, 0} };
   float t =0.0;
  do{
     t+=0.01;
     float a= 3.14*t;
     for(int i=0;i<3;i++){
       triangle[i]= consoleGl::mat3::rotate(a)*triangle[i];  	
      }
      wait(20);
   raster(triangle, frame);
   
   frame.print();
   if(t>=1)t=0;
   frames++;
   }while(frames<=100);
   
 
	return 0;
}
