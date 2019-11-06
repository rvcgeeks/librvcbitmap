/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS bitmap library -- include header file
 * some functions for pixel modification,image creation,etc...
 * 
*/

//____________________FUNCTIONS FOR GEOMETRICAL SHAPES_____________________

#include"rvcbitmap.h"

float circle(float x,float y,const float args[]){            //args[0]=radius , args[1]=x cord, args [2]=y cord
    return pow(x-args[1],2)+powl(y-args[2],2)-powl(args[0],2);
}
float ellipse(float x,float y,const float args[]){           //args[0]=x radius , args[1]=y radius, args[2]=x cord , args[3]= y cord
    return pow((x-args[2])/args[0],2)+powl((y-args[3])/args[1],2)-1;
}
float line(float x,float y,const float args[]){              //args[0],args[1]= x1,y1 , args[2],args[3] = x2,y2
    return (x-args[0])*(args[1]-args[3])-(args[0]-args[2])*(y-args[1]);
}
float segment(float x,float y,const float args[]){           //args[0],args[1]= x1,y1 , args[2],args[3] = x2,y2
    return (x>=min(args[0],args[2])&&x<=max(args[0],args[2])&&
            y>=min(args[1],args[3])&&y<=max(args[1],args[3]))
           ?line(x,y,args)
           :numeric_limits<float>::max();
}
float polygon(float x,float y,const float args[]){           //args[0]=no.of sides , args[2*i+1],args[2*i+2]= ith x,y points
    float fval=1.0f,tempargs[4];
    for(int i=0;i<int(args[0]);i++){
       
        fval*=segment(x,y,tempargs);
    }return fval;
}
//still more to add
