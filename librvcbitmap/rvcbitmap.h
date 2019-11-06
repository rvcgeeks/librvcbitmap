/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS bitmap library -- include header file
 * some functions for pixel modification,image creation,etc...
 * 
*/


#ifndef BITMAP_H
#define BITMAP_H
#include<iostream>
#include<fstream>
#include<vector>
#include<complex.h>
#include<cmath>
#include<limits>
#define MAX_TERMINAL_WIDTH 1000 //for terminal display ...for 6 font size and maximum zoom out
using namespace std;

//____________________CREATING A PROGRAMMABLE MODEL OF RGB COLOR IMAGE_________________
#include"pixel.h"
#include"bitmap.h"

//__________________________STRUCTURES FOR R/W OF BITMAP IMAGE_________________________
#include"filestructs.h"

//____________________________________UTILITIES________________________________________
float circle(float,float,const float[]);
float ellipse(float,float,const float[]);
float line(float,float,const float[]);
float segment(float,float,const float[]);
float polygon(float,float,const float[]);

static Pixel standard_hsv_array[]={
        Pixel(255,  0,  0),
        Pixel(255,255,  0),
        Pixel(  0,255,  0),
        Pixel(  0,255,255),
        Pixel(  0,  0,255),
        Pixel(255,  0,255)
};
static vector<Pixel> standard_hsv(standard_hsv_array,standard_hsv_array+6);  //global blender scheme for standard hsv to rgb conversion

Pixel blender(float,float,vector<Pixel> scheme=standard_hsv,float=1.0f,float=1.0f);
Bitmap TraceEdges(Bitmap);
Pixel FromComplex(float,float complex,float);
#endif

