#include <cmath>
#ifndef VEC2
#define VEC2

namespace consoleGl{
  struct  vec2 {
		float x;
 	    float y;
		float z;
		vec2 ():x(0),y(0),z(1){}
		vec2 (float X,float Y):x(X),y(Y),z(1){}
		vec2 (const vec2 & other){
    		 x=other.x;
   		     y=other.y;
     		 z=1;
	    }
 	    void print (){
   			 std::cout<<"x:"<<x<<std::endl;
    		 std::cout<<"y:"<<y<<std::endl;
  	
	    }
	    vec2 operator+(const vec2& other)const{
  			return vec2(x+other.x,y+other.y);
	    }
  
   	    vec2 operator-(const vec2& other)const {
  			return vec2(x-other.x,y-other.y);
 		 }
    	 vec2 operator*(float scale)const{
  			return vec2(x*scale,y*scale);
        }		
         float length()const{
      	return sqrt(x*x+y*y);
        }
        vec2 normal(){
        float l= length();
     	return vec2(x/l,y/l);
        }
        friend float dot (vec2 a,vec2 b){
     	return a.x*b.x+ a.y*b.y;
       }
  };

};
#endif
