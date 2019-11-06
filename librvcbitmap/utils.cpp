/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS bitmap library 
 * some functions for pixel modification,image creation,etc...
 * 
*/

//_______________________________EXTRA UTILITIES_________________________________________
//    function to linearly blend a scheme of colours into each other with
//    cyclic choice of colours
//    x = current grayscale value , v = frequency of cycle

#include"rvcbitmap.h"

Pixel blender(float span,float H,vector<Pixel> scheme,float S,float V){   //standard_hsv by default
    int n=scheme.size(),i=int(n*H/span);
    return Pixel(
        V*(scheme[i%n].red  +(scheme[(i+1)%n].red  -scheme[i%n].red  )*(n*S*H/span-i)),  //it is derived from the slope point form of equation of line
        V*(scheme[i%n].green+(scheme[(i+1)%n].green-scheme[i%n].green)*(n*S*H/span-i)),
        V*(scheme[i%n].blue +(scheme[(i+1)%n].blue -scheme[i%n].blue )*(n*S*H/span-i))
    );
}

Bitmap TraceEdges(Bitmap b){
    PixelMatrix p=b.toPixelMatrix(),dp(p[0].size(),p.size());Bitmap ret;
    for(int y=0;y<p[0].size()-1;y++){
        for(int x=0;x<p.size()-1;x++){
            float dx=float((p[x+1][y].red+p[x+1][y].green+p[x+1][y].blue)-(p[x][y].red+p[x][y].green+p[x][y].blue))/3;
            float dy=float((p[x][y+1].red+p[x][y+1].green+p[x][y+1].blue)-(p[x][y].red+p[x][y].green+p[x][y].blue))/3;
            int val=sqrt(pow(dx,2)+pow(dy,2));val=(val>MAX_RGB)?MAX_RGB:val;
            dp[x][y].red=dp[x][y].green=dp[x][y].blue=val;
        }
    }return ret.fromPixelMatrix(dp);
}
//____________________PLOT A PIXEL OF COMPLEX VALUE IN CONTOUR MAP________________________

Pixel FromComplex(
    float div,
    float complex x,
    float blackness=0.75f      //adjust the modulus blackness here
){
    float H,S,V;
    float theta=carg(x);
    if(theta<0)
        theta+=2*M_PI;
    H=theta;      //The argument of complex no. decides the hue
    S=1.0f;
    float r=cabs(x);   //whereas the radial dist. decides the stepped contrast value
    V=1-(r/div-int(r/div))*blackness;
    return blender(2*M_PI,H,standard_hsv,S,V);
}

//__________________________PLOT A COMPLEX CONTOUR MAP (MEMBER METHOD)______________________

Bitmap Bitmap::fromComplexFunction(
                   //PARAMETERS LIST:
    int dpu,                 //dpu=dots per unit scale
    float division,          //at what unit you want contrast division for modulus
    float complex start,     //coordinate of upper left corner of view
    float complex end,       //coordinate of lower right corner of view
    float complex (*f)(      //function pointer to input function
        float complex
    ),
    float blackness
){
    float r;
    long int row,col,i,j;
    long int m=dpu*creal(end),
             n=dpu*cimag(end);
    for(row=pixels.size()-1,j=dpu*cimag(start);j>n&&row>=0;j--,row--){
        for(col=0,i=dpu*creal(start);i<m&&col<pixels[0].size();i++,col++){
            Pixel color=FromComplex(division,f((i+I*j)/dpu),blackness);
            if(color.validate())
                pixels[row][col]=color;
        }
    }return *this;
}

//____________________DRAW AN IMPLICIT FUNCTION OF FORM f(x,y)=0_____________________________
//Global offset coordinates for centre of graph plane
Bitmap Bitmap::recentre(int vo,int ho){
    hoffset=ho,              //distance of centre from left border in px
    voffset=vo;              //distance of centre from upper border in px
    return *this;
}
Bitmap Bitmap::DrawShape(
                   //PARAMETERS LIST:
    int dpu,                 //dpu=dots per unit scale
    int thickness,           //line thickness in px
    float (*f)(              //function pointer to input function
        float,
        float,
        const float[]
    ),
    const float args[],      //this args array is used to pass extra constants for eg radius of circle,sides of triangle,etc...
    Pixel color    //color of shape (white by default)
){
    int row,col,i,j;
    for(row=pixels.size()-1,j=-hoffset;row>=0;j++,row--)
        for(col=0,i=-voffset;col<pixels[0].size();i++,col++){
            int fval=dpu*f(float(i)/dpu,float(j)/dpu,args);
            if(fval>=0&&fval<=thickness)
                pixels[row][col]=color;
        }
    return *this;
}
