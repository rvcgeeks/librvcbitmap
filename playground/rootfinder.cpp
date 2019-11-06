/**
 
  @author rvcgeeks____ 
  ________________________________________________________________________________________________
  
  FIND MULTIPLE SOLUTIONS OF A COMPLEX FUNCTION RECURSIVELY BY 2D INCREMENTAL SEARCH METHOD...
  greatly inspired by Youtube channel 3Blue!Brown's video @link https://youtu.be/b7FxPsqfkOY
  Created by rvcgeeks____ ,Pune on Sun 5/5/2019 3:15 am IST
  more geeks on github.com/rvcgeeks
  
  compile:     g++ rootfinder.cpp -lrvcbitmap
  run: ./a.out
  
  @params input complex function and window boundary points
  @returns all possible roots of given function in given window
  
*/

#include<rvcbitmap.h>
#include<stdio.h>

#define CPX double complex

int IMGWIDTH, IMGHEIGHT = 1000, WIDTH, HEIGHT, soln_no = 0;
PixelMatrix _argand_plane;

void plotCPX(
    CPX z, CPX theta
) {
    _argand_plane
        [ int(( 0.5 - cimag(z) / HEIGHT ) * (IMGHEIGHT - 2)) ]  //we have to negate y coordinate for rastering type plane
        [ int(( creal(z) / WIDTH + 0.5 ) * (IMGWIDTH - 2)) ]
    = blender(
        2 * M_PI, cimag(theta) - 2 * M_PI * floor(cimag(theta) / (2 * M_PI)),
        standard_hsv, 1, 1
    );
}

//___________________________IMPLEMENTATION________________________________

#define NUMS 1E4
#define ERR 1E-4
#define MESH_X 7
#define MESH_Y 9  // everytime given region is divided into 7 * 9 = 63 subregions

bool is_winding_non_zero(      //check winding number if non zero on selected boundary (terminating condition for recursion)... evaluating winding number by cauchy integral
    CPX f(CPX), CPX a, CPX c   //ckeck out https://en.wikipedia.org/wiki/Winding_number#Complex_analysis
) {
    CPX z, diff = c - a, b = a + creal(diff), d = a + cimag(diff) * I, theta = 0,
    eps = (creal(b) - creal(a) + cimag(b) - cimag(c) + creal(c) - creal(d) + cimag(a) - cimag(d)) / NUMS,
    delta = eps;       for(z = a; creal(z) <= creal(b); z += delta){ theta += f(z + delta) / f(z) - 1; plotCPX(z, theta); }   //upper edge
    delta = - I * eps; for(z = b; cimag(z) >= cimag(c); z += delta){ theta += f(z + delta) / f(z) - 1; plotCPX(z, theta); }   //right edge
    delta = - eps;     for(z = c; creal(z) >= creal(d); z += delta){ theta += f(z + delta) / f(z) - 1; plotCPX(z, theta); }   //down edge
    delta = I * eps;   for(z = d; cimag(z) <= cimag(a); z += delta){ theta += f(z + delta) / f(z) - 1; plotCPX(z, theta); }   //left edge
    return fabs(cimag(theta)) / (2 * M_PI) >= 1 - ERR;  //normalize by 2*pi for windng number
}

void findroots(
    CPX f(CPX), CPX a, CPX b, int depth = 0
) {
    if(!is_winding_non_zero(f, a, b))  //entry condition to check if there is solution in region with corners a and b else simply return
        return;
    CPX diff = b - a, m = (a + b) / 2;
    printf("  depth = %i     a = %10.10lf + %10.10lfi       b = %10.10lf + %10.10lfi\n", depth, creal(a), cimag(a), creal(b), cimag(b));
    if(cabs(diff) <= ERR) {    //print mid as solution if difference becomes reasonably negligible... (avoid stackoverflow)
        printf("                                                                                           x%i = %10.10lf + %10.10lfi\n", ++soln_no, creal(m), cimag(m));
        return;
    } for(int i = 0; i < MESH_Y; i++)
        for(int j = 0; j < MESH_X; j++) {        //recurse through all subregions in the mesh
                CPX st = a + j * creal(diff) / MESH_X + i * cimag(diff) / MESH_Y * I,
                   end = st + creal(diff) / MESH_X + cimag(diff) / MESH_Y * I;
                findroots(f, st, end, depth + 1);
            }
}

//___________________________________TESTING____________________________________

CPX TEST(CPX x) {   //test function set here
    return cpow(ccos(x), 7) + x * cpow(csin(x), 3);
}

int main(){
    
    CPX UPPERLEFT = -9 + 2.5*I, LOWERRIGHT = 9 - 2.5*I;  //window corners
    
    WIDTH = creal(LOWERRIGHT) - creal(UPPERLEFT);
    HEIGHT = cimag(UPPERLEFT) - cimag(LOWERRIGHT);
    IMGWIDTH = IMGHEIGHT * WIDTH / HEIGHT;
    _argand_plane = PixelMatrix(IMGWIDTH, IMGHEIGHT);
    
    findroots(TEST, UPPERLEFT, LOWERRIGHT); // fire up the solver
    
    Bitmap().fromPixelMatrix(_argand_plane).save("roots_position",true);
    return 0;
}