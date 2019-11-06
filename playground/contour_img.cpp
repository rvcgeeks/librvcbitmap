#include<rvcbitmap.h>

//______________DEFINITION OF INPUT COMPLEX FUNCTION__________________
float complex g(float complex z){
    return cpow(ccos(z), 7) + z * cpow(csin(z), 3);
}
//___________________CALL TO PLOTTER VIA MAIN__________________________
main(){
    Bitmap(3600, 1000).fromComplexFunction(200, 0.5, - 9 + 2.5*I, 9 - 2.5*I, g).save("rvc_contour", false);  //here 100 pixels per unit and x from -9 to 9 and y -2.5 to 2.5
    return 0;                                                          //as simple as that...
}
