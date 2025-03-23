#pragma once
namespace consoleGl{

void applyFragment(frame_buffer &fb, std::function<bool(int,int,float t)>func,float time) {
    for (int i = 0; i < fb.size(); i++) { 
        int x = i % fb.width;
        int y = i / fb.width;  
        fb.data[i] = func(x, y,time);  
    }
}  




	
}
