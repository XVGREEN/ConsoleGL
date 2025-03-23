#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include "src/consolegl.h"
#define PI 3.141592653589793

void delay(int k) {
    for (int i = 0; i < k * 10000; i++)
        for (int j = 0; j < k * 100; j++);
}
int main (){
   
   consoleGl::color color1(255,0,0);
   consoleGl::color color2(0,0,255);
   consoleGl::frame_buffer frame(140,100);
   int frames =0;
   consoleGl::vec2 triangle[3] = { {20, -10}, {15, 10}, {30,10} };
   float t= 0.0;
   do{
     t+=0.02;
     auto col= lerp(color1,color2,t);
     consoleGl::setColor(col);
     float angle = 2.0*PI*t;
     float s= 1.0;
     auto r= consoleGl::mat3::rotate(angle);
      consoleGl:: vec2 rvec[3]  =  {r*triangle[0]*s,
      								r*triangle[1]*s,
      								r*triangle[2]*s};

     consoleGl::raster(rvec,frame);
      frame.print();
      delay(6);
      frame.clear();
      frames++;
   	if(t>=1.)t=0;
   }while(frames<100);
  
   
  
 
	return 0;
}
