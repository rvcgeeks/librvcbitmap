/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS bitmap library -- include header file
 * some functions for pixel modification,image creation,etc...
 * 
*/

class Pixel{   //class representing single pixel rgb value
public:
    int red,
        green,
        blue;
    Pixel():
        red(0),
        green(0),
        blue(0)
    {}
    Pixel(int r,int g,int b):
        red(r),
        green(g),
        blue(b)
    {}
    Pixel(const Pixel& p):
        red(p.red),
        green(p.green),
        blue(p.blue)
    {}
    bool operator == (const Pixel& p){
    	return red == p.red && green == p.green && red == p.red;
    }
    bool validate();
friend ostream& operator<<(ostream&,const Pixel&);     //output a coloured box of pixel on terminal (for debugging purposes)
};
class PixelMatrix:public vector<vector<Pixel> >{       //Pixelmatrix is a wrapper over nested Pixel vectors
public:
    PixelMatrix(){}
    PixelMatrix(int,int);
    PixelMatrix rvcdisplay();
};
