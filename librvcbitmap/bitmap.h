/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS bitmap library -- include header file
 * some functions for pixel modification,image creation,etc...
 * 
*/

class Bitmap{         //Bitmap class serves as a container for Pixelmatrix class and reads and writes rgb values in bmp format with some utility functions. 
    PixelMatrix pixels;
  public:
    Bitmap(){};
    Bitmap(int,int);
    Bitmap open(string),
           save(string, bool),
           rvcdisplay();
    bool validate();
    Bitmap fromPixelMatrix(const PixelMatrix &);
    PixelMatrix toPixelMatrix();
    Bitmap fromComplexFunction(   //an extra utility that plots a contour map from a complex function
        int,float,
        float complex,
        float complex,
        float complex (*f)(float complex),  //method pointer to input complex function
        float=0.75
    );
    Bitmap DrawShape(
        int,int,
        float (*f)(
            float,
            float,
            const float[]
        ),
        const float[],
        Pixel=Pixel(255,255,255)
    );
    int voffset;
    int hoffset;
    Bitmap recentre(int,int);
};
