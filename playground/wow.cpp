#include<rvcbitmap.h>

main(){
    Bitmap plane(1200,800);
    plane.recentre(600,400);
    float R=4;int i,N=50;
    float fargs[]={3,0,0}; //fargs[0]= value of smaller circle

    for(i=0;i<N;i++){
        float theta=2*i*M_PI/N;
        fargs[1]=R*cos(theta);
        fargs[2]=R*sin(theta);
        plane.DrawShape(50,30,circle,fargs,blender(2*M_PI,theta));
    }
    plane.save("rvc_wow",false);
    return 0;
}
