#include <termios.h>
#include "src/consolegl.h"
#include "shaders/cube.h"
void processMove(consoleGl::Vec3 & pos){
    float sp=0.1;
	switch (consoleGl::getKey()){
		case 'w':{
		    pos.z+=sp;	
		    break;
		}
		case 's':{
		     pos.z-=sp;
		     break;
        }
        case 'a':{
             pos.x-=sp;
             break;
        }
        case 'd':{
            pos.x+=sp;
            break;
        }
	}
}
int main() {
   int fc = 0;
    const int fpp = 1;
    consoleGl::Vec2 resolution(80, 80);
    consoleGl::FrameBuffer frame(resolution.x, resolution.y);
    bool running = true;
    auto start_time = std::chrono::high_resolution_clock::now();
    consoleGl::Vec3 pos(0,0,-3);
    
    while (running) {
         processMove(pos);
       //  if(consoleGl::getKey()=='q') break;
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - start_time;
        auto time = (float)elapsed.count();
        
        consoleGl::ShaderUniforms uniforms = {resolution.x, resolution.y, time,
                                              pos.x,pos.y,pos.z};
        
        applyFragment(frame, cubeShader, uniforms);
        
        if (fc % fpp == 0) {
            frame.print();
        }
        
        fc++;
        consoleGl::delay(16);
        frame.clear();
        if(fc>=2000)break;
      
    }

    return 0;
}
       
    

    
 
